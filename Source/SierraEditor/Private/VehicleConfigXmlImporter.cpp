// Copyright (c) 2026, Christian Delicaat. All rights reserved.

#include "VehicleConfigXmlImporter.h"
#include "XmlFile.h"
#include "UObject/UnrealType.h"
#include "UObject/EnumProperty.h"

bool FVehicleConfigXmlImporter::ImportFile(const FString& FilePath, UObject* Target)
{
	FXmlFile XmlFile(FilePath);
	if (!XmlFile.IsValid())
	{
		UE_LOG(LogTemp, Error, TEXT("SierraEditor: Failed to parse XML: %s"), *FilePath);
		return false;
	}

	PopulateObject(XmlFile.GetRootNode(), Target);
	return true;
}

void FVehicleConfigXmlImporter::PopulateObject(const FXmlNode* Node, UObject* Target)
{
	UClass* Class = Target->GetClass();

	for (FXmlNode* Child : Node->GetChildrenNodes())
	{
		if (Child->GetTag() == TEXT("Name")) continue;

		FProperty* Prop = Class->FindPropertyByName(*Child->GetTag());
		if (Prop)
			SetPropertyFromNode(Child, Prop, Target);
	}
}

void FVehicleConfigXmlImporter::PopulateStruct(const FXmlNode* StructNode, UScriptStruct* Struct, void* StructData)
{
	for (FXmlNode* Child : StructNode->GetChildrenNodes())
	{
		FProperty* Prop = Struct->FindPropertyByName(*Child->GetTag());
		if (Prop)
			SetPropertyFromNode(Child, Prop, StructData);
	}
}

void FVehicleConfigXmlImporter::SetPropertyFromNode(FXmlNode* PropNode, FProperty* Prop, void* Container)
{
	// --- TArray ---
	if (FArrayProperty* ArrayProp = CastField<FArrayProperty>(Prop))
	{
		FScriptArrayHelper ArrayHelper(ArrayProp, ArrayProp->ContainerPtrToValuePtr<void>(Container));
		ArrayHelper.EmptyAndAddUninitializedValues(0);

		TArray<FXmlNode*> Members;
		for (FXmlNode* Child : PropNode->GetChildrenNodes())
			if (Child->GetTag() == TEXT("member")) Members.Add(Child);

		if (FStructProperty* InnerStruct = CastField<FStructProperty>(ArrayProp->Inner))
		{
			if (InnerStruct->Struct == TBaseStructure<FVector>::Get())
			{
				// TArray<FVector> — Vec3 curve array
				for (FXmlNode* Member : Members)
				{
					if (FXmlNode* Vec3Node = Member->FindChildNode(TEXT("Vec3")))
					{
						const int32 Idx = ArrayHelper.AddValue();
						*reinterpret_cast<FVector*>(ArrayHelper.GetRawPtr(Idx)) = ParseVec3(Vec3Node);
					}
				}
			}
			else
			{
				// TArray<FStruct> — generic struct array (e.g. TArray<FGearData>)
				for (FXmlNode* Member : Members)
				{
					TArray<FXmlNode*> MemberChildren = Member->GetChildrenNodes();
					if (MemberChildren.Num() == 0) continue;

					const int32 Idx = ArrayHelper.AddValue();
					PopulateStruct(MemberChildren[0], InnerStruct->Struct, ArrayHelper.GetRawPtr(Idx));
				}
			}
		}
		return;
	}

	// --- Single FVector (wrapped in <Vec3>) ---
	if (FStructProperty* StructProp = CastField<FStructProperty>(Prop))
	{
		void* StructData = StructProp->ContainerPtrToValuePtr<void>(Container);
		if (StructProp->Struct == TBaseStructure<FVector>::Get())
		{
			if (FXmlNode* Vec3Node = PropNode->FindChildNode(TEXT("Vec3")))
				*reinterpret_cast<FVector*>(StructData) = ParseVec3(Vec3Node);
		}
		else
		{
			// Generic nested struct (e.g. FLongGripCurve)
			PopulateStruct(PropNode, StructProp->Struct, StructData);
		}
		return;
	}

	// --- Flat Vec3 curve array stored as a float in C++ ---
	// When all keyframe Y values are identical the array was simplified to a plain float.
	// Recover the value as lerp(header[0].Y, header[1].Y, keyframe[2].Y).
	bool bHasMembers = false;
	for (FXmlNode* Child : PropNode->GetChildrenNodes())
		if (Child->GetTag() == TEXT("member")) { bHasMembers = true; break; }

	if (bHasMembers)
	{
		if (FFloatProperty* FloatProp = CastField<FFloatProperty>(Prop))
		{
			TArray<FXmlNode*> Members;
			for (FXmlNode* Child : PropNode->GetChildrenNodes())
				if (Child->GetTag() == TEXT("member")) Members.Add(Child);

			if (Members.Num() >= 3)
			{
				auto GetY = [&](int32 Idx) -> float
				{
					if (FXmlNode* Vec3 = Members[Idx]->FindChildNode(TEXT("Vec3")))
						if (FXmlNode* Y = Vec3->FindChildNode(TEXT("y")))
							return ParseFloat(Y->GetContent());
					return 0.f;
				};
				const float MinY  = GetY(0);
				const float MaxY  = GetY(1);
				const float NormY = GetY(2);
				FloatProp->SetPropertyValue_InContainer(Container, FMath::Lerp(MinY, MaxY, NormY));
			}
		}
		return;
	}

	// --- Scalar properties ---
	const FString Content = PropNode->GetContent();

	if (FFloatProperty* FloatProp = CastField<FFloatProperty>(Prop))
	{
		FloatProp->SetPropertyValue_InContainer(Container, ParseFloat(Content));
		return;
	}
	if (FDoubleProperty* DoubleProp = CastField<FDoubleProperty>(Prop))
	{
		DoubleProp->SetPropertyValue_InContainer(Container, (double)ParseFloat(Content));
		return;
	}
	if (FIntProperty* IntProp = CastField<FIntProperty>(Prop))
	{
		IntProp->SetPropertyValue_InContainer(Container, FCString::Atoi(*Content));
		return;
	}
	if (FBoolProperty* BoolProp = CastField<FBoolProperty>(Prop))
	{
		BoolProp->SetPropertyValue_InContainer(Container, Content.Equals(TEXT("True"), ESearchCase::IgnoreCase));
		return;
	}
	if (FEnumProperty* EnumProp = CastField<FEnumProperty>(Prop))
	{
		// XML format: "TypeName_ValueName" — strip the prefix up to and including the last '_'
		int32 UnderscorePos = INDEX_NONE;
		Content.FindLastChar(TEXT('_'), UnderscorePos);
		const FString EnumName = (UnderscorePos != INDEX_NONE) ? Content.RightChop(UnderscorePos + 1) : Content;

		const int64 Value = EnumProp->GetEnum()->GetValueByName(*EnumName);
		if (Value != INDEX_NONE)
			EnumProp->GetUnderlyingProperty()->SetIntPropertyValue(
				EnumProp->ContainerPtrToValuePtr<void>(Container), Value);
		return;
	}
}

FVector FVehicleConfigXmlImporter::ParseVec3(FXmlNode* Vec3Node)
{
	FVector Result = FVector::ZeroVector;
	if (FXmlNode* X = Vec3Node->FindChildNode(TEXT("x"))) Result.X = ParseFloat(X->GetContent());
	if (FXmlNode* Y = Vec3Node->FindChildNode(TEXT("y"))) Result.Y = ParseFloat(Y->GetContent());
	if (FXmlNode* Z = Vec3Node->FindChildNode(TEXT("z"))) Result.Z = ParseFloat(Z->GetContent());
	return Result;
}

float FVehicleConfigXmlImporter::ParseFloat(const FString& Value)
{
	// NFS Heat exports use locale-specific decimal separator (comma in European locales)
	return FCString::Atof(*Value.Replace(TEXT(","), TEXT(".")));
}
