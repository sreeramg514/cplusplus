#include<iostream>
#include<graphics.h>
#include<conio.h>
#include<cmath>

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
//	initgraph(&d,&m,"C:\\TC\\BGI");
	initwindow(900, 600); 
	cleardevice();
	cout <<"max xvalues is "<< getmaxx()<< endl;
	cout << "maxy value is "<< getmaxy()<< endl;
	int i, y=30, x=2*radius, R=60, yflag=0;
	int midx=maxx/2, midy=getmaxy()/2, posx=maxx-radius, posy=getmaxy(); 
	
	while(1){
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
		
		
//		cleardevice();
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
		if ((d1>=R-radius && d1<radius+R) or (d2>=R-radius && d2<radius+R))
			break;
//		if(((y+radius)>=posy&& (y+radius)<=abs(posy-R) ) && (x>=abs(posx-R) && x<=(posx+R)))
//		if((y+radius)>=(abs(posy-R)) && (x+radius>=abs(posx-R) && x+radius<=(posx+R)))
//			break;
		if(posx-radius<=0)
			posx=maxx;
		posx=posx-radius;
		delay(20);
		cleardevice();
		
	}
	x=getch();
	cout << "Entered key "<< x<<endl;
	closegraph();
}
	