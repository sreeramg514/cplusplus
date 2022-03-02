#include<iostream>
#include<graphics.h>
#include<conio.h>
#include<cmath>
#include <chrono>
#include <string>
using namespace std;

void get_obstacles(int ox, int oy, int orad=60){
//	cout<<"Inside get obstacles"<< ox << oy<< orad <<endl;

	circle(ox,oy,orad);
	floodfill(ox,oy,15);
}

main() {
	int d, m, radius=15, pause=0, maxx=800;
	char ch;
	d=DETECT;
	initwindow(1000, 600); 
	cleardevice();
	cout <<"max xvalues is "<< getmaxx()<< endl;
	cout << "maxy value is "<< getmaxy()<< endl;
	int i, y=30, x=2*radius, R=60, yflag=0, temp=1;
	int midx=maxx/2, midy=getmaxy()/2, posx=maxx-radius, posy=getmaxy(); 
	
	cleardevice();
	settextstyle(COMPLEX_FONT, HORIZ_DIR, 3);
	outtextxy(midx, midy, "Welcome to B-Ball");
	sleep(2);
	while(temp<=3){
		cleardevice();
		outtextxy(midx, midy+20, "Starts in ");
		char buffer[16] = {0};
		itoa(temp, buffer, 10);
		outtextxy(midx+150, midy+20, buffer);
		temp++;
		sleep(1);
	}
	chrono::steady_clock::time_point begin = chrono::steady_clock::now();
	while(1){
		settextstyle(COMPLEX_FONT, HORIZ_DIR, 2);
		chrono::steady_clock::time_point end = chrono::steady_clock::now();
		int t = (chrono::duration_cast<chrono::microseconds>(end - begin).count())/1000000;
		char buffer[16] = {0};
		itoa(t, buffer, 10);
		outtextxy(maxx+20, midy, "Score: ");
		outtextxy(maxx+100, midy, buffer);
		
		if (kbhit() or pause==1){
			if (getch()==32){
			  pause=!pause;
			  settextstyle(COMPLEX_FONT, HORIZ_DIR, 5);
			  outtextxy(midx, midy, ".Paused!");
			  continue;
			}
		}
		if(ismouseclick(WM_LBUTTONDOWN)){
			if(x>=radius)
				x=x-10;
		}
		if(ismouseclick(WM_LBUTTONUP)){
			clearmouseclick(WM_LBUTTONDOWN);
			clearmouseclick(WM_LBUTTONUP);
		}
		if(ismouseclick(WM_RBUTTONDOWN)){
			if(x<=maxx-radius)
				x=x+10;
		}
		if(ismouseclick(WM_RBUTTONUP)){
			clearmouseclick(WM_RBUTTONDOWN);
			clearmouseclick(WM_RBUTTONUP);
		}
		if(y>=getmaxy()-radius||y<=radius)
			yflag=!yflag;
		setcolor(1);
		setfillstyle(SOLID_FILL,1);
		circle(x,y,radius);
		floodfill(x,y,1);
		if(yflag) {
			y=y+5;
		} else {
			y=y-5;
		}
		setcolor(15);
		setfillstyle(SOLID_FILL,15);
		get_obstacles(posx, 0,R);
		get_obstacles(posx, posy, R);
		int d1 = sqrt((posx-x)*(posx-x) + (posy-y)*(posy-y));
		int d2 = sqrt((posx-x)*(posx-x) + (0-y)*(0-y));
		if ((d1>=R-radius && d1<radius+R) or (d2>=R-radius && d2<radius+R)){
			settextstyle(COMPLEX_FONT, HORIZ_DIR, 5);
			outtextxy(midx, midy, ".Game Over!");
			break;
		}
			
		if(posx-radius<=0)
			posx=maxx;
		posx=posx-radius;
		delay(15);
		cleardevice();
		
	}
	x=getch();
	closegraph();
}
	