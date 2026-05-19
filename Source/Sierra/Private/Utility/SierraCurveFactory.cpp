#include "Utility/SierraCurveFactory.h"

TObjectPtr<UCurveFloat> USierraFloatFactory::CreateFloatCurve(TArray<FVector> CurveData)
{
	const auto Curve = NewObject<UCurveFloat>();
	Curve->FloatCurve.Reset();

	const float MinX = CurveData[0].X;
	const float MinY = CurveData[0].Y;
	const float MaxX = CurveData[1].X;
	const float MaxY = CurveData[1].Y;
	const float MaxKeys = CurveData[1].Z;

	for (int i = 0; i < MaxKeys; i++)
	{
		const FVector KeyData = CurveData[2 + i];

		const float Time  = FMath::Lerp(MinX, MaxX, KeyData.X);
		const float Value = FMath::Lerp(MinY, MaxY, KeyData.Y);
		const FKeyHandle Handle = Curve->FloatCurve.AddKey(Time, Value);
		Curve->FloatCurve.SetKeyInterpMode(Handle, RCIM_Cubic);
	}
	
	return Curve;
}
