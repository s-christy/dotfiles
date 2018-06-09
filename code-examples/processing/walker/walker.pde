PVector p;

void setup() {
  p=new PVector(0, 0);
  size(500, 500);
  background(50);
  p.x=250;
  p.y=250;
}

void draw() {
  for (int i=0; i<500; i++) {
    fill(255);
    noStroke();
    ellipse(p.x, p.y, 1, 1);
    p.x+=random(2)-1;
    p.y+=random(2)-1;
  }
}
