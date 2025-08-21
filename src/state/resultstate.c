#include "resultstate.h"
#include <string.h>
#include "../rguiabs.h"
#include "state.h"
#include <stdio.h>
#include <winuser.h>

typedef struct _TierArray {
    char name[17];
    Tiers tierar[20];
} TierArray;

static TierArray tierar;
static INT tierAmount = 0;


VOID BeginTier(PCHAR name){
    strcpy_s(tierar.name, 17, name);
}



VOID PlaceTier(Tiers tier){
    if(tierAmount < 0 || tierAmount > 19) return;
    strcpy_s(tierar.tierar[tierAmount].tier, 5, tier.tier);
    strcpy_s(tierar.tierar[tierAmount].tierName, 50, tier.tierName);
    strcpy_s(tierar.tierar[tierAmount].peakTier, 30, tier.peakTier);

    tierAmount++;
}

VOID ResultState(){
    static FLOAT scroll = 0;
    static BOOL init = false;
    static Image img;
    static Texture text;
    if(init == false){
        SetWindowTitle(tierar.name);
        Image image = LoadImage("temp/head.png");
        text = LoadTextureFromImage(image);
        SetWindowIcon(image);
        init = true;
    }
    Vector2 pos = {Width() - 200, scroll + 5};
    DrawTextureEx(text, pos, 0, 1, WHITE);
    
    UINT64 final = 0;
    RGUIDrawText(tierar.name, 10, scroll + 10,  50, FALSE);
    if(GetMouseWheelMoveV().y != 0){
        scroll += GetMouseWheelMoveV().y * 20;
    }
    if(IsKeyDown(KEY_PAGE_DOWN)){
        scroll -= 100.0f * 10;
    }
    if(scroll >= 0){
        scroll = 0;
    }
    for(int i = 0; i < tierAmount; i++){
        RGUIDrawTextEx(tierar.tierar[i].tierName, 10, scroll + ((i + 2) * 80), 30, TEXT_COLOR_PRESSED, FALSE);
        RGUIDrawTextEx(tierar.tierar[i].tier, 10, scroll + ((i + 2) * 80) + 30, 30, TEXT_COLOR_PRESSED, FALSE);
        RGUIDrawText(tierar.tierar[i].peakTier, 60, scroll + ((i + 2) * 80) + 30, 30,FALSE);
        final = scroll + ((i + 2) * 80) + 30;
        DrawLine(10, scroll + ((i + 2) * 80) + 65, Width() - 10, scroll + ((i + 2) * 80) + 65, 
                    RGUIGetTextColor());
    }
    if(final == 0){
        RGUIDrawText("No data about this player found.....", 10, scroll + 100, 30, FALSE);
        final = scroll + 100;
    }
    INT button = RGUIDrawButton("Go Back", 10, final + 70, 70, 50);
    if(button == 1){
        SetWindowTitle("Native MCTiers");
        RGUISetIconToDefault();
        ChangeState(3);
        for(int i = 0; i < tierAmount; i++){
            sprintf_s(tierar.tierar[tierAmount].tier, 5, "");
            sprintf_s(tierar.tierar[tierAmount].peakTier, 30, "");
            strcpy_s(tierar.tierar[tierAmount].tierName, 50, "");
            strcpy_s(tierar.name, 16, "");
        }
        tierAmount = 0;
        ChangeState(0);
        init = false;
        scroll = 0;
        UnloadTexture(text);
        UnloadImage(img);
    }
}

