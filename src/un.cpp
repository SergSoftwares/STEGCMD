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
    int bits=0;
    mid(x,"BPP (BYTES per pixel):");printf("\r");scanf("%d",&bits);
	mid(x,"STEGBMP V0.0.1 - DECODER");n();
    ept(x);n();
    bool safe=0;
    mid(x,"Safe mode? (ignore content after message)");n();
    mid(x,"[Shall corrupt files which contain null bytes]");n();
    fflush(stdin);
    int i=0;
    mid(x,"[1] -> yes; [0] -> no");col(17);printf("\r");scanf("%d",&i);
    safe=i==1;
    ept(x);n();
    mid(x,"+-------------------------------+");n();
    mid(x,"|Type the Image input file name |");n();
    mid(x,"|NAME:                          |");rett(6,x,"|NAME:                          |");
    char fname[26];
    col(0xf0);
    fflush(stdin);
    scanf("%25s",&fname);
    mid(x,"+-------------------------------+");n();
    ept(x);n();
    col(0xf0);
    
    std::ifstream img,txt;
    img.open(fname,std::ios::binary|std::ios::ate);
    int fsize = img.tellg();
    std::stringstream str;
    //HERE STARTS THE REAL THING
    
    std::ofstream out("rec.html",std::ios::binary);
    if(safe)out<<"<html><body><pre>";
    std::stringstream bn;
    img.seekg(10);
    char pos=(char)img.get();
    img.seekg(pos);
    mid(x,"Extracting bits...");n();
    for(int z=pos;z<=fsize;z++)
	{
		char c=img.get();
		if(z%bits==0)bn<<(((c << 0) & 1)?'1':'0');
	}
    img.close();
    mid(x,"OK!");n();
    mid(x,"Doing sorcery...");n();
    mid(x,"Extracted and processed bits:");n();
    col(0xf0);
    std::string msg="";
    std::string bf="";
    int pow[]={1,2,4,8,16,32,64};
    int buf=0;
    int cnt=0;
    for(int i=0;i<bn.str().size();i++)
    {
    	std::stringstream strngp;
    	strngp<<i;
    	printf("\r");ept(x);printf("\r");mid(x,strngp.str());
    	bf+=bn.str()[i];
    	if(i%7==0 & i!=0)
    	{
    		int num=0;
    		for(int z=0;z<7;z++)
    		{
    			num+=(int)((bf[z+i-7]=='1'?1:0)*pow[6-z]);
    		}
    		out<<(char)num;
    		cnt++;
    		if(safe)
			{
				if(num==1){buf++;}
    			else buf=0;
	    		if(buf>=5)break;
	    	}
    	}
    }
    n();
    if(safe)
	{
		out<<"</pre><HR>";
		for(int i=0;i<bf.size();i++)
		{
			if(i%7==0&i!=0)out<<"|\n";
			out<<bf[i];
		}
		out<<"</body></html>";
	}
    out.close();
    mid(x,"FINISHED!");
    Sleep(1500);
    n();n();
    std::stringstream strng;
    strng<<(bn.str().size()-cnt)/7<<" more characters could have been embedded in this image.";
    mid(x,strng.str());
    Sleep(1500);
    
    return 0;
}
