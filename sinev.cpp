#include<iostream>
#include<graphics.h>
#include<conio.h>
#include<cmath>
#include<chrono>
#include<string>
#include<stack>

using namespace std;

int obs_color[6] = {
	9, //Light BLUE
	3, //CYAN
	5, //MAGENTA
	12, //LIGHTGREEN
	10, //LIGHTRED
	4 //RED
};



int level = 0;

class Player {
	public:	
		int posy=30, radius=15,  posx=2*radius, y_decider=0;
		stack<int> oldx, oldy;
		void draw_player(){
			set_ydecider();  // continuosly changes y position of player
			setcolor(15);
			setfillstyle(SOLID_FILL, 15);
			circle(posx,posy,radius);
			floodfill(posx,posy, 15);
			if(oldx.size() >= 14){
				
				for(int i=0; i<14; i++){
					setcolor(obs_color[level]);
					setfillstyle(SOLID_FILL, obs_color[level]);
					circle(oldx.top(),oldy.top(), 15-i);
				//	floodfill(oldx.top(),oldy.top(),  obs_color[level]);
					oldx.pop();
					oldy.pop();
				}
			}
		}
		void set_ydecider(){
			if(posy>=getmaxy()-radius||posy<=radius)
			y_decider=!y_decider;
			if(y_decider) {
				oldy.push(posy);
				posy=posy+5;
			} else {
				oldy.push(posy);
				posy=posy-5;
			}
		}
		void set_posx_by_mouse_actions(int maxx){
			if(ismouseclick(WM_LBUTTONDOWN)){
				if(posx>=radius){
					oldx.push(posx);
					posx=posx-10;
				}

			}
			if(ismouseclick(WM_LBUTTONUP)){
				clearmouseclick(WM_LBUTTONDOWN);
				clearmouseclick(WM_LBUTTONUP);
			}
			if(ismouseclick(WM_RBUTTONDOWN)){
				if(posx<=maxx-radius){
					oldx.push(posx);
					posx=posx+10;
				}

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
			if(score%5 == 0){
				if(level < 5) level++;		
			}
		}
		
		void draw_obstacles(){
			setcolor(obs_color[level]);
			setfillstyle(SOLID_FILL, obs_color[level]);
			circle(posx,0,radius);
			floodfill(posx,0, obs_color[level]);
			circle(posx,posy,radius);
			floodfill(posx,posy, obs_color[level]);
     
		}   
		void set_next_obs_position(){
			if(posx-(15+level)<=0)
				posx=maxx;
			posx=posx-(15+level);   
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
				setcolor(7);
		settextstyle(COMPLEX_FONT, HORIZ_DIR, 2);
		outtextxy(x+490, 10, (char *)"Sirish");
		outtextxy(10, 550, (char *)"Sreeram");
		outtextxy(10, 10, (char *)"Kiran");
		settextstyle(COMPLEX_FONT, HORIZ_DIR, 1);
		outtextxy(x+350, 550, (char *)"Inspired by Sine Line");
		settextstyle(COMPLEX_FONT, HORIZ_DIR, 5);
		setcolor(14);
	    outtextxy(x-20, y-50, (char *)" SINE-V");
	    setcolor(15);
	    settextstyle(COMPLEX_FONT, HORIZ_DIR, 4);
		outtextxy(x-40, y, (char *)" Starts in  ");
		char buffer[16] = {0};
		itoa(counter, buffer, 10);
		outtextxy(x+180, y, buffer);
		outtextxy(x+180, y, buffer);
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
int restart_game = 0;


void run_game(){
	Player pl;    
	Obstacles obs;  
	int pause=0,  maxx=800, player_x;
	if(restart_game){
	level=-1;	
	}
	
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
			settextstyle(COMPLEX_FONT, HORIZ_DIR, 3);
			outtextxy(midx-100, midy+40, (char *)".Restart Game! Click here -> ");
			setcolor(1);
			setfillstyle(SOLID_FILL, 1);
			circle(midx+330, midy+55,10);
			floodfill(midx+330, midy+55, 1);
			break;
		}
		obs.set_next_obs_position();
		delay(20);
		cleardevice();
	}
}
void click_handler(int x, int y){
    if (getpixel(x,y) == 1){
    	restart_game=1;
    	run_game();
	}
	
}
int main() {
	initwindow(1000, 600);
	run_game();
	registermousehandler(WM_LBUTTONDOWN, click_handler);
	char x=getch(); // pause games after gameover to see score
	closegraph();
}