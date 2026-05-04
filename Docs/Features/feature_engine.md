# Feature: Engine & Drivetrain

## Task 1: Engine RPM Simulation
- [ ] Implement engine RPM as a simulated value that rises with throttle input and falls when throttle is released
- [ ] Define idle RPM (1000) and redline RPM (4800) as tunable parameters
- [ ] Implement RPM rise and fall rates as separate tunable values so the engine response feels appropriately weighted
- [ ] Clamp RPM between idle and redline at all times

*RPM drives torque output — no RPM simulation means acceleration cannot scale correctly with engine state.*

---

## Task 2: Torque Curve
- [ ] Implement a torque curve that maps current RPM to an output torque multiplier
- [ ] Use the GNX engine friction torque spline data as a reference for how torque varies across the rev range
- [ ] Sample the torque curve each tick based on current RPM to get the effective torque output

*The torque curve gives the engine character — low-end torque, a power band, and tapering near redline.*

---

## Task 3: Acceleration
- [ ] Implement throttle input mapped to engine torque application at the driven wheels
- [ ] Scale forward force output by current torque curve value and current gear ratio
- [ ] Apply forward force using Unreal's `AddForce` at the vehicle center of mass

---

## Task 4: Braking
- [ ] Implement brake input that applies a decelerating force opposing the current velocity direction
- [ ] Scale braking force as a tunable parameter separate from engine torque
- [ ] Ensure braking works correctly on slopes without causing the vehicle to slide unintentionally

---

## Task 5: Reverse
- [ ] Implement reverse as a separate low-speed force mode, active only when the vehicle is at or near rest
- [ ] Cap reverse speed at a tunable maximum so the car cannot accelerate indefinitely backwards
- [ ] Ensure reverse input does not conflict with forward throttle input

---

## Task 6: Tuning & Validation
- [ ] Validate that RPM rises and falls responsively with throttle input
- [ ] Validate that acceleration force scales correctly across the RPM range
- [ ] Validate braking brings the car to a full stop reliably on flat and sloped surfaces
- [ ] Validate reverse works at low speed and is properly capped
- [ ] Expose engine parameters (idle RPM, redline, torque curve, brake force, reverse speed cap) as `UPROPERTY` fields for in-editor tuning
