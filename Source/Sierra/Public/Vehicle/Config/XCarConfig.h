// Copyright (c) 2026, Christian Delicaat. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Curves/CurveFloat.h"
#include "Engine/DataAsset.h"
#include "XCarConfig.generated.h"

UCLASS()
class SIERRA_API UXCarConfig : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	/** Control points (speed km/h → lateral offset m) for speed-dependent body sway. Built into XCarBodyYOffsetVSpeedCurve at load. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=XCar)
	TArray<FVector> XCarBodyYOffsetVSpeed;

	/** Runtime curve built from XCarBodyYOffsetVSpeed. Do not edit directly. */
	UPROPERTY()
	TObjectPtr<UCurveFloat> XCarBodyYOffsetVSpeedCurve;

	/** Global scale applied to all XCar body dynamic effects (1.0 = full effect, 0 = disabled). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=XCar)
	float XCarMultiplier {1.f};

	/** Base lateral body offset in meters (negative = leans left). Applies at rest before speed curve. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=XCar)
	float XCarYOffset {-0.005f};

	/** Ride height adjustment added to the front axle for visual body position (meters). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=XCar)
	float XCarRideHeightFront {0.002f};

	/** Ride height adjustment added to the rear axle for visual body position (meters). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=XCar)
	float XCarRideHeightRear {0.002f};

	/** Visual-only toe angle adjustment for front wheel suspension visualization (degrees). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=XCar)
	float XCarToeAngleFront {0.f};

	/** Visual-only toe angle adjustment for rear wheel suspension visualization (degrees). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=XCar)
	float XCarToeAngleRear {0.f};

	/** Height offset of the visual roll center used for body lean simulation (meters). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=XCar)
	float BodyRollCenterHeight {-0.3f};

	/** Scales the forward acceleration force that drives body pitch (nose-up under acceleration). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=XCar)
	float ForwardForceMultiplier {1.f};

	/** Scales the lateral force that drives body roll during cornering. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=XCar)
	float SideForceMultiplier {1.f};

	/** Scales the body roll response amplitude to lateral forces. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=XCar)
	float RollForceMultiplier {10.f};

	/** Scales the body pitch response amplitude to longitudinal forces. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=XCar)
	float PitchForceMultiplier {10.f};

	/** Additional pitch exaggeration scalar on top of the physics-derived pitch. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=XCar)
	float ScalarAdditionalPitch {1.f};

	/** Additional roll exaggeration scalar on top of the physics-derived roll. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=XCar)
	float ScalarAdditionalRoll {1.f};

	/** Scale of body squat (rear drops) under acceleration. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=XCar)
	float ScalarSquat {0.6f};

	/** Scale of body dive (nose drops) under braking. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=XCar)
	float ScalarDive {0.3f};

	/** Scale of lateral body translation (side-to-side shift) response. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=XCar)
	float ScalarY {0.f};

	/** Scale of vertical body translation (heave) response. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=XCar)
	float ScalarZ {0.3f};

	/** Maximum visual steering angle in degrees applied to the front wheel meshes. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=XCar)
	float WheelMaxVisualSteeringAngle {15.f};

	/** Spring stiffness for the visual front wheel spring simulation (N/m). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=XCar)
	float WheelSpringCoefficientFront {250.f};

	/** Spring stiffness for the visual rear wheel spring simulation (N/m). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=XCar)
	float WheelSpringCoefficientRear {250.f};

	/** Damping ratio for the front visual wheel spring (1.0 = critically damped, no oscillation). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=XCar)
	float WheelSpringDampingRatioFront {0.175f};

	/** Damping ratio for the rear visual wheel spring. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=XCar)
	float WheelSpringDampingRatioRear {0.175f};

	/** Simulated mass of the front wheel assembly for visual spring physics (kg). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=XCar)
	float WheelSpringMassFront {2.f};

	/** Simulated mass of the rear wheel assembly for visual spring physics (kg). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=XCar)
	float WheelSpringMassRear {2.f};

	/** Upper travel limit of the front visual wheel spring (meters). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=XCar)
	float WheelSpringUpperLimitFront {0.1f};

	/** Upper travel limit of the rear visual wheel spring (meters). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=XCar)
	float WheelSpringUpperLimitRear {0.1f};

	/** Lower travel limit of the front visual wheel spring (meters). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=XCar)
	float WheelSpringLowerLimitFront {-0.1f};

	/** Lower travel limit of the rear visual wheel spring (meters). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=XCar)
	float WheelSpringLowerLimitRear {-0.1f};

	/** Total upper bound of front wheel visual travel including all offsets (meters). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=XCar)
	float WheelUpperLimitFront {0.05f};

	/** Total upper bound of rear wheel visual travel (meters). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=XCar)
	float WheelUpperLimitRear {0.04f};

	/** Total lower bound of front wheel visual travel (meters). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=XCar)
	float WheelLowerLimitFront {-0.08f};

	/** Total lower bound of rear wheel visual travel (meters). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=XCar)
	float WheelLowerLimitRear {-0.09f};

	/** Visual caster angle adjustment for the front wheel meshes (degrees). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=XCar)
	float WheelCasterFront {0.f};

	/** Camber angle applied to front wheel meshes at the top of suspension travel (degrees). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=XCar)
	float WheelCamberTopFront {0.1f};

	/** Camber angle applied to rear wheel meshes at the top of suspension travel (degrees). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=XCar)
	float WheelCamberTopRear {0.15f};

	/** Camber angle applied to front wheel meshes at the bottom of suspension travel (degrees). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=XCar)
	float WheelCamberBottomFront {-0.2f};

	/** Camber angle applied to rear wheel meshes at the bottom of suspension travel (degrees). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=XCar)
	float WheelCamberBottomRear {-0.2f};

	/** Horizontal offset of the front wheel mesh at the top of travel (meters, affects scrub visual). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=XCar)
	float WheelXOffsetTopFront {-0.02118f};

	/** Horizontal offset of the rear wheel mesh at the top of travel (meters). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=XCar)
	float WheelXOffsetTopRear {-0.02135f};

	/** Horizontal offset of the front wheel mesh at the bottom of travel (meters). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=XCar)
	float WheelXOffsetBottomFront {-0.02118f};

	/** Horizontal offset of the rear wheel mesh at the bottom of travel (meters). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=XCar)
	float WheelXOffsetBottomRear {-0.02135f};

	/** Horizontal offset of the front wheel steering pivot point (meters). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=XCar)
	float WheelPivotPointXOffsetFront {0.f};

	/** Horizontal offset of the rear wheel steering pivot point (meters). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=XCar)
	float WheelPivotPointXOffsetRear {0.f};

	void BuildCurves();
	virtual void PostLoad() override;
};
