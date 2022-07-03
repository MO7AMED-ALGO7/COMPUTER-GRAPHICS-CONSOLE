#include<iostream>
#include<windows.h>

using namespace std ;

HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
COORD screen;

void setPixel(int x , int y , int color = 15 , char m = '*')
{
    screen.X = x ;
    screen.Y = y ;
    SetConsoleCursorPosition(h , screen);
    SetConsoleTextAttribute(h , color);
    cout<<m;
    Sleep(20);
}

void midPointEllipse(int xc , int yc , int rx , int ry)
{
    int ry2 = ry*ry ;
    int rx2 = rx*rx ;
    int p = ry2 + rx2*0.25 - ry*rx2;
    int x = 0 , y = ry ;
    while(ry2*x < rx2*y){
        setPixel(x+xc , y+yc);
        setPixel(-x+xc , y+yc);
        setPixel(x+xc , -y+yc);
        setPixel(-x+xc , -y+yc);
        x++;
        if(p<0) p+=2*ry2*x + ry2;
        else{
            y--;
            p+=2*ry2*x - 2*rx2*y + ry2 ;
        }
    }

    while( y>= 0){
        setPixel(x+xc , y+yc);
        setPixel(-x+xc , y+yc);
        setPixel(x+xc , -y+yc);
        setPixel(-x+xc , -y+yc);
        y--;
        if(p<0){
            x++;
            p += 2*ry2*x - 2*rx2*y + rx2;
        }
        else p+=-2*rx2*y+rx2;

    }
}

void changeTextFont(int xw = 15 , int yw = 15){

    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof(cfi);
    cfi.dwFontSize.X = xw ;
    cfi.dwFontSize.Y = yw ;
    cfi.FontFamily = FF_DECORATIVE;
    cfi.FontWeight = FW_NORMAL ;
    wcscpy(cfi.FaceName , L"Consolas");
    SetCurrentConsoleFontEx(h , FALSE , &cfi);
}

int main()
{
    //setPixel(50,25);
    changeTextFont(10,10);
    midPointEllipse(30,20,25,15);
    //cout<<"hello world";
    while(true){}
    return 0 ;
}
