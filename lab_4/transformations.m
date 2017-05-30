function [] = transformations()
	disp("**************************************************************************")
	
	input_matrix = [0 0 1; 0 10 1; 10 10 1; 10 0 1 ; 0 0 1];
	disp("\nEnter your choice:\n1. Translation\n2. Scaling\n3. ReflectAroundX\n4. ShearaboutY\n5. Rotate\n");
	choice = input("Your choice : ");
	
	temp_matrix = [1 0 0; 0 1 0 ; 0 0 1];
	identity_matrix = [1 0 0; 0 1 0 ; 0 0 1];

	if(choice <= 5)
		if(choice==1)
			translate_x = input('Enter translate_x : ');
            		translate_y = input('Enter translate_y : ');
            		temp_matrix = [1 0 translate_x ; 0 1 translate_y ; 0 0 1];
		end

		if(choice==2)
			scale_factor_x = input('Enter scale_factor_x : ');
            		scale_factor_y = input('Enter scale_factor_y : ');
            		temp_matrix = [scale_factor_x 0 0 ; 0 scale_factor_y 0 ; 0 0 1];
            	end

            	if(choice==3)
            		temp_matrix = [1 0 0 ; 0 -1 0 ; 0 0 1];
            	end

            	if(choice==4)
            		shear_factor = input('Enter the shearing factor : ');
            		temp_matrix = [1 0 0 ; shear_factor 1 0 ; 0 0 1];
            	end

            	if(choice==5)
            		theta= input('Enter the rotation_angle : ');
            		theta = (theta*3.14159265) / 180 ;
			%theta = theta*_x;
            		temp_matrix = [cos(theta) -sin(theta) 0;
            				sin(theta) cos(theta) 0;
            				0 0 1];
            	end
        else
        	disp("\nYou choosed an invalid choice\n")
	end

	 

 	trans = transpose(temp_matrix);
 	final = input_matrix*trans;
      plot(input_matrix(:,1),input_matrix(:,2),'--','LineWidth', 3);
      hold on
      plot(final(:,1),final(:,2),'b-','LineWidth', 3);