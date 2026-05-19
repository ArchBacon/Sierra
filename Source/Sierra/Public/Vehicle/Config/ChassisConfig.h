// Copyright (c) 2026, Christian Delicaat. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Curves/CurveFloat.h"
#include "Engine/DataAsset.h"
#include "ChassisConfig.generated.h"

UCLASS()
class SIERRA_API UChassisConfig : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	/** Percentage of total vehicle weight over the front axle (52 = 52% front, 48% rear). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Chassis)
	float FrontWeightBias {52.f};

	/** Height of the roll center above the ground in cm; affects body roll leverage. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Chassis)
	float RollCenter {11.f};

	/** Total vehicle mass in kg. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Chassis)
	float Mass {1350.f};

	/** Distance in meters from the center of mass to the front axle. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Chassis)
	float FrontAxle {1.33875f};

	/** Distance in meters between the front and rear axles. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Chassis)
	float WheelBase {2.71f};

	/** Distance in meters between the centers of the two front wheels. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Chassis)
	float TrackWidthFront {1.7341f};

	/** Distance in meters between the centers of the two rear wheels. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Chassis)
	float TrackWidthRear {1.73088f};

	/** Multiplier applied to gravity for this vehicle (1.0 = normal gravity). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Chassis)
	float GravityScale {1.0f};

	/** Scales the collision impulse threshold above which collision response effects trigger. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Chassis)
	float CollisionThresholdScalar {1.2f};

	/** Scales the effective inverse mass used in collision response (higher = lighter feel on impact). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Chassis)
	float CollisionInvMassScale {1.0f};

	/** Friction coefficient applied when two vehicles are in contact. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Chassis)
	float VehicleVsVehicleFriction {0.15f};

	/** Bounciness scalar applied when two vehicles collide (0 = no bounce, 1 = full elastic). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Chassis)
	float VehicleVsVehicleBounceScalar {0.125f};

	/** Scales the victim vehicle's lateral grip when being pit-maneuvered (lower = easier to spin). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Chassis)
	float PitManeuverVictimLateralGripScalar {1.0f};

	/** How aggressively the car's lateral velocity matches a side-swiping vehicle (rubbing effect). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Chassis)
	float SideSwipeSpeedMatchingScalar {0.5f};

	/** Suppresses spinning momentum when hitting a static obstacle. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Chassis)
	float AntiSpinVsStaticScalar {1.0f};

	/** Simulated effective mass increase for stability during vehicle-to-vehicle collisions. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Chassis)
	float MassRaiseVsVehicle {0.2f};

	/** Simulated effective mass increase for stability during vehicle-to-static collisions. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Chassis)
	float MassRaiseVsStatic {0.075f};

	/** Friction coefficient applied when the chassis underside contacts the terrain (bottoming out). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Chassis)
	float TerrainBottomOutFriction {0.72f};

	/** Inertia box dimensions (X=width, Y=height, Z=length) used when the vehicle is tumbling/rolling. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Chassis)
	FVector InertiaBoxTumbling {2.7f, 1.0f, 5.2f};

	/** Inertia box dimensions used for normal driving physics simulation. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Chassis)
	FVector InertiaBoxVehiclePhysics {1.93f, 1.24f, 4.5f};

	/** Inertia box dimensions used during collision impulse calculations. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Chassis)
	FVector InertiaBoxCollision {2.5f, 1.0f, 5.0f};

	/** Per-axis scale applied to the computed inertia tensor (1,1,1 = no change). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Chassis)
	FVector TensorScale {1.0f, 1.0f, 1.0f};

	/** Local center of gravity offset used specifically during tumble/rollover physics. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Chassis)
	FVector TumbleLocalCOG {0.0f, 0.22f, 0.066f};
};
