function setup(){
	var c = document.getElementById("brute");
	var ctx = c.getContext("2d");
	ctx.fillStyle = "grey";
	ctx.fillRect(0, 0, c.width, c.height);
	var board=[];
	var amplitude=5;
	//var marker=30;
	var marker=c.width-30;
	for (var i=0;i<c.width;i++){
		//board.push(10);
		//board.push((i-c.width/2)*(i-c.width/2)/300+amplitude*Math.sin(i/5)-100);
		board.push(30*Math.floor((1/30)*(i-c.width/2)*(i-c.width/2)/300)-100);
	}

		ctx.moveTo(0,c.height/2-board[0]);
		for(var i=0;i<c.width;i++){
			ctx.lineTo(i,c.height/2-board[i]);
		}
	var main=setInterval(function(){

		if(board[marker+1]<board[marker]){
			marker++;
		}else if(board[marker-1]<board[marker]){
			marker--;
		}else{
			//should be based on which direction it's going in
			marker+=Math.floor(Math.random()*3)-1;
		}


		ctx.fillStyle="red";
		ctx.fillRect(marker-5,c.height/2-board[marker]-5,10,10);
		ctx.stroke();
	},1000/30);
}
setup();
