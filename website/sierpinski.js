var c = document.getElementById("sierpinski");
var context = c.getContext("2d");
context.fillStyle = "white";
context.fillRect(0, 0, c.width, c.height);
var base="F-G-G"
var iter=0
function iterate(){
	var next=''
	for (var i =0;i<base.length;i++){
		if (base.charAt(i)=='F'){
			next=next+'F-G+F+G-F'
		}else if (base.charAt(i)=='G'){
			next=next+'GG'
		}else{
			next=next+base.charAt(i)
		}
	}
	base=next
}

function draw(){
	var x=500
	var y=350
	var rotScale=-2*Math.PI/3
	var rot=Math.PI
	var dist=3
	context.moveTo(x,y);
	for (var i=0;i<base.length;i++){
		if(base.charAt(i)=="F" || base.charAt(i)=="G"){
			x+=Math.cos(rot)*dist;
			y+=Math.sin(rot)*dist;
		}else if(base.charAt(i)=="-"){
			rot-=rotScale
		}else if(base.charAt(i)=="+"){
			rot+=rotScale
		}
		context.lineTo(x,y);
		setTimeout(100);
	}
	context.stroke();
}

var main=setInterval(function(){
	if(iter<7){
		iterate();
		iter++;
		context.beginPath();
		context.fillRect(0, 0, c.width, c.height);
		draw();
	}else{
		iter=0;
		base="F-G-G"
	}
},1000);

