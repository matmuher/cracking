/*******************************************************************************************
*
*   raylib [textures] example - sprite explosion
*
*   This example has been created using raylib 2.5 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2019 Anata and Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"
#include <stdio.h>

enum RET_CODES
	{
	FILE_NOT_FOUND = -1,
	PATCHED,
	INVALID_SIZE
	};

// Sprite's features
#define NUM_FRAMES_PER_LINE     4
#define NUM_LINES               7

RET_CODES patch(char* filename);

int main(int, char* argv[])
	{
	// Get file to patch from cmd 
	char* filename = argv[1] ? argv[1] : NULL;
	
	if (!filename)
		{
		puts("No patching programm was specified. Please put it's name as argument in cmd");
		
		return -1;
		}
		
	RET_CODES ret_patch = patch(filename);
	
	if(ret_patch != PATCHED)
		{
		return -1;
		}
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Kriss'a'ss Programm Cracker");

    InitAudioDevice();

    // Load explosion sound
    Sound fxBoom = LoadSound("resources/crack.wav");

    // Load explosion texture
    Texture2D crack_texture = LoadTexture("resources/crack.png");

    // Init variables for animation
    float frameWidth = (float)(crack_texture.width/NUM_FRAMES_PER_LINE);   // Sprite one frame rectangle width
    float frameHeight = (float)(crack_texture.height/NUM_LINES);           // Sprite one frame rectangle height
    int currentFrame = 0;
    int currentLine = 0;

    Rectangle frameRec = { 0, 0, frameWidth, frameHeight };
    Vector2 position = { 0.0f, 0.0f };

    bool active = false, cracked = false;
    int framesCounter = 0;

    SetTargetFPS(120);
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
		if (!cracked)
			{
		    // Check for mouse button pressed and activate explosion (if not active)
		    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && !active)
		    	{
		        position = GetMousePosition();
		        active = true;

		        position.x -= frameWidth/2.0f;
		        position.y -= frameHeight/2.0f;

		        PlaySound(fxBoom);
		    	}

		    // Compute explosion animation frames
		    if (active)
		    	{
		        framesCounter++;

		        if (framesCounter > 2)
		        	{
		            currentFrame++;

		            if (currentFrame >= NUM_FRAMES_PER_LINE)
				        {
			            currentFrame = 0;
			            currentLine++;

			            if (currentLine >= NUM_LINES)
					        {
				            currentLine = 0;
				            active = false;
				            cracked = true;
					        }
				        }

		            framesCounter = 0;
		        	}
		    	}

		    frameRec.x = frameWidth*currentFrame;
		    frameRec.y = frameHeight*currentLine;
		    //----------------------------------------------------------------------------------

		    // Draw
		    //----------------------------------------------------------------------------------
		    BeginDrawing();

		        ClearBackground(RAYWHITE);

		        // Draw explosion required frame rectangle
		        if (active) DrawTextureRec(crack_texture, frameRec, position, WHITE);

		    EndDrawing();
		    }
		else
			{
			BeginDrawing();

		        ClearBackground(RAYWHITE);

		        DrawText("Grats! Programm have been succefully cracked", 20, screenHeight/2, 30, VIOLET);

		    EndDrawing();
			}
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadTexture(crack_texture);   // Unload texture
    UnloadSound(fxBoom);        // Unload sound

    CloseAudioDevice();

    CloseWindow();              // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
	}


RET_CODES patch(char* filename)
	{
	const int VICTIM_PROGRAMM_SIZE = 8784;
	
	FILE* to_patch = fopen(filename, "r+");
	
	if(to_patch)
		{
		// Size validate
		fseek(to_patch, 0, SEEK_END);
		int size = ftell(to_patch);
		
		if (size != VICTIM_PROGRAMM_SIZE)
			{
			puts("[ERROR]: Check if you are trying to hack correct file");
			
			return INVALID_SIZE;
			}
		
		const int PATCH_ADDRESS = 0x10b9;
		fseek(to_patch, PATCH_ADDRESS, SEEK_SET);
		
		const short PATCH = 0x2375;
		fwrite(&PATCH, 1, sizeof(PATCH), to_patch);
		
		fclose(to_patch);
		
		return PATCHED;
		}
	else
		{
		printf("[ERROR]: %*s not found\n", 10, filename);
		
		return FILE_NOT_FOUND;
		}
	}