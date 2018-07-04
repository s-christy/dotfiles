function setup(){
	var c = document.getElementById("langton");
	var ctx = c.getContext("2d");
	ctx.fillStyle = "white";
	ctx.fillRect(0, 0, c.width, c.height);
	var res=5;
	var ax=c.width/(2*res);
	var ay=c.height/(2*res);
	var rot=0;
	var board=[];
	for (var i=0;i<c.width/res*c.height/res;i++){
		board.push(0);
	}

	var main=setInterval(function(){
		for(var x=0;x<c.width/res;x++){
			for(var y=0;y<c.height/res;y++){
				ctx.fillStyle = "white";
				if(board[x*c.width/res+y])ctx.fillStyle = "black";
				ctx.fillRect(x*res,y*res,res,res);
			}
		}
		ctx.fillStyle = "red";
		ctx.fillRect(ax*res,ay*res,res,res);

		for(var i=0;i<1000;i++){
			if(board[(ax+0)*c.width/res+ay+0]==0){
				rot--;
				board[(ax+0)*c.width/res+ay+0]=1;
			}else{
				rot++;
				board[(ax+0)*c.width/res+ay+0]=0;
			}
			if(rot==-1)rot=3;
			if(rot==4)rot=0;
			if(rot==0)ax++;
			if(rot==1)ay--;
			if(rot==2)ax--;
			if(rot==3)ay++;
			if(ax>c.width/res)ay-=c.width/res;
			if(ay>c.height/res)ay-=c.height/res;
		}
		ctx.stroke();
	},33);
}
setup();
