#include <stdio.h>
#include <windows.h>
#include <string>
#include <sstream>
#include <fstream>
#include <stdlib.h>

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
    int bits=0;
    int t=0;
    mid(x,"BPP (BYTES per pixel):  ");rett(23,x,"BPP (BYTES per pixel):  ");
    Sleep(1500);
    col(0xf0);
    printf("?");n();
    Sleep(1500);
    mid(x,"STEGBMP V0.0.1");n();
    Sleep(1000);
    mid(x,"Multi-color depth mode");n();
    Sleep(1000);
    ept(x);n();
    mid(x,"+-------------------------------+");n();
    mid(x,"|Type the Image input file name |");n();
    mid(x,"|NAME:                          |");rett(6,x,"|NAME:                          |");
    char fname[26];
    col(0xf0);
    scanf("%25s",&fname);
    mid(x,"+-------------------------------+");n();
    ept(x);n();

    mid(x,"+------------------------+");n();
    mid(x,"|Type the number of tries|");n();
    mid(x,"|TRIES:                  |");rett(7,x,"|TRIES:                  |");
    col(0xf0);
    scanf("%d",&t);
    mid(x,"+------------------------+");n();
    ept(x);n();
    
    std::ifstream img,txt;
    img.open(fname,std::ios::binary|std::ios::ate);
    int fsize = img.tellg();
    std::stringstream str;
	str<<"For that image, ";
    str<<(fsize-54)/8;
    str<<" bytes can be embedded.";
    mid(x,str.str());n();n();
    Sleep(1000);
    
    mid(x,"+-----------------------------+");n();
    mid(x,"|Type the TEXT input file name|");n();
    mid(x,"|NAME:                        |");rett(6,x,"|NAME:                        |");
    char ifname[24];
    col(0xf0);
    scanf("%23s",&ifname);
    mid(x,"+-----------------------------+");n();
    ept(x);n();
    Sleep(2000);
    mid(x,"Continue?");n();
    Sleep(1000);
    mid(x,"[Y]es or [N]o");n();
    col(0xf0);
    fflush(stdin);
    char c;
    scanf("%c",&c);
    if(!(c=='y'|c=='Y')){printf("\a");return 0;}
    system("md OUT");
    //HERE STARTS THE REAL THING
    
    txt.open(ifname,std::ios::binary);
    
    std::stringstream bin;
    std::stringstream bin2;
    while(txt.get(c))
    {
		if(c<0){mid(x,"char c<0 !!!???");n();continue;}
    	bin<<toBinary(c);
    }
    txt.close();
    bin<<toBinary((char)255)<<toBinary((char)255)<<toBinary((char)255)<<toBinary((char)255)<<toBinary((char)255);
    std::string bn=bin.str();
   	for(int i=1;i<t;i++)
   	{
    	img.seekg(0);
	    std::stringstream flnam;
	    flnam<<"OUT/out"<<i<<".bmp";
	    std::ofstream o(flnam.str().c_str(),std::ios::binary);
	    int z=0;
		for(z=0;z<10;z++)o<<(char)img.get();
	    char pos=(char)img.get();
	    o<<pos;
	    for(z=11;z<pos;z++)o<<(char)img.get();
	    int m=0;
	    for(z=pos;z<=fsize;z++)
		{
			if(m>bn.size())break;
			c=img.get();
			if(z%i==0)
			{
				o<<(char)(c ^ ((-(bn[m]=='1') ^ c) & (1 << 0)));
				m++;
			}
			else o<<(char)c;
		}
		while(img.get(c))o<<(char)c;
		o.close();
		img.clear();
	}

	img.close();
	mid(x,"FINISHED!");
    Sleep(1000);
    return 0;
}
