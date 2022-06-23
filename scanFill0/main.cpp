#include <iostream>
#include <windows.h>
#include <vector>
using namespace std;

using namespace std;

HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
COORD screen ;

int x01 = 0 ;
int y01 = 0 ;

bool isPenDown = false ;
bool isFill = false ;

vector<int> dataY ;
vector<vector<int>> dataX ;

void saveData(int x , int y) {

    int length = dataY.size();
    for (int i = 0 ; i < length ; i++){
        if(dataY[i] == y) {
            for (int j = 0 ; j < dataX[i].size() ; j++){
                if(dataX[i][j] == x) return;
            }
            dataX[i].push_back(x);
            return;
        }
    }
    dataY.push_back(y);
    dataX.push_back(vector<int>());
    dataX[length].push_back(x);
}

void setPixel(int x , int y , int color = 15 , char m = '*') // default valurs
{

    screen.X = x ;
    screen.Y = y ;
    SetConsoleCursorPosition(h , screen) ;
    SetConsoleTextAttribute(h , color) ; // color in range [0 , 15] ;
    cout << m ;
    SetConsoleTextAttribute(h , 15) ; // color white;
    Sleep(50);
}
int unitVect(int vect){

    if(vect!=0) return vect/abs(vect);
    return 0 ;
}
void bresnham_line(int x0 , int y0 , int x1 , int y1){

    int ux = unitVect(x1 - x0) , uy = unitVect(y1 - y0),
        dx = (x1 - x0)*ux , dy = (y1 - y0)*uy ;

        if(dx > dy)
        {
            int dxy = 2*dy - 2*dx , p = dxy + dx , i = 0 ;

            dy*=2;

            while(i<dx){
                setPixel(x0,y0,3);
                saveData(x0 , y0);
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

            dx *= 2 ;

            while( i < dy ){
                setPixel(x0,y0,3);
                saveData(x0,y0);
                y0 += uy ;

                if( p < 0 ) p += dx ;
                else{
                    p += dxy ;
                    x0+= ux ;
                }
                i++;

            }

        }
    x01 = x0 ;
    y01 = y0 ;



}

void goToXY(int x1 , int y1){

    if(isPenDown)
        bresnham_line(x01 , y01 , x1 , y1);
    else{
        x01 = x1 ;
        y01 = y1 ;
    }

}

void penDown(){
    isPenDown = true;
}

void penUp(){
    isPenDown = false ;
}

void beginScanFill(){
     isFill = true;
}

int fillColor = 15 ;

void fillScan(vector<int> dataXi , int y0) {
    bool fillState = true ;
    int length = dataXi.size();
    int k = 1 ;
    int xi = -1 ;
    for (int i = 0 ; i < length ; i++) {
        for (int j = i+1 ; j < length ; j++) {
            if(dataXi[j] < dataXi[i]){
                int a = dataXi[j] ;
                dataXi[j] = dataXi[i] ;
                dataXi[i] = a ;
            }
        }
        if(xi == -1) xi = dataXi[i];
        else if(dataXi[i] == xi + k) {k++;}
        else {
            if(fillState){
                for (int x0 = xi+k ; x0<dataXi[i] ; x0++)
                    setPixel(x0,y0,fillColor);
            }
            fillState = !fillState ;
            xi = dataXi[i];
            k = 1 ;
        }
    }
}

void endScanFill(){
    isFill = false ;

    for (int i = 0 ; i < dataY.size() ; i++) {
        fillScan(dataX[i] , dataY[i]);
    }

    dataX.clear();
    dataY.clear();
}

int main()
{

    beginScanFill();
        fillColor = 1 ;
        goToXY(40 , 15) ;
        penDown();
        goToXY(3,3);
        goToXY(40,3);
        goToXY(40,15);
        penUp();
    endScanFill();

    beginScanFill() ;
        fillColor = 2 ;
        goToXY(13,13) ;
        penDown() ;
        goToXY(15,15) ;
        goToXY(25,25) ;
        goToXY(15,25) ;
        goToXY(0,40) ;
        goToXY(13,13) ;
        penUp();
    endScanFill() ;

    beginScanFill() ;
        fillColor = 4;
        goToXY(50,3) ;
        penDown() ;
        goToXY(50,25) ;
        goToXY(80,25) ;
        goToXY(80,40) ;
        goToXY(50,3) ;
        penUp() ;
    endScanFill();

    while(true);
    return 0;
}
