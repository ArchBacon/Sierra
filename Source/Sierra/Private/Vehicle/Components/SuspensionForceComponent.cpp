// Copyright (c) 2026, Christian Delicaat. All rights reserved.

#include "Vehicle/Components/SuspensionForceComponent.h"

#include "Vehicle/ChassisComponent.h"
#include "Vehicle/PhysicsVehicle.h"
#include "Vehicle/SuspensionComponent.h"
#include "Vehicle/Config/SuspensionConfig.h"
#include "Vehicle/Config/TireConfig.h"

USuspensionForceComponent::USuspensionForceComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void USuspensionForceComponent::BeginPlay()
{
	Super::BeginPlay();

	Vehicle = Cast<APhysicsVehicle>(GetOwner());
	
	const auto VehicleConfig = Vehicle->GetConfig();
	ChassisConfig = VehicleConfig->ChassisConfig;
	TireConfig = VehicleConfig->TireConfig;
	SuspensionConfig = VehicleConfig->SuspensionConfig;
}

void USuspensionForceComponent::TickComponent(
	const float DeltaTime,
	const ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction
) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	const auto FrontSuspension = Vehicle->GetFrontSuspension();
	const auto SuspensionForcesFront = CalculateFrontSuspension(
		FrontSuspension[0], 
		FrontSuspension[1],
		DeltaTime,
		true
	);
	FrontSuspension[0]->CompressionDistance = SuspensionForcesFront.CompressionDistanceL;
	FrontSuspension[1]->CompressionDistance = SuspensionForcesFront.CompressionDistanceR;
	
	const auto RearSuspension = Vehicle->GetRearSuspension();
	const auto SuspensionForcesRear = CalculateFrontSuspension(
		RearSuspension[0], 
		RearSuspension[1], 
		DeltaTime,
		false
	);
	RearSuspension[0]->CompressionDistance = SuspensionForcesRear.CompressionDistanceL;
	RearSuspension[1]->CompressionDistance = SuspensionForcesRear.CompressionDistanceR;


	// Apply forces
	// DrawDebugDirectionalArrow(GetWorld(), FrontSuspension[0]->GetComponentLocation(), FrontSuspension[0]->GetComponentLocation() + FrontSuspension[0]->GetUpVector() * SuspensionForcesFront.ForceLeft * 0.02f, 50.f, FColor::Yellow, false, -1, 1, 2.f);
	Vehicle->GetChassis()->AddForceAtLocation(SuspensionForcesFront.ForceLeft * 100.f, FrontSuspension[0]->GetComponentLocation());
	FrontSuspension[0]->UpdateWheelPosition();
	// DrawDebugDirectionalArrow(GetWorld(), FrontSuspension[1]->GetComponentLocation(), FrontSuspension[1]->GetComponentLocation() + FrontSuspension[1]->GetUpVector() * SuspensionForcesFront.ForceRight * 0.02f, 50.f, FColor::Yellow, false, -1, 1, 2.f);
	Vehicle->GetChassis()->AddForceAtLocation(SuspensionForcesFront.ForceRight * 100.f, FrontSuspension[1]->GetComponentLocation());
	FrontSuspension[1]->UpdateWheelPosition();
	
	// DrawDebugDirectionalArrow(GetWorld(), RearSuspension[0]->GetComponentLocation(), RearSuspension[0]->GetComponentLocation() + RearSuspension[0]->GetUpVector() * SuspensionForcesRear.ForceLeft * 0.02f, 50.f, FColor::Yellow, false, -1, 1, 2.f);
	Vehicle->GetChassis()->AddForceAtLocation(SuspensionForcesRear.ForceLeft * 100.f, RearSuspension[0]->GetComponentLocation());
	RearSuspension[0]->UpdateWheelPosition();
	// DrawDebugDirectionalArrow(GetWorld(), RearSuspension[1]->GetComponentLocation(), RearSuspension[1]->GetComponentLocation() + RearSuspension[1]->GetUpVector() * SuspensionForcesRear.ForceRight * 0.02f, 50.f, FColor::Yellow, false, -1, 1, 2.f);
	Vehicle->GetChassis()->AddForceAtLocation(SuspensionForcesRear.ForceRight * 100.f, RearSuspension[1]->GetComponentLocation());
	RearSuspension[1]->UpdateWheelPosition();
}

FAxleForces USuspensionForceComponent::CalculateFrontSuspension(
	const TObjectPtr<USuspensionComponent> SuspensionLeft,
	const TObjectPtr<USuspensionComponent> SuspensionRight,
	const float DeltaTime,
	const bool bIsFront
) const {
	const auto SpringForcesL = CalculateSpringForce(SuspensionLeft, DeltaTime);
	const auto DamperForceL = CalculateDamperForce(SpringForcesL.ContactSpeed, true);
	
	const auto SpringForcesR = CalculateSpringForce(SuspensionRight, DeltaTime);
	const auto DamperForceR = CalculateDamperForce(SpringForcesR.ContactSpeed, true);
	
	const float SwaySpec = bIsFront ? SuspensionConfig->SwaySpecsFront : SuspensionConfig->SwaySpecsRear;
	const float SwayForce = SwaySpec * (SpringForcesL.CompressionDistance - SpringForcesR.CompressionDistance);
	
	const float ForceMagL = -(SpringForcesL.SpringForce + DamperForceL) * FVector::DotProduct(SuspensionLeft->GetUpVector(), SpringForcesL.SurfaceNormal);
	const float ForceMagR = -(SpringForcesR.SpringForce + DamperForceR) * FVector::DotProduct(SuspensionRight->GetUpVector(), SpringForcesR.SurfaceNormal);

	return FAxleForces
	{
		.ForceLeft = SuspensionLeft->GetUpVector() * (ForceMagL + SwayForce),
		.CompressionDistanceL = SpringForcesL.CompressionDistance,

		.ForceRight = SuspensionRight->GetUpVector() * (ForceMagR - SwayForce),
		.CompressionDistanceR = SpringForcesR.CompressionDistance,
	};
}

FSpringForces USuspensionForceComponent::CalculateSpringForce(
	const TObjectPtr<USuspensionComponent> Suspension,
	const float DeltaTime
) const {
	const auto Specs = SuspensionConfig->GetSpringSpecs(Suspension->bIsFront);
	const float TireRadius = (Suspension->bIsFront ? TireConfig->DiameterFront : TireConfig->DiameterRear) * 100.0f / 2.0f;
	const float TraceDistance = Specs.TravelSpecs + TireRadius;
	
	const FVector End = Suspension->GetComponentLocation(); // Point attached to the wheel
	const FVector Start = End + Suspension->GetUpVector() * Specs.TravelSpecs; // Point attached to chassis
	
	FHitResult Hit;
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(Vehicle); // ignore self
	GetWorld()->LineTraceSingleByProfile(
		Hit, 
		Start, 
		Start + -Suspension->GetUpVector() * TraceDistance,
		"Chassis",
		CollisionParams
	);
	Suspension->bIsGrounded = Hit.bBlockingHit;
	
	// Debug draw suspension trace
	// DrawDebugDirectionalArrow(GetWorld(), Hit.bBlockingHit ? Hit.ImpactPoint : Hit.TraceStart, Hit.TraceEnd, 50.f, FColor::Green, false, -1, 1, 1.f);
	// DrawDebugDirectionalArrow(GetWorld(), Hit.TraceStart, Hit.bBlockingHit ? Hit.ImpactPoint : Hit.TraceEnd, 50.f, FColor::Red, false, -1, 1, 2.f);

	// F=-K·(1+p·x)·x	Hooke's law (F=Kx) extended for linearly progressive spring rate
	const float CompressionDistance = FMath::Min(TraceDistance - Hit.Distance, Specs.TravelSpecs) * Hit.bBlockingHit;
	const float SpringRate = Specs.SpringSpecs * (1.0f + Specs.SpringProgression * CompressionDistance);
	const float SpringForce = -SpringRate * CompressionDistance;
	const float ContactSpeed = (CompressionDistance - Suspension->CompressionDistance) / DeltaTime;
	
	// Debug draw spring compression
	// DrawDebugDirectionalArrow(GetWorld(), Start, Start + -Suspension->GetUpVector() * (Specs.TravelSpecs - CompressionDistance), 50.f, FColor::Orange, false, -1, 1, 5.f);
	
	return FSpringForces
	{
		.SpringRate = SpringRate,
		.SpringForce = SpringForce,
		.ContactSpeed = ContactSpeed,
		.CompressionDistance = CompressionDistance,
		.SurfaceNormal = Hit.ImpactNormal,
	};
}

float USuspensionForceComponent::CalculateDamperForce(const float ContactSpeed, const bool bIsFront) const
{
	const auto Specs = SuspensionConfig->GetDamperSpecs(bIsFront);

	// ±(c·v^d) damping force
	// ContactSpeed is cm/s -> m/s.
	const float Speed = FMath::Abs(ContactSpeed) / 100.0f;

	float DamperForce = 0.0f;
	if (ContactSpeed > 0.0f) // Compression — opposes jounce, same direction as spring (negative)
	{
		const float BlowoutThreshold = Specs.ShockValving * Specs.ShockSpecs * FMath::Pow(Specs.ShockBlowOut, Specs.ShockDigression * 100.f);
		DamperForce = -(Specs.ShockValving * Specs.ShockSpecs) * FMath::Pow(Speed, Specs.ShockDigression);
		DamperForce = FMath::Max(DamperForce, -BlowoutThreshold);
	}
	else if (ContactSpeed < 0.0f) // Extension — opposes rebound, reduces lift (positive)
	{
		const float BlowoutThreshold = Specs.ShockValving * Specs.ShockExtSpecs * FMath::Pow(Specs.ShockBlowOut, Specs.ShockDigression * 100.f);
		DamperForce = (Specs.ShockValving * Specs.ShockExtSpecs) * FMath::Pow(Speed, Specs.ShockDigression);
		DamperForce = FMath::Min(DamperForce, BlowoutThreshold);
	}

	return DamperForce;
}
