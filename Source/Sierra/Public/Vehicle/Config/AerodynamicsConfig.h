// Copyright (c) 2026, Christian Delicaat. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "AerodynamicsConfig.generated.h"

UCLASS()
class SIERRA_API UAerodynamicsConfig : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	/** Overall aerodynamic force multiplier (scales all aero forces proportionally). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Aerodynamics)
	float AeroCoefficient {3.f};

	/** Longitudinal position of the aero center of pressure as a percentage (0 = front axle, 100 = rear axle). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Aerodynamics)
	float AeroCG {50.f};

	/** Drag coefficient (Cd); higher values produce more aerodynamic drag at speed. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Aerodynamics)
	float DragCoefficient {0.2446f};

	/** Aerodynamically limited top speed in km/h (drag balances engine thrust at this speed). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Aerodynamics)
	float TopSpeed {230.f};

	/** Base downforce coefficient; negative values press the car into the ground. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Aerodynamics)
	float Downforce {-1.0f};

	/** Additional downforce offset applied on top of the base value (baseline aero bias). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Aerodynamics)
	float DownforceOffset {-0.2f};

	/** Downforce offset applied while braking; positive shifts load toward the front. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Aerodynamics)
	float DownforceOffsetUnderBraking {0.05f};

	/** Downforce offset applied while in drift mode; negative increases rear-biased loading. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Aerodynamics)
	float DownforceOffsetInDrift {-0.4f};

	/** Aero coefficient used when throttle is lifted (typically lower than on-throttle value). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Aerodynamics)
	float AeroCoefficientOffThrottle {0.1f};

	/** Maximum lift coefficient achievable at altitude (positive = lifts away from ground). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Aerodynamics)
	float AeroCoefficientMaxLift {0.0f};

	/** Maximum aero coefficient contribution from ground effect (active at very low ride height). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Aerodynamics)
	float AeroCoefficientMaxGroundEffect {0.0f};

	/** Aero coefficient reduction when the car is at 90 degrees yaw off throttle. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Aerodynamics)
	float AeroCoefficientOffThrottle90DegLoss {0.0f};

	/** Ride-height-to-wheelbase ratio below which ground effect aero starts increasing. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Aerodynamics)
	float GroundEffectHeightRatio {30.f};

	/** Ride-height-to-wheelbase ratio above which lift forces become significant. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Aerodynamics)
	float LiftHeightRatio {99.f};

	/** Drag coefficient override applied when nitrous/NOS is active. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Aerodynamics)
	float NitrousDragCoefficient {0.8f};

	/** Top speed cap in km/h while nitrous is active. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Aerodynamics)
	float NitrousTopSpeed {240.f};

	/** Aero coefficient used when the car is airborne after a large jump. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Aerodynamics)
	float FlyingCarAeroCoef_BigAir {4.15f};

	/** Aero coefficient used when the car is airborne after a small bump. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Aerodynamics)
	float FlyingCarAeroCoef_SmallAir {7.0f};

	/** Speed threshold in km/h below which the low-speed in-air damping values are used. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Aerodynamics)
	float InAirDampingLowSpeed {100.f};

	/** Speed threshold in km/h above which the high-speed in-air damping values are used. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Aerodynamics)
	float InAirDampingHighSpeed {200.f};

	/** Angular damping (roll, pitch, yaw) applied while airborne at low speed. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Aerodynamics)
	FVector InAirDampingLow {0.4f, 0.4f, 0.4f};

	/** Angular damping (roll, pitch, yaw) applied while airborne at high speed. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Aerodynamics)
	FVector InAirDampingHigh {0.64f, 0.64f, 0.64f};

	/** Fraction of forward velocity absorbed/dampened on landing impact. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Aerodynamics)
	float LandingForwardVelocityDamping {0.2f};

	/** Duration in seconds over which the landing forward velocity damping is applied. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Aerodynamics)
	float LandingForwardVelocityDampingDuration {0.4f};
};
