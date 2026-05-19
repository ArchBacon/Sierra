// Copyright (c) 2026, Christian Delicaat. All rights reserved.

#include "Vehicle/Config/BrakesConfig.h"
#include "Utility/SierraCurveFactory.h"

void UBrakesConfig::PostLoad()
{
	Super::PostLoad();
	BuildCurves();
}

void UBrakesConfig::BuildCurves()
{
	if (FrontBrakeTorqueVsSpeed.Num() > 1)
		FrontBrakeTorqueVsSpeedCurve = USierraFloatFactory::CreateFloatCurve(FrontBrakeTorqueVsSpeed);

	if (HandbrakeTorqueVsSpeed.Num() > 1)
		HandbrakeTorqueVsSpeedCurve = USierraFloatFactory::CreateFloatCurve(HandbrakeTorqueVsSpeed);
}
