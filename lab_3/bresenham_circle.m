function [] = bresenham_circle(r)
getPoints(0,r,1,-1,1);
getPoints(0,r,1,-1,0);
getPoints(0,r,-1,-1,0);
getPoints(0,r.*-1,1,1,1);
getPoints(0,r.*-1,-1,1,1);
getPoints(0,r.*-1,-1,1,0);
getPoints(0,r.*-1,1,1,0);
getPoints(0,r,-1,-1,1);

function [] = getPoints(x, y, dx, dy, flag)
	h = 1-abs(y);
	px = [];
	py = [];
	
	while abs(x) < abs(y)
		if flag==1
			px = [px x];
			py = [py y];
		end
		
		if flag==0
			px = [px y];
			py = [py x];
		end
	
		if h<=0
			h = h + abs(x).*2 + 3;
		else
			h = h + (abs(x)-abs(y)).*2 + 5;
			y = y + dy;
		end
		x = x + dx;
	end
	
	scatter(px,py);
	hold on