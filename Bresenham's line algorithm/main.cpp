#include <iostream>
#include <windows.h>
#include<cmath>

using namespace std;


// *************  this code for putPixel at (x,y) coordinates  ******************

HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
COORD screen ;

void gotoXY(int x , int y)
{
    screen.X = x ;
    screen.Y = y ;
    SetConsoleCursorPosition(h,screen);
}
void setPixel(int color = 15 , char m = '*') // default valurs
{
    SetConsoleTextAttribute(h , color) ; // color in range [0 , 15] ;
    cout<<m ;
    SetConsoleTextAttribute(h , 15) ; // color white;
}

int unitVect(int vect){

    if(vect!=0) return vect/abs(vect);
    return 0 ;
}

void bresnham(int x0 , int y0 , int x1 , int y1){

    int ux = unitVect(x1 - x0) , uy = unitVect(y1 - y0),
        dx = (x1 - x0)*ux , dy = (y1 - y0)*uy ;

        if(dx > dy)
        {
            int dxy = 2*dy - 2*dx , p = dxy + dx , i = 0 ;

            dy*=2;

            while(i<=dx){
                gotoXY(x0 , y0) ;
                setPixel(3);
                x0 += ux ;

                if( p < 0 ) p += dy ;
                else
                {
                    p+=dxy ; y0 += uy ;
                }
                i++;
            }
        }
        else{
            int dxy = 2*dx - 2*dy , p = dxy + dy , i = 0 ;

            dx += 2 ;

            while( i <= dy ){
                gotoXY(x0 , y0) ;
                setPixel(3);
                y0 += uy ;

                if( p < 0 ) p += dx ;
                else{
                    p += dxy ;
                    x0 += ux ;
                }
                i++;
            }
        }


}

int main()
{
    bresnham(20 , 5 , 5 , 20);
    gotoXY(21 , 21) ;

    return 0;
}
