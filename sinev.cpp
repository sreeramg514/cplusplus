#include<iostream>
#include<graphics.h>
#include<conio.h>
#include<cmath>
#include<chrono>
#include<string>

using namespace std;

class Player {
	public:	
		int posy=30, radius=15,  posx=2*radius, y_decider=0;
		void draw_player(){
			set_ydecider();  // continuosly changes y position of player
			setcolor(1);
			setfillstyle(SOLID_FILL,1);
			circle(posx,posy,radius);
			floodfill(posx,posy,1);
		}
		void set_ydecider(){
			if(posy>=getmaxy()-radius||posy<=radius)
			y_decider=!y_decider;
			if(y_decider) {
				posy=posy+5;
			} else {
				posy=posy-5;
			}
		}
		void set_posx_by_mouse_actions(int maxx){
			cout<<"posxxxx " << posx<< endl;
			if(ismouseclick(WM_LBUTTONDOWN)){
				if(posx>=radius)
					posx=posx-10;
			}
			if(ismouseclick(WM_LBUTTONUP)){
				clearmouseclick(WM_LBUTTONDOWN);
				clearmouseclick(WM_LBUTTONUP);
			}
			if(ismouseclick(WM_RBUTTONDOWN)){
				if(posx<=maxx-radius)
				posx=posx+10;
			}
			if(ismouseclick(WM_RBUTTONUP)){
				clearmouseclick(WM_RBUTTONDOWN);
				clearmouseclick(WM_RBUTTONUP);
			}
		
		}
		
};

class Obstacles {
	public:
		int posx,  posy=getmaxy(), radius=60, maxx=800;
		void draw_obstacles(){
			setcolor(15);
			setfillstyle(SOLID_FILL,15);
			circle(posx,0,radius);
			floodfill(posx,0,15);
			circle(posx,posy,radius);
			floodfill(posx,posy,15);
			if(posx-15<=0)
				posx=maxx;
			posx=posx-15;
		}   
};

int display_score(chrono::steady_clock::time_point begin, int maxx, int midy){
	settextstyle(COMPLEX_FONT, HORIZ_DIR, 2);
	chrono::steady_clock::time_point end = chrono::steady_clock::now();
	int t = (chrono::duration_cast<chrono::microseconds>(end - begin).count())/1000000;
	char buffer[16] = {0};
	itoa(t, buffer, 10);
	outtextxy(maxx+20, midy, "Score: ");
	outtextxy(maxx+100, midy, buffer);	
	return 0;
}

void initialize_game(int x, int y){
	int counter=4;
	while(counter>=1){
		cleardevice();
		settextstyle(COMPLEX_FONT, HORIZ_DIR, 3);
	    outtextxy(x-40, y, "Welcome to SINE-V !!");
		outtextxy(x, y+40, " Starts in ");
		char buffer[16] = {0};
		itoa(counter, buffer, 10);
		outtextxy(x+150, y+40, buffer);
		counter--;
		sleep(1);
	}
}

int check_for_pause(int pause, int midx, int midy){
	if (kbhit() or pause==1){
		if (getch()==32){
			pause=!pause;
			settextstyle(COMPLEX_FONT, HORIZ_DIR, 5);
			outtextxy(midx, midy, ".Paused!");
		}
	}
	return pause;
}

int mouse_actions(int x, int radius, int maxx){
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
	return x;
		
}
int main(){
	initwindow(1000, 600); 
	Player pl;    
	Obstacles obs;  
	int pause=0,  maxx=800, player_x;

	int midx=maxx/2, midy=getmaxy()/2;
	initialize_game(midx, midy);
	chrono::steady_clock::time_point begin = chrono::steady_clock::now();
 
	obs.posx=maxx-pl.radius;                                                    
	while(1){
		display_score(begin, maxx, midy); //Displays Score
		pause = check_for_pause(pause, midx, midy);   // Checks for Pause and display pause
		if(pause == 1)
		continue;
		pl.set_posx_by_mouse_actions(maxx);
//		player_x = mouse_actions(player_x, pl.radius, maxx);    // Identify Mouse actions and set x of player; 
//		pl.posx = player_x;
		pl.draw_player();                     // Draw player in x position
		obs.draw_obstacles();				  // Draw obstacles 
		
		// Condition checks for clashing player and obstacles
		int d1 = sqrt((obs.posx-pl.posx)*(obs.posx-pl.posx) + (obs.posy-pl.posy)*(obs.posy-pl.posy));
		int d2 = sqrt((obs.posx-pl.posx)*(obs.posx-pl.posx) + (0-pl.posy)*(0-pl.posy));
		if ((d1>=obs.radius-pl.radius && d1<pl.radius+obs.radius) or (d2>=obs.radius-pl.radius && d2<pl.radius+obs.radius)){
			settextstyle(COMPLEX_FONT, HORIZ_DIR, 5);
			outtextxy(midx, midy, ".Game Over!");
			break;
		}
		
		delay(25);
		cleardevice();
	}
	char x=getch(); // pause games after gameover to see score
	closegraph();
}