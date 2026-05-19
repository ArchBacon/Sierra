# Suspension

## Spring Force

Hooke's law: F=-Kx
Spring force is the force exerted by the spring, no matter
if it's compressed or extended.
The original Hooke's Law is F=Kx, but this assumes an extending force.
Since we're compressing the suspension due to the car's weight, we will
have to invert the formula into F=-Kx, where K is the constant spring rate
in N/m and x is the distance in m where the other end of the spring is displaced
from it's original resting point.

From the suspension config, we use use SpringSpecs, which is K in the formula.
SpringSpec is written in N/cm

Since the compression distance is important, and the formula makes it technically unlimited,
we'd have to limit the distance our spring can move. Using the TravelSpec.

so the formula turns into F=-K * (min(travelSpec, compression distance))
so for the front suspension, F= -SpringRate * min(TravelSpec, CompressionDistance)
to make the force higher the more it'd compressed, we'll add a spring progression.
F=-Kpx
turning the formula into F = -K * p * x, where p is 1 + spring progression. but since the
progression is in cm, we have to convert it to m to fit the rest of the values. so,
p = 1 + (spring progression * compression distance)

F=Kpx
Compression = min(compression distance, travel spec)
F = (SpringSpecs * (1 + Progression * Compression) * compression)

