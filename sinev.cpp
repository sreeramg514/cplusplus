#include<iostream>
#include<graphics.h>
#include<conio.h>
#include<cmath>
#include<chrono>
#include<string>

using namespace std;

//Colors datatype
struct Color{
	unsigned short int r;
	unsigned short int g;
	unsigned short int b;
};

Color obs_color[10] = {
	{15, 66, 98}, //Color 1
	{20, 86, 128}, //Color 2
	{40, 66, 68}, //Color 3
	{50, 76, 135}, //Color 4
	{87, 34, 5}, //Color 5
	{22, 45, 198}, //Color 6
	{200, 100, 200}, //Color 7
	{70, 43, 97}, //Color 8
	{56, 64, 100}, //Color 9
	{67, 100, 46}, //Color 10
};

Color player_color[10] = {
	{15, 66, 98}, //Color 1
	{20, 86, 128}, //Color 2
	{40, 66, 68}, //Color 3
	{50, 76, 135}, //Color 4
	{87, 34, 5}, //Color 5
	{22, 45, 198}, //Color 6
	{200, 100, 200}, //Color 7
	{70, 43, 97}, //Color 8
	{56, 64, 100}, //Color 9
	{67, 100, 46}, //Color 10
};

int level = 0;

class Player {
	public:	
		int posy=30, radius=15,  posx=2*radius, y_decider=0;
		void draw_player(){
			set_ydecider();  // continuosly changes y position of player
			setcolor(COLOR(player_color[level].r, player_color[level].g, player_color[level].b));
			setfillstyle(SOLID_FILL,COLOR(player_color[level].r, player_color[level].g, player_color[level].b));
			circle(posx,posy,radius);
			floodfill(posx,posy,COLOR(player_color[level].r, player_color[level].g, player_color[level].b));
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
			//cout<<"posxxxx " << posx<< endl;
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
		
		static void change_level(int score, int maxx, int midy){
			if(score%25 == 0){
				if(level < 10) level++;
			}
		}
		
		void draw_obstacles(){
			setcolor(COLOR(obs_color[level].r, obs_color[level].g, obs_color[level].b));
			setfillstyle(SOLID_FILL, COLOR(obs_color[level].r, obs_color[level].g, obs_color[level].b));
			circle(posx,0,radius);
			floodfill(posx,0, COLOR(obs_color[level].r, obs_color[level].g, obs_color[level].b));
			circle(posx,posy,radius);
			floodfill(posx,posy, COLOR(obs_color[level].r, obs_color[level].g, obs_color[level].b));
			if(posx-15<=0)
				posx=maxx;
			posx=posx-15;
		}   
};


int display_score(chrono::steady_clock::time_point begin, int maxx, int midy){
	settextstyle(COMPLEX_FONT, HORIZ_DIR, 2);
	chrono::steady_clock::time_point end = chrono::steady_clock::now();
	int t = (chrono::duration_cast<chrono::microseconds>(end - begin).count())/1000000;
	static int prev_t = 0;
	if(t != prev_t){
		Obstacles::change_level(t, maxx, midy);
		prev_t = t;
	}
	char buffer[16] = {0};
	itoa(t, buffer, 10);
	outtextxy(maxx+20, midy, (char *)"Score: ");
	outtextxy(maxx+100, midy, buffer);	
	
	itoa(level+1, buffer, 10);
	outtextxy(maxx+20, midy-20, (char *)"Level: ");
	outtextxy(maxx+100, midy-20, buffer);
	
	return 0;
}

void initialize_game(int x, int y){
	int counter=4;
	while(counter>=1){
		cleardevice();
		settextstyle(COMPLEX_FONT, HORIZ_DIR, 3);
	    outtextxy(x-40, y, (char *)"Welcome to SINE-V !!");
		outtextxy(x, y+40, (char *)" Starts in ");
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
			outtextxy(midx, midy, (char *)".Paused!");
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
			outtextxy(midx, midy, (char *)".Game Over!");
			break;
		}
		
		delay(25);
		cleardevice();
	}
	char x=getch(); // pause games after gameover to see score
	closegraph();
}