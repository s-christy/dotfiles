var canvas = document.getElementById('canvas');
var ctx = canvas.getContext('2d');
count=0;
ctx.beginPath();
ctx.moveTo(75,75);
function clear(){
	count=0;
	ctx.beginPath();
	ctx.moveTo(75,75);
	ctx.clearRect(0,0,canvas.width,canvas.height);
}

function f(){
	len=count;
	ctx.lineTo(75+len*Math.cos(count*3*Math.PI/2),75+len*Math.sin(count*3*Math.PI/2));
	ctx.stroke();
	count+=1.01
}
main=setInterval(function(){
f()
if(count>100){
clear();
}
}, 10);


