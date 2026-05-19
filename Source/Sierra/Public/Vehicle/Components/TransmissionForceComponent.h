// Copyright (c) 2026, Christian Delicaat. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TransmissionForceComponent.generated.h"

class UAccelerationForceComponent;
class UTransmissionConfig;
class APhysicsVehicle;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SIERRA_API UTransmissionForceComponent : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY() TObjectPtr<APhysicsVehicle> Vehicle {nullptr};
	UPROPERTY() TObjectPtr<UTransmissionConfig> TransmissionConfig {nullptr};
	UPROPERTY() TObjectPtr<UAccelerationForceComponent> AccelComp {nullptr};
	
	int ReverseGear {0}; 
	int NeutralGear {1}; 
	int TopGear {0}; 

	int Gear {NeutralGear};
	
public:
	UPROPERTY() float ThrottleInput {0.0f};
	
	UTransmissionForceComponent();

	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	int GetActiveGear() const { return Gear; }
	float GetDriveTrainMultiplier() const;
	bool IsInReverseGear() const { return Gear == ReverseGear; }
	bool IsInNeutralGear() const { return Gear == NeutralGear; }
	bool IsInForwardGear() const { return Gear > NeutralGear; }
	
	UFUNCTION(BlueprintCallable, BlueprintPure)
	int GetActiveGearVisual() const { return Gear - 1; }
};
