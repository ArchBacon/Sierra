// Copyright (c) 2026, Christian Delicaat. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "SuspensionConfig.generated.h"

USTRUCT()
struct FDamperSpecs
{
	GENERATED_BODY()

	/** Low-speed damper valving rate; controls damper force before the digression point. */
	float ShockValving {0.f};
	/** Compression damping coefficient (bump). */
	float ShockSpecs {0.f};
	/** Rebound/extension damping coefficient. */
	float ShockExtSpecs {0.f};
	/** Shaft speed at which damping force starts to decrease (digression knee point). */
	float ShockDigression {0.f};
	/** Force multiplier cap before the damper blow-off valve activates. */
	float ShockBlowOut {0.f};
};

USTRUCT()
struct FSpringSpecs
{
	GENERATED_BODY()

	/** Spring rate in N/mm. */
	float SpringSpecs {0.f};
	/** Progressive rate coefficient; 0 = linear spring, higher = increasingly stiff with compression. */
	float SpringProgression {0.f};
	/** Total suspension travel in mm from full droop to full compression. */
	float TravelSpecs {0.f};
};

UCLASS(BlueprintType)
class SIERRA_API USuspensionConfig : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	/** Static camber angle in degrees for the front axle (negative = top of wheel tilts inward). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Suspension)
	float CamberFront {0.f};

	/** Static camber angle in degrees for the rear axle. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Suspension)
	float CamberRear {0.f};

	/** Static toe angle in degrees for the front axle (positive = toe-in). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Suspension)
	float ToeFront {0.f};

	/** Static toe angle in degrees for the rear axle. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Suspension)
	float ToeRear {0.f};

	/** Caster angle in degrees; higher values increase steering feel and self-centering. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Suspension)
	float Caster {7.f};

	/** Compression damping coefficient for the front shock absorbers. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Suspension)
	float ShockSpecsFront {20.8f};

	/** Compression damping coefficient for the rear shock absorbers. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Suspension)
	float ShockSpecsRear {29.8f};

	/** Rebound/extension damping coefficient for the front shocks. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Suspension)
	float ShockExtSpecsFront {37.5f};

	/** Rebound/extension damping coefficient for the rear shocks. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Suspension)
	float ShockExtSpecsRear {46.1f};

	/** Anti-roll bar stiffness for the front axle in N·m/deg. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Suspension)
	float SwaySpecsFront {23.5f};

	/** Anti-roll bar stiffness for the rear axle in N·m/deg. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Suspension)
	float SwaySpecsRear {32.f};

	/** Nominal front ride height from ground to chassis reference point in cm. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Suspension)
	float RideHeightSpecsFront {10.f};

	/** Nominal rear ride height from ground to chassis reference point in cm. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Suspension)
	float RideHeightSpecsRear {10.f};

	/** Front spring rate in N/mm. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Suspension)
	float SpringSpecsFront {370.f};

	/** Rear spring rate in N/mm. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Suspension)
	float SpringSpecsRear {414.f};

	/** Progressive rate coefficient for the front springs (0 = linear). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Suspension)
	float SpringProgressionFront {0.07f};

	/** Progressive rate coefficient for the rear springs (0 = linear). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Suspension)
	float SpringProgressionRear {0.07f};

	/** Total front suspension travel in mm. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Suspension)
	float TravelSpecsFront {30.f};

	/** Total rear suspension travel in mm. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Suspension)
	float TravelSpecsRear {30.f};

	/** Low-speed valving rate for the front dampers. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Suspension)
	float ShockValvingFront {175.f};

	/** Low-speed valving rate for the rear dampers. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Suspension)
	float ShockValvingRear {175.f};

	/** Shaft speed threshold at which front damper force begins to decrease (digression knee). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Suspension)
	float ShockDigressionFront {0.8f};

	/** Shaft speed threshold at which rear damper force begins to decrease. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Suspension)
	float ShockDigressionRear {0.8f};

	/** Maximum force multiplier before the damper blow-off valve releases pressure (shared front/rear). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Suspension)
	float ShockBlowOut {1.1f};

	// The local positions of each wheel relative to the vehicle body,
	// in order FL, FR, RL, RR.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Suspension)
	TArray<FVector> AttachPoints
	{
		{ 74.f,  133.f, 12.f},
		{-74.f,  133.f, 12.f},
		{ 74.f, -133.f, 12.f},
		{-74.f, -133.f, 12.f},
	};

	FDamperSpecs GetDamperSpecs(bool bIsFront) const;
	FSpringSpecs GetSpringSpecs(bool bIsFront) const;
};

inline FDamperSpecs USuspensionConfig::GetDamperSpecs(const bool bIsFront) const
{
	return FDamperSpecs
	{
		.ShockValving    = bIsFront ? ShockValvingFront    : ShockValvingRear,
		.ShockSpecs      = bIsFront ? ShockSpecsFront      : ShockSpecsRear,
		.ShockExtSpecs   = bIsFront ? ShockExtSpecsFront   : ShockExtSpecsRear,
		.ShockDigression = bIsFront ? ShockDigressionFront : ShockDigressionRear,
		.ShockBlowOut    = ShockBlowOut,
	};
}

inline FSpringSpecs USuspensionConfig::GetSpringSpecs(const bool bIsFront) const
{
	return FSpringSpecs
	{
		.SpringSpecs       = bIsFront ? SpringSpecsFront       : SpringSpecsRear,
		.SpringProgression = bIsFront ? SpringProgressionFront : SpringProgressionRear,
		.TravelSpecs       = bIsFront ? TravelSpecsFront       : TravelSpecsRear,
	};
}
