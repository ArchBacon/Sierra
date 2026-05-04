// Copyright (c) 2026, Christian Delicaat. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "VehicleConfig.generated.h"

class UTireConfig;
class USuspensionConfig;

UCLASS(BlueprintType)
class SIERRA_API UVehicleConfig : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Vehicle)
	TObjectPtr<USuspensionConfig> SuspensionConfig {nullptr};
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Vehicle)
	TObjectPtr<UTireConfig> TireConfig {nullptr};
};
