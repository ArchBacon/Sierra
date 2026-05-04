// Copyright (c) 2026, Christian Delicaat. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "TireConfig.generated.h"

// Default properties set to Buick GNX '87, taken fron NFS:Heat
UCLASS(BlueprintType)
class SIERRA_API UTireConfig : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Tire)
	TObjectPtr<UStaticMesh> Wheel {nullptr};
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Tire)
	TObjectPtr<UStaticMesh> Tire {nullptr};
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Tire)
	float DiameterFront {0.65373f};
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Tire)
	float DiameterRear {0.65373f};
};
