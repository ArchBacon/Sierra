// Copyright (c) 2026, Christian Delicaat. All rights reserved.

#include "Vehicle/Config/TireConfig.h"
#include "Utility/SierraCurveFactory.h"

void UTireConfig::PostLoad()
{
	Super::PostLoad();
	BuildCurves();
}

void UTireConfig::BuildCurves()
{
	if (RollingResistanceScalarVSpeed.Num() > 1)
		RollingResistanceScalarVSpeedCurve = USierraFloatFactory::CreateFloatCurve(RollingResistanceScalarVSpeed);
}
