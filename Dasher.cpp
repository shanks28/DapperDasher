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
bool isOnGround(AnimeData data,int windowHeight)
{
    return data.Pos.y>=windowHeight-data.rec.height;
}
AnimeData updateAnimeData(AnimeData data,float deltaTime,int animeFrame)
{
    //update running time
    data.runningTime+=deltaTime;
    if(data.runningTime>=data.updateTime)
    {
        data.runningTime=0.0;
        //update animation frame
        data.rec.x=data.frame*data.rec.width;
        data.frame++;
        if(data.frame>animeFrame)
        {
            //resetting the frame to 0 so that it can loop over the entire spirite sheet
            data.frame=0;

        }
    }
    return data;
}
int main()
{
    //window dimentsion
    int windowDimensions[2];
    windowDimensions[0]=512;
    windowDimensions[1]=380;
    InitWindow(windowDimensions[0],windowDimensions[1],"DapperDasher"); // this is what actually draws the window
    //rectangel dimensions
    // const int rec_width{50};
    // const int rec_height{80};
    const int gravity{3000};// this is in pixels/s /s
    const int base_increment{300};

    //nebula variables
    Texture2D nebula=LoadTexture("D:/GameDev/DapperDasher/textures/12_nebula_spritesheet.png");//this is the sprite sheet itself
    Rectangle nebularec{0.0,0.0, nebula.width/8, nebula.height/8}; 
    //this is defined as x,y width and height this is just 1 rectangle

    int nebVel{-200};//nebula x velocity in px/sec since it should move from left to right acting as an obstacle]

    const int sizeOfNebulae{6};

    //Nebula Animedata
    AnimeData nebulae[sizeOfNebulae]{};
    for(int i=0;i<sizeOfNebulae;i++)
    {
        nebulae[i].rec.x=0.0;
        nebulae[i].rec.y=0.0;
        nebulae[i].rec.width=nebula.width/8;
        nebulae[i].rec.height=nebula.height/8;
        nebulae[i].Pos.y=windowDimensions[1]-nebula.height/8;
        nebulae[i].frame=0;
        nebulae[i].runningTime=0.0;
        nebulae[i].updateTime=1.0/16.0;
    }
    for(int i=0;i<sizeOfNebulae;i++)// this is just o set it explicitly
    {
        nebulae[i].Pos.x=windowDimensions[0]+(i*base_increment);

    }
    // nebulae[0].Pos.x=windowDimensions[0];
    // nebulae[1].Pos.x=windowDimensions[0]+300;
    // nebulae[2].Pos.x=windowDimensions[0]+600;


    //scarfy variables
    Texture2D scrafy=LoadTexture("D:/GameDev/DapperDasher/textures/scarfy.png"); // this is a compound data type essentially making an object of the class texture2D and we can access all the functions  that come with the class and use it on the object itself
    AnimeData scarfyData;
    scarfyData.rec.width=scrafy.width/6;
    scarfyData.rec.height=scrafy.height;
    scarfyData.rec.x=0;
    scarfyData.rec.y=0;
    scarfyData.Pos.x=windowDimensions[0]/2-scarfyData.rec.width/2;
    scarfyData.Pos.y=windowDimensions[1]-scarfyData.rec.height;
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
    Texture2D background=LoadTexture("textures/far-buildings.png");
    float bgx{};
    SetTargetFPS(75); // this tells the system that it should display 60 complete frame per second to  the screen and well if we dont use this function then the sprite will achieve the highest possible frame rate 
    while(!WindowShouldClose())//since window should close will return true iff the x or the escape buttons are pressed
    {// the body of the while loop executes every frame
        BeginDrawing();
        ClearBackground(WHITE);
        //draw the background
        
        Vector2 bgPos{bgx,0.0};// this is to define the starting position of the background texture
        DrawTextureEx(background,bgPos,0.0,2.0,WHITE);
        const float dT{GetFrameTime()};// this is the time duration between each frame and as the acutal number of frames increases then the dT reduces and viceversa
        bgx-=20*dT; // this is to make it frame rate independent
        if(isOnGround(scarfyData,windowDimensions[1]))// this is the ground check condition
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
        for(int i=0;i<sizeOfNebulae;i++)
        {
            //update the position of each nebula
            nebulae[i].Pos.x+=nebVel*dT;
        }
        //this is to make it frame rate independent since speed is just rate of change of distance we just add it to the x pos every frame
        //scarfy pos
        //update the second nubulas position
        //this is the animation frame for the scarfy spirite
        scarfyData.Pos.y+=velocity * dT;// this is what actually moves the rectangle we multiply the position with dT because the units change from pizels per sec to pixels per frame
        if(!isInAir)
        {
            scarfyData=updateAnimeData(scarfyData,dT,5);
        }
        //update the nebula animation frame
        for(int i=0;i<sizeOfNebulae;i++)
        {
            nebulae[i]=updateAnimeData(nebulae[i],dT,7);
        }
        nebulae[0].runningTime+=dT;
        
        for(int i=0;i<sizeOfNebulae;i++)
        {
            //Draw the nebula
            DrawTextureRec(nebula,nebulae[i].rec,nebulae[i].Pos,WHITE);
        }
        
        //Draw scarfy        
        DrawTextureRec(scrafy,scarfyData.rec,scarfyData.Pos,WHITE);

        EndDrawing();// this ensures that every frame is correctly rendered by the gpu
    }
    UnloadTexture(scrafy);
    UnloadTexture(nebula);
    UnloadTexture(background);
    CloseWindow();// this function is just included for convention as it uses some under the hood functionaloty to actually close the window
}