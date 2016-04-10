/* @pjs preload="pics/star.png"; */
/* @pjs preload="pics/heart.png"; */

Maze maze;
Ball ball;
History history;
ArrayList<node> visited;
PImage star;
PImage heart;
boolean solved;
int score;
int lives;

void setup() {
 size(621, 485); 
 background(255);
 stroke(0, 190, 255);
 strokeWeight(2.0);
 strokeCap(ROUND);
 strokeJoin(ROUND);
 visited = new ArrayList<node>();
 maze = new Maze(23, 31);
 maze.generateMaze();
 ball = new Ball(1, 23, maze.maze);
 history = new History();
 star = loadImage("pics/star.png");
 star.resize(15, 15);
 heart = loadImage("pics/heart.png");
 heart.resize(15, 15);
 solved = false;
 score = 0;
 lives = 3;
 textSize(14);
}

void draw() {
  //main background
  fill(255, 77);
  filter(BLUR);
  rect(0, 0, width, 461);
  
  //score rect
  noStroke();
  fill(255);
  rect(0, 461, width, 24);
  fill(0, 190, 255);
  text(score, 530, 479);
  if (score > 99) {
    image(star, 560, 467);
  }
  else {
    image(star, 550, 467);
  }
  for (int i = 0; i < lives; i++) {
    heart.resize(15, 15);
    image(heart, 50 + (i * 20), 467);
  }
  
  //game
  if (lives > 0) {
    if (!isSolved(ball)) {
      image(star, 602, 222);
      history.display();
      maze.display();
      ball.display();
    }
    else {
      maze.generateMaze();
      ball = new Ball(1, 23, maze.maze);
      history.clear();
    }
  }
  else { //reset
    score = 0;
    lives = 3;
    maze.generateMaze();
    ball = new Ball(1, 23, maze.maze);
    history.clear();
  }
}

void keyPressed() {
  if (key == CODED) {
    if (keyCode == UP) {
      ball.up();
    } 
    else if (keyCode == DOWN) {
      ball.down();
    } 
    else if (keyCode == LEFT) {
      ball.left();
    } 
    else if (keyCode == RIGHT) {
      ball.right();
    } 
  } 
}

var game = document.getElementById("demo");
game.addEventListener('touchstart', handleTouchStart, false);        
game.addEventListener('touchmove', handleTouchMove, false);

var xDown = null;                                                        
var yDown = null;                                                        

function handleTouchStart(evt) {                                         
    xDown = evt.touches[0].clientX;                                      
    yDown = evt.touches[0].clientY;                                      
};                                                

function handleTouchMove(evt) {
    if ( ! xDown || ! yDown ) {
        return;
    }

    var xUp = evt.touches[0].clientX;                                    
    var yUp = evt.touches[0].clientY;

    var xDiff = xDown - xUp;
    var yDiff = yDown - yUp;

    if ( Math.abs( xDiff ) > Math.abs( yDiff ) ) {/*most significant*/
        if ( xDiff > 0 ) {
            /* left swipe */ 
			ball.left();
        } else {
            /* right swipe */
			ball.right();
        }                       
    } else {
        if ( yDiff > 0 ) {
            /* up swipe */ 
			ball.up();
        } else { 
            /* down swipe */
			ball.down();
        }                                                                 
    }
    /* reset values */
    xDown = null;
    yDown = null;                                             
};
///////////////////////////////////////////////////////
boolean isSolved(Ball b) {
 if (b.position.y != 23 || b.position.x != 61) {
   solved = false;
   return false;
 }
 score++;
 if (score % 3 == 0 && score > 0 && lives < 5) {
   lives++;
 }
 solved = true;
 return true;
}
///////////////////////////////////////////////////////
class Ball {
 PVector position;
 char[][] maze;
 float speed = 2; //1 or 2
 
 Ball(int x, int y, char[][] m) {
   position = new PVector(x, y);
   maze = m;
 }
 
 void up() {
   if(maze[int(position.y - 1)][int(position.x)] == ' ') {
     history.add(position.x, position.y);
     position.y -= speed;
     if (history.path.size() > 1) {
       if (history.path.get(history.path.size() - 2).x == position.x * 10 && history.path.get(history.path.size() - 2).y == position.y * 10) {
         history.clear();
         lives -= 1;
       }
     }
   }
 }
 void down() {
   if(maze[int(position.y + 1)][int(position.x)] == ' ') {
     history.add(position.x, position.y);
     position.y += speed;
     if (history.path.size() > 1) {
       if (history.path.get(history.path.size() - 2).x == position.x * 10 && history.path.get(history.path.size() - 2).y == position.y * 10) {
         history.clear();
         lives -= 1;
       }
     }
   }
 }
 void left() {
   if(maze[int(position.y)][int(position.x - 1)] == ' ') {
     history.add(position.x, position.y);
     position.x -= speed;
     if (history.path.size() > 1) {
       if (history.path.get(history.path.size() - 2).x == position.x * 10 && history.path.get(history.path.size() - 2).y == position.y * 10) {
         history.clear();
         lives -= 1;
       }
     }
   }
 }
 void right() {
   if(maze[int(position.y)][int(position.x + 1)] == ' ') {
     history.add(position.x, position.y);
     position.x += speed;
     if (history.path.size() > 1) {
       if (history.path.get(history.path.size() - 2).x == position.x * 10 && history.path.get(history.path.size() - 2).y == position.y * 10) {
         history.clear();
         lives -= 1;
       }
     }
   }
 }
 
 void display() {
   fill(255, 0, 0);
   stroke(255, 0, 0);
   ellipse(position.x * 10, position.y * 10, 10, 10);
 }
}
///////////////////////////////////////////////////////
class History {
  ArrayList<PVector> path;
  
  History() {
    path = new ArrayList<PVector>(0);
  }
  
  void add(float x, float y) {
    path.add(new PVector(x * 10, y * 10));
  }
  
  void clear() {
    path.clear();
  }
  
  void display() {
    fill(255, 200, 200);
    stroke(255, 200, 200);
    for (int i = 0; i < path.size(); i++) {
      ellipse(path.get(i).x, path.get(i).y, 3, 3);
    }
  }
}
///////////////////////////////////////////////////////
class Maze {
 char[][] maze;
 PVector2[][] map; 
 int h;
 int l;
 
 Maze(int arr_height, int arr_length) {
  maze = new char[2 * arr_height + 1][2 * arr_length + 1];
  h = arr_height;
  l = arr_length;
  map = new PVector2[2 * arr_height + 1][2 * arr_length + 1]; 
 }
 
 void generateMaze() {
  visited.clear();
  maze = gen_hard(h, l);
  map = text2map(maze, h, l);
 }
 
 void display() {
   stroke(0, 190, 255);
   for (int i = 0; i < 2 * h + 1; i++) {
    for (int j = 0; j < 2 * l + 1; j++) {
      if (map[i][j].start.x != map[i][j].end.x || map[i][j].start.y != map[i][j].end.y) {
        line(map[i][j].start.y, map[i][j].start.x, map[i][j].end.y, map[i][j].end.x);
      }
      else if (map[i][j].start.x == map[i][j].end.x && map[i][j].start.y == map[i][j].end.y) {
        //ellipse(map[i][j].start.y * -1, map[i][j].start.x * -1, 1, 1);
      }
    }
   }
 }
}
///////////////////////////////////////////////////////
class PVector2 {
  PVector start;
  PVector end;
  
  PVector2(PVector s, PVector e) {
   start = s;
   end = e;
  }
}
///////////////////////////////////////////////////////
class node {
  int i;
  int j;
  node() {
   i = 1;
   j = 1;
  }
  node(int a, int b) {
   i = a;
   j = b;
  }
  node(node x) {
   i = x.i;
   j = x.j;
  }
}
///////////////////////////////////////////////////////
boolean is_visited(node x) {
 for (int i = 0; i < visited.size(); i++) {
  if (visited.get(i).i == x.i && visited.get(i).j == x.j) {
   return true; 
  }
 }
 return false;
}
///////////////////////////////////////////////////////
char[][] gen_hard(int arr_height, int arr_length) {
  //init
  arr_height = 2 * arr_height + 1;
  arr_length = 2 * arr_length + 1;
  char[][] temp = new char[arr_height][arr_length];
  for (int a = 0; a < arr_height; a++) {
   for (int b = 0; b < arr_length; b++) {
       temp[a][b] = 'x';
     }
  }
  for (int a = 1; a < arr_height; a += 2) {
   for (int b = 1; b < arr_length; b += 2) {
       temp[a][b] = ' ';
     }
  }
  //create path
  ArrayList <node> PATH = new ArrayList<node>();
  ArrayList <String> choices = new ArrayList<String>();
  boolean complete = false;
  int i = 1;
  int j = 1;
  node root = new node(i, j);
  PATH.add(root);
  visited.add(root);
  while (!complete) {
    node n1 = new node(i - 2, j);
    node n2 = new node(i + 2, j);
    node n3 = new node(i, j - 2);
    node n4 = new node(i, j + 2);
   
    if (i - 2 > 0 && temp[i - 1][j] != ' ' && !is_visited(n1)) {
      choices.add("u");
    }
    if (i + 2 < arr_height - 1 && temp[i + 1][j] != ' ' && !is_visited(n2)) {
      choices.add("d");
    }
    if (j - 2 > 0 && temp[i][j - 1] != ' ' && !is_visited(n3)) {
      choices.add("l");
    }
    if (j + 2 < arr_length - 1 && temp[i][j + 1] != ' ' && !is_visited(n4)) {
      choices.add("r");
    }
    
    if (choices.size() > 0) {
      boolean moved = false;
      while (!moved) {
        int x = int(random(0, choices.size()));
        if (choices.get(x) == "u") {
          if (i - 2 > 0) {
            temp[i - 1][j] = ' ';
            i -= 2;
          }
          PATH.add(n1);
          visited.add(n1);
          moved = true;
        }
        if (choices.get(x) == "d") {
          if (i + 2 < arr_height - 1) {
            temp[i + 1][j] = ' ';
            i += 2;
          }
          PATH.add(n2);
          visited.add(n2);
          moved = true;
        }
        if (choices.get(x) == "l") {
          if (j - 2 > 0) {
            temp[i][j - 1] = ' ';
            j -= 2;
          }
          PATH.add(n3);
          visited.add(n3);
          moved = true;
        }
        if (choices.get(x) == "r") {
          if (j + 2 < arr_length - 1) {
            temp[i][j + 1] = ' ';
            j += 2;
          }
          PATH.add(n4);
          visited.add(n4);
          moved = true;
        }
      }
    }
    else {
      PATH.remove(PATH.size() - 1);
      if (PATH.size() != 0) {
        i = PATH.get(PATH.size() - 1).i;
        j = PATH.get(PATH.size() - 1).j;
      }
    }
    choices.clear();
    if (PATH.size() == 0) {
      complete = true;
    }
  }  

  //change 'x' to walls
  for (i = 0; i < arr_height; i++) {
   for (j = 0; j < arr_length; j++) {
     boolean up = false;
     boolean down = false;
     boolean left = false;
     boolean right = false;
     if (temp[i][j] == 'x') {
       if (j - 1 >= 0) {
         if (temp[i][j - 1] != ' ') {
           left = true;
         }
       }
       if (j + 1 < arr_length) {
         if (temp[i][j + 1] != ' ') {
           right = true;
         }
       }
       if (i - 1 >= 0) {
         if (temp[i - 1][j] != ' ') {
           up = true;
         }
       }
       if (i + 1 < arr_height) {
         if (temp[i + 1][j] != ' ') {
           down = true;
         }
       }
       
       if (left && right && !(up && down)){
         temp[i][j] = '-';
       }
       else if (up && down && !(left && right)) {
         temp[i][j] = '|';
       }
       else {
         temp[i][j] = '+';
       }
     }
   }
  }
  return temp;
}
///////////////////////////////////////////////////////
PVector2[][] text2map(char[][] temp, int arr_height, int arr_length) {
  arr_height = 2 * arr_height + 1;
  arr_length = 2 * arr_length + 1;
  PVector2[][] map = new PVector2[arr_height][arr_length];
  
  for(int i = 0; i < arr_height; i++) {
    for(int j = 0; j < arr_length; j++) {
      if (temp[i][j] == '+') {
        map[i][j] = new PVector2(new PVector(i * -10, j * -10), new PVector(i * -10, j * -10)); //negatives used as markers
      }
      else if (temp[i][j] == ' ') {
        map[i][j] = new PVector2(new PVector(i, j), new PVector(i, j)); //ignored in display
      } 
      else if (temp[i][j] == '-') {
          map[i][j] = new PVector2(new PVector(i * 10, (j - 1) * 10), new PVector(i * 10, (j + 1) * 10));
      }
      else if (temp[i][j] == '|') {
          map[i][j] = new PVector2(new PVector((i - 1) * 10, j * 10), new PVector((i + 1) * 10, j * 10));
      }
    }
  }  
  return map;
}
