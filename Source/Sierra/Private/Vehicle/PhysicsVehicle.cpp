// Copyright (c) 2026, Christian Delicaat. All rights reserved.

#include "Vehicle/PhysicsVehicle.h"

#include "Sierra/Sierra.h"
#include "Vehicle/SuspensionConfig.h"
#include "Vehicle/VehicleConfig.h"
#include "Vehicle/Components/SuspensionComponent.h"

APhysicsVehicle::APhysicsVehicle()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;
	
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;
	
	Chassis = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Chassis"));
	Chassis->SetupAttachment(RootComponent);
	Chassis->SetMassOverrideInKg(NAME_None, 1576.f);
	Chassis->SetSimulatePhysics(true);
	Chassis->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
	Chassis->SetCollisionProfileName("Chassis");

	// Front Left
	SuspensionFrontLeft = CreateDefaultSubobject<USceneComponent>(TEXT("Suspension_FL"));
	SuspensionFrontLeft->SetupAttachment(Chassis);
	SuspensionFrontLeft->SetRelativeRotation(FRotator(0.0f, 90.0f, 0.0f));
	TireFrontLeft = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tire_FL"));
	TireFrontLeft->SetupAttachment(SuspensionFrontLeft);
	TireFrontLeft->SetCollisionProfileName(TEXT("Wheel"));
	TireFrontLeft->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
	TireFrontLeft->SetRelativeScale3D(FVector(1.0f, 1.0f, 1.0f));
	WheelFrontLeft = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wheel_FL"));
	WheelFrontLeft->SetupAttachment(TireFrontLeft);
	WheelFrontLeft->SetCollisionProfileName(TEXT("Wheel"));

	// Front Right
	SuspensionFrontRight = CreateDefaultSubobject<USceneComponent>(TEXT("Suspension_FR"));
	SuspensionFrontRight->SetupAttachment(Chassis);
	SuspensionFrontRight->SetRelativeRotation(FRotator(0.0f, 90.0f, 0.0f));
	TireFrontRight = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tire_FR"));
	TireFrontRight->SetupAttachment(SuspensionFrontRight);
	TireFrontRight->SetCollisionProfileName(TEXT("Wheel"));
	TireFrontRight->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
	TireFrontRight->SetRelativeScale3D(FVector(-1.0f, 1.0f, 1.0f));
	WheelFrontRight = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wheel_FR"));
	WheelFrontRight->SetupAttachment(TireFrontRight);
	WheelFrontRight->SetCollisionProfileName(TEXT("Wheel"));

	// Rear Left
	SuspensionRearLeft = CreateDefaultSubobject<USceneComponent>(TEXT("Suspension_RL"));
	SuspensionRearLeft->SetupAttachment(Chassis);
	SuspensionRearLeft->SetRelativeRotation(FRotator(0.0f, 90.0f, 0.0f));
	TireRearLeft = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tire_RL"));
	TireRearLeft->SetupAttachment(SuspensionRearLeft);
	TireRearLeft->SetCollisionProfileName(TEXT("Wheel"));
	TireRearLeft->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
	TireRearLeft->SetRelativeScale3D(FVector(1.0f, 1.0f, 1.0f));
	WheelRearLeft = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wheel_RL"));
	WheelRearLeft->SetupAttachment(TireRearLeft);
	WheelRearLeft->SetCollisionProfileName(TEXT("Wheel"));

	// Rear Right
	SuspensionRearRight = CreateDefaultSubobject<USceneComponent>(TEXT("Suspension_RR"));
	SuspensionRearRight->SetupAttachment(Chassis);
	SuspensionRearRight->SetRelativeRotation(FRotator(0.0f, 90.0f, 0.0f));
	TireRearRight = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tire_RR"));
	TireRearRight->SetupAttachment(SuspensionRearRight);
	TireRearRight->SetCollisionProfileName(TEXT("Wheel"));
	TireRearRight->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
	TireRearRight->SetRelativeScale3D(FVector(-1.0f, 1.0f, 1.0f));
	WheelRearRight = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wheel_RR"));
	WheelRearRight->SetupAttachment(TireRearRight);
	WheelRearRight->SetCollisionProfileName(TEXT("Wheel"));
	
	// Suspension
	SuspensionComponent = CreateDefaultSubobject<USuspensionComponent>(TEXT("SuspensionComponent"));
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
	Chassis->SetStaticMesh(ChassisMesh);

	// Front Left
	SuspensionFrontLeft->SetRelativeLocation(VehicleConfig->SuspensionConfig->AttachPoints[0]);
	TireFrontLeft->SetStaticMesh(TireMesh);
	WheelFrontLeft->SetStaticMesh(WheelMesh);

	// Front Right
	SuspensionFrontRight->SetRelativeLocation(VehicleConfig->SuspensionConfig->AttachPoints[1]);
	TireFrontRight->SetStaticMesh(TireMesh);
	WheelFrontRight->SetStaticMesh(WheelMesh);

	// Rear Left
	SuspensionRearLeft->SetRelativeLocation(VehicleConfig->SuspensionConfig->AttachPoints[2]);
	TireRearLeft->SetStaticMesh(TireMesh);
	WheelRearLeft->SetStaticMesh(WheelMesh);

	// Rear Right
	SuspensionRearRight->SetRelativeLocation(VehicleConfig->SuspensionConfig->AttachPoints[3]);
	TireRearRight->SetStaticMesh(TireMesh);
	WheelRearRight->SetStaticMesh(WheelMesh);
}

void APhysicsVehicle::BeginPlay()
{
	Super::BeginPlay();
}

void APhysicsVehicle::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APhysicsVehicle::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

