// Copyright (c) 2026, Christian Delicaat. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "AnalyticalTireConfig.generated.h"

/** Describes how body slip angle bleeds longitudinal (traction or braking) grip. */
USTRUCT(BlueprintType)
struct FSlipAngleInfluenceOnLongGrips
{
	GENERATED_BODY()

	/** Slip angle in degrees below which longitudinal grip is unaffected. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Tire|Analytical")
	float MinimumSlipAngle {2.0f};

	/** Slip angle in degrees at which the full lateral influence on longitudinal grip is reached. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Tire|Analytical")
	float LargeSlipAngle {10.f};

	/** Maximum fraction by which lateral slip reduces longitudinal grip (0 = no reduction, 1 = full reduction). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Tire|Analytical")
	float MaximumLateralInfluence {1.0f};

	/** Exponent on the slip angle → influence curve; higher = sharper onset. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Tire|Analytical")
	float LateralInfluencePower {1.25};
};

/** Describes how wheel spin ratio bleeds lateral grip. */
USTRUCT(BlueprintType)
struct FSpinRatioInfluenceOnLateralGrips
{
	GENERATED_BODY()

	/** Spin ratio below which lateral grip is unaffected by longitudinal spin. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Tire|Analytical")
	float MinimumSpinRatio {0.1f};

	/** Spin ratio at which full longitudinal spin influence on lateral grip is reached. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Tire|Analytical")
	float LargeSpinRatio {1.0f};

	/** Maximum fraction by which spin reduces lateral grip. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Tire|Analytical")
	float MaximumLongInfluence {1.0f};

	/** Exponent on the spin ratio → lateral influence curve; higher = sharper onset. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Tire|Analytical")
	float LongInfluencePower {1.5f};
};

/** Two-point description of a longitudinal (traction or braking) grip vs spin ratio curve. */
USTRUCT(BlueprintType)
struct FLongGripCurve
{
	GENERATED_BODY()

	/** Wheel spin ratio at which peak longitudinal grip occurs (Pacejka peak slip). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Tire|Analytical")
	float SpinRatioForPeakGrip {0.05f};

	/** Peak longitudinal grip coefficient at the optimal spin ratio. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Tire|Analytical")
	float PeakGrip {1.6f};

	/** Spin ratio at which grip stabilizes to the sustained FinalGrip value. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Tire|Analytical")
	float SpinRatioForFinalGrip {0.6f};

	/** Sustained grip coefficient beyond the peak (sliding/saturated regime). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Tire|Analytical")
	float FinalGrip {1.45f};
};

/** Two-point description of a lateral grip vs slip angle curve. */
USTRUCT(BlueprintType)
struct FLateralGripCurve
{
	GENERATED_BODY()

	/** Normalized lateral slip at which peak lateral grip occurs. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Tire|Analytical")
	float SlipForPeakGrip {0.5f};

	/** Rate of lateral grip buildup from zero to peak (cornering stiffness proxy). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Tire|Analytical")
	float InitialGripRate {0.25f};

	/** Slip angle in degrees at which peak lateral grip occurs. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Tire|Analytical")
	float SlipAngleForPeakGrip {22.f};

	/** Peak lateral grip coefficient. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Tire|Analytical")
	float PeakGrip {2.05f};
};

UCLASS()
class SIERRA_API UAnalyticalTireConfig : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	/** Longitudinal grip curve used when the vehicle has no body slip angle (driving straight). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Tire|Analytical")
	FLongGripCurve LongGripForZeroSlipAngle {};

	/** Longitudinal grip curve used at large body slip angles (combined cornering + acceleration). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Tire|Analytical")
	FLongGripCurve LongGripForLargeSlipAngle {};

	/** Braking longitudinal grip curve at zero body slip angle (straight-line braking). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Tire|Analytical")
	FLongGripCurve BrakingLongGripForZeroSlipAngle {};

	/** Braking longitudinal grip curve at large body slip angles (combined braking + cornering). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Tire|Analytical")
	FLongGripCurve BrakingLongGripForLargeSlipAngle {};

	/** Lateral grip curve when there is no longitudinal wheel spin (pure cornering). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Tire|Analytical")
	FLateralGripCurve LateralGripForZeroSpinRatio {};

	/** Lateral grip curve under high wheel spin during traction (combined slip). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Tire|Analytical")
	FLateralGripCurve LateralGripForLargeSpinRatio {};

	/** Lateral grip curve under high wheel spin during braking (combined slip under braking). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Tire|Analytical")
	FLateralGripCurve BrakingLateralGripForLargeSpinRatio {};

	/** Defines how body slip angle reduces longitudinal grip during traction. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Tire|Analytical")
	FSlipAngleInfluenceOnLongGrips TractionSlipAngleInfluenceOnLongGrips {};

	/** Defines how body slip angle reduces longitudinal grip during braking. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Tire|Analytical")
	FSlipAngleInfluenceOnLongGrips BrakingSlipAngleInfluenceOnLongGrips {};

	/** Defines how wheel spin ratio reduces lateral grip during traction. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Tire|Analytical")
	FSpinRatioInfluenceOnLateralGrips TractionSpinRatioInfluenceOnLateralGrips {};

	/** Defines how wheel spin ratio reduces lateral grip during braking. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Tire|Analytical")
	FSpinRatioInfluenceOnLateralGrips BrakingSpinRatioInfluenceOnLateralGrips {};

	/** Global multiplier applied to all lateral grip forces. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Tire|Analytical")
	float LateralFrictionScale {1.0f};

	/** Global multiplier applied to all longitudinal grip forces. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Tire|Analytical")
	float LongitudinalFrictionScale {1.0f};

	/** Converts applied torque to slip ratio for the analytical model (higher = more slip per torque). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Tire|Analytical")
	float TorqueRatioToSlipRatioConstant {0.5f};

	/** Grip sensitivity scale during normal contact (higher = sharper grip transitions). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Tire|Analytical")
	float GripFactor {10.f};

	/** Grip sensitivity scale when the tire is fully sliding. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Tire|Analytical")
	float SlidingGripFactor {10.f};

	/** How much vertical load (weight) affects grip; 0 = no load sensitivity. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Tire|Analytical")
	float WheelLoadTireResponse {0.0f};

	/** Bias toward longitudinal vs lateral grip when both are active simultaneously. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Tire|Analytical")
	float LongitudinalBias {0.0f};

	/** Maximum available grip force in Newtons (caps the total combined force output). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Tire|Analytical")
	float AvailableGrip {25000.f};

	/** Camber angle in degrees at which grip is at its maximum. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Tire|Analytical")
	float CamberAngleForMaximumGrip {2.0f};

	/** Camber angle in degrees at which grip falls to CamberMinimumGrip. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Tire|Analytical")
	float CamberAngleForMinimumGrip {10.0f};

	/** Grip coefficient at the worst camber angle (CamberAngleForMinimumGrip). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Tire|Analytical")
	float CamberMinimumGrip {1.0f};

	/** Distance in meters the tire must travel before lateral force builds to steady-state (relaxation length). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Tire|Analytical")
	float LateralRelaxationLength {1.8f};

	/** Maximum sidewall deflection allowed; 0 = rigid tire (no deformation modeled). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Tire|Analytical")
	float MaximumLateralDeflection {0.0f};
};
