// Copyright (c) 2026, Christian Delicaat. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Curves/CurveFloat.h"
#include "Engine/DataAsset.h"
#include "TransmissionConfig.generated.h"

USTRUCT(BlueprintType)
struct FGearData
{
	GENERATED_BODY()

	/** Gear ratio multiplied by FinalGear to produce the overall drive ratio. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Transmission)
	float GearRatio {1.f};

	/** Power transmission efficiency for this gear (1.0 = lossless). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Transmission)
	float GearEfficiency {1.f};

	/** Vehicle speed in km/h at which the auto-gearbox triggers an upshift. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Transmission)
	float GearUpSpeed {0.f};

	/** Engine RPM at which the auto-gearbox triggers an upshift. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Transmission)
	float GearUpRPM {0.f};

	/** Engine RPM at which the auto-gearbox triggers a downshift. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Transmission)
	float GearDownRPM {0.f};
};

UCLASS()
class SIERRA_API UTransmissionConfig : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	/** Throttle output curve during an upshift (time → throttle fraction). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Transmission)
	TArray<FVector> UpShiftThrottle;

	/** Runtime curve built from UpShiftThrottle. Do not edit directly. */
	UPROPERTY()
	TObjectPtr<UCurveFloat> UpShiftThrottleCurve;

	/** Clutch engagement curve during an upshift (time → clutch fraction). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Transmission)
	TArray<FVector> UpShiftClutch;

	/** Runtime curve built from UpShiftClutch. Do not edit directly. */
	UPROPERTY()
	TObjectPtr<UCurveFloat> UpShiftClutchCurve;

	/** Throttle output curve during a downshift (time → throttle fraction). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Transmission)
	TArray<FVector> DownShiftThrottle;

	/** Runtime curve built from DownShiftThrottle. Do not edit directly. */
	UPROPERTY()
	TObjectPtr<UCurveFloat> DownShiftThrottleCurve;

	/** Clutch engagement curve during a downshift (time → clutch fraction). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Transmission)
	TArray<FVector> DownShiftClutch;

	/** Runtime curve built from DownShiftClutch. Do not edit directly. */
	UPROPERTY()
	TObjectPtr<UCurveFloat> DownShiftClutchCurve;

	/** Scales downshift aggressiveness based on road slope (slope → scalar). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Transmission)
	TArray<FVector> DownShiftSlopeScalar;

	/** Runtime curve built from DownShiftSlopeScalar. Do not edit directly. */
	UPROPERTY()
	TObjectPtr<UCurveFloat> DownShiftSlopeScalarCurve;

	/** Per-gear ratio, efficiency, and auto-shift thresholds. Index 0 = first gear. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Transmission)
	TArray<FGearData> Gears;

	/** Index of the highest forward gear (1-based). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Transmission)
	int32 TopGear {4};

	/** Final drive ratio multiplied with each gear ratio to get wheel torque ratio. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Transmission)
	float FinalGear {3.42f};

	/** Total time in seconds for a gear change to complete (includes clutch travel). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Transmission)
	float GearChangeTime {0.4f};

	/** Clutch slip ratio during a shift (0 = fully engaged, 1 = fully slipping). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Transmission)
	float ClutchSlip {0.6f};

	/** Rotational inertia of the drivetrain. Higher values slow response to RPM changes during shifts. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Transmission)
	float TransmissionInertia {1.f};

	/** Front/rear torque split for AWD (0 = rear-only, 1 = front-only). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Transmission)
	float TorqueSplit {0.f};

	/** Front/rear torque split override applied when in drift mode. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Transmission)
	float TorqueSplitInDrift {0.f};

	/** Front/rear torque split override on dirt or off-road surfaces. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Transmission)
	float DirtTorqueSplit {0.f};

	/** Front differential lock ratio (0 = open/free, 1 = fully locked). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Transmission)
	float DifferentialFront {0.f};

	/** Rear differential lock ratio (0 = open/free, 1 = fully locked). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Transmission)
	float DifferentialRear {0.6f};

	/** Center differential lock ratio for AWD torque distribution (0 = open, 1 = locked). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Transmission)
	float DifferentialCenter {0.f};

	/** Scales the torque output when driving in reverse gear. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Transmission)
	float ReverseTorqueMultiplier {1.f};

	/** Maximum torque (N·m) the driveshaft can transmit before body-twist effect starts. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Transmission)
	float DriveShaftTorqueMax {0.f};

	/** How strongly driveshaft torque twists/rolls the vehicle body (visual effect). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Transmission)
	float DriveShaftTorqueEffect {0.f};

	/** Additional braking force applied to the drivetrain during a downshift. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Transmission)
	float ShiftDownBrakeDynamicFactor {0.f};

	/** Minimum tire traction fraction (0–1) required to allow an upshift in any gear. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Transmission)
	float MinTireTractionToShiftUp {0.8f};

	/** Minimum tire traction fraction required specifically to shift out of first gear. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Transmission)
	float MinTireTractionToShiftUpFirstGear {0.6f};

	void BuildCurves();
	virtual void PostLoad() override;
};
