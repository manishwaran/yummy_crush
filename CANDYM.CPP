#include<iostream.h>
#include<conio.h>
#include<dos.h>
#include<stdlib.h>
#include<math.h>
#include<stdio.h>
#include<graphics.h>
#define MAX_SIZE 50

struct stack
{
	int x,y,c;
	char m;
}s[MAX_SIZE];

struct candy
{
	int mat;
}can[20][20];

void create();
int get(int);
void h_check(int,int,int,int,int);
void v_check(int,int,int,int,int);
void horizontal(int);
void vertical(int);
void interchange(int,int,int,int);
void mark(int);
void recover(int);
int first(int);
int second(int,int);
void fill(int,int);
void push(int,int,int,char);
stack pop();

void setpage();
void startpage();
void loading();
void drawline();

int r1,r2,c1,c2,r,c,top=-1,set;
int maxx,maxy,midx,midy;
char *msg;

void main()
{
	clrscr();
	int gd=DETECT,gm;
	int x,x1,x2,y1,y2;
	char a;
	initgraph(&gd,&gm,"..\\bgi");
	maxx=getmaxx();
	maxy=getmaxy();
	midx=maxx/2;
	midy=maxy/2;
	startpage();
	loading();
	cleardevice();
	setpage();
	settextstyle(4,0,4);
	setcolor(4);
	outtextxy(midx-textwidth("YOUR SPECIFICATION")/2,50,"YOUR SPECIFICATION");
	settextstyle(3,0,2);
	setcolor(5);
	outtextxy(40,120,"ENTER NUMBER OF ROWS ");
	outtextxy(midx+70,120,":");
	r=get(10);
	setcolor(3);sprintf(msg,"%d",r);
	outtextxy(midx+90,120,msg);
	setcolor(5);
	outtextxy(40,190,"ENTER NUMBER OF COLUMNS ");
	outtextxy(midx+70,190,":");
	c=get(10);
	setcolor(3);
	sprintf(msg,"%d",c);
	outtextxy(midx+90,190,msg);
	for(int i=0;i<15;i++)
	{
		settextstyle(4,0,4);
		sprintf(msg,"LETS PLAY !!!");
		outtextxy((maxx/2)-(textwidth("LETS PLAY !!!")/2),350,msg);
		delay(100);
	}

	create();
	horizontal(0);
	vertical(0);
	while(top>=0)
	{
			mark(top);
			recover(0);
			horizontal(0);
			vertical(0);
	}


	do
	{
		drawline();
		settextstyle(3,0,1);
		setcolor(RED);
		outtextxy((x=50),(y1=400),"ENTER ROW1 AND COLUMN1  : (   ,   ) ");
		x1=x+textwidth("ENTER  ROW1 AND COLUMN1  : ( ")-25;
		x2=x+textwidth("ENTER  ROW1 AND COLUMN1  : (   , ")-30;
		r1=get(r);
		setcolor(CYAN);
		sprintf(msg,"%d",r1);
		outtextxy(x1,y1,msg);
		c1=get(c);
		sprintf(msg,"%d",c1);
		outtextxy(x2,y1,msg);
		setcolor(RED);
		outtextxy(x,430,"ENTER ROW2 AND COLUMN2  : (   ,   )");
		r2=get(r);
		setcolor(CYAN);
		sprintf(msg,"%d",r2);
		outtextxy(x1,430,msg);
		c2=get(c);
		sprintf(msg,"%d",c2);
		outtextxy(x2,430,msg);

		set=0;
		r1--,r2--,c1--,c2--;
		if(abs(r2-r1)==0)
			v_check(r1,c1,r2,c2,0);
		else if(abs(c2-c1)==0)
			h_check(r1,c1,r2,c2,0);
		else
		{
			msg="ENTER VALID ENTRY !";
			outtextxy(midx-textwidth(msg),450,msg);
			delay(500);
			continue;
		}
		do
		{
			horizontal(0);
			vertical(0);
			mark(top);
			drawline();
			recover(0);
			drawline();
			horizontal(0);
			vertical(0);
		}while(top>=0);
		clrscr();
		cleardevice();
		drawline();
		settextstyle(3,0,2);
		setcolor(RED);
		outtextxy(midx-textwidth("TO END PRESS 'E' : ")/2,y1,"TO END PRESS 'E' : ");
		a=getch();
	}while(a!='e');
	cleardevice();
	setpage();
	settextstyle(3,0,8);
	setcolor(RED);
	outtextxy(midx-textwidth("THANK YOU !")/2,midy-20-textheight("THANK YOU !")/2,"THANK YOU !");
	delay(2000);
}

void drawline()
{
	clrscr();
	cleardevice();
	setpage();
	int x1,x2,y1,y2,box,xpad,ypad,px1,py1,px2,py2,pt;
	box=30;
	xpad=8;
	ypad=5;
	px1=x1=midx-(r*box+r*xpad)/2;
	py1=y1=midy-(c*box+c*ypad)/2-(maxy-400)/2;
	px2=x2=x1+box;
	py2=y2=y1+box;
	py1-=box-15;
	pt=(px1+px2)/2;

	for(int i=0;i<r;i++)
	{
		settextstyle(0,0,1);
		sprintf(msg,"%d",i+1);
		pt-=textwidth(msg)/2;
		outtextxy(pt,py1,msg);
		pt+=box+xpad+xpad/2;
	}
	pt=(py1+py2)/2;
	px1-=box-10;
	for(i=0;i<c;i++)
	{
		settextstyle(0,0,1);
		sprintf(msg,"%d",i+1);
		pt-=textheight(msg)/2;
		outtextxy(px1,pt,msg);
		pt+=box+2*ypad;
	}

	for(i=0;i<r;i++)
	{
		x1=midx-(r*box+r*xpad)/2;
		x2=x1+box;
		for(int j=0;j<c;j++)
		{
			if(can[i][j].mat==1)
			   setfillstyle(1,RED);
			else if(can[i][j].mat==2)
			   setfillstyle(1,MAGENTA);
			else if(can[i][j].mat==3)
			   setfillstyle(1,BLUE);
			else if(can[i][j].mat==4)
			   setfillstyle(1,GREEN);
			else if(can[i][j].mat==0)
			   setfillstyle(1,YELLOW);
			else
			   setfillstyle(1,CYAN);
			bar3d(x1,y1,x2,y2,(x2-x1)/8,0);
			x1+=box+xpad;
			x2=x1+box;
		}
		y1+=box+ypad;
		y2=y1+box;
	}
	delay(1000);
}
void startpage()
{
	setpage();
	setcolor(4);
	settextstyle(4,0,6);
	outtextxy(midx-textwidth("CANDY   CRUSH   M")/2,midy-170,"CANDY   CRUSH   M");
	delay(500);
	setpage();
	settextstyle(3,0,3);
	outtextxy(midx-textwidth("DEVELOPED BY")/2,midy-100,"DEVELOPED BY");
	delay(400);
	setlinestyle(1,1,2);
	rectangle(midx-220,midy-40,midx+220,midy+90);
	for(int p=0;p<15;p++)
	{
		setcolor(p);
		settextstyle(4,0,8);
		outtextxy(midx-textwidth("MANISH")/2,midy-30,"MANISH");delay(200);
		sound(350);
	}
	nosound();
	getch();
}

void setpage()
{
	setbkcolor(BLACK);
	setcolor(WHITE);
	setlinestyle(0,0,1);
	rectangle(0,0,maxx,maxy);
	rectangle(3,3,maxx-3,maxy-3);
}

void loading()
{
	cleardevice();
	setpage();
	setcolor(13);
	settextstyle(TRIPLEX_FONT,HORIZ_DIR,0);
	setusercharsize(2, 1, 1, 1);
	outtextxy(138,198,"LOADING");
	setcolor(13);
	settextstyle(TRIPLEX_FONT,HORIZ_DIR,0);
	setusercharsize(2, 1, 1, 1);
	setcolor(BLUE);
	rectangle(119,199,421,231);
	rectangle(118,198,422,232);
	setcolor(10);
	for(int ii=120;ii<=420;ii++)
	{
		line(ii,200,ii,230);
		sound(ii+1500);
		delay(10);
		nosound();
	}
}
int get(int range)
{
	int tem1,tem,rescl,i=0;
	char *a;
	while(i<3)
	{
		a[i]=getche();
		i++;
		if(a[i-1]==13||a[i-1]==32)
			break;
	}
	a[i]=NULL;
	tem1=atoi(a);
	if(tem1>0&&tem1<=range)
	{
		return tem1;
	}
	else
	{
		sprintf(msg,"INPUT ERROR !!!");
		outtextxy((maxx/2)-(textwidth("INPUT ERROR !!!")/2),maxy-100,msg);
		delay(500);
		rescl=getbkcolor();
		setcolor(2);
		setcolor(rescl);outtextxy((maxx/2)-(textwidth("INPUT ERROR !!!")/2),maxy-100,msg);
		setcolor(15);
		sprintf(msg,"GIVE INPUT IN BETWEEN 0 AND %d",range+1);
		outtextxy((maxx/2)-(textwidth(msg)/2),maxy-100,msg);
		delay(500);
		rescl=getbkcolor();
		setcolor(2);
		setcolor(rescl);outtextxy((maxx/2)-(textwidth(msg)/2),maxy-100,msg);
		setcolor(GREEN);
		tem1=get(range);
	}
	return tem1;
}


void push(int x,int y,int count,char m)
{
	if(top>=MAX_SIZE)
	{
		cout<<"\nSTACK OVERFLOW !";
		exit(1);
	}
	else
	{
		top++;
		s[top].x=x;
		s[top].y=y;
		s[top].c=count;
		s[top].m=m;
	}
}

stack pop()
{
	stack tem;
	if(top<0)
	{
		cout<<"\nSTACK UNDERFLOW !";
		exit(1);
	}
	tem=s[top];
	top--;
	return tem;
}

void create()
{
	randomize();
	for(int i=0;i<r;i++)
		for(int j=0;j<c;j++)
			can[i][j].mat=rand()%5;
}

void interchange(int x1,int y1,int x2,int y2)
{
	int tem=can[x1][y1].mat;
	can[x1][y1].mat=can[x2][y2].mat;
	can[x2][y2].mat=tem;
	drawline();
}

void h_check(int x1,int y1,int x2,int y2,int cc)
{
	if(cc<2)
	{
		int tem=can[x1][y1].mat,deg=-1,count=1,i;
		if(y2-2>=0)
			i=y2-2;
		else
			i=0;
		for(;i<=y2+2&&i<c;i++)
		{
			if(i!=y2)
			{
				if(can[x2][i].mat==tem)
				{
					count++;
					if(count==3)
					{
						deg=i-2;
					}
				}
				else if(count<3)
					count=1;
				else
					break;
			}
			else if(count==3)
				deg=i-2;
		}
		h_check(x2,y2,x1,y1,cc+1);
		if(count>=3&&set==0)
		{
			interchange(x1,y1,x2,y2);
			set=1;
		}
		return;
	}
	else
	{
		int tem=can[x1][y1].mat,y=0;
		if((tem==can[x2+1][y1].mat&&x2+1<r)&&(tem==can[x2+2][y1].mat&&x2+2<r))
			y=1;
		tem=can[x2][y2].mat;
		if((tem==can[x1-1][y1].mat&&x1-1>=0)&&(tem==can[x1-2][y1].mat&&x1-2>=0))
			y=1;
		if(y==1&&set==0)
		{
			interchange(x1,y1,x2,y2);
			set=1;
		}
		return;
	}
}

void v_check(int x1,int y1,int x2,int y2,int cc)
{
	if(cc<2)
	{
		int tem=can[x1][y1].mat,deg=-1,count=1,i;
		if(x2-2>=0)
			i=x2-2;
		else
			i=0;
		for(;i<=x2+2&&i<r;i++)
		{
			if(i!=x2)
			{
				if(can[i][y2].mat==tem)
				{
					count++;
					if(count==3)
					{
						deg=i-2;
					}
				}
				else if(count<3)
					count=1;
				else
					break;
			}
			else if(count==3)
				deg=i-2;
		}
		v_check(x2,y2,x1,y1,cc+1);
		if(count>=3&&set==0)
		{
			interchange(x1,y1,x2,y2);
			set=1;
		}
		return;
	}
	else
	{
		int tem=can[x1][y1].mat,y=0;
		if((tem==can[x2][y2+1].mat&&y2+1<c)&&(tem==can[x2][y1+2].mat&&y2+2<c))
			y=1;
		tem=can[x2][y2].mat;
		if((tem==can[x1][y1-1].mat&&y1-1>=0)&&(tem==can[x1][y1-2].mat&&y1-2>=0))
			y=1;
		if(y==1&&set==0)
		{
			interchange(x1,y1,x2,y2);
			set=1;
		}
		return;
	}
}

void horizontal(int x)
{
	if(x<r)
	{
	int count;
	for(int i=0;i<c;)
	{
		count=1;
		for(int j=1+i;j<c;j++)
		{
		if(can[x][i].mat==can[x][j].mat)
			count++;
		else
			break;
		}
		if(count>=3)
		push(x,i,count,'h');
		i=j;
	}
	horizontal(x+1);
	}
}

void vertical(int y)
{
	if(y<c)
	{
		int count;
		for(int i=0;i<r;)
		{
			count=1;
			for(int j=i+1;j<r;j++)
				if(can[i][y].mat==can[j][y].mat)
					count++;
				else
					break;
			if(count>=3)
			push(i,y,count,'v');
			i=j;
		}
		vertical(y+1);
	}
}

void mark(int mtop)
{
	if(mtop>=0)
	{
		stack tem=pop();
		if(tem.m=='h')
			for(int i=tem.y;i<tem.y+tem.c;i++)
				can[tem.x][i].mat=-1;
		else
			for(int j=tem.x;j<tem.x+tem.c;j++)
				can[j][tem.y].mat=-1;
		mark(top);
	}
}

int first(int y)
{
	for(int i=r-1;i>=0;i--)
		if(can[i][y].mat==-1)
			return i;
	return -2;
}

int second(int y,int f)
{

	for(int i=f;i>=0;i--)
		if(can[i][y].mat!=-1)
			return i;
	return -2;
}

void fill(int y,int x)
{
	randomize();
	static int previous;
	for(int i=x;i>=0;i--)
	{
		int tem=rand()%5;
		if(previous==tem)
			i++;
		else
			previous=can[i][y].mat=tem;

	}
}

void recover(int y)
{
	if(y<c)
	{
		int mptr;
		while((mptr=first(y))>=0)
		{
			int uptr=second(y,mptr);
			if(uptr>=0)
			{
				can[mptr][y].mat=can[uptr][y].mat;
				can[uptr][y].mat=-1;
			}
			else
			{
				fill(y,mptr);
				recover(y+1);
				return;
			}
		}
		recover(y+1);
		return;
	}
}
