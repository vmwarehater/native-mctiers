#include "extern/naett/naett.h"
#include "extern/raylib/raylib.h"
#include "rguiabs.h"

#include "state/state.h"

INT main(INT argc, PCHAR argv[]){
    naettInit(NULL);
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    SetTraceLogLevel(LOG_ERROR);
    SetTargetFPS(60);
    InitWindow(900, 1200, "Native Mctiers");
    RGUIInit();
    while(!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(RGUIGetBackgroundColor());
        RenderStates();
        EndDrawing();
    }
    RGUICleanup();
    CloseWindow();

    return 0;
}