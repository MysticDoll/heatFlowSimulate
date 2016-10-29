#!/bin/bash
expr $1 + 1 > /dev/null 2>&1
if [ $? -lt 2 ]
then
  ret=$1
else
  ret=1
fi

if [ $# -ne 1 ]; then
  ret=1
fi

echo $ret

ffmpeg -r $ret -i ./graph/%5d.png -c:v libx264 -pix_fmt yuv420p "out."$ret"fps.mp4" 
