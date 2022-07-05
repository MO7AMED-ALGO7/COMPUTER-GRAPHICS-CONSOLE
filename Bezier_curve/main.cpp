#include <iostream>
#include <windows.h>
#include <cmath>
#include <vector>

using namespace std ;

HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
COORD screen;

vector<int> dataY;
vector<vector<int>> dataX ;

bool isThisPointColored(int x , int y)
{
    int len = dataY.size();
    for (int i = 0 ; i < len ; i++)
    {
        if(dataY[i] == y)
        {
            for (int j = 0 ; j < dataX[i].size() ; j++)
            {
                if(dataX[i][j] == x) return true;
            }
            dataX[i].push_back(x);
            return false;
        }
    }
    dataY.push_back(y);
    dataX.push_back(vector<int>());
    dataX[len].push_back(x);
}

void setPixel(int x , int y , int color = 15 , char c = '*')
{
    screen.X = x ;
    screen.Y = y ;
    SetConsoleCursorPosition(h,screen);
    SetConsoleTextAttribute(h , color);
    cout<<c ;
    Sleep(20);
}

int factorial(int n)
{
    if(n>0) return n*factorial(n-1);
    return 1 ;
}

struct Point{
    int x;
    int y;
};

void floodFill(int x , int y)
{
    if(isThisPointColored(x,y)) return;
    setPixel(x,y,4,'@');

    floodFill(x+1,y);
    floodFill(x-1,y);
    floodFill(x , y+1);
    floodFill(x , y-1);
}

void drawBezierCurv(vector<Point> points)
{
    int len = points.size();
    int n = len - 1;

    for (float t = 0 ; t <= 1 ; t+=0.01)
    {
        float sx = 0;
        float sy = 0;
        for(int i = 0 ; i < len ; i++)
        {
            float bin = factorial(n)/(factorial(i)*factorial(n-i))*pow(t,i)*pow(1-t,n-i);
            sx += bin*points[i].x;
            sy += bin*points[i].y;
        }

        if(!isThisPointColored(round(sx),round(sy)))
            setPixel(round(sx) , round(sy));
    }
}

void changeTextFont(int xw = 15 , int yw = 15)
{
    CONSOLE_FONT_INFOEX cfi ;
    cfi.cbSize = sizeof(cfi);
    cfi.dwFontSize.X = xw ;
    cfi.dwFontSize.Y = yw ;
    cfi.FontFamily = FF_DECORATIVE;
    cfi.FontWeight = FW_NORMAL ;
    wcscpy(cfi.FaceName , L"Consolas");
    SetCurrentConsoleFontEx(h , FALSE , &cfi);

}

void drawHeartAt(int x , int y)
{
     dataX.clear();
     dataY.clear();
     vector<Point> points0;

    points0.push_back({12+x,20+y});
    points0.push_back({2+x,8+y});
    points0.push_back({4+x,5+y});
    drawBezierCurv(points0);
    points0.clear();

    points0.push_back({4+x,5+y});
    points0.push_back({8+x,3+y});
    points0.push_back({12+x,7+y});
    drawBezierCurv(points0);
    points0.clear();

    points0.push_back({12+x,20+y});
    points0.push_back({22+x,8+y});
    points0.push_back({20+x,5+y});
    drawBezierCurv(points0);
    points0.clear();

    points0.push_back({20+x,5+y});
    points0.push_back({16+x,3+y});
    points0.push_back({12+x,7+y});
    drawBezierCurv(points0);
    points0.clear();

    floodFill(16+x,7+y);
}

int main()
{
    //setPixel(80,10);
    changeTextFont(20,20);

    drawHeartAt(0,0);
    drawHeartAt(10,10);
    drawHeartAt(30,15);
    drawHeartAt(40,18);

    while(true){}
    return 0;
}
