// Copyright (c) 2026, Christian Delicaat. All rights reserved.

#include "Vehicle/Config/SteeringConfig.h"
#include "Utility/SierraCurveFactory.h"

void USteeringConfig::PostLoad()
{
	Super::PostLoad();
	BuildCurves();
}

void USteeringConfig::BuildCurves()
{
	if (BrakeInputRemap.Num() > 1)
		BrakeInputRemapCurve = USierraFloatFactory::CreateFloatCurve(BrakeInputRemap);

	if (CounterSteerRate.Num() > 1)
		CounterSteerRateCurve = USierraFloatFactory::CreateFloatCurve(CounterSteerRate);

	if (SteerRate.Num() > 1)
		SteerRateCurve = USierraFloatFactory::CreateFloatCurve(SteerRate);

	if (GentleInputSteerRate.Num() > 1)
		GentleInputSteerRateCurve = USierraFloatFactory::CreateFloatCurve(GentleInputSteerRate);

	if (CenterSteerRate.Num() > 1)
		CenterSteerRateCurve = USierraFloatFactory::CreateFloatCurve(CenterSteerRate);

	if (SteeringRangeOnThrottle.Num() > 1)
		SteeringRangeOnThrottleCurve = USierraFloatFactory::CreateFloatCurve(SteeringRangeOnThrottle);

	if (SteeringRangeOffThrottle.Num() > 1)
		SteeringRangeOffThrottleCurve = USierraFloatFactory::CreateFloatCurve(SteeringRangeOffThrottle);

	if (ThrottleMappingFirstGear.Num() > 1)
		ThrottleMappingFirstGearCurve = USierraFloatFactory::CreateFloatCurve(ThrottleMappingFirstGear);

	if (ThrottleMappingSecondGear.Num() > 1)
		ThrottleMappingSecondGearCurve = USierraFloatFactory::CreateFloatCurve(ThrottleMappingSecondGear);

	if (ThrottleMappingThirdAndAbove.Num() > 1)
		ThrottleMappingThirdAndAboveCurve = USierraFloatFactory::CreateFloatCurve(ThrottleMappingThirdAndAbove);
}
