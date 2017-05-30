function z = cohenSutherland()

	xmin=20; xmax=40; ymin=20 ; ymax=40 ;
 	xf1=10 ; yf1=10 ; xf2=41  ; yf2=47 ;
 	plot([xf1 xf2], [yf1 yf2], 'r--','LineWidth', 3);
 	hold on;
	code1 = code(xf1, yf1, xmin, xmax, ymin, ymax);
	code2 = code(xf2, yf2, xmin, xmax, ymin, ymax);

		if bitand(code1,code2) > 0
			disp("Line  outside the clipping window");
			exit(1);
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

	boundries_x = [xmin,xmax,xmax,xmin,xmin];
	boundries_y = [ymin,ymin,ymax,ymax,ymin];
	plot(boundries_x, boundries_y, 'b-', 'LineWidth', 3);
	hold on;
	line_x = [xf1,xf2];
	line_y = [yf1,yf2];
	plot(line_x, line_y, 'g-', 'LineWidth', 5);

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
