int numParts=5000;
particle plist[]=new particle[numParts];
float initV=50;
float step=.0000001;

void setup() {
  size(500, 500, P3D);
  for (int i=0; i<numParts; i++) {
    plist[i]=new particle(new PVector(random(width), random(height), random(width)), new PVector(random(initV)-initV/2.0, random(initV)-initV/2.0, random(initV)-initV/2.0));
    //plist[i].pos=plist[i].pos.mult(.1);
  }
}

void draw() {
  background(255);
  for (int i=0; i<numParts; i++) {
    plist[i].show();
    plist[i].update();
  }
}

class particle {
  PVector pos;
  PVector dir;
  particle(PVector posi, PVector diri) {
    pos=posi;
    dir=diri;
  }
  void show() {
    //stroke(0);
    //if(pos.z>0){
    //  strokeWeight(pos.z/100.0);
    //}else{
    //  stroke(0);
    //}
    stroke(3);
    point(pos.x, pos.y, pos.z);
  }
  void update(){
    pos=pos.add(dir);
    for(int i=0;i<numParts;i++){
      dir.x-=step*(pos.x-plist[i].pos.x);
      dir.y-=step*(pos.y-plist[i].pos.y);
      dir.z-=step*(pos.z-plist[i].pos.z);
      //dir=pos.sub(plist[i].pos);
    }
  }
}
