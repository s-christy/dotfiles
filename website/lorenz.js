function setup(){
	var c = document.getElementById("test");
	var ctx = c.getContext("2d");
	ctx.fillStyle = "grey";
	ctx.fillRect(0, 0, c.width, c.height);
	//ctx.globalAlpha=.007;

	ctx.beginPath();
	var initV= [0.0, 1.0, 1.05];
	var sigma=10.0;
	var rho=28.0;
	var beta=2.6667;
	var scale=8;
	var inc=.015;
	var main=setInterval(function(){
		for(var i=0;i<100;i++){
			var x=initV[0];
			var y=initV[1];
			var z=initV[2];
			initV[0]+=inc*(sigma*(y-x));
			initV[1]+=inc*(-x*z+rho*x-y);
			initV[2]+=inc*(x*y-beta*z);


			//ctx.moveTo(scale*initV[0]+c.width/2,scale*initV[1]+c.height/2);
			ctx.lineTo(scale*x+c.width/2,scale*y+c.height/2);
			ctx.strokeStyle="white";
			ctx.lineWidth=1;
			ctx.stroke();
		}
	},1000/30);
}
setup();

/*
 *
float scale=20;
float inc=.01;
float inc2=.0001;
float iterations=1000;
float count=1;
int brush=2;
PVector initV= new PVector(0.0, 1.0, 1.05);
boolean loop=true;

void setup() {
  size(200, 200, P3D);
  background(0);
  frameRate(1000000);
}
void draw() {
  translate(width/2, height/2, -5000);
  rectMode(CENTER);
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
    stroke(255, 150, 0, 10);
    count++;
    line(scale*initV.x, scale*initV.y, scale*initV.z, scale*x, scale*y, scale*z);
  }
}
void mousePressed() {
  if (loop) {
    noLoop();
    loop=false;
  } else {
    loop();
    loop=true;
  }
}
 */
