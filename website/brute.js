function setup(){
	var c = document.getElementById("brute");
	var ctx = c.getContext("2d");
	ctx.fillStyle = "grey";
	ctx.fillRect(0, 0, c.width, c.height);
	var board=[];
	var amplitude=5;
	var marker=10;
	for (var i=0;i<c.width;i++){
		//board.push(10);
		board.push((i-c.width/2)*(i-c.width/2)/300+amplitude*Math.sin(i/5)-100);
	}

	var main=setInterval(function(){

		if(board[marker+1]<board[marker]){
			marker++;
		}else{
			marker--;
		}


		ctx.moveTo(0,c.height/2-board[0]);
		for(var i=0;i<c.width;i++){
			ctx.lineTo(i,c.height/2-board[i]);
		}
		ctx.fillStyle="red";
		ctx.fillRect(marker,c.height/2-board[marker],10,10);
		ctx.stroke();
	},30);
}
setup();
