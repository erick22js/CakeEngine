
Math.rad2deg = function(rad){
	return (rad/Math.PI)*180;
}

Math.deg2rad = function(deg){
	return (deg/180)*Math.PI;
}

Math.matrixmul = function(m1, m2){
	var nm = [
		[0, 0, 0],
		[0, 0, 0],
		[0, 0, 0],
	];
	
	for(var li=0; li<3; li++){
		
		for(var ci=0; ci<3; ci++){
			var data = 0;
			
			for(var ci2=0; ci2<3; ci2++){
				var d1 = m1[li][ci2];
				var d2 = m2[ci2][ci];
				
				data += d1*d2;
			}
			
			nm[li][ci] = data;
		}
		
	}
	
	return nm;
}

Math.matrixrotX = function(m1, rad){
	var m2 = [
		[1, 0, 0],
		[0, Math.cos(rad), -Math.sin(rad)],
		[0, Math.sin(rad), Math.cos(rad)],
	];
	return Math.matrixmul(m2, m1);
}

Math.matrixrotY = function(m1, rad){
	var m2 = [
		[Math.cos(rad), 0, -Math.sin(rad)],
		[0, 1, 0],
		[Math.sin(rad), 0, Math.cos(rad)],
	];
	return Math.matrixmul(m2, m1);
}

Math.matrixrotZ = function(m1, rad){
	var m2 = [
		[Math.cos(rad), -Math.sin(rad), 0],
		[Math.sin(rad), Math.cos(rad), 0],
		[0, 0, 1],
	];
	return Math.matrixmul(m2, m1);
}

Math.matrixident = function(){
	var nm = [
		[1, 0, 0],
		[0, 1, 0],
		[0, 0, 1],
	];
	return nm;
}

// Rotations (in degress)
// x:20 (0.349); y:145 (2.530); z:78 (1.361)

/* Matrices

M1: (Z)
[
	[0.208, 	0.978, 	0],
	[-0.978, 	0.208, 	0],
	[0, 		0, 		1],
]

M2: (Y)
[
	[-0.819, 0, 0.574],
	[0, 	 1, 0],
	[-0.574, 0, -0.819],
]

M3: (X)
[
	[1, 0, 		0],
	[0, 0.94, 	0.342],
	[0, -0.342, 0.94],
]

M2*M3:
[
	[-0.819, 	-0.196, 0.54],
	[0, 		0.94, 	0.342],
	[-0.574, 	0.28,	-0.77]
]

M1*(M2*M3):
[
	[-0.17, 	0.879, 	0.447],
	[0.801, 	0.387, 	-0.457],
	[-0.574, 	0.28, 	-0.77],
]

*/

var Matrix = [
	[-0.17, 	0.879, 	0.447],
	[0.801, 	0.387, 	-0.457],
	[-0.574, 	0.28, 	-0.77],
]

/**
	
	Rot Z
	cos Z	-sin Z	0
	sin Z	cos Z	0
	0		0		1
	
	Rot Y
	cos Y	0		sin Y
	0		1		0
	-sin Y	0		cos Y
	
	Rot X
	1		0		0
	0		cos X	-sin X
	0		sin X	cos X
	
	
	A = cos Z;	B = sin Z
	C = cos Y;	D = sin Y
	E = cos X;	F = sin X
	
	
	Rot X
	1	0	0
	0	E	-F
	0	F	E
	
	Rot Y
	C	0	D
	0	1	0
	-D	0	C
	
	Rot Z
	A	-B	0
	B	A	0
	0	0	1
	
	Rot Y*Rot X
	C	DF	DE
	0	E	-F
	-D	CF	CE
	
	Rot Z*(Rot Y*Rot X)
	(AC)		(ADF-BE)		(ADE+BF)
	(BC)		(BDF+AE)		(BDE-AF)
	(-D)		(CF)			(CE)
*/

var Rotation = [0, 0, 0];
var Scaling = [0, 0, 0];
var Translation = [0, 0, 0];

/*
	Calculate matrix
*/

/*
	-D = -(sin Y)
	
	RotY = 
*/

function multiply_matrices(m1, m2, simplify=true){
	var nm = [
		["", "", ""],
		["", "", ""],
		["", "", ""],
	];
	
	for(var li=0; li<3; li++){
		
		for(var ci=0; ci<3; ci++){
			var data = "0";
			
			for(var ci2=0; ci2<3; ci2++){
				var d1 = m1[li][ci2];
				var d2 = m2[ci2][ci];
				if(simplify){
					if((d1=="0")||(d2=="0")){
						
					}
					else{
						if(d1=="1"){
							if(d2=="1"){
								if(data=="0"){
									data = "1";
								}
								else{
									data += "+1";
								}
							}
							else{
								if(data=="0"){
									data = d2;
								}
								else{
									data += "+"+d2;
								}
							}
						}
						else if(d2=="1"){
							if(data=="0"){
								data = d1;
							}
							else{
								data += "+"+d1;
							}
						}
						else{
							if(data=="0"){
								data = d1+"*"+d2;
							}
							else{
								data += "+"+d1+"*"+d2;
							}
						}
					}
				}
				else{
					if(data=="0"){
						data = d1+"*"+d2;
					}
					else{
						data += "+"+d1+"*"+d2;
					}
				}
			}
			
			if((data=="0")||(data.length<=2)){
				
			}
			else{
				data = "("+data+")";
			}
			
			nm[li][ci] = data;
		}
		
	}
	
	return nm;
}

function print_matrix(m){
	document.write(
		"|"+m[0][0]+"&nbsp;&nbsp;&nbsp;&nbsp;"+m[0][1]+"&nbsp;&nbsp;&nbsp;&nbsp;"+m[0][2]+"|<br/>"+
		"|"+m[1][0]+"&nbsp;&nbsp;&nbsp;&nbsp;"+m[1][1]+"&nbsp;&nbsp;&nbsp;&nbsp;"+m[1][2]+"|<br/>"+
		"|"+m[2][0]+"&nbsp;&nbsp;&nbsp;&nbsp;"+m[2][1]+"&nbsp;&nbsp;&nbsp;&nbsp;"+m[2][2]+"|<br/><br/>"
	);
}

const MatRotZ = [
	["A", "-B", "0"],
	["B", "A", "0"],
	["0", "0", "1"],
];

const MatRotY = [
	["C", "0", "D"],
	["0", "1", "0"],
	["-D", "0", "C"],
];

const MatRotX = [
	["1", "0", "0"],
	["0", "E", "-F"],
	["0", "F", "E"],
];

const MatProdRotYRotX = multiply_matrices(MatRotY, MatRotX, false);
const MatProdRotYRotX2 = multiply_matrices(MatRotY, MatRotX, true);

const MatProdRotZRotYRotX = multiply_matrices(MatRotZ, MatProdRotYRotX2, false);
const MatProdRotZRotYRotX2 = multiply_matrices(MatRotZ, MatProdRotYRotX2, true);

print_matrix(MatRotX);
print_matrix(MatRotY);
print_matrix(MatRotZ);
print_matrix(MatProdRotYRotX);
print_matrix(MatProdRotYRotX2);
print_matrix(MatProdRotZRotYRotX);
print_matrix(MatProdRotZRotYRotX2);

print_matrix(Matrix);

var D = -Matrix[2][0];
var C = Math.cos(Math.asin(D));
var A = Matrix[0][0]/C;
var B = Matrix[1][0]/C;
var F = Matrix[2][1]/C;
var E = Matrix[2][2]/C;

/* Fix Parameters */
while(true){
	/* Try all tests and check for approximation */
	var t1 = (A*(D*F)+-B*E);
	var t2 = (A*(D*E)+-B*-F);
	var t3 = (B*(D*F)+A*E);
	var t4 = (B*(D*E)+A*-F);
	document.write("Test1: "+t1.toFixed(3)+"<br/>");
	document.write("Test2: "+t2.toFixed(3)+"<br/>");
	document.write("Test3: "+t3.toFixed(3)+"<br/>");
	document.write("Test4: "+t4.toFixed(3)+"<br/><br/>");
	break;
}

document.write("A: "+A.toFixed(3)+"<br/>"); // cos Z
document.write("B: "+B.toFixed(3)+"<br/>"); // sin Z
document.write("C: "+C.toFixed(3)+"<br/>"); // cos Y
document.write("D: "+D.toFixed(3)+"<br/>"); // sin Y
document.write("E: "+E.toFixed(3)+"<br/>"); // cos X
document.write("F: "+F.toFixed(3)+"<br/>"); // sin X

Rotation[0] = Math.atan(F/E);//Math.asin(Matrix[1][2]);
Rotation[1] = Math.atan(D/C);
Rotation[2] = Math.atan(B/A);//Math.asin(Matrix[0][1]);


/*
	Output results
*/

document.write("Rotation:<br\>x:"+Math.rad2deg(Rotation[0]).toFixed(3)+";<br\>y:"+Math.rad2deg(Rotation[1]).toFixed(3)+";<br\>z:"+Math.rad2deg(Rotation[2]).toFixed(3)+";");

document.write("<br/><br/><br/>");


var tmat = Math.matrixident();
print_matrix(tmat);

tmat = Math.matrixrotX(tmat, -Math.deg2rad(20));
print_matrix(tmat);

tmat = Math.matrixrotY(tmat, -Math.deg2rad(145));
print_matrix(tmat);

tmat = Math.matrixrotZ(tmat, -Math.deg2rad(78));
print_matrix(tmat);
