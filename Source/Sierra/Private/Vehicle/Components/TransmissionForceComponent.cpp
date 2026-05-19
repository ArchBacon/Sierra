// Copyright (c) 2026, Christian Delicaat. All rights reserved.

#include "Vehicle/Components/TransmissionForceComponent.h"

#include "Kismet/KismetMathLibrary.h"
#include "Vehicle/ChassisComponent.h"
#include "Vehicle/PhysicsVehicle.h"
#include "Vehicle/Components/AccelerationForceComponent.h"
#include "Vehicle/Config/TransmissionConfig.h"

UTransmissionForceComponent::UTransmissionForceComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTransmissionForceComponent::BeginPlay()
{
	Super::BeginPlay();

	Vehicle = Cast<APhysicsVehicle>(GetOwner());

	const auto VehicleConfig = Vehicle->GetConfig();
	TransmissionConfig = VehicleConfig->TransmissionConfig;
	AccelComp = Vehicle->GetAccelerationComponent();
	
	TopGear = TransmissionConfig->TopGear + 1; // +1 to offset for reverse
}

void UTransmissionForceComponent::TickComponent(
	const float DeltaTime,
	const ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction
) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	const FVector Velocity = Vehicle->GetChassis()->GetPhysicsLinearVelocity();
	const FVector Forward = Vehicle->GetChassis()->GetRightVector();
	const float KmH = FVector::DotProduct(Velocity, Forward) * 0.036f;
	const float RPM = AccelComp->GetRPM();
	
	const auto GearData = TransmissionConfig->Gears[Gear];
	
	// Check for auto up-shifting
	if (UKismetMathLibrary::NearlyEqual_FloatFloat(KmH, 0.0f))
	{
		Gear = NeutralGear;
	}
	
	if (ThrottleInput > 0.0f && KmH >= 0.001f) // We want to drive forward
	{
		// Shift by speed
		if (Gear == NeutralGear + 1)
		{
			if (KmH >= GearData.GearUpSpeed * 3.6f)
			{
				Gear++;
			}
		}
		// Shift by RPM
		else if (RPM >= GearData.GearUpRPM && Gear != TopGear)
		{
			Gear++;
		}
	}
	else if (RPM <= GearData.GearDownRPM && KmH <= (TransmissionConfig->Gears[Gear - 1].GearUpSpeed * 3.6f))
	{
		Gear--;
	}
	else if (ThrottleInput < 0.0f) // We want to reverse
	{
		if (KmH <= 0.0f)
		{
			Gear = ReverseGear;
		}
	}
	
	if (KmH > 0.0f && Gear == ReverseGear)
	{
		Gear = NeutralGear;
	}
	if (KmH < 0.0f && Gear > NeutralGear)
	{
		Gear = NeutralGear;
	}
	
	Gear = FMath::Clamp(Gear, ReverseGear, TopGear);
}

float UTransmissionForceComponent::GetDriveTrainMultiplier() const
{
	const auto GearData = TransmissionConfig->Gears[Gear];
	const float Multiplier = GearData.GearEfficiency
		* GearData.GearRatio
		* TransmissionConfig->FinalGear;
	
	return Multiplier;
}

