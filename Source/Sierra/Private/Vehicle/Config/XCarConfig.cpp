// Copyright (c) 2026, Christian Delicaat. All rights reserved.

#include "Vehicle/Config/XCarConfig.h"
#include "Utility/SierraCurveFactory.h"

void UXCarConfig::PostLoad()
{
	Super::PostLoad();
	BuildCurves();
}

void UXCarConfig::BuildCurves()
{
	if (XCarBodyYOffsetVSpeed.Num() > 1)
		XCarBodyYOffsetVSpeedCurve = USierraFloatFactory::CreateFloatCurve(XCarBodyYOffsetVSpeed);
}
