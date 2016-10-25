# heatFlowSimulate
## Compile
```sh
$ g++ --std=c++11 -o heatFlow.out heatFlow.cpp
```

## Generate Graph
```sh
$ ./graph-gen.sh
```

## Generate Video from Graphs
Require [ffmpeg](https://www.ffmpeg.org/)
```sh
$ ./video-gen <framerate> # output ./out.<framerate>x.mp4
```
