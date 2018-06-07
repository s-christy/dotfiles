PVector a;
PVector av;
PVector aa;

float damping=.01;

void setup(){
  size(500,500);
  a=new PVector(250,250);
  av=new PVector(0,0);
  aa=new PVector(0,0);
}

void draw(){
  background(0);
  fill(255);
  ellipse(a.x,a.y,20,20);
  aa.x=.05*(mouseX-a.x)-damping*av.x;
  av.x+=aa.x;
  a.x+=av.x;
  aa.y=.05*(mouseY-a.y)-damping*av.y;
  av.y+=aa.y;
  a.y+=av.y;
}
