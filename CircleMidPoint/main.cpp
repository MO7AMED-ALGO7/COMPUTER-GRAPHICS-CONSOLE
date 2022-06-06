#include<iostream>
#include<windows.h>

using namespace std ;

HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

COORD screen ;

void setPixel(int x , int y , int color = 15) // default color
{
    screen.X = x;
    screen.Y = y ;
    SetConsoleCursorPosition(h, screen);
    SetConsoleTextAttribute(h , color);
    cout << '*';
    SetConsoleTextAttribute(h , 15);
}

void midPointCircle(int xc , int yc , int radius)
{
    double p = 5/4 - radius ;
    int x = 0 ,
        y = radius;

    while( x <= y )
    {
        setPixel(x + xc , y + yc , 5);
        setPixel(-x + xc , y + yc , 6);
        setPixel(x + xc , -y + yc , 7);
        setPixel(-x + xc , -y + yc , 8);

        setPixel(y + xc , x + yc , 9);
        setPixel(-y + xc , x + yc , 10);
        setPixel(y + xc , -x + yc , 11);
        setPixel(-y + xc , -x + yc , 12);

        if( p < 0 )
        {
            x++;
            p += 2*x + 1 ;
        }
        else
        {
            x++;
            y--;
            p += 2*x + 1 - 2*y ;
        }

    }
}

void changeTextFont(int xw , int yw)
{
    CONSOLE_FONT_INFOEX cfi ;
    cfi.cbSize = sizeof(cfi) ;
    cfi.nFont = 0 ;
    cfi.dwFontSize.X = xw ;  // Width of each character in the font
    cfi.dwFontSize.Y = yw ;  // Height of each character in the font
    cfi.FontFamily = FF_DONTCARE ;
    cfi.FontWeight = FW_NORMAL ;
    wcscpy(cfi.FaceName , L"Consolas") ;
    SetCurrentConsoleFontEx(h , FALSE , &cfi) ;
}

int main()
{
    changeTextFont(5,5);
    midPointCircle(15,15,10);

    // center of circle
    setPixel(15,15);
    while(true){}
    return 0 ;
}
