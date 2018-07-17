//see: https://en.wikipedia.org/wiki/Chaos_theory#Chaotic_dynamics
function setup(){
	var c = document.getElementById("test");
	var ctx = c.getContext("2d");
	ctx.fillStyle = "grey";
	ctx.fillRect(0, 0, c.width, c.height);
	var x=Math.random();
	var y=Math.random();

	var main=setInterval(function(){
		for(var i=0;i<4;i++){
			ctx.beginPath();
			ctx.moveTo(x*c.width,y*c.height);
			xn=4*x*(1-x)
			yn=x+y
			xn=xn%1
			yn=yn%1
			if(xn<0)xn+=1;
			if(yn<0)yn+=1;
			ctx.lineTo(xn*c.width,yn*c.height);
			x=xn;
			y=yn;
			ctx.strokeStyle="white";
			ctx.stroke();
		}
	},1000/30);
}
setup();

