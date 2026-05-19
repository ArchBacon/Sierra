// Copyright (c) 2026, Christian Delicaat. All rights reserved.

#include "Vehicle/ChassisComponent.h"

#include "Kismet/KismetMathLibrary.h"
#include "Vehicle/PhysicsVehicle.h"
#include "Vehicle/Config/AerodynamicsConfig.h"
#include "Vehicle/Config/ChassisConfig.h"
#include "Vehicle/Config/EngineConfig.h"
#include "Vehicle/Config/TireConfig.h"
#include "Vehicle/Config/TransmissionConfig.h"

UChassisComponent::UChassisComponent() = default;

void UChassisComponent::BeginPlay()
{
	Super::BeginPlay();
	Vehicle = Cast<APhysicsVehicle>(GetOwner());

	const auto VehicleConfig = Vehicle->GetConfig();
	ChassisConfig = VehicleConfig->ChassisConfig;
	SuspensionConfig = VehicleConfig->SuspensionConfig;

	{   // Calculate frontal area
		const auto TireConfig = VehicleConfig->TireConfig;
		const auto AeroConfig = VehicleConfig->AerodynamicsConfig;
		const auto TransmissionConfig = VehicleConfig->TransmissionConfig;
		const auto EngineConfig = VehicleConfig->EngineConfig;

		const float WheelRadius_m = TireConfig->DiameterRear / 2.0f;         // m
		const float MaxSpeed = AeroConfig->TopSpeed / 3.6f;                   // km/h -> m/s
		const float AngularSpeed = MaxSpeed / WheelRadius_m;                  // rad/s

		const FGearData& TopGearData = TransmissionConfig->Gears[TransmissionConfig->TopGear + 1];
		const float TopRPM = AngularSpeed * TopGearData.GearRatio * TransmissionConfig->FinalGear * (60.f / TWO_PI);

		const float EngineTorque = EngineConfig->TorqueCurve->GetFloatValue(TopRPM) * 1.356f;  // Nm
		const float DriveForce = EngineTorque * TopGearData.GearRatio * TransmissionConfig->FinalGear * TopGearData.GearEfficiency / WheelRadius_m;  // N

		// FrontalArea (m²) so that aerodynamic drag equals drive force at top speed
		FrontalArea = DriveForce / (0.5f * AeroConfig->DragCoefficient * 1.29f * MaxSpeed * MaxSpeed);
	}
}

void UChassisComponent::UpdateCenterOfMass() const
{
	const float ChassisHeight = GetStaticMesh()->GetBoundingBox().GetSize().Z;

	const FVector CoG = ChassisConfig->InertiaBoxTumbling * 100.f * ChassisConfig->TumbleLocalCOG;
	FVector CenterOfMass;
	CenterOfMass.X = CoG.X;
	CenterOfMass.Y = CoG.Z;
	CenterOfMass.Z = -(ChassisHeight / 2.0f) + CoG.Y;

	Vehicle->GetChassis()->SetCenterOfMass(CenterOfMass);
}
