# Feature: Steering & Grip

## Task 1: Steering Input & Wheel Rotation
- [ ] Map steering axis input to front wheel rotation angle each tick
- [ ] Implement a tunable maximum steering angle so the wheels cannot turn beyond a physical limit
- [ ] Implement a tunable steering speed so the wheels turn progressively rather than snapping instantly to the target angle

---

## Task 2: Ackermann Steering Geometry
- [ ] Implement Ackermann geometry so the inner front wheel turns at a sharper angle than the outer front wheel during a corner
- [ ] Calculate inner and outer steering angles based on wheelbase and track width
- [ ] Apply the correct angle to each front wheel independently each tick

*Without Ackermann geometry, both front wheels point the same direction, causing the inner wheel to scrub during cornering.*

---

## Task 3: Lateral Grip & Slip
- [ ] Calculate the sideways velocity component of each wheel relative to its rolling direction each tick
- [ ] Apply a lateral friction force opposing the sideways slip at each wheel using `AddForceAtLocation`
- [ ] Implement a slip threshold beyond which grip starts to fall off, allowing the car to slide predictably
- [ ] Tune grip strength and slip falloff for arcade feel — slides should be controllable rather than sudden

---

## Task 4: Weight Transfer
- [ ] Implement longitudinal weight transfer so braking shifts load to the front wheels and acceleration shifts load to the rear wheels
- [ ] Implement lateral weight transfer so cornering shifts load to the outside wheels
- [ ] Scale available grip per wheel based on its current load so weight transfer meaningfully affects handling

*Weight transfer gives the car physical believability — the nose dips under braking, the rear squats under acceleration, and the body leans in corners.*

---

## Task 5: Tuning & Validation
- [ ] Validate steering feels responsive and appropriately scaled to input
- [ ] Validate Ackermann geometry — inner wheel should visibly turn tighter than outer wheel in corners
- [ ] Validate lateral grip — car should resist sliding at normal speeds and slide predictably when pushed
- [ ] Validate weight transfer is visible and affects handling in a natural way
- [ ] Expose steering and grip parameters (max angle, steering speed, grip strength, slip threshold) as `UPROPERTY` fields for in-editor tuning
