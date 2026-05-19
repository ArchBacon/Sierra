// Copyright (c) 2026, Christian Delicaat. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ForcedInductionConfig.generated.h"

UENUM(BlueprintType)
enum class EForcedInductionType : uint8
{
	None,               // No forced induction; naturally aspirated engine.
	TurboCharger,       // Exhaust-driven turbo; has boost lag and spool time.
	RootsBlower,        // Positive-displacement roots supercharger; instant boost, no lag.
	CentrifugalBlower,  // Centrifugal supercharger; boost increases with RPM.
	TwinScrew,          // Twin-screw supercharger; high efficiency, low lag.
};

UCLASS()
class SIERRA_API UForcedInductionConfig : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	/** Type of forced induction hardware fitted to this engine. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=ForcedInduction)
	EForcedInductionType InductionType {EForcedInductionType::TurboCharger};

	/** Maximum boost pressure in PSI at full load and peak RPM. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=ForcedInduction)
	float PeakPSI {4.f};

	/** Seconds for a turbocharger to spool from idle to peak boost (turbo lag duration). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=ForcedInduction)
	float LagTime {0.6f};

	/** Seconds for boost pressure to bleed off after the throttle is lifted. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=ForcedInduction)
	float SpinDownTime {0.5f};

	/** Normalized RPM (0–1 of RedLine) above which boost begins building. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=ForcedInduction)
	float BoostStartRpm {0.4f};

	/** Minimum throttle fraction required to start building boost pressure. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=ForcedInduction)
	float BoostMinThrottle {0.7f};

	/** Throttle fraction above which boost always increases regardless of RPM. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=ForcedInduction)
	float BoostAlwaysThrottle {1.f};

	/** Boost level at low throttle or low RPM as a fraction of PeakPSI. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=ForcedInduction)
	float LowBoost {0.f};

	/** Boost level at high throttle or high RPM as a fraction of PeakPSI. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=ForcedInduction)
	float HighBoost {0.1f};

	/** Whether this setup has a blow-off valve that vents pressure on throttle lift (affects audio/VFX). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=ForcedInduction)
	bool HasBlowoffValve {true};

	/** Whether this setup has a bypass valve that recirculates pressure internally (supercharger whine). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=ForcedInduction)
	bool HasBypassValve {false};
};
