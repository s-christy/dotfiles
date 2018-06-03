float scale=20;
float inc=.01;
float inc2=.0001;
float iterations=1000;
float count=1;
int brush=2;
PVector initV= new PVector(0.0, 1.0, 1.05);

void setup() {
  size(200, 200, P3D);
  background(255);
  frameRate(1000000);
}
void draw() {
  translate(width/2, height/2, -200);
  rectMode(CENTER);
  stroke(0, 0, 0, 10);
  strokeWeight(brush);
  float sigma=10.0;
  float rho=28.0;
  float beta=2.6667;
  for (float t=0; t<iterations; t++) {
    float x=initV.x;
    float y=initV.y;
    float z=initV.z;
    initV.x+=inc*(sigma*(y-x));
    initV.y+=inc*(-x*z+rho*x-y);
    initV.z+=inc*(x*y-beta*z);
    line(scale*initV.x, scale*initV.y, scale*initV.z, scale*x, scale*y, scale*z);
  }
}
