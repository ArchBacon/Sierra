// Copyright (c) 2026, Christian Delicaat. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "ChassisComponent.generated.h"

class UEngineConfig;
class UTransmissionConfig;
class UAerodynamicsConfig;
class UTireConfig;
class APhysicsVehicle;
class UChassisConfig;
class USuspensionConfig;

UCLASS()
class SIERRA_API UChassisComponent : public UStaticMeshComponent
{
	GENERATED_BODY()
	
	UPROPERTY() TObjectPtr<APhysicsVehicle> Vehicle {nullptr};
	UPROPERTY() TObjectPtr<UChassisConfig> ChassisConfig {nullptr};
	UPROPERTY() TObjectPtr<USuspensionConfig> SuspensionConfig {nullptr};
public:
	UChassisComponent();
	
	UPROPERTY(VisibleAnywhere) float FrontalArea {0.0f};
	
protected:
	virtual void BeginPlay() override;
	
public:
	void UpdateCenterOfMass() const;
};
