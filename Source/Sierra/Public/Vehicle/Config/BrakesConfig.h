// Copyright (c) 2026, Christian Delicaat. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Curves/CurveFloat.h"
#include "Engine/DataAsset.h"
#include "BrakesConfig.generated.h"

UCLASS()
class SIERRA_API UBrakesConfig : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	/** Control points (speed km/h → torque N·m) for front brake torque vs vehicle speed. Built into FrontBrakeTorqueVsSpeedCurve at load. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Brakes)
	TArray<FVector> FrontBrakeTorqueVsSpeed;

	/** Runtime curve built from FrontBrakeTorqueVsSpeed. Do not edit directly. */
	UPROPERTY()
	TObjectPtr<UCurveFloat> FrontBrakeTorqueVsSpeedCurve;

	/** Constant rear brake torque in N·m applied when the brake pedal is fully depressed. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Brakes)
	float RearBrakeTorque {1050.f};

	/** Control points (speed km/h → torque N·m) for handbrake torque vs vehicle speed. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Brakes)
	TArray<FVector> HandbrakeTorqueVsSpeed;

	/** Runtime curve built from HandbrakeTorqueVsSpeed. Do not edit directly. */
	UPROPERTY()
	TObjectPtr<UCurveFloat> HandbrakeTorqueVsSpeedCurve;

	/** Brake input fraction below which no braking force is applied (dead zone). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Brakes)
	float BrakeScalarDeadZone {1.0f};

	/** Minimum time in seconds the handbrake must be held before it takes full effect. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Brakes)
	float MinHandbrakeTime {0.1f};

	/** Additional braking force added when the vehicle is moving in reverse. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Brakes)
	float BackwardsExtraBrakeStrength {15.f};

	/** Constant bonus braking force added on top of the standard brake torque (any direction). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Brakes)
	float ExtraBrakeStrength {0.0f};

	/** Constant torque offset added to front brake output (positive = more front bias). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Brakes)
	float FrontBrakeOffset {0.0f};

	/** Constant torque offset added to rear brake output. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Brakes)
	float RearBrakeOffset {0.0f};

	/** Time in seconds to ramp from zero to full brake pressure after the pedal is pressed. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Brakes)
	float TimeForFullBrakeStrength {0.1f};

	/** Scales front brake force when steering input is active (1.0 = no reduction). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Brakes)
	float FrontBrakeScalarWhenSteering {1.0f};

	/** Scales rear brake force when steering input is active (1.0 = no reduction). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Brakes)
	float RearBrakeScalarWhenSteering {1.0f};

	void BuildCurves();
	virtual void PostLoad() override;
};
