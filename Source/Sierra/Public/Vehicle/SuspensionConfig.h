// Copyright (c) 2026, Christian Delicaat. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "SuspensionConfig.generated.h"

// Default properties set to Buick GNX '87, taken fron NFS:Heat
UCLASS(BlueprintType)
class SIERRA_API USuspensionConfig : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	// The resting distance between the wheel and the chassis attach point.
	// This is how high the car sits at rest before any forces are applied.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Suspension)
	float RideHeightSpecsFront {10.f};
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Suspension)
	float RideHeightSpecsRear {10.f};
	
	// How much the spring rate increases as the suspension compresses.
	// A value of 0 would be perfectly linear — the same resistance throughout travel.
	// At 0.07 the spring gets slightly stiffer the more it compresses,
	// which prevents bottoming out under heavy load.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Suspension)
	float SpringProgressionFront {0.07f};
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Suspension)
	float SpringProgressionRear {0.07f};
	
	// The base spring stiffness per axle. Higher means more resistance to compression.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Suspension)
	float SpringSpecsFront {370.f};
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Suspension)
	float SpringSpecsRear {414.f};
	
	// The total range of suspension movement from full droop to full bump.
	// The wheel cannot travel beyond this limit in either direction.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Suspension)
	float TravelSpecsFront {30.f};
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Suspension)
	float TravelSpecsRear {30.f};
	
	// The velocity threshold at which the shock absorber's relief valve opens,
	// allowing it to move freely beyond that point. Prevents the chassis from
	// taking a hard hit on a big impact. At 1.1 it's a tight threshold,
	// meaning the valve opens quickly
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Suspension)
	float ShockBlowOut {1.1f};
	
	// How quickly the damping force tapers off at high shaft velocity.
	// At 1.0 the damping would stay constant regardless of speed.
	// At 0.8 it drops off moderately at high velocity, keeping the suspension
	// compliant over sharp bumps without going fully stiff.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Suspension)
	float ShockDigressionFront {0.8f};
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Suspension)
	float ShockDigressionRear {0.8f};
	
	// The base stiffness scalar for the shock absorber.
	// Think of it as the overall resistance level of the damper before
	// digression and compression/rebound curves are applied on top.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Suspension)
	float ShockValvingFront {175.f};
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Suspension)
	float ShockValvingRear {175.f};
	
	// The local positions of each wheel relative to the vehicle body,
	// in order FL, FR, RL, RR. These are the raycast origins for the
	// suspension system — where each wheel hangs from the chassis.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Suspension)
	TArray<FVector> AttachPoints {
		{ 74.f,  133.f, 12.f},	// Front Left
		{-74.f,  133.f, 12.f},	// Front Right
		{ 74.f, -133.f, 12.f},	// Rear left
		{-74.f, -133.f, 12.f},	// Rear Right
	};
	
	// TODO: Make into float curve
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Suspension)
	TArray<FVector> ShockExtSpecsFront {
		{0.0f, 0.0f, 1.0f},
		{250.f, 37.5f, 8.0f},
		{0.0f, 1.0f, 0.0f},
		{0.07666667f, 1.0f, 0.0f},
		{0.1783333f, 1.0f, 0.0f},
		{0.3116667f, 1.0f, 0.0f},
		{0.53f, 1.0f, 0.0f},
		{0.7416667f, 1.0f, 0.0f},
		{0.9066667f, 1.0f, 0.0f},
		{1.0f, 1.0f, 0.0f},
	};
	
	// TODO: Make into float curve
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Suspension)
	TArray<FVector> ShockExtSpecsRear {
		{0.0f, 0.0f, 1.0f},
		{250.f, 46.1f, 8.0f},
		{0.0f, 1.0f, 0.0f},
		{0.11f, 1.0f, 0.0f},
		{0.2733333f, 1.0f, 0.0f},
		{0.4716667f, 1.0f, 0.0f},
		{0.625f, 1.0f, 0.0f},
		{0.7966667f, 1.0f, 0.0f},
		{0.865f, 1.0f, 0.0f},
		{1.0f, 1.0f, 0.0f},
	};
	
	// TODO: Make into float curve
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Suspension)
	TArray<FVector> ShockSpecsFront {
		{0.0f, 0.0f, 1.0f},
		{250.f, 20.8f, 8.0f},
		{0.0f, 1.0f, 0.0f},
		{0.095f, 1.0f, 0.0f},
		{0.1766667f, 1.0f, 0.0f},
		{0.275f, 1.0f, 0.0f},
		{0.41f, 1.0f, 0.0f},
		{0.54f, 1.0f, 0.0f},
		{0.65f, 1.0f, 0.0f},
		{1.0f, 1.0f, 0.0f},
	};
	
	// TODO: Make into float curve
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Suspension)
	TArray<FVector> ShockSpecsRear {
		{0.0f, 0.0f, 1.0f},
		{250.f, 29.8f, 8.0f},
		{0.0f, 1.0f, 0.0f},
		{0.08666667f, 1.0f, 0.0f},
		{0.21f, 1.0f, 0.0f},
		{0.4133333f, 1.0f, 0.0f},
		{0.5866666f, 1.0f, 0.0f},
		{0.7416667f, 1.0f, 0.0f},
		{0.85f, 1.0f, 0.0f},
		{1.0f, 1.0f, 0.0f},
	};
	
	// TODO: Make into float curve
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Suspension)
	TArray<FVector> SwaySpecsFront {
	    {0.0f, 0.0f, 1.0f},
		{250.0f, 23.5f, 8.0f},
		{0.0f, 1.0f, 0.0f},
		{0.1616667f, 1.0f, 0.0f},
		{0.2733333f, 1.0f, 0.0f},
		{0.41f, 1.0f, 0.0f},
		{0.595f, 1.0f, 0.0f},
		{0.7533333f, 1.0f, 0.0f},
		{0.8816667f, 1.0f, 0.0f},
		{1.0f, 1.0f, 0.0f},
	};
	
	// TODO: Make into float curve
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Suspension)
	TArray<FVector> SwaySpecsRear {
	    {0.0f, 0.0f, 1.0f},
		{250.0f, 32.0f, 8.0f},
		{0.0f, 1.0f, 0.0f},
		{0.19f, 1.0f, 0.0f},
		{0.3716667f, 1.0f, 0.0f},
		{0.4683333f, 1.0f, 0.0f},
		{0.635f, 1.0f, 0.0f},
		{0.7816667f, 1.0f, 0.0f},
		{0.8766667f, 1.0f, 0.0f},
		{1.0f, 1.0f, 0.0f},
	};
	
	// TODO: Make into float curve
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Suspension)
	TArray<FVector> CamberFront {
	    {0.0f, -10.0f, 1.0f},
		{250.0f, 0.0f, 8.0f},
		{0.0f, 1.0f, 0.0f},
		{0.15f, 1.0f, 0.0f},
		{0.29f, 1.0f, 0.0f},
		{0.43125f, 1.0f, 0.0f},
		{0.57f, 1.0f, 0.0f},
		{0.71f, 1.0f, 0.0f},
		{0.85f, 1.0f, 0.0f},
		{1.0f, 1.0f, 0.0f},
	};
	
	// TODO: Make into float curve
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Suspension)
	TArray<FVector> CamberRear {
	    {0.0f, -10.0f, 1.0f},
		{250.0f, 0.0f, 8.0f},
		{0.0f, 1.0f, 0.0f},
		{0.15f, 1.0f, 0.0f},
		{0.29125f, 1.0f, 0.0f},
		{0.4325f, 1.0f, 0.0f},
		{0.57f, 1.0f, 0.0f},
		{0.71125f, 1.0f, 0.0f},
		{0.85f, 1.0f, 0.0f},
		{1.0f, 1.0f, 0.0f},
	};
	
	// TODO: Make into float curve
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Suspension)
	TArray<FVector> Caster {
	    {0.0f, 7.0f, 1.0f},
		{250.0f, 10.0f, 8.0f},
		{0.0f, 0.0f, 0.0f},
		{0.1421488f, 0.0f, 0.0f},
		{0.2343802f, 0.0f, 0.0f},
		{0.4f, 0.0f, 0.0f},
		{0.5454544f, 0.0f, 0.0f},
		{0.6975208f, 0.0f, 0.0f},
		{0.8231404f, 0.0f, 0.0f},
		{1.0f, 0.0f, 0.0f},
	};
	
	// TODO: Make into float curve
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Suspension)
	TArray<FVector> ToeFront {
	    {0.0f, -9.0f, 1.0f},
		{250.0f, 0.0f, 8.0f},
		{0.0f, 1.0f, 0.0f},
		{0.15f, 1.0f, 0.0f},
		{0.29f, 1.0f, 0.0f},
		{0.43f, 1.0f, 0.0f},
		{0.57f, 1.0f, 0.0f},
		{0.71f, 1.0f, 0.0f},
		{0.84875f, 1.0f, 0.0f},
		{1.0f, 1.0f, 0.0f},
	};
	
	// TODO: Make into float curve
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Suspension)
	TArray<FVector> ToeRear {
	    {0.0f, -10.0f, 1.0f},
		{250.0f, 0.0f, 8.0f},
		{0.0f, 1.0f, 0.0f},
		{0.15f, 1.0f, 0.0f},
		{0.295f, 1.0f, 0.0f},
		{0.428f, 1.0f, 0.0f},
		{0.57f, 1.0f, 0.0f},
		{0.85f, 1.0f, 0.0f},
		{0.895f, 1.0f, 0.0f},
		{1.0f, 1.0f, 0.0f},
	};
};
