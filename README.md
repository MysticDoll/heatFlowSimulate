# heatFlowSimulate
## Condition
- Simulate on Iron plate(60cm x 40cm)
- Heat source is that provides 773K each time on circle with radius of 10 cm on the center of the area.(Dirichlet Condition)
- Initial State is 300K out of heat source. In heat source, 773K are given.
- Thermal insulation condition are given in boundaries of the area (Neumann boundary condition)

## Compile
```sh
$ g++ --std=c++11 -o heatFlow.out heatFlow.cpp
```

## Generate Graph (after execute ./heatFlow.out)
```sh
$ ./graph-gen.sh
```

## Generate Video from Graphs (after generate graphs)
Require [ffmpeg](https://www.ffmpeg.org/)
```sh
$ ./video-gen <framerate> # output ./out.<framerate>x.mp4
```
