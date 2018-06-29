var canvas = document.getElementById('canvas');
var ctx = canvas.getContext('2d');
var x=150;
var y=150;
var rot=2*Math.PI/3;
count=0;
ctx.beginPath();
ctx.moveTo(x,y);
function clear(){
	count=0;
	ctx.beginPath();
	ctx.moveTo(x,y);
	ctx.clearRect(0,0,canvas.width,canvas.height);
}

function f(){
	len=count;
	ctx.lineTo(x+len*Math.cos(count*rot),y+len*Math.sin(count*rot));
	ctx.stroke();
	count+=1.01
}
main=setInterval(function(){
	f()
	if(count>300000){
		//clear();
	}
}, 10);


