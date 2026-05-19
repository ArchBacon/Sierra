// Copyright (c) 2026, Christian Delicaat. All rights reserved.

#include "Vehicle/SuspensionComponent.h"

#include "Sierra/Sierra.h"
#include "Vehicle/ChassisComponent.h"
#include "Vehicle/PhysicsVehicle.h"
#include "Vehicle/Config/SuspensionConfig.h"
#include "Vehicle/Config/TireConfig.h"
#include "Vehicle/Config/VehicleConfig.h"

USuspensionComponent::USuspensionComponent() = default;

void USuspensionComponent::BeginPlay()
{
	Super::BeginPlay();
	
	Vehicle = Cast<APhysicsVehicle>(GetOwner());
	
	const auto VehicleConfig = Vehicle->GetConfig();
	TireConfig = VehicleConfig->TireConfig;
}

FVector USuspensionComponent::GetChassisAttachPoint(
	const TObjectPtr<UVehicleConfig> VehicleConfig,
	FVector AttachPoint,
	const bool bIsFront
) {
	const float TravelSpec = bIsFront ? VehicleConfig->SuspensionConfig->TravelSpecsFront : VehicleConfig->SuspensionConfig->TravelSpecsRear;
	const float TireDiameter = bIsFront ? VehicleConfig->TireConfig->DiameterFront : VehicleConfig->TireConfig->DiameterRear;
	const float TireRadius = TireDiameter * 50.f;  // we use 50 because the diameter is in m, and we need the radius in cm 
	
	return 
	{
		AttachPoint.X,
		AttachPoint.Y,
		TravelSpec - TireRadius
	};
}

void USuspensionComponent::UpdateWheelPosition() const
{
	if (!Wheel)
	{
		UE_LOGFMT(LogSierra, Warning, "Wheel is null on suspension {0}", GetName());
		return;	
	}
	
	Wheel->SetRelativeLocation(-GetUpVector() * (Travel - CompressionDistance));
}

float USuspensionComponent::GetWheelAngularSpeed() const
{
	const float Diameter = bIsFront ? TireConfig->DiameterFront : TireConfig->DiameterRear;
	const float Radius = Diameter / 2.0f * 100.f;
	const auto Velocity = Vehicle->GetChassis()->GetPhysicsLinearVelocityAtPoint(GetComponentLocation());
	
	return FVector::DotProduct(Velocity, GetForwardVector()) / Radius;
}
