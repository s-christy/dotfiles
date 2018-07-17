//see: https://en.wikipedia.org/wiki/Chaos_theory#Chaotic_dynamics

function shuffle(array) {
	let counter=array.length;
	while (counter>0) {
		let index=Math.floor(Math.random()*counter);
		counter--;
		let temp=array[counter];
		array[counter]=array[index];
		array[index]=temp;
	}
	return array;
}

function display(ctx,c,nextPoints) {
	//display it
	ctx.fillStyle = "grey";
	ctx.fillRect(0, 0, c.width, c.height);
	for(var i=0;i<nextPoints.length-1;i++){
		ctx.beginPath();
		ctx.moveTo(nextPoints[i][0]*c.width,nextPoints[i][1]*c.height);
		ctx.lineTo(nextPoints[i+1][0]*c.width,nextPoints[i+1][1]*c.height);
		ctx.strokeStyle="white";
		ctx.stroke();
	}
}

function copy(points){
	//copy array
	var nextPoints=[];
	for(var i=0;i<points.length;i++){
		nextPoints.push(points[i]);
	}
	return nextPoints;
}

function length(points){
	var dist=0;
	for(var i=0;i<points.length-1;i++){
		dist+=Math.sqrt((points[i][0]-points[i+1][0])*(points[i][0]-points[i+1][0])+(points[i][1]-points[i+1][1])*(points[i][1]-points[i+1][1]))
	}
	return dist;
}

function setup(){
	var c = document.getElementById("test");
	var ctx = c.getContext("2d");
	ctx.fillStyle = "grey";
	ctx.fillRect(0, 0, c.width, c.height);
	points=[];
	for(var i=0;i<5;i++){
		points.push([Math.random(),Math.random()]);
	}
	display(ctx,c,points);
	var minLen=length(points);

	var main=setInterval(function(){
		var nextPoints=copy(points);
		nextPoints=shuffle(nextPoints);
		var len=length(nextPoints);
		if(len<minLen){
			minLen=len;
			display(ctx,c,nextPoints);
		}
	},1000/30);
}
setup();

