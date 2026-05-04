# Goal: Implement a Driveable Arcade Vehicle in Unreal Engine

I switched from the Bee engine to Unreal Engine for three reasons. First, I am significantly more familiar with Unreal, meaning I can spend more time on actual features rather than fighting the tooling. Second, Bee's tooling is very limited — debugging and iteration are slow and frustrating, which is a serious problem when implementing systems I haven't built before. Third, Unreal has substantially more documentation, community resources, and built-in physics tooling available, which is critical for a project of this scope.

By the end of week 7, I will deliver a car in Unreal Engine that can accelerate, brake, reverse, and steer responsively on a blocked-out track that includes non-flat terrain. The vehicle will not use Unreal's Chaos Vehicles component — instead, physics behaviour is driven through Unreal's built-in force and collision system, with custom suspension, engine, and handling logic implemented primarily in C++ with Blueprint used where appropriate. Suspension and handling values are informed by real-world physics principles, with NFS Heat's vehicle config data for the 1987 Buick Grand National/GNX used as a tuning reference baseline.

---

## Week 1–2 — Basic Driving (Completed)

A driveable Blueprint prototype has been produced with functional acceleration, deceleration, steering, and basic grip. A test surface was built with a flat driving area, repeated bump strips, and a ramp to validate basic suspension behaviour. This serves as a proof of concept and a foundation for the C++ implementation.

**Delivered:**
- Blueprint vehicle with basic wheel friction and input response
- Test surface with flat area, bumps, and a ramp for suspension validation
- Steering, acceleration, braking, and grip all functional at a basic level

---

## Week 3–4 — C++ Conversion, Engine & Suspension

Convert the Blueprint prototype to C++ and implement a physically grounded suspension system alongside a proper engine and drivetrain model.

**Implementation details:**
- Convert the majority of Blueprint logic to C++, with Blueprint retained for exposed tuning parameters and editor integration
- Implement suspension as a per-wheel raycast system, calculating spring and damper forces each tick and applying them to the vehicle body using Unreal's built-in `AddForce` and `AddForceAtLocation` functions
- Spring compression, damper velocity, separate bump and rebound damping, progression, digression, travel limits, and ride height all implemented as tunable per-axle parameters using GNX config data as the starting reference
- Implement engine RPM simulation with a torque curve driving forward force output
- Implement acceleration and braking as force application scaled by current gear ratio and RPM
- Implement reverse as a separate low-speed force mode

**Success criteria:** Car sits correctly at rest, suspension responds to bumps and slopes, acceleration and braking feel distinct and RPM-dependent.

---

## Week 5–6 — Steering, Grip & Handling Tuning

Implement full steering behaviour and tune the overall handling for responsive arcade driving.

**Implementation details:**
- Implement steering angle input mapped to front wheel rotation, with a tunable steering speed and maximum angle
- Implement Ackermann steering geometry so the inner and outer front wheels turn at different angles during a corner
- Implement lateral friction force per wheel to resist sideways sliding, scaled by how much the wheel is slipping sideways relative to its rolling direction
- Implement weight transfer by shifting the downforce distribution across wheels based on acceleration, braking, and cornering forces, affecting how much grip each wheel has at any given moment
- Tune steering responsiveness, grip strength, and slip threshold so the car feels arcade-appropriate — easy to control, with predictable slides rather than sudden loss of control

**Success criteria:** Car is fully driveable on the blocked-out terrain including slopes and bumps. Steering, braking, and acceleration all interact correctly. Weight transfer is visible and feels natural.

---

## Week 7 — Polish & Hand-In

Final tuning pass and submission of all deliverables.

**Implementation details:**
- Final suspension, engine, and handling tuning pass to ensure consistent driving feel across different terrain
- C++ code cleaned up, commented, and structured for readability
- Learning log up to date with weekly entries covering implementation decisions, problems encountered, and solutions found
- Short playtest session to gather handling feedback

**Success criteria:** All deliverables submitted. Car is stable, driveable, and feels good to control on varied terrain.

---

## Week 8 — Gearbox, Differential & Stretch Goal: Automatic Shifting

Implement a gearbox and differential system to complete the drivetrain, with automatic gear shifting as a stretch goal.

**Implementation details:**
- Implement a gear ratio table that scales torque and wheel speed output based on the currently selected gear
- Implement manual or semi-automatic gear shifting so the player can shift up and down through at least 3 forward gears
- Implement a differential that distributes torque between the driven wheels, affecting how the car behaves under acceleration in corners
- Reference GNX drivetrain data where applicable (Turbo Hydramatic 200-4R, 4-speed automatic, rear-wheel drive)

**Stretch goal: Automatic shifting**
- Implement automatic upshift and downshift logic based on engine RPM thresholds so the car shifts without player input
- Current gear and RPM exposed to HUD for player feedback

**Success criteria:** Car drives through at least 3 gears with correct torque scaling per gear. Differential distributes power to the rear wheels correctly. Stretch goal met if shifting happens automatically based on RPM.

---

## Week 9–10 — Oral Defense Preparation

Remaining development time used for driving feel refinement and stretch goal polish. Oral defense preparation takes priority from week 9 onward.
