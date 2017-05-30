function[] = transformations_3_D()

cube = [0 0 0 1; 10 0 0 1; 10 10 0 1; 0 10 0 1; 0 0 0 1;
		0 0 10 1; 10 0 10 1; 10 10 10 1; 0 10 10 1; 0 0 10 1;
		10 0 10 1; 10 0 0 1; 10 10 0 1; 10 10 10 1; 0 10 10 1; 0 10 0 1];


prompt = ("\n\nEnter one of the following options:\n1.Translation\n2.Uniform Scaling\n3.Scaling\n4.Reflection\n5.Rotation\n6.Sheering\n");
choice = input(prompt);

trans = eye(4);

switch choice
	case 1
		xt = input("Enter the translation in X:");
		trans(1, 4) =  xt;
		yt = input("Enter the translation in Y:");
		trans(2, 4) =  yt;
		zt = input("Enter the translation in Z:");
		trans(3, 4) =  zt;
	case 2
		s = input("Enter the scale-factor :");
		trans(4, 4) = s;
	case 3
		xs = input("Enter the scale-factor in X:");
		trans(1, 1) =  xs;
		ys = input("Enter the scale-factor in Y:");
		trans(2, 2) =  ys;
		zs = input("Enter the scale-factor in Z:");
		trans(3, 3) =  zs;
	case 4
		disp('Reflection wrt the XY Plane is:');
		trans(3, 3) =  -1;
	case 5
		theta = input("Enter the angle for rotation about X-Axis:");
		theta = (theta*3.14159265)/180;
		trans(2, 2) = cos(theta);
		trans(2, 3) = -1*sin(theta);
		trans(3, 3) = cos(theta);
		trans(3, 2) = sin(theta);
	case 6
		xsh = input("Enter the sheer in X:");
		ysh = input("Enter the sheer in Y:");
		zsh = input("Enter the sheer in Z:");
		trans(1, 3) = xsh;
		trans(2, 3) = ysh;
		trans(3, 2) = zsh;
	otherwise
		disp('Wrong Input.');
end

trans = transpose(trans);
cube3 = cube*trans;
cube3 = cube3*trans(4,4);

axis([-15 15 -15 15 -15 15]);

plot3(cube(:, 1), cube(:, 2), cube(:, 3), 'LineWidth', 2, '-o', 'color', 'r');



hold on;

plot3(cube3(:, 1), cube3(:, 2), cube3(:, 3), 'LineWidth', 2, '-o', 'color', 'g');

%axis([0 20 0 20 0 20]);
