// Copyright (c) 2026, Christian Delicaat. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "AssetTypeActions_Base.h"

class FSierraEditorModule : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:
	TArray<TSharedRef<FAssetTypeActions_Base>> RegisteredActions;
};
