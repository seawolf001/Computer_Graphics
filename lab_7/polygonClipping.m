function m = polygonClipping()
	X = [5,30,40,55,30,5];
	Y = [30,5,30,30,55,30];
	pointsX = [];
	pointsY = [];
	xmin=10; xmax=50; ymin=10 ; ymax=50 ;
	boundries_x = [xmin,xmax,xmax,xmin,xmin];
	boundries_y = [ymin,ymin,ymax,ymax,ymin];
	plot(boundries_x, boundries_y, 'g-', 'LineWidth', 3);
	hold on;
	for i = 1:5
		[pointsX,pointsY] = Clipping(X(i),Y(i),X(i+1),Y(i+1),xmin, ymin, xmax, ymax,pointsX,pointsY);
	end
	pointsX = [pointsX pointsX(1)];
	pointsY = [pointsY pointsY(1)];
	plot(pointsX, pointsY, 'b-', 'LineWidth', 3);
end
function [pointsX,pointsY] = Clipping(xf1 , yf1 , xf2 , yf2 , xmin, ymin, xmax, ymax,pointsX,pointsY)
 	plot([xf1 xf2], [yf1 yf2], 'r--','LineWidth', 3);
 	hold on;
	code1 = code(xf1, yf1, xmin, xmax, ymin, ymax);
	code2 = code(xf2, yf2, xmin, xmax, ymin, ymax);

		if bitand(code1,code2) > 0

		end

	while bitor(code1,code2) > 0

		slope  = (yf2-yf1)/(xf2-xf1);
		codex = code1 ;
		xi = xf1 ;
		yi = yf1 ;

		if(codex==0)
			codex = code2;
			xi = xf2 ;
			yi = yf2 ;
		end

		if bitand(codex,8)>0
			y = ymax;
			x = xi + 1/slope*(ymax-yi);
		elseif bitand(codex,4)>0
			y = ymin ;
			x = xi + 1/slope*(ymin-yi);
		elseif bitand(codex,2)>0
			x = xmax;
			y = yi + slope*(xmax-xi);
		elseif bitand(codex,1)>0
			x = xmin;
			y = yi + slope*(xmin-xi);
		end

		if codex == code1
			xf1 = x;
			yf1 = y;
			code1 = code(xf1, yf1, xmin, xmax, ymin, ymax);
		elseif codex == code2
			xf2 = x ;
			yf2 = y ;
			code2 = code(xf2, yf2, xmin, xmax, ymin, ymax);
		end
	end
	pointsX = [pointsX xf1];
	pointsX = [pointsX xf2];
	pointsY = [pointsY yf1];
	pointsY = [pointsY yf2];
end
function c = code(xf2, yf2, xmin, xmax, ymin, ymax)
	c = 0;
	if (yf2>ymax)
		c = 8;
	end
	if (yf2<ymin)
		c = 4;
	end
	if (xf2>xmax)
		c = bitor(c,2);
	end
	if (xf2<xmin)
		c = bitor(c,1);
	end
end
