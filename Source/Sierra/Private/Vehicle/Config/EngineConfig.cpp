// Copyright (c) 2026, Christian Delicaat. All rights reserved.

#include "Vehicle/Config/EngineConfig.h"
#include "Utility/SierraCurveFactory.h"

void UEngineConfig::PostLoad()
{
	Super::PostLoad();
	BuildCurves();
}

void UEngineConfig::BuildCurves()
{
	if (Torque.Num() > 1)
		TorqueCurve = USierraFloatFactory::CreateFloatCurve(Torque);

	if (TorqueNoise.Num() > 1)
		TorqueNoiseCurve = USierraFloatFactory::CreateFloatCurve(TorqueNoise);

	if (EngineFrictionTorque.Num() > 1)
		EngineFrictionTorqueCurve = USierraFloatFactory::CreateFloatCurve(EngineFrictionTorque);

	if (EngineBrakingVsGear.Num() > 1)
		EngineBrakingVsGearCurve = USierraFloatFactory::CreateFloatCurve(EngineBrakingVsGear);
}
