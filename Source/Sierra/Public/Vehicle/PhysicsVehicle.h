// Copyright (c) 2026, Christian Delicaat. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "VehicleConfig.h"
#include "GameFramework/Pawn.h"
#include "PhysicsVehicle.generated.h"

class USuspensionConfig;
class USuspensionComponent;
class UVehicleConfig;

USTRUCT(BlueprintType)
struct FWheelComponents
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Wheel)
	TObjectPtr<UStaticMeshComponent> Wheel {nullptr};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Wheel)
	TObjectPtr<UStaticMeshComponent> Tire {nullptr};
};

UENUM()
enum class EWheelIndex : uint8 { FrontLeft, FrontRight, RearLeft, RearRight };

UCLASS()
class SIERRA_API APhysicsVehicle : public APawn
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Vehicle, meta=(AllowPrivateAccess="true"))
	TObjectPtr<USceneComponent> Root {nullptr};
	
	/** Vehicle */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Vehicle, meta=(AllowPrivateAccess="true"))
	TObjectPtr<UStaticMeshComponent> Chassis {nullptr};
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Vehicle, meta=(AllowPrivateAccess="true"))
	TObjectPtr<USceneComponent> SuspensionFrontLeft {nullptr};
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Vehicle, meta=(AllowPrivateAccess="true"))
	TObjectPtr<UStaticMeshComponent> WheelFrontLeft {nullptr};
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Vehicle, meta=(AllowPrivateAccess="true"))
	TObjectPtr<UStaticMeshComponent> TireFrontLeft {nullptr};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Vehicle, meta=(AllowPrivateAccess="true"))
	TObjectPtr<USceneComponent> SuspensionFrontRight {nullptr};
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Vehicle, meta=(AllowPrivateAccess="true"))
	TObjectPtr<UStaticMeshComponent> WheelFrontRight {nullptr};
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Vehicle, meta=(AllowPrivateAccess="true"))
	TObjectPtr<UStaticMeshComponent> TireFrontRight {nullptr};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Vehicle, meta=(AllowPrivateAccess="true"))
	TObjectPtr<USceneComponent> SuspensionRearLeft {nullptr};
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Vehicle, meta=(AllowPrivateAccess="true"))
	TObjectPtr<UStaticMeshComponent> WheelRearLeft {nullptr};
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Vehicle, meta=(AllowPrivateAccess="true"))
	TObjectPtr<UStaticMeshComponent> TireRearLeft {nullptr};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Vehicle, meta=(AllowPrivateAccess="true"))
	TObjectPtr<USceneComponent> SuspensionRearRight {nullptr};
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Vehicle, meta=(AllowPrivateAccess="true"))
	TObjectPtr<UStaticMeshComponent> WheelRearRight {nullptr};
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Vehicle, meta=(AllowPrivateAccess="true"))
	TObjectPtr<UStaticMeshComponent> TireRearRight {nullptr};
	
	/** Mesh Config */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Vehicle, meta=(AllowPrivateAccess="true"))
	TObjectPtr<UStaticMesh> ChassisMesh {nullptr};
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Vehicle, meta=(AllowPrivateAccess="true"))
	TObjectPtr<UStaticMesh> TireMesh {nullptr};
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Vehicle, meta=(AllowPrivateAccess="true"))
	TObjectPtr<UStaticMesh> WheelMesh {nullptr};
	
	/** Data Config */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Vehicle, meta=(AllowPrivateAccess="true"))
	TObjectPtr<UVehicleConfig> VehicleConfig {nullptr};
	
	/** Components */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Vehicle, meta=(AllowPrivateAccess="true"))
	TObjectPtr<USuspensionComponent> SuspensionComponent {nullptr};
	
public:
	APhysicsVehicle();
	virtual void OnConstruction(const FTransform& Transform) override;
	
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	
protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
public:
	TObjectPtr<UVehicleConfig> GetVehicleConfig() const { return VehicleConfig; };
	TObjectPtr<USuspensionConfig> GetSuspensionConfig() const { return VehicleConfig->SuspensionConfig; };
	TObjectPtr<UTireConfig> GetTireConfig() const { return VehicleConfig->TireConfig; };
	
	TArray<TObjectPtr<USceneComponent>> GetFrontSuspension() const { return {SuspensionFrontLeft, SuspensionFrontRight}; };
	TArray<TObjectPtr<USceneComponent>> GetRearSuspension() const { return {SuspensionRearLeft, SuspensionRearRight}; };
};
