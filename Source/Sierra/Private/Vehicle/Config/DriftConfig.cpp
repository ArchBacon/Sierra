// Copyright (c) 2026, Christian Delicaat. All rights reserved.

#include "Vehicle/Config/DriftConfig.h"
#include "Utility/SierraCurveFactory.h"

void UDriftConfig::PostLoad()
{
	Super::PostLoad();
	BuildCurves();
}

void UDriftConfig::BuildCurves()
{
	if (YawDampeningAtAngle.Num() > 1)
		YawDampeningAtAngleCurve = USierraFloatFactory::CreateFloatCurve(YawDampeningAtAngle);

	if (YawDampeningAtSpeed.Num() > 1)
		YawDampeningAtSpeedCurve = USierraFloatFactory::CreateFloatCurve(YawDampeningAtSpeed);
}
