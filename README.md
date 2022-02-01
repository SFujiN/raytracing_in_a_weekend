# Raytracing In A Weekend
My run amok of raytracing in a weekend, purely for educational purposes. Cheers!

# How to run
from main directory cd to src
```
~>cd src
```
then run build.bat
```
~\src>build
```
then cd to bin directory and run main.exe
```
~\bin>main.exe
```
this should output image.ppm in the data directory

ex.
![nHD resolution render](https://github.com/SFujiN/raytracing_in_a_weekend/blob/main/data/image.ppm?raw=true)

# Specs

CPU: Intel Core i9-9900k @ 3.60GHz

# Render times of final scene
| Resolution | Time         |
| :---       | :---:        |
| nHD        | 00:02:34:753 |
| qHD        | 00:05:36:171 |
| HD         | 00:10:09:192 |
| Full HD    | 00:22:44:677 |
| QHD        | 00:41:00:254 |
| 4K UHD     | 01:30:24:244 |

## Citations
- Ray tracing in One Weekend:
Ray Tracing in One Weekend. raytracing.github.io/books/RayTracingInOneWeekend.html
Accessed 25 001. 2022

- Triangle Rendering (Möller-Trumbore intersection algorithm):
https://en.wikipedia.org/wiki/M%C3%B6ller%E2%80%93Trumbore_intersection_algorithm