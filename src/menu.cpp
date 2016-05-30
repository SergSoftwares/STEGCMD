#include <stdio.h>
#include <windows.h>
#include <string>
#include <sstream>
#include <fstream>

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

void ept(int x)
{
	SetConsoleTextAttribute(hConsole, 17);
	for(int i=0;i<x-1;i++)
    {
    	printf(" ");
    }
}

void p()
{
	printf("\f");
}

void n()
{
	printf("\n");
}

void col(int c)
{
	SetConsoleTextAttribute(hConsole, c);
}

void mid(int x, std::string c)
{
	SetConsoleTextAttribute(hConsole, 17);
	int s=((x-1)/2)-(c.size()/2);
	for(int i=0;i<s;i++)
    {
    	printf(" ");
    }
    SetConsoleTextAttribute(hConsole, 0xf0);
    printf(c.c_str());
    SetConsoleTextAttribute(hConsole, 00);
    printf(" ");
    SetConsoleTextAttribute(hConsole, 17);
    for(int i=s+c.size();i<x-2;i++)
    {
    	printf(" ");
    }
}

void ret(int x)
{
	for(int i=0;i<x;i++)
	{
		printf("\b");
	}
}

void rett(int a,int x,std::string c)
{
	int s=((x)/2)-(c.size()/2);
	ret(x-s-a);
}

std::string toBinary(int n)
{
    std::string r;
    while(n!=0) {r=(n%2==0 ?"0":"1")+r; n/=2;}
    while(r.size()!=7)r="0"+r;
    return r;
}

int main(int argc, char *argv[]) {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int x,y;

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    x = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    y = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    while(true)
    {
    	col(17);
    	system("cls");
	    mid(x,"STEGCMD V0.0.1");n();
	    ept(x);n();
	    mid(x,"+-------------------------+");n();
	    mid(x,"|Welcome to STEGCMD V0.0.1|");n();
	    mid(x,"+-------------------------+");n();
	    ept(x);n();
	    mid(x,"Select an option:");n();
	    mid(x,"[1] -> STEGBMP; [2] -> QUIT");n();
	    int c=0;
	    fflush(stdin);
	    ept(x);rett(1,x," ");scanf("%d",&c);
	    int i=0;
	    switch(c)
	    {
	    	case 1:
				system("cls");
				mid(x,"STEGBMP V0.0.1");n();
				mid(x,"Select an option:");n();
				fflush(stdin);
	    		mid(x,"[1] -> Encoder; [2] -> Multi-depth Encoder; [3] -> Decoder; [4] -> Quit");printf("\r");scanf("%d",&i);
	    		switch(i)
	    		{
	    			case 1:system("cls");system("call main.exe");break;
	    			case 2:system("cls");system("call multi.exe");break;
	    			case 3:system("cls");system("call un.exe");break;
	    		}
			break;
			case 2:
				goto end;
			break;
	    }
	}
	end:
    return 0;
}
