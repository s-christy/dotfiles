function setup(){
	var c = document.getElementById("test");
	var ctx = c.getContext("2d");
	ctx.fillStyle = "grey";
	ctx.fillRect(0, 0, c.width, c.height);
	ctx.globalAlpha=.2;

	var scale=.05;
	for(var i=0;i<100;i++){
		var x=.5;
		var y=.5;
		var rot=0.0;
		ctx.beginPath();
		ctx.moveTo(x*c.width,y*c.height);
		for(var j=0;j<10;j++){
			x+=scale*Math.cos(rot);
			y+=scale*Math.sin(rot);
			rot+=Math.random()-.5;
			ctx.lineTo(x*c.width,y*c.height);
			ctx.strokeStyle="white";
			ctx.stroke();
		}
	}
}
setup();

