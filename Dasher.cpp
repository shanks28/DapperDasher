#include<cstdio>
#include "raylib.h"
int main()
{
    //window dimentsion
    const int width{512};
    const int height{380};
    InitWindow(width,height,"DapperDasher"); // this is what actually draws the window
    //rectangel dimensions
    const int rec_width{50};
    const int rec_height{80};
    const int gravity{1};// this is p/f /f
    int posY{height-rec_height};//here we treat the rectangle as a single point on the top left corner of the rectangel of that width so height of the window would place the point at the bottom of the canvas and subtracting the height od the rectangel will place the actual rectangle on the bottn
    int velocity{0};
    //is the rectangle in the air
    bool isInAir{1};
    //jump velocity
    const int jumpVel{-22};

    SetTargetFPS(60);
    while(!WindowShouldClose())//since window should close will return true iff the x or the escape buttons are pressed
    {// the body of the while loop executes every frame
        BeginDrawing();
        ClearBackground(WHITE);
        if(posY>=height-rec_height)// this is the ground check condition
        {
            //rectangle is on the ground
            isInAir=false;
            velocity=0;
        }
        else
        {
            //rectangle is in the air and need to come back due to gravity
            velocity+=gravity;
            isInAir=true;
        }
        if(IsKeyPressed(KEY_SPACE)&&isInAir==false)// this means that ti will only jump if the rectangle is on the ground
        {
            velocity += jumpVel;// always remember our convention that we need a negative value if we want our sprite to move upward from the bottom of the canvas this makes it jump indirectly
        }
        
        posY+=velocity;// this is what actually moves the rectangle
        DrawRectangle(width/2,posY,rec_width,rec_height,BLUE);
        EndDrawing();
    }
    CloseWindow();// this function is just included for convention as it uses some under the hood functionaloty to actually close the window
}