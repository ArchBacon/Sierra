#pragma once

#include "CoreMinimal.h"
#include "SierraCurveFactory.generated.h"

UCLASS()
class USierraFloatFactory : public UObject
{
	GENERATED_BODY()

public:
	static TObjectPtr<UCurveFloat> CreateFloatCurve(TArray<FVector> CurveData);
};
