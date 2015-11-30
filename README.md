# Maze-Master
Create mazes of any size and solve them! A* search algorithm is used to solve the mazes.

Start from either of the two openings along the top & bottom walls or the left & right walls and make your way across the maze to the other endpoint to solve. 

## Creator
### Instructions
To generate a maze: 
* Navigate to the `creator` directory
* Compile `main.cpp` (i.e. `g++ main.cpp`)
* Run the program (i.e. `./a.out`)
* Add arguments to the command line to skip the UI (i.e. `./a.out 47 15 E`)

### Examples
Easy Maze | Hard Maze
:--------:|:---------:
![img](http://imgur.com/i8JCV6S.png) | ![img](http://imgur.com/A61aLOR.png)

## Solver
## Instructions
To solve a maze:
* Navigate to the `solver` directory
* Compile `main.cpp` (i.e. `g++ main.cpp`)
* Run the program (i.e. `./a.out)
* Add the file path as the argument to skip the UI (i.e. `./a.out maze.txt`)

### Examples
Easy Maze Solved | Hard Maze Solved
:---------------:|:----------------:
![img](http://imgur.com/SIomL9r.png) | ![img](http://imgur.com/eAd3qGE.png)


### UI for Linux
A simple UI for creating and solving a maze is provided for Linux users in the bash script `mazemaster.sh`.
Convert the file to an executable by running `chmode u+x mazemaster.sh` in the original directory.
Run the program by entering `./mazemaster.sh` in the original directory.

## Features
* Maze creator with user's choice of dimensions and difficulty setting.
  * Maze dimensions are recommended to be within the dimensions of the console for viewing purposes.
  * Easy difficulty provides multiple solutions to the maze.
  * Hard difficulty provides one unique solution to the maze.
* Maze solver uses A* search to find a solution to a maze (if a solution is possible) and prints the result.
