function setup(){
	var canvas = document.getElementById('randomwalk');
	var walkContext = canvas.getContext('2d');
	var x=150;
	var y=150;
	var rot=2*Math.PI/3;
	var count=0;
	walkContext.beginPath();
	walkContext.moveTo(x,y);
	function clear(){
		count=0;
		x=150;
		y=150;
		walkContext.beginPath();
		walkContext.moveTo(x,y);
		walkContext.clearRect(0,0,canvas.width,canvas.height);
	}
	function f(){
		x+=Math.floor(Math.random()*3)-1;
		y+=Math.floor(Math.random()*3)-1;
		walkContext.lineTo(x,y);
		walkContext.stroke();
		count++;
	}
	main=setInterval(function(){
		for(var i=0;i<10;i++){
			f()
			if(count>3000){
				clear();
			}
		}
	}, 10);
}
setup();
