// Copyright (c) 2026, Christian Delicaat. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SuspensionForceComponent.generated.h"

class USuspensionComponent;
class USuspensionConfig;
class UTireConfig;
class UChassisConfig;
class APhysicsVehicle;

USTRUCT()
struct FSpringForces
{
	GENERATED_BODY()
	
	float SpringRate {0.0f};
	float SpringForce {0.0f};
	float ContactSpeed {0.0f};
	float CompressionDistance {0.0f};
	FVector SurfaceNormal {0.0f, 0.0f, 1.0f};
};

USTRUCT()
struct FAxleForces
{
	GENERATED_BODY()
	
	FVector ForceLeft {0.0f, 0.0f, 0.0f};
	float CompressionDistanceL {0.0f};
	
	FVector ForceRight {0.0f, 0.0f, 0.0f};
	float CompressionDistanceR {0.0f};
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SIERRA_API USuspensionForceComponent : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY() TObjectPtr<APhysicsVehicle> Vehicle {nullptr};
	UPROPERTY() TObjectPtr<UChassisConfig> ChassisConfig {nullptr};
	UPROPERTY() TObjectPtr<UTireConfig> TireConfig {nullptr};
	UPROPERTY() TObjectPtr<USuspensionConfig> SuspensionConfig {nullptr};
	
public:
	USuspensionForceComponent();

	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
private:
	[[nodiscard]] FAxleForces CalculateFrontSuspension(TObjectPtr<USuspensionComponent> SuspensionLeft, TObjectPtr<USuspensionComponent> SuspensionRight, float DeltaTime, bool bIsFront) const;
	[[nodiscard]] FSpringForces CalculateSpringForce(TObjectPtr<USuspensionComponent> Suspension, float DeltaTime) const;
	[[nodiscard]] float CalculateDamperForce(float ContactSpeed, bool bIsFront) const;
};
