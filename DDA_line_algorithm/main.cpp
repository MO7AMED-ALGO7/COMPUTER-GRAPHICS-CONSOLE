#include <iostream>
#include <windows.h>
#include<cmath>

using namespace std;


// *************  this code for putPixel at (x,y) coordinates  ******************

HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
COORD screen ;
void setPixel(int x , int y , int color = 15 , char m = '*') // default valurs
{
    screen.X = x ;
    screen.Y = y ;
    SetConsoleCursorPosition(h,screen);
    SetConsoleTextAttribute(h , color) ; // color in range [0 , 15] ;
    cout<<m ;
    SetConsoleTextAttribute(h , 15) ; // color white;
}

void dda_line(double x0 , double y0 , int x1 , int y1){

    int dx = x1 - x0 ,
        dy = y1 - y0 ,
        steps ;

    if(abs(dx)<abs(dy)) steps = abs(dy) ;
    else steps = abs(dx) ;

    double xinc = (double)dx/steps ;
    double yinc = (double)dy/steps ;

    while(steps >= 0){
        setPixel(round(x0),round(y0),4) ;
        x0 += xinc ;
        y0 += yinc ;
        steps--;
    }

}

int main()
{
    dda_line(1,1,20,5);
    return 0;
}
