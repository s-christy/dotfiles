function setup(){
	var c = document.getElementById("test");
	var ctx = c.getContext("2d");
	ctx.fillStyle = "grey";
	ctx.fillRect(0, 0, c.width, c.height);

	var a=1;
	var n=2;
	var used=[1];
	var recaman=[];
	for(var x=0;x<c.width;x++){
		recaman.push(a);

		if(!(used.indexOf(a-n)>=0) && a-n>0){
			a=a-n;
		}else{
			a=a+n;
		}


		used.push(a);
		n+=1;
	}

	for(var x=0;x<recaman.length-1;x++){
		ctx.beginPath();
        	var l1=[5*recaman[x],0];
        	var l2=[5*(recaman[x]+recaman[x+1])/2,3*Math.abs(recaman[x]-recaman[x+1])];
        	var l3=[5*recaman[x+1],0];
		ctx.moveTo(l1[0],l1[1]);
		ctx.lineTo(l2[0],l2[1]);
		ctx.lineTo(l3[0],l3[1]);
		ctx.strokeStyle="white";
		ctx.stroke();
	}
}
setup();

