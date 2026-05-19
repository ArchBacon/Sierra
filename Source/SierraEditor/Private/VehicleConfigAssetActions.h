// Copyright (c) 2026, Christian Delicaat. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "AssetTypeActions_Base.h"

class FVehicleConfigAssetActions : public FAssetTypeActions_Base
{
public:
	explicit FVehicleConfigAssetActions(UClass* InClass) : SupportedClass(InClass) {}

	virtual FText   GetName()           const override { return INVTEXT("Vehicle Config"); }
	virtual FColor  GetTypeColor()      const override { return FColor(100, 200, 100); }
	virtual UClass* GetSupportedClass() const override { return SupportedClass; }
	virtual uint32  GetCategories()           override { return EAssetTypeCategories::Misc; }

	virtual void GetActions(const TArray<UObject*>& InObjects, FToolMenuSection& Section) override;

private:
	UClass* SupportedClass;

	static void ExecuteImportFromXml(TArray<TWeakObjectPtr<UObject>> WeakObjects);
};
