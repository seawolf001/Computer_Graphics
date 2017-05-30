
function [] = bresenhams_line()
	x1 = input("Enter x-coordinate of first Point  : ");
	y1 = input("Enter y-coordinate of first Point  : ");
	x2 = input("Enter x-coordinate of second Point : ");
	y2 = input("Enter y-coordinate of second Point : ");
	
	dx = abs(x2-x1);
	dy = abs(y2-y1);
	y_increment = 1;
	d = dy.*2 - dx;
	d1 = dy.*2;
	d2 = (dy-dx).*2;
	flag = 1;

	if y2 < y1
		y_increment = -1;
	end

	if dy > dx
		flag = 0;
		d = dx.*2 - dy;
		d1 = dx.*2;
		d2 = (dx-dy).*2;
	end
	
	x = x1;
	y = y1;
	px = [x];
	py = [y];
	
	while x < x2
		if d<=0
			d = d + d1;
		else
			d = d + d2;
		
			if flag==1
				y = y + y_increment;
			end

			if flag==0
				x = x + 1;
			end
		end

		if flag==1
			x = x + 1;
		end

		if flag==0
			y = y + y_increment;
		end
		
		px = [px x];
		py = [py y];
	end
plot(px,py);