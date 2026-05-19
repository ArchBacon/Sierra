// Copyright (c) 2026, Christian Delicaat. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "VehicleConfig.generated.h"

class UXCarConfig;
class UTransmissionConfig;
class USteeringConfig;
class UForcedInductionConfig;
class UEngineConfig;
class UDriftConfig;
class UBrakesConfig;
class UAerodynamicsConfig;
class UChassisConfig;
class UTireConfig;
class USuspensionConfig;

UCLASS(BlueprintType)
class SIERRA_API UVehicleConfig : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	/** Drag, downforce, top speed, and in-air stability parameters. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Vehicle)
	TObjectPtr<UAerodynamicsConfig> AerodynamicsConfig {nullptr};

	/** Brake torque curves, handbrake, and brake bias settings. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Vehicle)
	TObjectPtr<UBrakesConfig> BrakesConfig {nullptr};

	/** Vehicle mass, dimensions, inertia, and contact response settings. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Vehicle)
	TObjectPtr<UChassisConfig> ChassisConfig {nullptr};

	/** All drift initiation, sustain, exit, and donut tuning parameters. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Vehicle)
	TObjectPtr<UDriftConfig> DriftConfig {nullptr};

	/** Torque curve, RPM limits, flywheel, anti-bog, and rev limiter settings. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Vehicle)
	TObjectPtr<UEngineConfig> EngineConfig {nullptr};

	/** Turbo/supercharger type, boost pressure, lag, and valve settings. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Vehicle)
	TObjectPtr<UForcedInductionConfig> ForcedInductionConfig {nullptr};

	/** Steering rates, ranges, throttle mapping, and aligning torque settings. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Vehicle)
	TObjectPtr<USteeringConfig> SteeringConfig {nullptr};

	/** Spring rates, damper specs, camber/toe/caster, and wheel attach points. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Vehicle)
	TObjectPtr<USuspensionConfig> SuspensionConfig {nullptr};

	/** Tire dimensions, inertia, grip model references, and rolling resistance. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Vehicle)
	TObjectPtr<UTireConfig> TireConfig {nullptr};

	/** Gear ratios, differential settings, shift curves, and traction thresholds. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Vehicle)
	TObjectPtr<UTransmissionConfig> TransmissionConfig {nullptr};

	/** Visual body dynamics: roll/pitch/squat/dive, wheel spring simulation, camber travel. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Vehicle)
	TObjectPtr<UXCarConfig> XCarConfig {nullptr};
};
