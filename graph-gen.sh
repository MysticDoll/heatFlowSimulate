#!/bin/bash

x=0;
while [ $x -lt 1000 ]; do i=``
  gnuplot -e "set pm3d map; set cbrange[300:800]; splot \"./dat/"$x".mesh.dat\" using 1:2:3; set terminal png; set out \"./graph/"$(printf %03d $x)".png\"; replot;"
  x=$((x + 1))
done
