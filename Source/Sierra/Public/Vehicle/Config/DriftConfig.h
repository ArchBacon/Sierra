// Copyright (c) 2026, Christian Delicaat. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Curves/CurveFloat.h"
#include "Engine/DataAsset.h"
#include "DriftConfig.generated.h"

UCLASS()
class SIERRA_API UDriftConfig : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	/** Yaw damping multiplier curve vs drift angle (angle deg → scalar). Reduces snap at large angles. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Drift)
	TArray<FVector> YawDampeningAtAngle;

	/** Runtime curve built from YawDampeningAtAngle. Do not edit directly. */
	UPROPERTY()
	TObjectPtr<UCurveFloat> YawDampeningAtAngleCurve;

	/** Yaw damping multiplier curve vs vehicle speed (km/h → scalar). Reduces snap at high speeds. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Drift)
	TArray<FVector> YawDampeningAtSpeed;

	/** Runtime curve built from YawDampeningAtSpeed. Do not edit directly. */
	UPROPERTY()
	TObjectPtr<UCurveFloat> YawDampeningAtSpeedCurve;

	/** Drift scale contribution from pulling the handbrake. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Drift)
	float Drift_scale_from_handbrake {0.5f};

	/** Drift scale contribution from a quick gas stab (blip throttle). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Drift)
	float Drift_scale_from_gas_stab {0.1f};

	/** Lateral velocity damping applied while in drift to slow sideways sliding. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Drift)
	float Drift_sideways_damping {0.025f};

	/** Speed in km/h at which the brake-stab effect fades back to normal handling. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Drift)
	float Brake_stab_return_speed {10.f};

	/** Drift scale threshold at which the maximum side force begins to be applied. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Drift)
	float Drift_scale_for_maximum_side_force {0.3f};

	/** Strength of momentum preservation at drift initiation (keeps entry speed). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Drift)
	float Maintain_entry_speed_amount {0.005f};

	/** Base magnitude of the artificial side force applied to sustain drift. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Drift)
	float Side_force_magnitude {13.f};

	/** Angular velocity damping applied to the vehicle while drifting. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Drift)
	float Drift_angular_damping {0.05f};

	/** Slip angle in degrees above which the full counter-steer rate is applied. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Drift)
	float High_slip_angle_for_counter_steering {40.f};

	/** Minimum slip angle in degrees required to enter drift via handbrake input. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Drift)
	float Slip_angle_to_enter_drift_when_handbraking {6.f};

	/** Yaw torque applied (N·m) when throttle is suddenly released during drift. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Drift)
	float Gas_let_off_yaw_torque {-0.1f};

	/** Slip angle below which drift scale contribution drops to zero. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Drift)
	float Slip_angle_for_zero_drift_scale {0.f};

	/** Steering authority while in drift as a fraction of normal steering. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Drift)
	float Default_steering {0.1f};

	/** Slip angle in degrees below which drift mode automatically exits. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Drift)
	float Drift_angle_to_exit_drift {3.f};

	/** Drift scale contribution from lifting the throttle during drift. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Drift)
	float Drift_scale_from_gas_let_off {0.35f};

	/** Drift scale contribution from counter-steering input. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Drift)
	float Drift_scale_from_counter_steering {1.f};

	/** Handbrake drift scale contribution at high vehicle speed. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Drift)
	float DriftScaleFromHandbrakeAtHighSpeed {0.3f};

	/** Handbrake drift scale contribution at low vehicle speed. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Drift)
	float DriftScaleFromHandbrakeAtLowSpeed {0.6f};

	/** Minimum longitudinal grip multiplier applied during a donut maneuver. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Drift)
	float DonutLongitudinalGripMin {1.f};

	/** Maximum longitudinal grip multiplier during a donut. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Drift)
	float DonutLongitudinalGripMax {1.f};

	/** Minimum lateral grip multiplier during a donut (lower = looser, more spin). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Drift)
	float DonutLateralGripMin {0.1f};

	/** Maximum lateral grip multiplier during a donut. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Drift)
	float DonutLateralGripMax {1.f};

	/** Slip angle above which drift scale begins to reduce (blends toward zero). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Drift)
	float Slip_angle_to_start_blending_down_drift_scale {0.f};

	/** Default steering remapping multiplier on off-road surfaces. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Drift)
	float Default_steering_remapping_offroad {0.5f};

	/** Drift scale contribution from brake input. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Drift)
	float Drift_scale_from_braking {1.f};

	/** Minimum slip angle in degrees required to enter drift via standard oversteer. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Drift)
	float Slip_angle_to_enter_drift {7.5f};

	/** Yaw torque in N·m applied to the vehicle during a donut maneuver. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Drift)
	float Donut_yaw_torque {45000.f};

	/** Upper speed limit in km/h for donut mode to remain active. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Drift)
	float Donut_speed_limit_high {35.f};

	/** Lower speed limit in km/h for donut mode to be accessible. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Drift)
	float Donut_speed_limit_low {5.f};

	/** Drift scale contribution from steering input while in drift. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Drift)
	float Drift_scale_from_steering {1.6f};

	/** Initial yaw torque in N·m applied at the very start of drift initiation. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Drift)
	float Initial_yaw_torque {0.f};

	/** Additional yaw torque in N·m applied during a fishtail oscillation. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Drift)
	float ExtraFishTailTorque {9000.f};

	/** Initial drift scale applied when entering drift after a Scandinavian flick. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Drift)
	float Starting_drift_scale_after_scandinavian_flick {0.75f};

	/** Maximum counter-steer authority applied at low slip angles (negative = opposite lock). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Drift)
	float Max_countersteering_at_low_slip_angle {-0.175f};

	/** Scales the side force magnitude by the current drift progression scale. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Drift)
	float Side_force_multiplier {5.5f};

	/** Slip angle in degrees above which side force starts to be applied. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Drift)
	float Drift_angle_for_side_force {4.75f};

	/** Rate at which forward vehicle speed is bled off per frame during drift. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Drift)
	float Reduce_forward_speed_amount {0.005f};

	/** Minimum slip angle in degrees required to enter drift via brake input. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Drift)
	float Slip_angle_to_enter_drift_when_braking {2.f};

	/** Speed in km/h at which the side force reaches its maximum magnitude. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Drift)
	float Speed_for_maximum_side_force {90.f};

	/** Remaps the counter-steer input curve on tarmac surfaces. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Drift)
	float Counter_steering_remapping {0.1f};

	/** Remaps the counter-steer input curve on off-road surfaces. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Drift)
	float Counter_steering_remapping_offroad {-0.3f};

	/** Minimum slip angle required to enter drift after a Scandinavian flick. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Drift)
	float Slip_angle_to_enter_drift_after_scandinavian_flick {10.f};

	/** Maximum yaw torque in N·m the drift system can apply. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Drift)
	float Maximum_yaw_torque {12500.f};

	/** Mid-range yaw torque in N·m (blended between min and max based on drift state). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Drift)
	float Mid_yaw_torque {10550.f};

	/** Minimum yaw torque in N·m applied at the start or tail of a drift. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Drift)
	float Minimum_yaw_torque {1550.f};

	/** Rate at which drift scale decays when the vehicle is outside the sustain conditions. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Drift)
	float Drift_scale_decay {0.55f};

	/** Minimum slip angle required to enter drift on off-road surfaces. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Drift)
	float Slip_angle_to_enter_drift_offroad {6.5f};

	/** Initial drift scale value at the very moment drift is entered. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Drift)
	float Starting_drift_scale {0.0001f};

	/** Default steering remapping multiplier on tarmac surfaces. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Drift)
	float Default_steering_remapping {0.4f};

	/** Minimum vehicle speed in km/h required to allow drift initiation. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Drift)
	float Minimum_speed_to_enter_drift {30.f};

	/** Minimum side force magnitude maintained during drift scale decay. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Drift)
	float Min_decay_side_force_magnitude {0.f};

	/** Scales the destabilizing effect of longitudinal forces on the drift angle. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Drift)
	float LongitudinalInstabilityEffectScalar {0.f};

	/** Speed in km/h above which drift chaining (back-to-back drifts) becomes available. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Drift)
	float Speed_for_drift_chaining {150.f};

	/** Slip angle below which the drift scale starts decaying toward zero. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Drift)
	float Drift_angle_for_decay {6.5f};

	/** Maximum counter-steer authority at high slip angles (negative = full opposite lock). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Drift)
	float Max_countersteering_at_high_slip_angle {-1.f};

	/** Exponent controlling the power curve shape of counter-steer authority vs slip angle. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Drift)
	float Max_counter_steering_power {1.25f};

	/** Speed in km/h below which no side force is applied. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Drift)
	float Speed_for_no_sideforce {0.f};

	/** Minimum slip angle required to enter drift after a gas stab entry. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Drift)
	float Slip_angle_to_enter_drift_after_gas_stab {3.f};

	/** Absolute maximum counter-steer fraction that can be applied (1.0 = full lock). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Drift)
	float Max_countersteering {-1.f};

	/** Slip angle below which counter-steering assistance is not applied. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Drift)
	float Low_slip_angle_for_counter_steering {3.f};

	/** Time in seconds to reach maximum grip effect during a donut maneuver. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Drift)
	float TimeForMaxDonutGripEffect {1.f};

	/** Maximum speed difference in km/h allowed when the system tries to maintain entry speed. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Drift)
	float Max_speed_difference_for_maintain_speed {12.5f};

	/** Initial drift scale used when chaining consecutive drifts together. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Drift)
	float Starting_drift_scale_from_drift_chaining {0.01f};

	/** Time in seconds to blend yaw damping in at drift entry. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Drift)
	float Time_to_blend_damping {0.25f};

	/** Minimum drift angle in degrees before side force begins contributing. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Drift)
	float Minimum_drift_angle_for_side_force {1.5f};

	/** Slip angle at which throttle input has its full influence on drift scale. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Drift)
	float Drift_angle_for_full_gas_influence {6.f};

	/** Per-frame decay rate applied when the slip angle is below Drift_angle_for_decay. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Drift)
	float Decay_rate {0.018f};

	/** Initial drift scale applied immediately after a gas stab entry. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Drift)
	float Starting_drift_scale_after_gas_stab {0.1f};

	/** Slip angle considered a "deep" drift; used to gate certain sustained drift behaviors. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Drift)
	float Slip_angle_for_deep_drift {18.f};

	/** Steering authority multiplier ramped in as drift exits (1.0 = full normal steering). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Drift)
	float Steering_amount_on_exit_drift {1.f};

	/** Slip angle at which yaw damping fully fades out. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Drift)
	float Slip_angle_for_full_damping_fade {0.f};

	/** Minimum slip angle to enter drift after a brake stab entry. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Drift)
	float Slip_angle_to_enter_drift_after_brake_stab {2.f};

	/** Whether releasing the handbrake while drifting immediately exits drift mode. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Drift)
	bool Exit_drift_on_handbrake {true};

	void BuildCurves();
	virtual void PostLoad() override;
};
