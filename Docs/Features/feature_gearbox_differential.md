# Feature: Gearbox & Differential

## Task 1: Gear Ratio Table
- [ ] Define a gear ratio table with at least 3 forward gears and 1 reverse gear
- [ ] Reference GNX drivetrain data as a baseline (Turbo Hydramatic 200-4R, 4-speed automatic, rear-wheel drive)
- [ ] Apply the current gear ratio as a multiplier on torque output and wheel speed each tick

*Gear ratios determine how engine torque translates to wheel force — lower gears multiply torque more, higher gears trade torque for top speed.*

---

## Task 2: Manual / Semi-Automatic Shifting
- [ ] Implement upshift and downshift input bindings so the player can change gear manually
- [ ] Prevent shifting above the highest gear or below first gear
- [ ] Prevent downshifting into a gear that would push RPM above redline
- [ ] Apply a brief torque interruption on each shift to simulate clutch engagement

---

## Task 3: Differential
- [ ] Implement a differential that splits torque between the two rear driven wheels
- [ ] Under equal traction conditions, distribute torque evenly between left and right rear wheels
- [ ] Under unequal traction (e.g. one wheel in the air or on a slippery surface), allow torque distribution to shift toward the wheel with more load

*The GNX is rear-wheel drive, so the differential only applies to the rear axle.*

---

## Task 4: Stretch Goal — Automatic Shifting
- [ ] Implement RPM-based upshift logic so the car automatically shifts up when RPM reaches a tunable upper threshold
- [ ] Implement RPM-based downshift logic so the car automatically shifts down when RPM drops below a tunable lower threshold
- [ ] Expose upshift and downshift RPM thresholds as tunable parameters
- [ ] Display current gear and RPM on the HUD for player feedback

---

## Task 5: Tuning & Validation
- [ ] Validate that each gear produces a distinct and noticeable difference in acceleration feel
- [ ] Validate that the differential distributes torque correctly under both equal and unequal traction conditions
- [ ] Validate manual shifting works correctly and prevents invalid gear changes
- [ ] If stretch goal is implemented, validate automatic shifting triggers at the correct RPM thresholds
- [ ] Expose gear ratio table and differential parameters as `UPROPERTY` fields for in-editor tuning
