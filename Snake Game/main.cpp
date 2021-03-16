#include <iostream>
#include<conio.h>
#include <windows.h>
#include <dos.h>
#include <time.h>

#define MAXSNAKESIZE 100

using namespace std;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

void gotoxy(int x, int y){
    CursorPosition.X=x;
    CursorPosition.Y= y;
    SetConsoleCursorPosition(console,CursorPosition);
}
class Point
{
private:
    int x;
    int y;
public:
    Point(){
        x=y=10;
    }
    Point(int x, int y){
        this-> x=x;
        this-> y=y;
    }
    void SetPoint(int x, int y){
        this-> x=x;
        this-> y=y;
    }
    int GetX(){
        return x;
    }
    int GetY(){
        return y;
    }
    void MoveUp(){
        y--;
    }
    void MoveDown(){
        y++;
    }
    void MoveRight(){
        x++;
    }
    void MoveLeft(){
        x--;
    }
    void Draw(){
        gotoxy(x,y);
        cout<<"*";
    }
    void Erase(){
        gotoxy(x,y);
        cout<<" ";
    }
    void Debug(){
        gotoxy(x,y);
        cout<<"("<<x<<","<<y<<")";
    }
    void CopyPos(Point * p){
        p->x = x;
        p->y = y;
    }
};

class Snake{
private:
    Point * cell[MAXSNAKESIZE];
    int siz;
    char dir;
    Point fruit;
public:
    Snake(){
        siz = 1;
        cell[0]= new Point(20,20);
        for(int i=1;i<MAXSNAKESIZE;i++){
            cell[i] = NULL;
        }
        fruit.SetPoint(rand()%50, rand()%25);

    }
    void AddCell(int x,int y){
        cell[siz++] = new Point(x,y);
    }
    void TurnUp(){
    dir = 'z';
    }
    void TurnDown(){
    dir = 's';
    }
    void TurnRight(){
    dir = 'd';
    }
    void TurnLeft(){
    dir = 'q';
    }

    void Move(){
    //clear screen
    system("cls");
    //making body follow head
    for(int i=siz-1;i>0;i--)
        cell[i-1]->CopyPos(cell[i]);

    //moving head
    switch(dir){
    case 'z':
        cell[0]->MoveUp();
        break;
    case 's':
        cell[0]->MoveDown();
        break;
    case 'd':
        cell[0]->MoveRight();
        break;
    case 'q':
        cell[0]->MoveLeft();
        break;
    }
    //collision
    if(fruit.GetX()== cell[0]->GetX() && fruit.GetY() == cell[0]->GetY())
    {
        AddCell(0,0);
        fruit.SetPoint(rand()%50, rand()%25);

    }
    //drawing snake
    for(int i=0; i<siz;i++)
        cell[i]->Draw();
        fruit.Draw();

    Sleep(100);
}
    void Debug(){
        for(int i=0;i<siz;i++){
          cell[i]->Debug();
        }
    }

};

int main()
{
    //random no generation
    srand((unsigned)time(NULL));

    //test snake
    Snake snake;
    char op = 'l';
    do{
        if(kbhit()){
            op = getch();
        }
        switch(op){
        case 'z':
        case 'Z':
            snake.TurnUp();
            break;
        case 's':
        case 'S':
            snake.TurnDown();
            break;
        case 'd':
        case 'D':
            snake.TurnRight();
            break;
        case 'q':
        case 'Q':
            snake.TurnLeft();
            break;
        }

    snake.Move();
    }while(op != 'e');
Point p(20,20);
p.Draw();
return 0;
}
