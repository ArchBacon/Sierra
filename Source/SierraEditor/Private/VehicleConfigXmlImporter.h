// Copyright (c) 2026, Christian Delicaat. All rights reserved.

#pragma once

#include "CoreMinimal.h"

class FXmlNode;
class FProperty;
class UScriptStruct;

class FVehicleConfigXmlImporter
{
public:
	static bool ImportFile(const FString& FilePath, UObject* Target);

private:
	static void PopulateObject(const FXmlNode* Node, UObject* Target);
	static void PopulateStruct(const FXmlNode* StructNode, UScriptStruct* Struct, void* StructData);
	static void SetPropertyFromNode(FXmlNode* PropNode, FProperty* Prop, void* Container);
	static FVector ParseVec3(FXmlNode* Vec3Node);
	static float  ParseFloat(const FString& Value);
};
