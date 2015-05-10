#include <time.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>
#include <iostream>
using namespace std;
#define N 21

void set_color(int num)
{
    HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hout, num);
}
void set_location(int valuex, int valuey)
{
    HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD crd;
    crd.X = valuex * 2;
    crd.Y = valuey;
    SetConsoleCursorPosition(hout, crd);
}

void print_panel()
{
    set_color(7);
    for(int i = 0; i <= N-1; i++)
    {
        for(int j = 0; j <= N-1; j++)
        {
            if(i==0 || i==N-1 || j==0 || j==N-1)
                cout << "¡õ";
            else cout << "¡ö";
        }
        cout << endl;
    }
    set_location(N+3, 2);
    cout << "SCORE = 0";
    set_location(N+3, 4);
    cout << "LEVEL = 0";
}

double random(int head, int tail)
{
    return head + (tail-head)*rand()/(RAND_MAX+1.0);
}

void game()
{
    int len = 1;
    int** snake = NULL;
    int apple[2];
    bool exist = false;
    char ch = 'p';
    int store[2];
    int level = 0;

    snake = (int **)realloc(snake, sizeof(int*) * len);
    for(int i = 0; i < len; i++)
        snake[i] = (int *)malloc(sizeof(int) * 2);
    snake[0][0] = N/2;
    snake[0][1] = N/2;
    set_location(snake[0][1], snake[0][1]);
    set_color(11);
    cout << "¡Ñ";

    srand((unsigned)time(NULL));
    while(1)
    {
        if(!exist)
        {
            apple[0] = (int)random(1,N-1);
            apple[1] = (int)random(1,N-1);
            set_location(apple[0], apple[1]);
            set_color(random(12, 12));
            cout << "¡ï";
            exist = true;
            set_location(0, N);
        }

        store[0] = snake[len-1][0];
        store[1] = snake[len-1][1];
        for(int i = len-1; i >= 1; i--)
        {
            snake[i][0] = snake[i-1][0];
            snake[i][1] = snake[i-1][1];
            set_location(snake[i][0], snake[i][1]);
            set_color(11);
            cout << "¡ñ";
        }
        if(kbhit())
        {
            set_location(0, N);
            ch = getche();
        }
        switch(ch)
        {
        case 'a':
        case 'A':
            snake[0][0]--;
            break;
        case 'w':
        case 'W':
            snake[0][1]--;
            break;
        case 'd':
        case 'D':
            snake[0][0]++;
            break;
        case 's':
        case 'S':
            snake[0][1]++;
            break;
        default:
            break;
        }
        set_location(snake[0][0], snake[0][1]);
        set_color(11);
        cout << "¡Ñ";

        if(snake[0][0]==apple[0] && snake[0][1]==apple[1])
        {
            exist = false;
            len++;
            set_location(N+7, 2);
            set_color(7);
            cout << len-1;
            if(level != (len-2)/3 + 1)
            {
                set_location(N+7, 4);
                set_color(7);
                cout << ++level;
            }
            snake = (int**)realloc(snake, sizeof(int*) * len);
            snake[len-1] = (int*)malloc(sizeof(int) * 2);
            snake[len-1][0] = store[0];
            snake[len-1][1] = store[1];
            set_location(snake[len-1][0], snake[len-1][1]);
            set_color(11);
            cout << "¡ñ";
        }
        else
        {
            set_location(store[0], store[1]);
            set_color(7);
            cout << "¡ö";

            if(snake[0][0]==0||snake[0][0]==N-1||snake[0][1]==0||snake[0][1]==N-1)
            {

                set_location(N/2 - 2, N/2);
                for(int i = 0; i < len; i++)
                    free(snake[i]);
                cout << "GAME OVER!";
                break;
            }

            int flag = 0;
            for(int i = 1; i <= len-1; i++)
            {
                if(snake[0][0]==snake[i][0] && snake[0][1]==snake[i][1])
                {
                    set_location(N/2 - 2, N/2);
                    cout << "GAME OVER!";
                    for(int i = 0; i < len; i++)
                        free(snake[i]);
                    flag = 1;
                    break;
                }
            }
            if (flag == 1) break;

            if(len >= 16)
            {
                set_location(N/2 - 1, N/2);
                cout << "YOU WIN!";
                for(int i = 0; i < len; i++)
                    free(snake[i]);
                break;
            }
        }
        Sleep(300-50*level);
    }
    set_location(0, N);
}
int main()
{
    print_panel();
    game();
    return 0;
}
