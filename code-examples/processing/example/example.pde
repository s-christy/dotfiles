ArrayList<point> points;
int numPoints=4;

void setup() {
  size(600, 600);
  points=new ArrayList<point>();
  for (int i=0; i<numPoints; i++) {
    points.add(new point());
  }
}

void interp() {
  stroke(255);
  strokeWeight(1);
  //linear();
  linear2();
}

void linear2() {
  for (int i=0; i<numPoints-1; i++) {
    point p1=points.get(i);
    point p2=points.get(i+1);
    for (float t=0; t<1; t+=.01) {
      line(map(t, 0, 1, p1.pos.x, p2.pos.x), map(t, 0, 1, p1.pos.y, p2.pos.y), map(t+.01, 0, 1, p1.pos.x, p2.pos.x), map(t+.01, 0, 1, p1.pos.y, p2.pos.y));
    }
  }
}

void linear() {
  for (int i=0; i<numPoints-1; i++) {
    point p1=points.get(i);
    point p2=points.get(i+1);
    for (float t=0; t<1; t+=.01) {
      line(map(t, 0, 1, p1.pos.x, p2.pos.x), map(t, 0, 1, p1.pos.y, p2.pos.y), map(t+.01, 0, 1, p1.pos.x, p2.pos.x), map(t+.01, 0, 1, p1.pos.y, p2.pos.y));
    }
  }
}

void draw() {
  if (mousePressed) {
    points.get(2).pos.x=mouseX;
    points.get(2).pos.y=mouseY;
  }
  background(50);
  for (int i=0; i<numPoints; i++) {
    point p=points.get(i);
    p.show();
  }
  interp();
}

class point {
  PVector pos=new PVector(random(width), random(width));
  void show() {
    ellipse(pos.x, pos.y, 10, 10);
  }
}
