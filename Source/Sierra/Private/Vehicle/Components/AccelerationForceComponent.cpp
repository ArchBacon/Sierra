// Copyright (c) 2026, Christian Delicaat. All rights reserved.

#include "Vehicle/Components/AccelerationForceComponent.h"

#include "Kismet/KismetMathLibrary.h"
#include "Sierra/Sierra.h"
#include "Vehicle/ChassisComponent.h"
#include "Vehicle/PhysicsVehicle.h"
#include "Vehicle/SuspensionComponent.h"
#include "Vehicle/Components/TransmissionForceComponent.h"
#include "Vehicle/Config/AerodynamicsConfig.h"
#include "Vehicle/Config/BrakesConfig.h"
#include "Vehicle/Config/EngineConfig.h"
#include "Vehicle/Config/TireConfig.h"
#include "Vehicle/Config/TransmissionConfig.h"

UAccelerationForceComponent::UAccelerationForceComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UAccelerationForceComponent::BeginPlay()
{
	Super::BeginPlay();

	Vehicle = Cast<APhysicsVehicle>(GetOwner());

	const auto VehicleConfig = Vehicle->GetConfig();
	EngineConfig = VehicleConfig->EngineConfig;
	TransmissionConfig = VehicleConfig->TransmissionConfig;
	TireConfig = VehicleConfig->TireConfig;
	AerodynamicsConfig = VehicleConfig->AerodynamicsConfig;
	BrakesConfig = VehicleConfig->BrakesConfig;
	TransmissionComponent = Vehicle->GetTransmissionComponent();

	DragFactor = 0.5f * AerodynamicsConfig->DragCoefficient * Vehicle->GetChassis()->FrontalArea * 1.29f;
}

void UAccelerationForceComponent::TickComponent(const float DeltaTime, const ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	const float KmH = 0.036f * FVector::DotProduct(
		Vehicle->GetChassis()->GetPhysicsLinearVelocity(), 
		Vehicle->GetChassis()->GetRightVector()
	);

	// Update values
	UpdateRPM();
	ApplyDriveForce();
	
	// Resisting forces
	ApplyDrag();
	ApplyRollingResistance();
	
	// Brake
	if (
		(UKismetMathLibrary::NearlyEqual_FloatFloat(ThrottleInput, 0.0f) && TransmissionComponent->IsInNeutralGear())
		|| (ThrottleInput > 0.0f && TransmissionComponent->IsInReverseGear())
		|| (ThrottleInput < 0.0f && TransmissionComponent->IsInForwardGear())
	) {
		ApplyBrakes(KmH);
		GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Red, "Braking");
	}
}

float UAccelerationForceComponent::GetSpeed() const
{
	return 0.036f * FVector::DotProduct(
		Vehicle->GetChassis()->GetPhysicsLinearVelocity(), 
		Vehicle->GetChassis()->GetRightVector()
	);
}

void UAccelerationForceComponent::ApplyRollingResistance() const
{
	for (const auto Suspension : Vehicle->GetSuspension())
	{
		const float WheelRadius = (Suspension->bIsFront ? TireConfig->DiameterFront : TireConfig->DiameterRear) / 2.0f * 100.f;
		const FVector WheelForward = Suspension->GetForwardVector();
		const FVector WheelVelocity = Vehicle->GetChassis()->GetPhysicsLinearVelocityAtPoint(Suspension->GetComponentLocation());

		const float AngularSpeed = FVector::DotProduct(WheelVelocity, WheelForward) / WheelRadius;
		const FVector RollingResistance = -TireConfig->RollingResistanceScalarVSpeedCurve->GetFloatValue(FMath::Abs(AngularSpeed)) * WheelForward;

		Vehicle->GetChassis()->AddForceAtLocation(RollingResistance * 100.f, Suspension->GetComponentLocation());

		// Debug
		const FVector RRStart = Vehicle->GetActorLocation() - (Vehicle->GetActorForwardVector() * 10.f);
		DrawDebugDirectionalArrow(GetWorld(), RRStart, RRStart + RollingResistance, 50.f, FColor::Black, false, -1, 1, 2.f);
	}
}

void UAccelerationForceComponent::ApplyDrag() const
{
	const FVector Velocity = Vehicle->GetChassis()->GetPhysicsLinearVelocity();
	const FVector VelocityMS = Velocity / 100.f;
	const FVector Drag = -DragFactor * VelocityMS * VelocityMS.Length();

	Vehicle->GetChassis()->AddForce(Drag * 100.f);

	// Debug
	const FVector DragStart = Vehicle->GetActorLocation() + (Vehicle->GetActorForwardVector() * 10.f);
	DrawDebugDirectionalArrow(GetWorld(), DragStart, DragStart + Drag, 50.f, FColor::Orange, false, -1, 1, 3.f);
}

void UAccelerationForceComponent::ApplyDriveForce() const
{
	const FVector Velocity = Vehicle->GetChassis()->GetPhysicsLinearVelocity();
	float Throttle = (RPM >= EngineConfig->MaxRpm) ? 0 : ThrottleInput;
	
	const float WheelRadius = TireConfig->DiameterRear / 2.0f;
	const auto AngularSpeedL = Vehicle->GetRearSuspension()[0]->GetWheelAngularSpeed();
	const auto AngularSpeedR = Vehicle->GetRearSuspension()[1]->GetWheelAngularSpeed();
	
	// Drive force
	const float EngineTorque = Throttle * EngineConfig->TorqueCurve->GetFloatValue(RPM)  * 1.356f;
	const float DriveTorque = EngineTorque * TransmissionComponent->GetDriveTrainMultiplier();
	const float DriveForce = DriveTorque / WheelRadius;
	
	const float ThrottleLift = 1.0f - FMath::Abs(Throttle);
	const float EngineBrakingScalar = EngineConfig->EngineBrakingVsGearCurve ? EngineConfig->EngineBrakingVsGearCurve->GetFloatValue(TransmissionComponent->GetActiveGear()) : 1.f;
	const float FrictionTorque = ThrottleLift * EngineBrakingScalar * EngineConfig->EngineFrictionTorqueCurve->GetFloatValue(RPM) * 1.356f;
	const float ResistanceTorque = ThrottleLift * EngineBrakingScalar * EngineConfig->EngineResistance * 1.356f;
	// Engine braking must oppose motion direction — flip sign in reverse so it decelerates rather than accelerates
	const float GearSign = TransmissionComponent->IsInReverseGear() ? -1.f : 1.f;
	const float FrictionForce = FrictionTorque * TransmissionComponent->GetDriveTrainMultiplier() / WheelRadius * GearSign;
	const float ResistanceForce = ResistanceTorque * TransmissionComponent->GetDriveTrainMultiplier() / WheelRadius * GearSign;
	float TotalForce = DriveForce + (FrictionForce + ResistanceForce * 0.5f * (TransmissionComponent->IsInReverseGear() ? 0.5f : 1.0f));

	// Prevent engine braking from moving a nearly stationary car
	if (FMath::Abs(FVector::DotProduct(Vehicle->GetActorRightVector(), Velocity)) < 10.f && FMath::IsNearlyZero(Throttle, 0.01f))
		TotalForce = 0.0f;

	const float SpeedDiff = AngularSpeedL - AngularSpeedR;
	const float LockingTorque = SpeedDiff * TransmissionConfig->DifferentialRear;

	const auto Suspension = Vehicle->GetRearSuspension();
	const FVector TractionL = Suspension[0]->GetForwardVector() * (TotalForce * 0.5f - LockingTorque);
	const FVector TractionR = Suspension[1]->GetForwardVector() * (TotalForce * 0.5f + LockingTorque);

	Vehicle->GetChassis()->AddForceAtLocation(TractionL * 100.f, Suspension[0]->GetComponentLocation());
	Vehicle->GetChassis()->AddForceAtLocation(TractionR * 100.f, Suspension[1]->GetComponentLocation());
	
	// Debug
	DrawDebugDirectionalArrow(GetWorld(), Suspension[0]->GetComponentLocation(), Suspension[0]->GetComponentLocation() + TractionL, 50.f, FColor::Green, false, -1, 1, 2.f);
	DrawDebugDirectionalArrow(GetWorld(), Suspension[1]->GetComponentLocation(), Suspension[1]->GetComponentLocation() + TractionR, 50.f, FColor::Green, false, -1, 1, 2.f);
}

void UAccelerationForceComponent::ApplyBrakes(const float Speed) const
{
	const bool bIsReversing = Speed < 0.0f;
	const int ForceDirection = -FMath::Sign(Speed);
	
	for (const auto Suspension : Vehicle->GetFrontSuspension())
	{
		const float WheelRadius = TireConfig->DiameterFront / 2.0f;
		const float BrakeForce = (BrakesConfig->FrontBrakeTorqueVsSpeedCurve->GetFloatValue(Speed) + BrakesConfig->FrontBrakeOffset + BrakesConfig->BackwardsExtraBrakeStrength * bIsReversing) / WheelRadius;

		Vehicle->GetChassis()->AddForceAtLocation(Suspension->GetForwardVector() * ForceDirection * BrakeForce * 100.f, Suspension->GetComponentLocation());
		DrawDebugDirectionalArrow(GetWorld(), Suspension->GetComponentLocation(), Suspension->GetComponentLocation() + Suspension->GetForwardVector() * ForceDirection * BrakeForce, 50.f, FColor::Red, false, -1, 1, 2.f);
	}

	for (const auto Suspension : Vehicle->GetRearSuspension())
	{
		const float WheelRadius = TireConfig->DiameterRear / 2.0f;
		const float BrakeForce = (BrakesConfig->RearBrakeTorque + BrakesConfig->RearBrakeOffset + BrakesConfig->BackwardsExtraBrakeStrength * bIsReversing) / WheelRadius;

		Vehicle->GetChassis()->AddForceAtLocation(Suspension->GetForwardVector() * ForceDirection * BrakeForce * 100.f, Suspension->GetComponentLocation());
		DrawDebugDirectionalArrow(GetWorld(), Suspension->GetComponentLocation(), Suspension->GetComponentLocation() + Suspension->GetForwardVector() * ForceDirection * BrakeForce, 50.f, FColor::Red, false, -1, 1, 2.f);
	}
}

void UAccelerationForceComponent::UpdateRPM()
{
	const float Multiplier = TransmissionComponent->GetDriveTrainMultiplier();
	float AngularSpeedL = Vehicle->GetRearSuspension()[0]->GetWheelAngularSpeed();
	AngularSpeedL += FMath::Sign(AngularSpeedL) * 15.f;
	float AngularSpeedR = Vehicle->GetRearSuspension()[1]->GetWheelAngularSpeed();
	AngularSpeedR += FMath::Sign(AngularSpeedR) * 15.f;
	
	const float AngularSpeed = FMath::Abs(AngularSpeedL) * TransmissionConfig->DifferentialRear + FMath::Abs(AngularSpeedR) * (1.0f - TransmissionConfig->DifferentialRear);
	RPM = FMath::Max(EngineConfig->Idle, (AngularSpeed) * Multiplier * (60.f / TWO_PI));
}
