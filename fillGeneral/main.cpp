#include <iostream>
#include <windows.h>
#include <vector>

using namespace std;

HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
COORD screen ;

int x01 = 0 ;
int y01 = 0 ;
bool isPenDown = false;

vector<int> dataY;           // [y0 , y1 , y2 , .... , yn]
vector<vector<int>> dataX;   // [[x0,x1,x2,...,xn] , [x0,...,xn]......]

int xmin = 1000,
    xmax = -1 ,
    ymin = 1000,
    ymax = -1;

bool isForFill = false ;

bool isPointOnLine(int x0 , int y0){
    if(!isForFill) return false;

    int ly = dataY.size();
    int indx = 0 ;

    for(int i = 0 ; i < ly ; i++){
        if(dataY[i] == y0){
            int lx = dataX[i].size();
            int k = -1 ;
            for (int j = 0 ; j < lx ; j++){
                if(k == -1){
                    if(dataX[i][j] - 1 == x0){
                        dataX[i][j] = x0 ;
                        return false;
                    }
                    else if( x0 < dataX[i][j]){
                        dataX[i].insert(dataX[i].begin()+j,2,x0);
                        return false;
                    }
                }else{
                    if(dataX[i][j] + 1 == x0){
                        if(j < lx - 1 && dataX[i][j+1] == x0){
                            dataX[i].erase(next(dataX[i].begin(),j),next(dataX[i].begin(),(j+2)));
                            return true;
                        }
                        dataX[i][j] = x0 ;
                        return false ;
                    }else if(x0 > dataX[i][j]) indx = j ;
                     else if(x0 <= dataX[i][j]) return true;
                }
                k*=-1;
            }
            dataX[i].insert(dataX[i].begin()+indx+1,2,x0);
            return false;
        }
    }

    dataY.push_back(y0);
    dataX.push_back(vector<int>());
    dataX[ly].push_back(x0);
    dataX[ly].push_back(x0);

    return false;
}

void setPixel(int x , int y , int color = 15 , char m = '*') // default valurs
{
    if(isForFill){
        xmin = min(xmin,min(x01,x));
        xmax = max(xmax,max(x01,x));
        ymin = min(ymin,min(y01,y));
        ymax = max(ymax,max(y01,y));
        isPointOnLine(x,y);
    }

    screen.X = x ;
    screen.Y = y ;
    SetConsoleCursorPosition(h,screen);
    SetConsoleTextAttribute(h , color) ; // color in range [0 , 15] ;
    cout<<m ;
    SetConsoleTextAttribute(h , 15) ; // color white;
    Sleep(20);
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
                setPixel(x0,y0);
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
                setPixel(x0,y0);
                y0 += uy ;
                if( p < 0 ) p += dx ;
                else{
                    p += dxy ;
                    x0+= ux ;
                }
                i++;
            }
        }
}

void penDown(){isPenDown = true;}
void penUp(){isPenDown = false;}

void beginFill(){isForFill = true;}

void savePoint(int x = xmin , int y = ymin){

    if(x < xmin || x > xmax || y < ymin || y > ymax) return;
    else if(isPointOnLine(x,y)) return;

    savePoint(x+1,y);
    savePoint(x-1,y);
    savePoint(x,y+1);
    savePoint(x,y-1);
}

int fillColor = 4;

void endFill(){
    xmin-=1;
    xmax+=1;
    ymin-=1;
    ymax+=1;

    savePoint();
    for (int i = 0; i < dataY.size() ; i++){
        int y = dataY[i];
        if(y<=ymin || y>=ymax || dataX[i].size() == 2) continue;
        for(int j = 1 ; j < dataX[i].size() ; j+=2){
            for(int x = dataX[i][j]+1 ; x<dataX[i][j+1] ; x++){
                setPixel(x,y,fillColor);
            }
        }
    }
    isForFill = false;
    dataX.clear();
    dataY.clear();

    xmin = 1000;
    xmax = -1;
    ymin = 1000;
    ymax = -1 ;
}

void goToXY(int x , int y){
    if(isPenDown)
        bresnham_line(x01,y01,x,y);
    x01 = x ;
    y01 = y ;
}

void changeTextFont(int xw = 15 , int yw = 15){

     CONSOLE_FONT_INFOEX cfi;
     cfi.cbSize = sizeof(cfi);
     cfi.nFont = 0 ;
     cfi.dwFontSize.X = xw ;
     cfi.dwFontSize.Y = yw ;
     cfi.FontFamily = FF_DECORATIVE;
     cfi.FontWeight = FW_NORMAL ;
     wcscpy(cfi.FaceName , L"Consolas");
     SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE),FALSE , &cfi);
}

void midPointCircle(int xc , int yc , int raduis){
    int p = 1-raduis ;
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
        if( p < 0 )
        {
            x ++;
            p+=2*x+1;
        }
        else
        {
            x++;
            y--;

            p+=2*x+1-2*y;
        }
    }
}

int main()
{
    //bresnham_line(5,5,15,20);
    changeTextFont(10,10);
    beginFill();
        penUp();
        goToXY(13,13);
        penDown();
        goToXY(15,15);
        goToXY(25,25);
        goToXY(15,25);
        goToXY(5,40);
        goToXY(13,13);
        penUp();
        goToXY(40,15);
        penDown();
        goToXY(3,3);
        goToXY(40,3);
        goToXY(40,15);
        midPointCircle(50,20,10);
    endFill();

    /*beginFill();
        fillColor = 1;
        penUp();
        goToXY(40,15);
        penDown();
        goToXY(3,3);
        goToXY(40,3);
        goToXY(40,15);
        penUp();
    endFill();

    beginFill();
        fillColor = 2;
        midPointCircle(50,20,10);
    endFill();*/

    while(true){}
    return 0;
}
