#include "extern/naett/naett.h"
#include "extern/raylib/raylib.h"
#include "rguiabs.h"

#include "state/state.h"
#include <winbase.h>

#define DEBUG

#ifndef DEBUG
INT WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
#else 
INT main(INT argc, PCHAR argv[])
#endif
{
    naettInit(NULL);
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    SetTraceLogLevel(LOG_ERROR);
    SetTargetFPS(60);
    InitWindow(900, 1200, "Native Mctiers");
    int x = GetMonitorWidth(GetCurrentMonitor());
    int y = GetMonitorHeight(GetCurrentMonitor());
    SetWindowSize(x / 3, y / 1.5);
    SetWindowPosition(x / 2, y / 2);
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