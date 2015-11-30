#!/bin/bash

g++ ./creator/main.cpp -o create.o
g++ ./solver/main.cpp -o solve.o

echo "Welcome to Maze Master!"
echo ""

width=0
height=0
difficulty=""
echo "Enter the width of the maze: "
while [ $width -le 0 ]; do
	read width
done
echo "Enter the height of the maze: "
while [ $height -le 0 ]; do
	read height
done
echo "Enter E for an easy maze, enter H for a hard maze: "
while [[ $difficulty != "E" && $difficulty != "H" ]]; do
	read difficulty
done

./create.o $width $height $difficulty | tee maze.txt

solution=""
echo "Would you like to view the solution? (Y/N): "
while [[ $solution != "Y" && $solution != "N" ]]; do
	read solution
done

if [[ $solution == "Y" ]]; then
	./solve.o maze.txt 
fi
