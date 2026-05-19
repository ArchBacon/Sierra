# Feature: Suspension

## ~~Task 1: Per-Wheel Raycast System~~
- [x] Cast a ray downward from each wheel position each tick to detect the ground
- [x] Calculate the compression distance between the wheel's rest position and the detected ground contact point
- [x] Store the previous frame's compression distance to calculate suspension velocity for damper calculations

*Each wheel operates independently, meaning the suspension responds correctly on uneven and sloped terrain.*

---

## Task 2: Spring Force
- [ ] Implement spring force per wheel using compression distance and the configured spring rate
- [ ] Apply front spring rate (370) and rear spring rate (414) as separate tunable parameters
- [ ] Implement spring progression (0.07 front and rear) so the spring rate increases nonlinearly as the suspension compresses further

*Spring force is applied upward at each wheel position using `AddForceAtLocation`.*

---

## Task 3: Damper Force
- [ ] Implement separate bump (compression) and rebound (extension) damping per wheel
- [ ] Apply front compression damping (20.8) and rebound damping (37.5) as tunable parameters
- [ ] Apply rear compression damping (29.8) and rebound damping (46.1) as tunable parameters
- [ ] Implement shock digression (0.8 front and rear) so damping force tapers off at high suspension shaft velocity
- [ ] Implement shock valving (175 front and rear) as the base damping stiffness scalar
- [ ] Implement shock blowout threshold (1.1) so the damper relief valve opens on extreme impacts

*Rebound damping is intentionally higher than compression on both axles to keep the tires planted after a bump.*

---

## Task 4: Travel Limits & Ride Height
- [ ] Enforce suspension travel limits (30 units front and rear) with hard stops at both bump and droop limits
- [ ] Apply ride height offset (10 front and rear) so the car sits at the correct resting height
- [ ] Clamp wheel position within upper and lower travel bounds each tick

---

## Task 5: Force Application
- [ ] Apply combined spring and damper force to the vehicle body at each wheel's world position using `AddForceAtLocation`
- [ ] Ensure forces are applied in world space upward direction, not local vehicle space, so slopes are handled correctly

---

## Task 6: Tuning & Validation
- [ ] Validate suspension on flat surface — car should sit at correct ride height with no bouncing at rest
- [ ] Validate suspension over bump strips — suspension should compress and rebound smoothly
- [ ] Validate suspension on ramp — all four wheels should maintain contact independently
- [ ] Expose all suspension parameters (spring rate, damping, travel, ride height, progression, digression) as `UPROPERTY` fields for in-editor tuning
