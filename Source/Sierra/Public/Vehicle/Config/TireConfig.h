// Copyright (c) 2026, Christian Delicaat. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Curves/CurveFloat.h"
#include "UObject/Object.h"
#include "TireConfig.generated.h"

class UAnalyticalTireConfig;

UCLASS(BlueprintType)
class SIERRA_API UTireConfig : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	/** Control points (speed km/h → scalar) for rolling resistance vs vehicle speed. Built into RollingResistanceScalarVSpeedCurve at load. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Tire)
	TArray<FVector> RollingResistanceScalarVSpeed;

	/** Runtime curve built from RollingResistanceScalarVSpeed. Do not edit directly. */
	UPROPERTY()
	TObjectPtr<UCurveFloat> RollingResistanceScalarVSpeedCurve;

	/** Static mesh used to render the wheel rim. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Tire)
	TObjectPtr<UStaticMesh> Wheel {nullptr};

	/** Static mesh used to render the tire. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Tire)
	TObjectPtr<UStaticMesh> Tire {nullptr};

	/** Analytical grip model parameters for the front tires. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Tire)
	TObjectPtr<UAnalyticalTireConfig> TireConfigFront {nullptr};

	/** Analytical grip model parameters for the rear tires. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Tire)
	TObjectPtr<UAnalyticalTireConfig> TireConfigRear {nullptr};

	/** Overall front tire diameter in meters (used to convert wheel angular velocity to vehicle speed). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Tire)
	float DiameterFront {0.65373f};

	/** Overall rear tire diameter in meters. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Tire)
	float DiameterRear {0.65373f};

	/** Rotational inertia of the front wheel+tire assembly in kg·m² (affects spin-up and braking response). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Tire)
	float TireInertiaFront {1.17649f};

	/** Rotational inertia of the rear wheel+tire assembly in kg·m². */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Tire)
	float TireInertiaRear {1.2716f};

	/** Front tire section width in mm (affects contact patch size). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Tire)
	float SectionWidthFront {230.19f};

	/** Rear tire section width in mm. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Tire)
	float SectionWidthRear {230.19f};

	/** Front rim diameter in meters (used to derive tire sidewall height). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Tire)
	float RimDiameterFront {0.43803f};

	/** Rear rim diameter in meters. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Tire)
	float RimDiameterRear {0.43803f};

	/** Base grip coefficient applied when off throttle (multiplies into the analytical model). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Tire)
	float StaticGripOffThrottle {0.2f};

	/** How easily the tire breaks traction for burnouts (0 = hard to spin, 1 = very easy). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Tire)
	float BurnoutTendency {0.3f};

	/** Rate at which tire temperature rises under lateral/longitudinal load. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Tire)
	float TireHeatIncreaseRate {0.f};

	/** Rate at which tire temperature returns to ambient when load is removed. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Tire)
	float TireHeatDecayRate {0.f};

	void BuildCurves();
	virtual void PostLoad() override;
};
