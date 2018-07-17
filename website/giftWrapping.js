//see: https://en.wikipedia.org/wiki/Gift_wrapping_algorithm

function DiamondAngle(y, x)
{
    if (y >= 0)
        return (x >= 0 ? y/(x+y) : 1-x/(-x+y));
    else
        return (x < 0 ? 2-y/(-x-y) : 3+x/(x-y));
}

function setup(){
	var c = document.getElementById("test");
	var ctx = c.getContext("2d");
	ctx.fillStyle = "grey";
	ctx.fillRect(0, 0, c.width, c.height);
	var v1=[0,1]
	var v2=[0,0]
	var points=[];
	var march=0;
	var best=0;
	var bestVec=[0,0]
	var bests=[]
	for(var i=0;i<500;i++){
		var r=Math.random()/3;
		var t=Math.random()*100
		points.push([r*Math.cos(t)+.5,r*Math.sin(t)+.5])
	}
	var beginning=0;
	for(var i=0;i<points.length;i++){
		if(points[i][0]>points[beginning][0])beginning=i;
	}
	var main=setInterval(function(){
		for(var i=0;i<100;i++){
			v2=[points[march][0]-points[beginning][0],points[march][1]-points[beginning][1]]
			angle=DiamondAngle(v2[0],v2[1])
			//ctx.strokeStyle="green";
			if(angle>best){
				best=angle;
				bestVec=march;
				ctx.strokeStyle="red";
				ctx.beginPath();
				ctx.moveTo(c.width*points[march][0],c.height*points[march][1]);
				ctx.lineTo(c.width*points[beginning][0],c.height*points[beginning][1]);
				ctx.stroke();
			}else{
				//ctx.strokeStyle="green";
				//ctx.beginPath();
				//ctx.moveTo(c.width*points[march][0],c.height*points[march][1]);
				//ctx.lineTo(c.width*points[beginning][0],c.height*points[beginning][1]);
				//ctx.stroke();
			}
			march++;

			if(march>points.length-1){
				march=0;
				bests.push(bestVec)
				best=0;
				ctx.fillStyle = "grey";
				ctx.fillRect(0, 0, c.width, c.height);
				beginning=bestVec;
				//console.log(bests)
				for(var i=0;i<points.length;i++){
					ctx.fillStyle = "white";
					if(i==beginning)ctx.fillStyle = "red";
					ctx.fillRect(c.width*points[i][0],c.height*points[i][1],2,2);
					ctx.stroke();
				}
				for(var i=0;i<bests.length-1;i++){
					//console.log("hello?");
					ctx.strokeStyle="black";
					ctx.beginPath();
					ctx.moveTo(c.width*points[bests[i]][0],c.height*points[bests[i]][1]);
					ctx.lineTo(c.width*points[bests[i+1]][0],c.height*points[bests[i+1]][1]);
					ctx.stroke();
				}
			}
		}
	},1000/30);
}
setup();

