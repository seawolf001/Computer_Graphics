function [] = dda_lines(flag)
	x1 = input("Enter x-coordinate of first Point  : ");
	y1 = input("Enter y-coordinate of first Point  : ");
	x2 = input("Enter x-coordinate of second Point : ");
	y2 = input("Enter y-coordinate of second Point : ");
	dx = x2-x1;
	dy = y2-y1;
	if flag==0
		
		length = abs(x2-x1);
		
		if length < abs(y2-y1)
			length = abs(y2-y1);
		end
		
		dx = dx./length;
		dy = dy./length;
	end

	if flag==1
		while abs(dx)>=1 || abs(dy)>=1
			dx = dx./2;
			dy = dy./2;
		end
	end

	x = x1;
	y = y1;

	px = [x];
	py = [y];
	
	while x<x2
		x = x+dx;
		y = y+dy;
		px = [px round(x)];
		py = [py round(y)];
	end
	plot(px,py);