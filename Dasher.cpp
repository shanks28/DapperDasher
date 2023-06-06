#include<cstdio>
#include "raylib.h"
struct AnimeData
{
    Rectangle rec;
    Vector2 Pos;
    int frame;
    float updateTime;
    float runningTime;
};
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
    AnimeData nebData{
        {0.0,0.0, nebula.width/8, nebula.height/8},//Rectangle rec
        {width,height-nebula.height/8},//Vector 2 Pos
        0,//int frame
        1.0/12.0,//float updateTeime
        0//Float runningTime
    };
    Rectangle nebularec{0.0,0.0, nebula.width/8, nebula.height/8}; 
    //this is defined as x,y width and height this is just 1 rectangle

    Vector2 nebPos{width,height-nebularec.height};
    int nebVel{-200};//nebula x velocity in px/sec since it should move from left to right acting as an obstacle

    //Nebula Animedata
    AnimeData neb2Data{
        {0.0,0.0,nebula.width/8,nebula.height/8}
        ,{width+300,height-nebula.height/8}
        ,0,
        1.0/16.0
        ,0.0
    };

    //scarfy variables
    Texture2D scrafy=LoadTexture("D:/GameDev/DapperDasher/textures/scarfy.png"); // this is a compound data type essentially making an object of the class texture2D and we can access all the functions  that come with the class and use it on the object itself
    AnimeData scarfyData;
    scarfyData.rec.width=scrafy.width/6;
    scarfyData.rec.height=scrafy.height;
    scarfyData.rec.x=0;
    scarfyData.rec.y=0;
    scarfyData.Pos.x=width/2-scarfyData.rec.width/2;
    scarfyData.Pos.y=height-scarfyData.rec.height;
    scarfyData.frame=0;
    scarfyData.updateTime=1.0/12.0;
    scarfyData.runningTime=0.0;


    //int posY{height-rec_height};//here we treat the rectangle as a single point on the top left corner of the rectangel of that width so height of the window would place the point at the bottom of the canvas and subtracting the height od the rectangel will place the actual rectangle on the bottn
    int velocity{0};
    //is the rectangle in the air
    bool isInAir{};
    //jump velocity
    const int jumpVel{-1000};// px/s
    //update time 
    
    SetTargetFPS(60); // this tells the system that it should display 60 complete frame per second to  the screen and well if we dont use this function then the sprite will achieve the highest possible frame rate 
    while(!WindowShouldClose())//since window should close will return true iff the x or the escape buttons are pressed
    {// the body of the while loop executes every frame
        BeginDrawing();
        ClearBackground(WHITE);
        const float dT{GetFrameTime()};// this is the time duration between each frame and as the acutal number of frames increases then the dT reduces and viceversa
        if(scarfyData.Pos.y>=height-scarfyData.rec.height)// this is the ground check condition
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
        nebData.Pos.x+=nebVel*dT;//this is to make it frame rate independent since speed is just rate of change of distance we just add it to the x pos every frame
        //scarfy pos
        //update the second nubulas position
        neb2Data.Pos.x+=nebVel*dT;
        
        scarfyData.Pos.y+=velocity * dT;// this is what actually moves the rectangle we multiply the position with dT because the units change from pizels per sec to pixels per frame
        if(!isInAir)
        {
            scarfyData.runningTime+=dT;

            if(scarfyData.runningTime>=scarfyData.updateTime)
            {
            //update running time
                scarfyData.runningTime=0.0;
                scarfyData.rec.x=scarfyData.frame*scarfyData.rec.width;
                scarfyData.frame++;
                if(scarfyData.frame>5)
                {
                    scarfyData.frame=0;
                }
            }
        }
        //update the nebula animation frame
        nebData.runningTime+=dT;
        if(nebData.runningTime>=nebData.updateTime)
        {
            nebData.runningTime=0.0;
            nebData.rec.x=nebData.frame* nebData.rec.width;
            nebData.frame++;
            if(nebData.frame>7)
            {
                nebData.frame=0;
            }
        }
        //update the nebula animation frame
        neb2Data.runningTime+=dT;
        if(neb2Data.runningTime>=neb2Data.updateTime)
        {
            neb2Data.runningTime=0.0;
            neb2Data.rec.x=neb2Data.frame* neb2Data.rec.width;
            neb2Data.frame++;
            if(neb2Data.frame>7)
            {
                neb2Data.frame=0;
            }
        }
        
        //Draw nebula
        DrawTextureRec(nebula,nebData.rec,nebData.Pos,WHITE);
        // Draw the second nebula
        DrawTextureRec(nebula,neb2Data.rec,neb2Data.Pos,RED);
        //Draw scarfy        
        DrawTextureRec(scrafy,scarfyData.rec,scarfyData.Pos,WHITE);

        EndDrawing();// this ensures that every frame is correctly rendered by the gpu
    }
    UnloadTexture(scrafy);
    UnloadTexture(nebula);
    CloseWindow();// this function is just included for convention as it uses some under the hood functionaloty to actually close the window
}