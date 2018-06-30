sessionStorage.setItem("uniqueIdSessionStorage", "xyz");
var barnsley = document.getElementById("conway");
var barnsleyContext = barnsley.getContext("2d");
var x=0;
var y=0;
var scale=40;
var xoffset=barnsley.width/2;
var yoffset=barnsley.height;
barnsleyContext.fillStyle = "white";
barnsleyContext.fillRect(0, 0, barnsley.width, barnsley.height);

var main=setInterval(function(){
	for(var i=0;i<1000;i++){
		var xn=0;
		var yn=0;
		var r=Math.random()*100;
		if(r<1){
			xn=0;
			yn=.16*y;
		}else if(r<86){
			xn=.85*x+.04*y;
			yn=-.04*x+.85*y+1.6;
		}else if(r<93){
			xn=.2*x-.26*y;
			yn=.23*x+.22*y+1.6;
		}else{
			xn=-.15*x+.28*y;
			yn=.26*x+.24*y+.44;
		}
		x=xn;
		y=yn;
		barnsleyContext.fillStyle = "green";
		barnsleyContext.fillRect(xoffset+x*scale,yoffset-y*scale,1,1);
	}
	barnsleyContext.stroke();
},1);

