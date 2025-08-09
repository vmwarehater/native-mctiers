#include "extern/naett/naett.h"
#include "extern/raylib/raylib.h"
#include "rguiabs.h"

#include "state/state.h"

INT main(INT argc, PCHAR argv[]){
    naettInit(NULL);
    SetTargetFPS(60);
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    SetTraceLogLevel(LOG_ERROR);
    InitWindow(800, 1000, "Open Mctiers");
    RGUIInit();
    while(!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(RGUIGetBackgroundColor());
        RenderStates();
        EndDrawing();
    }
    CloseWindow();

    return 0;
}