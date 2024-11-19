/*************
 **  PA4_GWheat
 **  GABE  WHEAT
 **  4/15/2022
 **  gwheat1@umbc.edu
 **  zig zags pacman while bouncing off 
 **  top and bottom and wrapping around
 **  
 */
 
//variables
  float[] xPos = new float[100];
  float[] yPos = new float[100];
  PShape ghost, body, head, foot1,foot2,foot3, eye1, eye2, pup1, pup2;
  float pacmanX = 600;
  float pacmanY = 250;
  float ghostX = 80;
  float ghostY = 80;
  float xDelta = 2;
  float yDelta = 4;
  float easing = 0.008;
  final float PACMAN_SIZE = 70;
  final float GHOST_SIZE = 70;
  float dotSize = 6;
  int score = 0;
  float pacmanMove = 5;
/*
 * setup - prepares envirnment size and color
 */
void setup() {
  //set canvas size and color
  size(1200, 500);
  background(0);
  frameRate(90);
  dotPositions();

  
}

/*
 * draw - move pacman on diagonals and bounce off top 
 * and bottom while rapping around left to right
 */
void draw() {
  if (score <= 50){
    background(0);

    drawPacman();
    //move Pacman
    makePacmanMove();

    //draws ghost and sets bounds
    drawGhost();

    drawDots();

    fill(255, 0 , 0);
    textSize(40);
    text("Score: ", 1000, 40);
    text(score, 1150, 40);
    gameOver();
  }
}





void drawPacman() {
background(0);
  fill(255,255,0);
  arc(pacmanX,pacmanY,70,70,radians(50),radians(320));
}
/*
 * DrawPacman - draws a packman a the given x, y
 */

  
void makePacmanMove() {
  makePacmanBound();
  makePacmanWrap();

  if(key == CODED) {
    if(keyCode == UP) {
      pacmanY -= pacmanMove;
    }
  else if(keyCode == DOWN) {
    pacmanY += pacmanMove;
  }
  else if(keyCode == LEFT) {
    pacmanX -= pacmanMove;
  }
  else if(keyCode == RIGHT) {
    pacmanX += pacmanMove;
  }
}
}
/*
 * makePacmanBounce - redirects pacman to opposite direction 
 * when hitting top/bottom
 */
void makePacmanBound() {
   

  if (pacmanY > height - PACMAN_SIZE/2){ 
    pacmanY = height - PACMAN_SIZE/2;
  } else if (pacmanY < PACMAN_SIZE/2){
    pacmanY = PACMAN_SIZE/2;
    
}


}
/*
 * makePacmanWrap - puts pacman on left when it reaches right
 */
void makePacmanWrap() {
  if(pacmanX == width + PACMAN_SIZE/2){
    pacmanX = 0;
  } else if (pacmanX < 0) {
    pacmanX = width;
  }
}

  
void drawGhost() {
noStroke();
  // create shape group  
  ghost = createShape(GROUP);
  
//create body of ghost
  body = createShape(RECT, 0, 0, GHOST_SIZE, GHOST_SIZE/2);
  body.setFill(#3427FF);

//create arc of ghost
  head = createShape(ARC, 35, 0, GHOST_SIZE, GHOST_SIZE, PI, TWO_PI);
  head.setFill(#3427FF);

// create bottom half of ghost 
  foot1= createShape(TRIANGLE, 0, GHOST_SIZE/2, 0, 60, 20, GHOST_SIZE/2);
  foot1.setFill(#3427FF);
  foot2= createShape(TRIANGLE, 20, GHOST_SIZE/2, 35, 60, 50, GHOST_SIZE/2);
  foot2.setFill(#3427FF);
  foot3= createShape(TRIANGLE, 50, GHOST_SIZE/2, GHOST_SIZE, 60, GHOST_SIZE, GHOST_SIZE/2);
  foot3.setFill(#3427FF);

//create eyes
  eye1 = createShape(ELLIPSE, 17, 0, 20, 20);
  eye1.setFill(255);
  eye2 = createShape(ELLIPSE, 53, 0, 20, 20);
  eye2.setFill(255);

//make pupils
  pup1 = createShape(ELLIPSE, 17, 0, 10, 10);
  pup1.setFill(#3427FF);
  pup2 = createShape(ELLIPSE, 53, 0, 10, 10);
  pup2.setFill(#3427FF);

//add all parts of ghost to group
  ghost.addChild(body);
  ghost.addChild(head);
  ghost.addChild(foot1);
  ghost.addChild(foot2);
  ghost.addChild(foot3);
  ghost.addChild(eye1);
  ghost.addChild(eye2);
  ghost.addChild(pup1);
  ghost.addChild(pup2);
  shape(ghost, ghostX, ghostY);
  moveGhost();
}

void moveGhost() {
  // make ghost follow mouse
  float targetX = pacmanX;
  float targetY = pacmanY;
  float dx = targetX - ghostX;
  ghostX += dx * easing;
  float dy = targetY - ghostY;
  ghostY += dy * easing;

  // make it so the ghost does not go past the end of screen
  if (ghostX >= width -75){
    ghostX = width -76;
  } else if (ghostX <0){
    ghostX = 0;
  } else if (ghostY >= height - 65) {
    ghostY = height -65;
  } else if (ghostY <= 35){
    ghostY = 35;
  } else{
    shape(ghost, ghostX, ghostY);
  }
  }

 void dotPositions() {
   for (int i= 0; i <50; i++ ) {
   xPos[i] = random(10,1150);
    yPos[i] = random(10,490);
   
   
 }
 }
 void drawDots() {
  // draw dots and make them dissapear when pac man goes over them 
   fill(255);
    for (int i= 0; i <50; i++ ) {
    ellipse(xPos[i], yPos[i], dotSize, dotSize);
    float dist = sqrt((xPos[i] - pacmanX) * (xPos[i] - pacmanX) + (yPos[i] - pacmanY) * (yPos[i] -pacmanY));
   if(dist <= 35) {
     xPos[i] = -100;
     yPos[i] = -100;
     score = score +1;
     break;
     
   } 

 }
 }
 void gameOver() {
   float dist = sqrt((pacmanX - ghostX) * (pacmanX - ghostX) + (pacmanY - ghostY) * (pacmanY - ghostY));
  if(dist <= PACMAN_SIZE  + 25){
    background(0);
    fill(255);
    textSize(90);
    text("You Suck", (width/4)-150, height/2);
    pacmanX = ghostX;
    pacmanY = ghostY;
  } else if (score >= 50){
    background(0);
    fill(255);
    textSize(120);
    text("WIN", (width/4)-150, height/2);
    pacmanX = width+ 800;
    pacmanY = height + 600;
  }
}
