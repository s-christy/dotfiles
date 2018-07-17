function setup(){
	var c = document.getElementById("flock");
	var ctx = c.getContext("2d");
	ctx.fillStyle = "grey";
	ctx.fillRect(0, 0, c.width, c.height);

	var birds=[];
	for (var i=0;i<100;i++){
		birds.push([c.width*Math.random(),c.height*Math.random(),Math.random()*Math.PI*2]);
	}
	console.log(birds);
	var main=setInterval(function(){
		ctx.fillStyle = "black";
		ctx.fillRect(0, 0, c.width, c.height);
		ctx.beginPath();
		for(var i=0;i<birds.length;i++){
			dir=[Math.sin(birds[i][2]),Math.cos(birds[i][2])];
			ctx.moveTo(birds[i][0],birds[i][1]);
			ctx.lineTo(birds[i][0]+10*dir[0],birds[i][1]+10*dir[1]);
			birds[i][0]+=Math.sin(birds[i][2]);
			birds[i][1]+=Math.cos(birds[i][2]);
			if(birds[i][0]>c.width)birds[i][0]-=c.width;
			if(birds[i][1]>c.height)birds[i][1]-=c.height;
			if(birds[i][0]<0)birds[i][0]+=c.width;
			if(birds[i][1]<0)birds[i][1]+=c.height;
			//This is the nearest 30 px, try knn later, but keep in mind that it will be more expensive
			var num=0;
			for(var j=0;j<birds.length;j++){
				if(
					(birds[j][0]-birds[i][0])*
					(birds[j][0]-birds[i][0])+
					(birds[j][0]-birds[i][0])*
					(birds[j][0]-birds[i][0])<30*30){
					num++;
					birds[i][2]=(birds[j][2]+birds[i][2])/2;
				}
			}
			//birds[i][2]/=num;
			birds[i][2]+=.001;
		}
		ctx.strokeStyle="white";
		ctx.stroke();
	},1000/30);
}
setup();
