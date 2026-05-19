// Copyright (c) 2026, Christian Delicaat. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AccelerationForceComponent.generated.h"

class UTransmissionForceComponent;
class UBrakesConfig;
class UAerodynamicsConfig;
class UChassisConfig;
class UTireConfig;
class UTransmissionConfig;
class UEngineConfig;
class APhysicsVehicle;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SIERRA_API UAccelerationForceComponent : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY() TObjectPtr<APhysicsVehicle> Vehicle {nullptr};
	UPROPERTY() TObjectPtr<UEngineConfig> EngineConfig {nullptr};
	UPROPERTY() TObjectPtr<UTransmissionConfig> TransmissionConfig {nullptr};
	UPROPERTY() TObjectPtr<UTireConfig> TireConfig {nullptr};
	UPROPERTY() TObjectPtr<UAerodynamicsConfig> AerodynamicsConfig {nullptr};
	UPROPERTY() TObjectPtr<UBrakesConfig> BrakesConfig {nullptr};
	UPROPERTY() TObjectPtr<UTransmissionForceComponent> TransmissionComponent {nullptr};

	UPROPERTY(VisibleAnywhere)
	float RPM {1000.f};
	UPROPERTY(VisibleAnywhere)
	float DragFactor {0.0f};

public:
	UPROPERTY() float ThrottleInput {0.0f};
	UPROPERTY() float HandbrakeInput {0.0f};

	UAccelerationForceComponent();

	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	UFUNCTION(BlueprintCallable, BlueprintPure)
	float GetRPM() const { return RPM; }
	UFUNCTION(BlueprintCallable, BlueprintPure)
	float GetSpeed() const; 
	
protected:
	void ApplyRollingResistance() const;
	void ApplyDrag() const;
	void ApplyDriveForce() const;
	void ApplyBrakes(float Speed) const;
	void UpdateRPM();
};
