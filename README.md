# Minkowski Difference and Collision Detection #

This demonstrates the Minkowski Difference. All points from polygons A are subtracted from polygon B with the resulting points put through a convex hull algorithm.
This hull can be used for the purposes of collision detection. A collision occurs between polygon A and B if the origin is found within the resulting hull.
In this demo, a line is drawn from the resulting hull to the origin which represents both the collision normal and depth. These values could then be used later in the pipeline for collision response.

This code is for reference purposes only. The code has been taken from an old project and hasn't been updated to compile.

### Demo ###
https://github.com/Jaromc/minkowski/assets/89912906/9fd2b584-38c8-4269-841b-e35b5ed9090e

