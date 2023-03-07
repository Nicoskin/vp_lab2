#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <windows.h>
#include <time.h>

using namespace std;

class walker{
public:
    int start_x, start_y, x, y;
    double r;
    char arr[10][10];

void init(){
    start_x=5; //начальные координаты
    start_y=5;
    r=0;
    for(int i =0;i<10;i++){
        for(int j=0;j<10;j++){
            arr[i][j]='-';
        }
}

}
void changepos(){
     cout<<"start_x:"<<start_x<<endl;
     cout<<"start_y:"<<start_y<<endl;
    srand(time(NULL));
    x=rand()%5-2; //сколько ходит
    y=rand()%5-2;
     cout<<"x:"<<x<<endl;
     cout<<"y:"<<y<<endl;
    if (start_x + x > 10) x = 10; // ограничения
    if (start_y + y > 10) y = 10;
    if (start_x + x < 0) x = 0;
    if (start_y + y < 0) y = 0; //
    arr[start_x + x][start_y + y]='S';
    start_x+=x;
    start_y+=y;
    r=sqrt(pow((start_x+x),2)+pow((start_y+y),2)); //считает расстояние от 0,0
     cout<<"r:"<<r<<endl;
    x=0;
    y=0; 
    for(int i =0;i<10;i++){
        for(int j=0;j<10;j++){
            cout<<arr[i][j]<<" ";
        }
        cout<<""<<endl;
    }
    arr[start_x + x][start_y + y]='-';
    r=0;
}

};

int main()
{
walker _w;
_w.init();
while(true){
    _w.changepos();
    Sleep(1000);
    system("cls");
}
return 0;
}