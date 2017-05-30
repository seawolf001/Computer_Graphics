function [] = circle()
	x_centre = input("enter the x coordinate of circle : ");
	y_centre = input("enter the x coordinate of circle : ");
	radius = input("enter the radius of circle : ");

	d = 3-2*radius;
	x = 0, y = radius;
	px = [x];
	py = [y];

	while x < y
		if (d < 0)
		   d += 4*x + 6;
		else 
		   d += 4*(x-y) + 10;
		   y--;
		end
		x++;
		
		px = cat(1,px,round(x_centre+x));
		py = cat(1,py,round(y_centre+y));

		px = cat(1,px,round(x_centre-x));
		py = cat(1,py,round(y_centre+y));
		
		px = cat(1,px,round(x_centre+x));
		py = cat(1,py,round(y_centre-y));
		
		px = cat(1,px,round(x_centre-x));
		py = cat(1,py,round(y_centre-y));
		
		px = cat(1,px,round(x_centre+y));
		py = cat(1,py,round(y_centre+x));
		
		px = cat(1,px,round(x_centre-y));
		py = cat(1,py,round(y_centre+x));
		
		px = cat(1,px,round(x_centre+y));
		py = cat(1,py,round(y_centre-x));
		
		px = cat(1,px,round(x_centre-y));
		py = cat(1,py,round(y_centre-x));
		
	end
	plot(px,py,'-*');
