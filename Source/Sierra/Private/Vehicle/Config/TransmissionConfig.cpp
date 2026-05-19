// Copyright (c) 2026, Christian Delicaat. All rights reserved.

#include "Vehicle/Config/TransmissionConfig.h"
#include "Utility/SierraCurveFactory.h"

void UTransmissionConfig::PostLoad()
{
	Super::PostLoad();
	BuildCurves();
}

void UTransmissionConfig::BuildCurves()
{
	if (UpShiftThrottle.Num() > 1)
		UpShiftThrottleCurve = USierraFloatFactory::CreateFloatCurve(UpShiftThrottle);

	if (UpShiftClutch.Num() > 1)
		UpShiftClutchCurve = USierraFloatFactory::CreateFloatCurve(UpShiftClutch);

	if (DownShiftThrottle.Num() > 1)
		DownShiftThrottleCurve = USierraFloatFactory::CreateFloatCurve(DownShiftThrottle);

	if (DownShiftClutch.Num() > 1)
		DownShiftClutchCurve = USierraFloatFactory::CreateFloatCurve(DownShiftClutch);

	if (DownShiftSlopeScalar.Num() > 1)
		DownShiftSlopeScalarCurve = USierraFloatFactory::CreateFloatCurve(DownShiftSlopeScalar);
}
