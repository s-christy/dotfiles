function setup(){
	var c = document.getElementById("conway");
	var ctx = c.getContext("2d");
	ctx.fillStyle = "white";
	ctx.fillRect(0, 0, c.width, c.height);
	var board=[];
	for (var i=0;i<c.width/10*c.height/10;i++){
		board.push(Math.floor(Math.random()*2));
	}

	var main=setInterval(function(){
		var nextBoard=board.slice(0);
		for(var x=0;x<c.width/10;x++){
			for(var y=0;y<c.height/10;y++){
				ctx.fillStyle = "white";
				if(board[x*c.width/10+y])ctx.fillStyle = "black";
				ctx.fillRect(x*10,y*10,10,10);

				neighbors=0;
				if(board[(x+1)*c.width/10+y+1])neighbors++;
				if(board[(x+1)*c.width/10+y+0])neighbors++;
				if(board[(x+1)*c.width/10+y-1])neighbors++;
				if(board[(x+0)*c.width/10+y+1])neighbors++;
				if(board[(x+0)*c.width/10+y-1])neighbors++;
				if(board[(x-1)*c.width/10+y+1])neighbors++;
				if(board[(x-1)*c.width/10+y+0])neighbors++;
				if(board[(x-1)*c.width/10+y-1])neighbors++;
				if(nextBoard[(x)*c.width/10+y]){
					if(neighbors<2)nextBoard[(x)*c.width/10+y]=0;
					if(neighbors==2)nextBoard[(x)*c.width/10+y]=1;
					if(neighbors==3)nextBoard[(x)*c.width/10+y]=1;
					if(neighbors>3)nextBoard[(x)*c.width/10+y]=0;
				}else{
					if(neighbors==3)nextBoard[(x)*c.width/10+y]=1;
				}
			}
		}
		ctx.stroke();
		board=nextBoard;
	},1000/30);
}
setup();
