#include<cstdio>
#include "raylib.h"
int main()
{
    int width{400};
    int height{500};
    InitWindow(width,height,"DapperDasher");
    SetTargetFPS(60);
    while(WindowShouldClose()==false)
    {
        BeginDrawing();
        ClearBackground(RED);
        EndDrawing();
    }
}