// Copyright (c) 2026, Christian Delicaat. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "SuspensionComponent.generated.h"

class UTireConfig;
class APhysicsVehicle;
class UVehicleConfig;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SIERRA_API USuspensionComponent : public USceneComponent
{
	GENERATED_BODY()
	
	UPROPERTY() TObjectPtr<APhysicsVehicle> Vehicle {nullptr};
	UPROPERTY() TObjectPtr<UTireConfig> TireConfig {nullptr};
	
public:
	USuspensionComponent();
	
	virtual void BeginPlay() override;
	
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> Wheel {nullptr};
	
	UPROPERTY(BlueprintReadOnly)
	bool bIsFront {false};
	UPROPERTY(BlueprintReadOnly)
	bool bIsGrounded {false};
	float CompressionDistance {0.0f};
	float Travel {0.0f};
	static FVector GetChassisAttachPoint(TObjectPtr<UVehicleConfig> VehicleConfig, FVector AttachPoint, bool bIsFront);
	
	void UpdateWheelPosition() const;
	float GetWheelAngularSpeed() const;
};
