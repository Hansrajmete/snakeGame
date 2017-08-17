#include<iostream>
#include<stdlib.h>
#include<unistd.h>
#include<ncurses.h>
using namespace std;
int gameover;
const int width=20,height =15;
int x,y,fx,fy,score;
enum eDir{STOP=0,LEFT,RIGHT,UP,DOWN};
eDir dir;

#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
 
char kbhit(void)
{
  struct termios oldt, newt;
  int ch;
  int oldf;
 
  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
  fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
 
  ch = getchar();
 
  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
  fcntl(STDIN_FILENO, F_SETFL, oldf);
 
  if(ch != EOF)
  {
    return ch;
  }
 
  return 'q';
}
 

struct snake
{
int x,y;};
	struct snake sn[100];


void setup()
{
	gameover=0;
	dir=STOP;
	score=0;
	x=width/2;
	y=height/2;
	
	fx=rand()%width;
	fy=rand()%height;
	while(fx<=0||fx>=width-1||fy<=0||fy>=height-1)
	{
		fx=rand()%width;
		fy=rand()%height;
	
	}
	for(int i=0;i<100;i++)
	sn[i].x=sn[i].y=0;
	sn[0].x=x;
	sn[0].y=y;

}

int psnake(int x,int y)
{
	for(int i=0;i<=score;i++)
		if(sn[i].x==x&&sn[i].y==y)
{

	return 1;
}
	return 0;
}


void draw()
{
	usleep(200000);
	system("clear");
	for(int i=0;i<width;i++)
		cout<<"#";
	cout<<endl;
	for(int j=1;j<height-1;j++)
	{
		for(int k=0;k<width;k++)
			{if(k==0||k==width-1)
				cout<<"#";
			else if(psnake(k,j)&&sn[0].x==k&&sn[0].y==j)
				cout<<"+";
			else if(psnake(k,j))
				cout<<"o";
			else if(j==fy&&k==fx)
				cout<<"$";
			else
				cout<<" ";}
			cout<<endl;
	}
	for(int i=0;i<width;i++)
		cout<<"#";
	cout<<endl;
}



void updatesnake()
{
for(int i=score;i>0;i--){
	sn[i].x=sn[i-1].x;
	sn[i].y=sn[i-1].y;}


	sn[0].x=x;
	sn[0].y=y;


}
	static char s='q';
void input()
{
	char temp=kbhit();
	if(temp==27){
		char y=kbhit();
		char z=kbhit();
		if(z==65)
			temp='w';
		else if(z==66)
			temp='s';
		else if(z==67)
			temp='d';
		else if(z==68)
			temp='a';
	}
	if(temp!='q')
	{	
		if(((s=='w'||s=='W')&&(temp=='s'||temp=='S'))||((s=='s'||s=='S')&&(temp=='w'||temp=='W'))||((s=='a'||s=='A')&&(temp=='d'||temp=='D'))||((s=='d'||s=='D')&&(temp=='a'||temp=='A')))
		{}
		else
		s=temp;
	}
	if(1)
	{
		switch(s)
		{
			case 'W':
			case 'w':
					dir=UP;
					y--;
					break;

			case 'a':
			case 'A':
					dir=LEFT;
					x--;
					break;
			case 's':
			case 'S':
					dir=DOWN;
					y++;
					break;
			case 'd':
			case 'D':
					dir=RIGHT;
					x++;
					break;
		}
	}
}


int bite()
{


	for(int i=1;i<score;i++)
	{
		if(sn[i].x==sn[0].x&&sn[i].y==sn[0].y)
			return 1;
	}
	return 0;

}
void logic()
{
	if(x==fx&&y==fy)
	{
		score++;
		sn[score].x=sn[score-1].x;
		sn[score].y=sn[score-1].x;
	fx=rand()%width;
	fy=rand()%height;
	while(fx<=0||fx>=width-1||fy<=0||fy>=height-1)
	{
		fx=rand()%width;
		fy=rand()%height;
	
	}
	}
	else if(x<=0||x>=width-1||y<=0||y>=height-1||bite())
	{
		cout<<"game over your score is "<<score<<endl;
		exit(0);
	}
	updatesnake();
}

int main()
{
	setup();
	while(!gameover)
	{
		draw();
		input();
		logic();
	}
}
