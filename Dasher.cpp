#include<cstdio>
#include "raylib.h"
int main()
{
    //window dimentsion
    const int width{512};
    const int height{380};
    InitWindow(width,height,"DapperDasher"); // this is what actually draws the window
    //rectangel dimensions
    // const int rec_width{50};
    // const int rec_height{80};
    const int gravity{3000};// this is in pixels/s /s

    //nebula variables
    Texture2D nebula=LoadTexture("D:/GameDev/DapperDasher/textures/12_nebula_spritesheet.png");//this is the sprite sheet itself
    Rectangle nebularec{0.0,0.0, nebula.width/8, nebula.height/8}; 
    //this is defined as x,y width and height this is just 1 rectangle

    Vector2 nebPos{width,height-nebularec.height};
    int nebVel{-200};//nebula x velocity in px/sec since it should move from left to right acting as an obstacle

    Rectangle neb2Rec{0.0,0.0, nebula.width/8, nebula.height/8};
    Vector2 neb2Pos{width+300,height-nebularec.height};
    int neb2Frame{};
    const float neb2updateTime{1.0/16.0};
    float neb2RunningTime;

    //scarfy variables
    Texture2D scrafy=LoadTexture("D:/GameDev/DapperDasher/textures/scarfy.png"); // this is a compound data type essentially making an object of the class texture2D and we can access all the functions  that come with the class and use it on the object itself
    Rectangle scrafyrec;//compound datatype this is to select which particular image we want to select from the sprite sheet at any given point of time
    scrafyrec.width=scrafy.width/6;
    scrafyrec.height=scrafy.height;
    scrafyrec.x=0;
    scrafyrec.y=0;
    //animation frame
    int frame{};
    
    Vector2 scrafyPos;//compound datatype this is for the position of the scarfy sprite on the canvas
    scrafyPos.x=width/2-scrafyrec.width/2;// this splits the scrafy frame into 2 equal half and thus the image itself appears at the center of the screen
    scrafyPos.y=height-scrafyrec.height;// since we treate the image as a upper left point

    //nebula update variables
    int nebFrame{};
    const float nebUpdateTime{1.0/12.0};
    float nebRunningTime{};

    //int posY{height-rec_height};//here we treat the rectangle as a single point on the top left corner of the rectangel of that width so height of the window would place the point at the bottom of the canvas and subtracting the height od the rectangel will place the actual rectangle on the bottn
    int velocity{0};
    //is the rectangle in the air
    bool isInAir{};
    //jump velocity
    const int jumpVel{-1000};// px/s
    //update time 
    const float updateTime{1.0/12.0};//this is the amount of time that should pass between each animation frame
    float runningTime{0.0};// this is to keep a check of how much time has passed since the last time we updated our animation frame

    SetTargetFPS(60); // this tells the system that it should display 60 complete frame per second to  the screen and well if we dont use this function then the sprite will achieve the highest possible frame rate 
    while(!WindowShouldClose())//since window should close will return true iff the x or the escape buttons are pressed
    {// the body of the while loop executes every frame
        BeginDrawing();
        ClearBackground(WHITE);
        const float dT{GetFrameTime()};// this is the time duration between each frame and as the acutal number of frames increases then the dT reduces and viceversa
        if(scrafyPos.y>=height-scrafyrec.height)// this is the ground check condition
        {
            //rectangle is on the ground
            isInAir=false;
            velocity=0;
        }
        else
        {
            //rectangle is in the air and need to come back due to gravity
            velocity+=gravity * dT; // this is in pixels per sec and we need to convert it into pixels per frame which thus makes it independent of   the frame rate
            isInAir=true;
        }
        if(IsKeyPressed(KEY_SPACE)&&isInAir==false)// this means that ti will only jump if the rectangle is on the ground
        {
            velocity += jumpVel;// always remember our convention that we need a negative value if we want our sprite to move upward from the bottom of the canvas this makes it jump indirectly
        }
        //update nebula pos
        nebPos.x+=nebVel*dT;//this is to make it frame rate independent since speed is just rate of change of distance we just add it to the x pos every frame
        //scarfy pos
        //update the second nubulas position
        neb2Pos.x+=nebVel*dT;
        
        scrafyPos.y+=velocity * dT;// this is what actually moves the rectangle we multiply the position with dT because the units change from pizels per sec to pixels per frame
        if(!isInAir)
        {
            runningTime+=dT;

            if(runningTime>=updateTime)
            {
            //update running time
                runningTime=0.0;
                scrafyrec.x=frame*scrafyrec.width;
                frame++;
                if(frame>5)
                {
                    frame=0;
                }
            }
        }
        //update the nebula animation frame
        nebRunningTime+=dT;
        if(nebRunningTime>=nebUpdateTime)
        {
            nebRunningTime=0.0;
            nebularec.x=nebFrame* nebularec.width;
            nebFrame++;
            if(nebFrame>7)
            {
                nebFrame=0;
            }
        }
        //update the nebula animation frame
        neb2RunningTime+=dT;
        if(neb2RunningTime>=neb2updateTime)
        {
            neb2RunningTime=0.0;
            nebularec.x=neb2Frame* neb2Rec.width;
            neb2Frame++;
            if(neb2Frame>7)
            {
                neb2Frame=0;
            }
        }
        
        //Draw nebula
        DrawTextureRec(nebula,nebularec,nebPos,WHITE);
        // Draw the second nebula
        DrawTextureRec(nebula,neb2Rec,neb2Pos,RED);
        //Draw scarfy        
        DrawTextureRec(scrafy,scrafyrec,scrafyPos,WHITE);

        EndDrawing();// this ensures that every frame is correctly rendered by the gpu
    }
    UnloadTexture(scrafy);
    UnloadTexture(nebula);
    CloseWindow();// this function is just included for convention as it uses some under the hood functionaloty to actually close the window
}