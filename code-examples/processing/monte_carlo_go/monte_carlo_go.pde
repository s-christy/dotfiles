

class board {
  int size=10;
  int w=30;
  int offset=100;
  int [][] b=new int[size][size];
  board() {
    for (int i=0; i<size; i++) {
      for (int j=0; j<size; j++) {
        b[i][j]=-1;
      }
    }
    //b[2][2]=1;
    //b[5][4]=0;
    //b[0][0]=0;
    //b[9][9]=0;
  }
  void display() {
    for (int i=0; i<size; i++) {
      for (int j=0; j<size; j++) {
        noFill();
        rect(offset+i*w, offset+j*w, w, w);
        if (b[i][j]==0) {
          fill(255);
          ellipse(offset+i*w+w/2, offset+j*w+w/2, w, w);
        } else if (b[i][j]==1) {
          fill(0);
          ellipse(offset+i*w+w/2, offset+j*w+w/2, w, w);
        }
      }
    }
  }
}

board b=new board();

void setup() {
  size(500, 500);
}

void mouseClicked() {
  for (int i=0; i<b.size; i++) {
    for (int j=0; j<b.size; j++) {
      if (mouseX>b.offset+i*b.w && mouseY>b.offset+j*b.w &&
        mouseX<b.offset+i*b.w+b.w && mouseY<b.offset+j*b.w+b.w) {
        b.b[i][j]=1;
      }
    }
  }
}

int pickRandom(int side){
  int numOpen=0;
  for (int i=0; i<b.size; i++) {
    for (int j=0; j<b.size; j++) {
      if (b.b[i][j]==-1)numOpen++;
    }
  }
  int indOpen=0;
  int rand=(int)random(numOpen);
  for (int i=0; i<b.size; i++) {
    for (int j=0; j<b.size; j++) {
      if (b.b[i][j]==-1) {
        if (rand==indOpen)b.b[i][j]=side;
        indOpen++;
      }
    }
  }
  return numOpen;
}

void draw() {
  background(100);
  b.display();
  pickRandom(0);
  pickRandom(1);
}
