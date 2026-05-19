// Copyright (c) 2026, Christian Delicaat. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Curves/CurveFloat.h"
#include "Engine/DataAsset.h"
#include "SteeringConfig.generated.h"

UCLASS()
class SIERRA_API USteeringConfig : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	/** Remaps raw brake pedal input through a curve before it is passed to the physics. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Steering)
	TArray<FVector> BrakeInputRemap;

	/** Runtime curve built from BrakeInputRemap. Do not edit directly. */
	UPROPERTY()
	TObjectPtr<UCurveFloat> BrakeInputRemapCurve;

	/** Rate in deg/s at which wheels counter-steer vs current drift/slip angle. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Steering)
	TArray<FVector> CounterSteerRate;

	/** Runtime curve built from CounterSteerRate. Do not edit directly. */
	UPROPERTY()
	TObjectPtr<UCurveFloat> CounterSteerRateCurve;

	/** How fast the front wheels move toward driver input in deg/s vs vehicle speed. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Steering)
	TArray<FVector> SteerRate;

	/** Runtime curve built from SteerRate. Do not edit directly. */
	UPROPERTY()
	TObjectPtr<UCurveFloat> SteerRateCurve;

	/** Slower steer rate applied for small/gentle steering inputs to improve precision. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Steering)
	TArray<FVector> GentleInputSteerRate;

	/** Runtime curve built from GentleInputSteerRate. Do not edit directly. */
	UPROPERTY()
	TObjectPtr<UCurveFloat> GentleInputSteerRateCurve;

	/** Rate in deg/s at which steering returns to center when no input is applied. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Steering)
	TArray<FVector> CenterSteerRate;

	/** Runtime curve built from CenterSteerRate. Do not edit directly. */
	UPROPERTY()
	TObjectPtr<UCurveFloat> CenterSteerRateCurve;

	/** Maximum steering angle in degrees when reversing. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Steering)
	float ReverseSteeringRange {35.f};

	/** Maximum steering angle (degrees) vs speed curve while the throttle is applied. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Steering)
	TArray<FVector> SteeringRangeOnThrottle;

	/** Runtime curve built from SteeringRangeOnThrottle. Do not edit directly. */
	UPROPERTY()
	TObjectPtr<UCurveFloat> SteeringRangeOnThrottleCurve;

	/** Maximum steering angle (degrees) vs speed curve while off throttle. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Steering)
	TArray<FVector> SteeringRangeOffThrottle;

	/** Runtime curve built from SteeringRangeOffThrottle. Do not edit directly. */
	UPROPERTY()
	TObjectPtr<UCurveFloat> SteeringRangeOffThrottleCurve;

	/** Reduces available steering range as yaw rate increases (stability limiter). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Steering)
	float SteeringVsAngularVelocity {0.f};

	/** Reduces available steering range as body slip angle increases (stability limiter). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Steering)
	float SteeringVsSlipAngle {0.f};

	/** Throttle response curve (input → output) applied specifically in first gear. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Steering)
	TArray<FVector> ThrottleMappingFirstGear;

	/** Runtime curve built from ThrottleMappingFirstGear. Do not edit directly. */
	UPROPERTY()
	TObjectPtr<UCurveFloat> ThrottleMappingFirstGearCurve;

	/** Throttle response curve applied in second gear. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Steering)
	TArray<FVector> ThrottleMappingSecondGear;

	/** Runtime curve built from ThrottleMappingSecondGear. Do not edit directly. */
	UPROPERTY()
	TObjectPtr<UCurveFloat> ThrottleMappingSecondGearCurve;

	/** Throttle response curve applied in third gear and above. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Steering)
	TArray<FVector> ThrottleMappingThirdAndAbove;

	/** Runtime curve built from ThrottleMappingThirdAndAbove. Do not edit directly. */
	UPROPERTY()
	TObjectPtr<UCurveFloat> ThrottleMappingThirdAndAboveCurve;

	/** Maximum front wheel steering angle in degrees (hard limit). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Steering)
	float MaxSteeringAngle {35.f};

	/** How strongly tire self-aligning torque pulls the steering toward center during normal driving. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Steering)
	float AligningTorqueEffect {0.3f};

	/** Aligning torque strength while in drift mode (typically reduced to let the driver steer freely). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Steering)
	float AligningTorqueEffectInDrift {0.f};

	/** Maximum steering angle at which self-aligning torque is applied. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Steering)
	float MaxAngleSteeringAlignEffect {0.f};

	/** Maximum counter-steer angle before aligning torque assistance stops. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Steering)
	float MaxAngleCounterSteerAlignEffect {0.f};

	/** Slip angle in degrees above which the full drift counter-steer rate applies. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Steering)
	float DriftAngleForCounterSteerRate {40.f};

	/** Steering rate in deg/s used for counter-steering during a drift. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Steering)
	float DriftCountersteerRate {80.f};

	/** Steering rate in deg/s while driving in reverse. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Steering)
	float ReverseSteerRate {47.f};

	/** Counter-steer rate in deg/s while reversing. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Steering)
	float ReverseCounterSteerRate {80.f};

	/** Return-to-center rate in deg/s while reversing. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Steering)
	float ReverseCenterSteerRate {80.f};

	/** Duration in seconds that throttle is limited after a downshift (prevents wheelspin). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Steering)
	float TimeThrottlingAfterDownShift {0.2f};

	/** Throttle output cap (0–1) applied during the post-downshift throttle limiting period. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Steering)
	float AmountThrottlingAfterDownShift {0.7f};

	/** Speed in km/h below which post-downshift throttle limiting is skipped entirely. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Steering)
	float MinSpeedForThrottlingAfterDownShift {10.f};

	void BuildCurves();
	virtual void PostLoad() override;
};
