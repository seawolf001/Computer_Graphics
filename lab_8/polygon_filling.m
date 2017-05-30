clc
clear

function func = update(a,b)
        if(a-b>0)
                func=1;
        elseif(a-b<0)
                func=-1;
        else
                func=0;
        end
end

function func = find_inter(x,y,a,b,line)
        result=0;
        ymax = 0;
        ymin = 0;
        xmax = 0;
        xmin = 0;
        if(x>a)
                xmin=a;
                xmax=x;
        else
                xmin=x;
                xmax=a;
        end
        if(y>b)
                ymin=b;
                ymax=y;
        else
                ymin=y;
                ymax=b;
        end
        if(b==y)
                result=-999999;
        elseif(a==x)
                if(line>=ymin && line<=ymax)
                          result = x;
                else
                          result=-999999;
          end
        else
                if(line<ymin || line>ymax)
                          result=-999999;
                else
                          result= x+((line-y)/((b-y)/(a-x)));
          end
        end
        func = result;
end

point = input("Enter the no. of points in polygon:        ");
x_vals = [];
y_vals = [];
for i = 1:point
        x = input("Enter the x co-ordinate of point:        ");
        y = input("Enter the y co-ordinate of point:        ");
        x_vals(i)=x;
          y_vals(i)=y;
end
ymin=y_vals(1);
ymax=y_vals(1);
for i= 2:point
        if(y_vals(i)>ymax)
                ymax=y_vals(i);
        elseif(y_vals(i)<ymin)
                ymin=y_vals(i);
        end
end
ymin;
ymax;
final_points_x = [];
tot_x = 1;
final_points_y = [];
tot_y = 1;
for i = ymin:ymax
        i
        flag = 0;
        count = 1;
        prev_inter_point = -999999;
        inter_points = [];
        for j = 1:point-1
                inter_point = find_inter(x_vals(j),y_vals(j),x_vals(j+1),y_vals(j+1),i);
                if(inter_point==-999999)
                        flag=update(y_vals(j+1),y_vals(j));
                        prev_inter_point=inter_point;
                        continue
                end
                if(y_vals(j+1)-y_vals(j)>0)
                        if(flag==1 && prev_inter_point==inter_point)
                                flag=update(y_vals(j+1),y_vals(j));
                                prev_inter_point=inter_point;
                                continue
                        end
                elseif(y_vals(j+1)-y_vals(j)<0)
                        if(flag==-1 && prev_inter_point==inter_point)
                                flag=update(y_vals(j+1),y_vals(j));
                                prev_inter_point=inter_point;
                                continue
                        end
                end
                inter_points(count) = inter_point;
                flag = update(y_vals(j+1),y_vals(j));
                prev_inter_point=inter_point;
                count=count+1;
        end
        inter_point = find_inter(x_vals(point),y_vals(point),x_vals(1),y_vals(1),i);
        if(inter_point!=-999999)
                if(y_vals(1)-y_vals(point)>0)
                        if(flag!=1 || prev_inter_point!=inter_point)
                                inter_points(count) = inter_points;
                                count=count+1;
                        end
                elseif(y_vals(1)-y_vals(point)<0)
                        if(flag!=-1 || prev_inter_point!=inter_point)
                                inter_points(count) = inter_point;
                                count=count+1;
                        end
                else
                        inter_points(count) = inter_point;
                        count=count+1;
                end
        end
        inter_points;
        inter_points=sort(inter_points);
        for j = 1:2:count-2
    a=inter_points(j);
    b=inter_points(j+1);
                for k = a:b
                        final_points_x(tot_x)= k;
                        final_points_y(tot_y)= i;
                        tot_x=tot_x+1;
                        tot_y=tot_y+1;
                end
        end
end
axis_x= [-300,300];
axis_y= [0,0];
line(axis_x,axis_y,'Color',[0.0,1.0,0.0],'LineWidth',2);
axis_y= [-300,300];
axis_x= [0,0];
line(axis_x,axis_y,'Color',[0.0,1.0,0.0],'LineWidth',2);
hold on
scatter(final_points_x,final_points_y)
axis([-300 300 -300 300]);
xlabel('X-Axis');
ylabel('Y-Axis');
title('Polygon filling algorithm');
