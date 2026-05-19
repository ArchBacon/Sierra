// Copyright (c) 2026, Christian Delicaat. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Curves/CurveFloat.h"
#include "Engine/DataAsset.h"
#include "EngineConfig.generated.h"

UCLASS()
class SIERRA_API UEngineConfig : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	/** Control points (RPM, Nm, 0) that define the engine torque curve. Built into TorqueCurve at load. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Engine)
	TArray<FVector> Torque;

	/** Runtime curve built from Torque control points. Do not edit directly. */
	UPROPERTY()
	TObjectPtr<UCurveFloat> TorqueCurve;

	/** Control points for torque noise (roughness) at each RPM. Simulates engine vibration character. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Engine)
	TArray<FVector> TorqueNoise;

	/** Runtime curve built from TorqueNoise. Do not edit directly. */
	UPROPERTY()
	TObjectPtr<UCurveFloat> TorqueNoiseCurve;

	/** Drag torque the engine applies to the drivetrain at each RPM when off throttle. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Engine)
	TArray<FVector> EngineFrictionTorque;

	/** Runtime curve built from EngineFrictionTorque. Do not edit directly. */
	UPROPERTY()
	TObjectPtr<UCurveFloat> EngineFrictionTorqueCurve;

	/** Control points (gear index → braking scalar) that scale engine braking per gear. Built into EngineBrakingVsGearCurve at load. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Engine)
	TArray<FVector> EngineBrakingVsGear;

	/** Runtime curve built from EngineBrakingVsGear. Do not edit directly. */
	UPROPERTY()
	TObjectPtr<UCurveFloat> EngineBrakingVsGearCurve;

	/** RPM the engine settles to when no throttle is applied. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Engine)
	float Idle {1000.f};

	/** RPM at which the rev limiter begins cutting fuel/ignition. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Engine)
	float RedLine {4800.f};

	/** Absolute RPM ceiling; engine cannot exceed this value. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Engine)
	float MaxRpm {5050.f};

	/** Flywheel rotational inertia in kg. Heavier = smoother idle, slower revs. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Engine)
	float FlyWheelMass {15.f};

	/** Constant drag torque in N·m applied to resist engine rotation (negative resists spin). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Engine)
	float EngineResistance {-450.f};

	/** Top speed cap in km/h in forward gears. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Engine)
	float SpeedLimiter {600.f};

	/** Top speed cap in km/h when reversing. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Engine)
	float SpeedLimiterReverse {600.f};

	/** Top speed cap in km/h when nitrous/NOS is active. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Engine)
	float SpeedLimiterNOS {600.f};

	/** Smoothing factor for transitions in engine load (0 = instant, higher = slower). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Engine)
	float EngineLoadLerp {0.5f};

	/** Minimum engine load fraction maintained at maximum vehicle speed. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Engine)
	float MinLoadAtTopSpeed {0.45f};

	/** Torque noise multiplier applied when throttle is fully released. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Engine)
	float ZeroLoadTorqueNoise {1.f};

	/** Torque noise multiplier applied at full throttle. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Engine)
	float FullLoadTorqueNoise {1.5f};

	/** Maximum torque boost multiplier the anti-bog system can apply to prevent stalling. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Engine)
	float EngineAntibogMaxMult {1.f};

	/** Time in ms for the anti-bog system to ramp from zero to max effect. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Engine)
	float EngineAntibogRampTime {50.f};

	/** Total duration in seconds of the engine startup/ignition animation sequence. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Engine)
	float IgnitionSequenceLength {1.4f};

	/** Duration of the rev-up portion within the ignition sequence. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Engine)
	float EngineRevSequenceLength {1.f};

	/** Duration in seconds that full throttle is held during the ignition rev. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Engine)
	float EngineRevFullThrottleDuration {0.15f};

	/** Duration in seconds the rev limiter bounces the engine before it settles. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Engine)
	float RevLimiterTime {0.18f};

	void BuildCurves();
	virtual void PostLoad() override;
};
