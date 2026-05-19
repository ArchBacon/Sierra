// Copyright (c) 2026, Christian Delicaat. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Config/VehicleConfig.h"
#include "GameFramework/Pawn.h"
#include "PhysicsVehicle.generated.h"

class UTransmissionForceComponent;
struct FInputActionValue;
class UInputAction;
class UInputMappingContext;
class UAccelerationForceComponent;
class UChassisComponent;
class USuspensionComponent;
class USuspensionConfig;
class USuspensionForceComponent;
class UVehicleConfig;

UCLASS()
class SIERRA_API APhysicsVehicle : public APawn
{
	GENERATED_BODY()

	// UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Vehicle, meta=(AllowPrivateAccess="true"))
	// TObjectPtr<USceneComponent> Root {nullptr};
	
	/** Vehicle */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Vehicle, meta=(AllowPrivateAccess="true"))
	TObjectPtr<UChassisComponent> Chassis {nullptr};
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Vehicle, meta=(AllowPrivateAccess="true"))
	TObjectPtr<USuspensionComponent> SuspensionFrontLeft {nullptr};
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Vehicle, meta=(AllowPrivateAccess="true"))
	TObjectPtr<UStaticMeshComponent> WheelFrontLeft {nullptr};
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Vehicle, meta=(AllowPrivateAccess="true"))
	TObjectPtr<UStaticMeshComponent> TireFrontLeft {nullptr};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Vehicle, meta=(AllowPrivateAccess="true"))
	TObjectPtr<USuspensionComponent> SuspensionFrontRight {nullptr};
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Vehicle, meta=(AllowPrivateAccess="true"))
	TObjectPtr<UStaticMeshComponent> WheelFrontRight {nullptr};
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Vehicle, meta=(AllowPrivateAccess="true"))
	TObjectPtr<UStaticMeshComponent> TireFrontRight {nullptr};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Vehicle, meta=(AllowPrivateAccess="true"))
	TObjectPtr<USuspensionComponent> SuspensionRearLeft {nullptr};
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Vehicle, meta=(AllowPrivateAccess="true"))
	TObjectPtr<UStaticMeshComponent> WheelRearLeft {nullptr};
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Vehicle, meta=(AllowPrivateAccess="true"))
	TObjectPtr<UStaticMeshComponent> TireRearLeft {nullptr};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Vehicle, meta=(AllowPrivateAccess="true"))
	TObjectPtr<USuspensionComponent> SuspensionRearRight {nullptr};
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
	TObjectPtr<USuspensionForceComponent> SuspensionComponent {nullptr};
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Vehicle, meta=(AllowPrivateAccess="true"))
	TObjectPtr<UAccelerationForceComponent> AccelerationComponent {nullptr};
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Vehicle, meta=(AllowPrivateAccess="true"))
	TObjectPtr<UTransmissionForceComponent> TransmissionComponent {nullptr};
	
	/** Input */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess="true"))
	UInputMappingContext* DefaultMappingContext {nullptr};
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess="true"))
	UInputAction* ThrottleAction {nullptr};
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess="true"))
	UInputAction* BrakeAction {nullptr};
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess="true"))
	UInputAction* SteerAction {nullptr};
	
public:
	APhysicsVehicle();
	virtual void OnConstruction(const FTransform& Transform) override;
	
	/** Overrides */
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	
	virtual void NotifyControllerChanged() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	/** Input Responses */
	void Throttle(const FInputActionValue& Value);
	void ThrottleEnd(const FInputActionValue& Value);
	
	/** Getters */
	TObjectPtr<UVehicleConfig> GetConfig() const { return VehicleConfig; }
	TObjectPtr<UChassisComponent> GetChassis() const { return Chassis; }
	TObjectPtr<UAccelerationForceComponent> GetAccelerationComponent() const { return AccelerationComponent; }
	TObjectPtr<UTransmissionForceComponent> GetTransmissionComponent() const { return TransmissionComponent; }
	
	UFUNCTION(BlueprintCallable, BlueprintPure)
	TArray<USuspensionComponent*> GetFrontSuspension() const { return {SuspensionFrontLeft, SuspensionFrontRight}; }
	UFUNCTION(BlueprintCallable, BlueprintPure)
	TArray<USuspensionComponent*> GetRearSuspension() const { return {SuspensionRearLeft, SuspensionRearRight}; }
	UFUNCTION(BlueprintCallable, BlueprintPure)
	TArray<USuspensionComponent*> GetSuspension() const { return {SuspensionFrontLeft, SuspensionFrontRight, SuspensionRearLeft, SuspensionRearRight}; }
};
