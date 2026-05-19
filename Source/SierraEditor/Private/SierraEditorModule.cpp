// Copyright (c) 2026, Christian Delicaat. All rights reserved.

#include "SierraEditorModule.h"
#include "AssetToolsModule.h"
#include "VehicleConfigAssetActions.h"

#include "Vehicle/Config/AerodynamicsConfig.h"
#include "Vehicle/Config/BrakesConfig.h"
#include "Vehicle/Config/ChassisConfig.h"
#include "Vehicle/Config/DriftConfig.h"
#include "Vehicle/Config/EngineConfig.h"
#include "Vehicle/Config/ForcedInductionConfig.h"
#include "Vehicle/Config/SteeringConfig.h"
#include "Vehicle/Config/SuspensionConfig.h"
#include "Vehicle/Config/TireConfig.h"
#include "Vehicle/Config/AnalyticalTireConfig.h"
#include "Vehicle/Config/TransmissionConfig.h"
#include "Vehicle/Config/XCarConfig.h"

IMPLEMENT_MODULE(FSierraEditorModule, SierraEditor)

void FSierraEditorModule::StartupModule()
{
	IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();

	const TArray<UClass*> ConfigClasses =
	{
		UAerodynamicsConfig::StaticClass(),
		UBrakesConfig::StaticClass(),
		UChassisConfig::StaticClass(),
		UDriftConfig::StaticClass(),
		UEngineConfig::StaticClass(),
		UForcedInductionConfig::StaticClass(),
		USteeringConfig::StaticClass(),
		USuspensionConfig::StaticClass(),
		UTireConfig::StaticClass(),
		UAnalyticalTireConfig::StaticClass(),
		UTransmissionConfig::StaticClass(),
		UXCarConfig::StaticClass(),
	};

	for (UClass* Class : ConfigClasses)
	{
		TSharedRef<FVehicleConfigAssetActions> Action = MakeShared<FVehicleConfigAssetActions>(Class);
		AssetTools.RegisterAssetTypeActions(Action);
		RegisteredActions.Add(Action);
	}
}

void FSierraEditorModule::ShutdownModule()
{
	if (!FModuleManager::Get().IsModuleLoaded("AssetTools")) return;

	IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
	for (TSharedRef<FAssetTypeActions_Base>& Action : RegisteredActions)
		AssetTools.UnregisterAssetTypeActions(Action);
}
