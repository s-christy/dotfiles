ArrayList<point> points;
int numPoints=4;

void setup() {
  size(600, 600);
  points=new ArrayList<point>();
  for (int i=0; i<numPoints; i++) {
    points.add(new point(i));
  }
}

void interp() {
  stroke(255);
  strokeWeight(1);
  for (int i=0; i<numPoints-1; i++) {
    point p1=points.get(i);
    point p2=points.get(i+1);
    for (float t=0; t<1; t+=.01) {
      line(linear(t, p1.x, p2.x), linear(t, p1.y, p2.y), linear(t+.01, p1.x, p2.x), linear(t+.01, p1.y, p2.y));
      line(poly(t, p1.x, p2.x), poly(t, p1.y, p2.y), poly(t+.01, p1.x, p2.x), poly(t+.01, p1.y, p2.y));
    }
  }
}
float linear(float t,float x1,float x2){
  return t*(x2-x1)+x1;
}
float poly(float t,float x1,float x2){
  return t*(x2-x1)+x1+10;
}

void draw() {
  if (mousePressed) {
    //points.get(2).pos.x=mouseX;
    points.get(2).y=mouseY;
    points.get(2).value=mouseY;
  }
  background(50);
  for (int i=0; i<numPoints; i++) {
    point p=points.get(i);
    p.show();
  }
  interp();
}

class point {
  float x;
  point(float xpos){
    x=map(xpos,0,numPoints,0,width);
  }
//  PVector pos=new PVector(random(width), random(width));
  float value=random(height);
  float y=value;
  void show() {
    ellipse(x, value, 10, 10);
  }
}
