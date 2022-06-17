#include <iostream>
#include<windows.h>

using namespace std;

HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

COORD screen ;

void changeTextFont(int xw = 0 , int yw = 15){
    CONSOLE_FONT_INFOEX cfi ;
    cfi.cbSize = sizeof(cfi) ;
    cfi.nFont = 0;
    cfi.dwFontSize.X = xw;       // Width of each character in the font
    cfi.dwFontSize.Y = yw;          // Height
    cfi.FontFamily = FF_DONTCARE;
    cfi.FontWeight = FW_NORMAL;
    std::wcscpy(cfi.FaceName, L"Consolas"); // Choose your font
    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
}

void setPixel(int x , int y , int color = 15) // default valurs
{

        screen.X = x ;
        screen.Y = y ;
        SetConsoleCursorPosition(h,screen);
        SetConsoleTextAttribute(h , color) ; // color in range [0 , 15] ;
        cout<<"*" ;
        SetConsoleTextAttribute(h , 15) ; // color white;
        //Sleep(10);
}

void bresenhamCircle(int xc , int yc , int raduis){


    int p = 3 - 2*raduis ;
    int x = 0 , y = raduis ;
    while( x <= y )
    {

         setPixel(x+xc,y+yc);
         setPixel(-x+xc,y+yc);
         setPixel(x+xc,-y+yc);
         setPixel(-x+xc,-y+yc);

         setPixel(y+xc,x+yc);
         setPixel(-y+xc,x+yc);
         setPixel(y+xc,-x+yc);
         setPixel(-y+xc,-x+yc);
         x++;
        if( p <= 0 )
        {
            p += 4*x + 6;
        }
        else
        {
            y--;
            p += 4*( x - y ) + 10;
        }
    }
}

int main()
{
    changeTextFont(8,8);
    bresenhamCircle(30,30,20);
    setPixel(30,30);
    while(true){}
    return 0;
}
