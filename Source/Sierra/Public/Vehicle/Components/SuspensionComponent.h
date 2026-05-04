// Copyright (c) 2026, Christian Delicaat. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SuspensionComponent.generated.h"

class APhysicsVehicle;

USTRUCT()
struct FSuspensionData
{
	GENERATED_BODY()
	
	float HitDistance {0.0f};
	FVector HitNormal {0.0f, 0.0f, 0.0f};
	bool bGrounded {false};
	float Speed {0.0f};
	float Compression {0.0f};
	float VisualOffset {0.0f};
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SIERRA_API USuspensionComponent : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY()
	TObjectPtr<APhysicsVehicle> OwningPawn {nullptr};
	
	TMap<TObjectPtr<USceneComponent>, FSuspensionData> SuspensionData {};

public:
	USuspensionComponent();

	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
private:
	void UpdateSuspensionData(TObjectPtr<USceneComponent> Suspension, float RideHeight, float TireRadius, float DeltaTime);
};
