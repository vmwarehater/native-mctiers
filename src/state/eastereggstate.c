#include "eastereggstate.h"
#include "../extern/raylib/raylib.h"
#include "../rguiabs.h"
#include <winuser.h>







VOID EasterEggState(){
    static Texture2D text;
    static BOOL init = false;
    if(init == false){
        text = LoadTexture("resources/img/default.png");
        init = true;
    }
    ClearBackground(WHITE);
    Vector2 pos = {(float)Width() / 2, (float)Height() / 2};
    DrawTextureEx(text, pos, 0, 1, WHITE);
    DrawText("You aren't supposed to be here...", 10, 10, 30, RED);
    MessageBoxW(NULL, L"Native McTiers has crashed, we are sorry for the inconvenience",
                      L"Native McTiers", MB_OK | MB_ICONERROR);
}