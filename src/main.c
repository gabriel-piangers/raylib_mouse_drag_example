/*******************************************************************************************
*
*   raylib [<module>] example - <name/short description>
*
*   Example complexity rating: [★☆☆☆] 1/4
*
*   Example originally created with raylib 5.5, last time updated with raylib 5.6
*
*   Example contributed by <author_name> (@<user_github>) and reviewed by Ramon Santamaria (@raysan5)
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) <year_created>-<year_updated> <author_name> (@<user_github>)
*
********************************************************************************************/

#include "raylib.h"
#include "raymath.h"
#include "resource_dir.h" // remove later

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - 2D Mouse dragging ");

    Rectangle boxRect = { screenWidth/2 - 40, screenHeight/2 - 40, 80.0f, 120.0f };
    Rectangle boxScaled = boxRect;           // BoxRect with scale applied
    Color boxColor = RED;
    bool pickedUp = false;
    Vector2 mouseOffset = { 0.0f, 0.0f };    // Stores the offset of the mouse relative to the box's position
    float boxScale = 1.0f;
    float maxScale = 2.0f;
    float minScale = 0.5f;
    float scallingSpeed = 0.1f;

    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        Vector2 mousePosition = GetMousePosition();
        float wheelMove = GetMouseWheelMove();

        // Input
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(mousePosition, boxScaled)) {
            pickedUp = true;
            mouseOffset = (Vector2) { boxRect.x - mousePosition.x, boxRect.y - mousePosition.y };
        }
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && pickedUp) {
            pickedUp = false;
        }

        // Box update
        if (pickedUp) {
            boxRect.x = mousePosition.x + mouseOffset.x;
            boxRect.y = mousePosition.y + mouseOffset.y;
        }
        if (wheelMove && CheckCollisionPointRec(mousePosition, boxScaled)) {
            boxScale = Clamp(boxScale + wheelMove*scallingSpeed, minScale, maxScale);
        }

        boxScaled.width = boxRect.width * boxScale;
        boxScaled.height = boxRect.height * boxScale;
        boxScaled.x = boxRect.x - boxRect.width*(boxScale - 1)/2;
        boxScaled.y = boxRect.y - boxRect.height*(boxScale - 1)/2;

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            DrawRectangleRec(boxScaled, boxColor);

            DrawText("Use mouse to drag and drop the box and mouse wheel to scale!", 10, 10, 20, GRAY);
            DrawText(TextFormat("Box scale: %.2f", boxScale), 10, 40, 20, LIGHTGRAY);
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}