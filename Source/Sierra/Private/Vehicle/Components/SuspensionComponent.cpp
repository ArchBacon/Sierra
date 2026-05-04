// Copyright (c) 2026, Christian Delicaat. All rights reserved.

#include "Vehicle/Components/SuspensionComponent.h"

#include "DSP/BufferDiagnostics.h"
#include "Sierra/Sierra.h"
#include "Vehicle/PhysicsVehicle.h"
#include "Vehicle/SuspensionConfig.h"
#include "Vehicle/TireConfig.h"

USuspensionComponent::USuspensionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void USuspensionComponent::BeginPlay()
{
	Super::BeginPlay();

	OwningPawn = Cast<APhysicsVehicle>(GetOwner());
	
	// Load default value for suspension data
	for (const auto& FrontSuspension : OwningPawn->GetFrontSuspension())
	{
		SuspensionData.Add(FrontSuspension, {});
	} 
	for (const auto& FrontSuspension : OwningPawn->GetRearSuspension())
	{
		SuspensionData.Add(FrontSuspension, {});
	} 
}

void USuspensionComponent::TickComponent(
	const float DeltaTime,
	const ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction
) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	auto SuspensionConfig = OwningPawn->GetSuspensionConfig();
	auto TireConfig = OwningPawn->GetTireConfig();
	
	// Front Suspension
	for (const auto& Suspension : OwningPawn->GetFrontSuspension())
	{
		UpdateSuspensionData(Suspension, SuspensionConfig->RideHeightSpecsFront, TireConfig->DiameterFront * 50.f, DeltaTime);
	}
	
	// Rear Suspension
	for (const auto& Suspension : OwningPawn->GetRearSuspension())
	{
		UpdateSuspensionData(Suspension, SuspensionConfig->RideHeightSpecsRear, TireConfig->DiameterRear * 50.f, DeltaTime);
	}
}

void USuspensionComponent::UpdateSuspensionData(
	const TObjectPtr<USceneComponent> Suspension,
	const float RideHeight,
	const float TireRadius,
	const float DeltaTime
) {
	const FVector Start = Suspension->GetComponentLocation();	 // Ride height is same as rear (for now)
	const FVector End = Start + (-Suspension->GetUpVector() * (RideHeight + TireRadius));
	
	FHitResult Hit;
	GetWorld()->LineTraceSingleByProfile(Hit, Start, End, "Chassis");
		
	DrawDebugDirectionalArrow(
		GetWorld(),
		Hit.TraceStart,
		Hit.bBlockingHit ? Hit.Location : Hit.TraceEnd,
		100.f,
		Hit.bBlockingHit ? FColor::Green : FColor::Red,
		false,
		-1.f,
		SDPG_Foreground,
		5.0f
	);
	
	float MaxTravel = OwningPawn->GetSuspensionConfig()->TravelSpecsFront;
	
	SuspensionData[Suspension].Compression = RideHeight - Hit.Distance;
	UE_LOGFMT(LogSierra, Log, "Compression: {0}", SuspensionData[Suspension].Compression);
	SuspensionData[Suspension].Speed = (SuspensionData[Suspension].HitDistance - Hit.Distance) / DeltaTime;
	UE_LOGFMT(LogSierra, Log, "Speed: {0}", SuspensionData[Suspension].Speed);
	SuspensionData[Suspension].HitDistance = Hit.Distance;
	UE_LOGFMT(LogSierra, Log, "HitDistance: {0}", SuspensionData[Suspension].HitDistance);
	SuspensionData[Suspension].HitNormal = Hit.Normal;
	UE_LOGFMT(LogSierra, Log, "HitNormal: {0}", SuspensionData[Suspension].HitNormal.ToString());
	SuspensionData[Suspension].bGrounded = Hit.bBlockingHit;
	UE_LOGFMT(LogSierra, Log, "Grounded: {0}", SuspensionData[Suspension].bGrounded);
	SuspensionData[Suspension].VisualOffset = FMath::Max(Hit.Distance - TireRadius, -MaxTravel);
	UE_LOGFMT(LogSierra, Log, "Offset: {0}", SuspensionData[Suspension].VisualOffset);
}

