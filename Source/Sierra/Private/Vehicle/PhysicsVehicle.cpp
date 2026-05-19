// Copyright (c) 2026, Christian Delicaat. All rights reserved.

#include "Vehicle/PhysicsVehicle.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Sierra/Sierra.h"
#include "Vehicle/ChassisComponent.h"
#include "Vehicle/SuspensionComponent.h"
#include "Vehicle/Components/AccelerationForceComponent.h"
#include "Vehicle/Components/SuspensionForceComponent.h"
#include "Vehicle/Components/TransmissionForceComponent.h"
#include "Vehicle/Config/SuspensionConfig.h"

APhysicsVehicle::APhysicsVehicle()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;
	
	// Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	// RootComponent = Root;
	
	Chassis = CreateDefaultSubobject<UChassisComponent>(TEXT("Chassis"));
	// Chassis->SetupAttachment(RootComponent);
	Chassis->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
	Chassis->SetCollisionProfileName(TEXT("Chassis"));
	RootComponent = Chassis;
	
	// Front Left
	SuspensionFrontLeft = CreateDefaultSubobject<USuspensionComponent>(TEXT("Suspension_FL"));
	SuspensionFrontLeft->SetupAttachment(Chassis);
	SuspensionFrontLeft->SetRelativeRotation(FRotator(0.0f, 90.0f, 0.0f));
	SuspensionFrontLeft->bIsFront = true;
	TireFrontLeft = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tire_FL"));
	TireFrontLeft->SetupAttachment(SuspensionFrontLeft);
	TireFrontLeft->SetCollisionProfileName(TEXT("Wheel"));
	TireFrontLeft->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
	TireFrontLeft->SetRelativeScale3D(FVector(1.0f, 1.0f, 1.0f));
	WheelFrontLeft = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wheel_FL"));
	WheelFrontLeft->SetupAttachment(TireFrontLeft);
	WheelFrontLeft->SetCollisionProfileName(TEXT("Wheel"));

	// Front Right
	SuspensionFrontRight = CreateDefaultSubobject<USuspensionComponent>(TEXT("Suspension_FR"));
	SuspensionFrontRight->SetupAttachment(Chassis);
	SuspensionFrontRight->SetRelativeRotation(FRotator(0.0f, 90.0f, 0.0f));
	SuspensionFrontRight->bIsFront = true;
	TireFrontRight = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tire_FR"));
	TireFrontRight->SetupAttachment(SuspensionFrontRight);
	TireFrontRight->SetCollisionProfileName(TEXT("Wheel"));
	TireFrontRight->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
	TireFrontRight->SetRelativeScale3D(FVector(-1.0f, 1.0f, 1.0f));
	WheelFrontRight = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wheel_FR"));
	WheelFrontRight->SetupAttachment(TireFrontRight);
	WheelFrontRight->SetCollisionProfileName(TEXT("Wheel"));

	// Rear Left
	SuspensionRearLeft = CreateDefaultSubobject<USuspensionComponent>(TEXT("Suspension_RL"));
	SuspensionRearLeft->SetupAttachment(Chassis);
	SuspensionRearLeft->SetRelativeRotation(FRotator(0.0f, 90.0f, 0.0f));
	SuspensionRearLeft->bIsFront = false;
	TireRearLeft = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tire_RL"));
	TireRearLeft->SetupAttachment(SuspensionRearLeft);
	TireRearLeft->SetCollisionProfileName(TEXT("Wheel"));
	TireRearLeft->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
	TireRearLeft->SetRelativeScale3D(FVector(1.0f, 1.0f, 1.0f));
	WheelRearLeft = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wheel_RL"));
	WheelRearLeft->SetupAttachment(TireRearLeft);
	WheelRearLeft->SetCollisionProfileName(TEXT("Wheel"));

	// Rear Right
	SuspensionRearRight = CreateDefaultSubobject<USuspensionComponent>(TEXT("Suspension_RR"));
	SuspensionRearRight->SetupAttachment(Chassis);
	SuspensionRearRight->SetRelativeRotation(FRotator(0.0f, 90.0f, 0.0f));
	SuspensionRearRight->bIsFront = false;
	TireRearRight = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tire_RR"));
	TireRearRight->SetupAttachment(SuspensionRearRight);
	TireRearRight->SetCollisionProfileName(TEXT("Wheel"));
	TireRearRight->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
	TireRearRight->SetRelativeScale3D(FVector(-1.0f, 1.0f, 1.0f));
	WheelRearRight = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wheel_RR"));
	WheelRearRight->SetupAttachment(TireRearRight);
	WheelRearRight->SetCollisionProfileName(TEXT("Wheel"));
	
	// Components
	SuspensionComponent = CreateDefaultSubobject<USuspensionForceComponent>(TEXT("SuspensionComponent"));
	AccelerationComponent = CreateDefaultSubobject<UAccelerationForceComponent>(TEXT("AccelerationComponent"));
	TransmissionComponent = CreateDefaultSubobject<UTransmissionForceComponent>(TEXT("TransmissionComponent"));
}

void APhysicsVehicle::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	if (!VehicleConfig)
	{
		UE_LOGFMT(LogSierra, Warning, "VehicleConfig is null");
		return;
	}
	
	if (!VehicleConfig->SuspensionConfig)
	{
		UE_LOGFMT(LogSierra, Warning, "SuspensionConfig is null");
		return;
	}
	
	// Chassis
	Chassis->SetSimulatePhysics(true);
	Chassis->SetMassOverrideInKg(NAME_None, 1576.f);
	Chassis->SetStaticMesh(ChassisMesh);
	
	SuspensionFrontLeft->Wheel = TireFrontLeft;
	SuspensionFrontRight->Wheel = TireFrontRight;
	SuspensionRearLeft->Wheel = TireRearLeft;
	SuspensionRearRight->Wheel = TireRearRight;

	// Front Left
	SuspensionFrontLeft->SetRelativeLocation(USuspensionComponent::GetChassisAttachPoint(
		VehicleConfig,
		VehicleConfig->SuspensionConfig->AttachPoints[0],
		true)
	);
	SuspensionFrontLeft->Travel = VehicleConfig->SuspensionConfig->TravelSpecsFront;
	SuspensionFrontLeft->UpdateWheelPosition();
	TireFrontLeft->SetStaticMesh(TireMesh);
	WheelFrontLeft->SetStaticMesh(WheelMesh);

	// Front Right
	SuspensionFrontRight->SetRelativeLocation(USuspensionComponent::GetChassisAttachPoint(
		VehicleConfig,
		VehicleConfig->SuspensionConfig->AttachPoints[1],
		true)
	);
	SuspensionFrontRight->Travel = VehicleConfig->SuspensionConfig->TravelSpecsFront;
	SuspensionFrontRight->UpdateWheelPosition();
	TireFrontRight->SetStaticMesh(TireMesh);
	WheelFrontRight->SetStaticMesh(WheelMesh);

	// Rear Left
	SuspensionRearLeft->SetRelativeLocation(USuspensionComponent::GetChassisAttachPoint(
		VehicleConfig,
		VehicleConfig->SuspensionConfig->AttachPoints[2],
		false)
	);
	SuspensionRearLeft->Travel = VehicleConfig->SuspensionConfig->TravelSpecsRear;
	SuspensionRearLeft->UpdateWheelPosition();
	TireRearLeft->SetStaticMesh(TireMesh);
	WheelRearLeft->SetStaticMesh(WheelMesh);

	// Rear Right
	SuspensionRearRight->SetRelativeLocation(USuspensionComponent::GetChassisAttachPoint(
		VehicleConfig,
		VehicleConfig->SuspensionConfig->AttachPoints[3],
		false)
	);
	SuspensionRearRight->Travel = VehicleConfig->SuspensionConfig->TravelSpecsRear;
	SuspensionRearRight->UpdateWheelPosition();;
	TireRearRight->SetStaticMesh(TireMesh);
	WheelRearRight->SetStaticMesh(WheelMesh);
}

void APhysicsVehicle::BeginPlay()
{
	Super::BeginPlay();
	
	Chassis->UpdateCenterOfMass();
}

void APhysicsVehicle::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APhysicsVehicle::NotifyControllerChanged()
{
	Super::NotifyControllerChanged();
	
	// Add Input Mapping Context
	if (const APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

void APhysicsVehicle::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(ThrottleAction, ETriggerEvent::Triggered, this, &APhysicsVehicle::Throttle);
		EnhancedInputComponent->BindAction(ThrottleAction, ETriggerEvent::Completed, this, &APhysicsVehicle::ThrottleEnd);
	}
}

void APhysicsVehicle::Throttle(const FInputActionValue& Value)
{
	AccelerationComponent->ThrottleInput = Value.Get<float>();
	TransmissionComponent->ThrottleInput = Value.Get<float>();
}

void APhysicsVehicle::ThrottleEnd(const FInputActionValue&)
{
	AccelerationComponent->ThrottleInput = 0.0f;
	TransmissionComponent->ThrottleInput = 0.0f;
}

