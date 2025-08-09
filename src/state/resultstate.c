#include "resultstate.h"
#include <string.h>
#include "../rguiabs.h"
#include "state.h"
#include <stdio.h>

typedef struct _TierArray {
    char name[16];
    Tiers tierar[20];
} TierArray;

static TierArray tierar;
static int tierAmount = 0;

void BeginTier(char* name){
    strcpy_s(tierar.name, 16, name);
}

void PlaceTier(Tiers tier){
    if(tierAmount < 0 || tierAmount > 19) return;
    strcpy_s(tierar.tierar[tierAmount].tier, 5, tier.tier);
    strcpy_s(tierar.tierar[tierAmount].tierName, 10, tier.tierName);
    tierAmount++;
}

void ResultState(){
    static UINT64 scroll = 0;
    UINT64 final = 0;
    RGUIDrawText(tierar.name, 10, scroll + 10,  50, FALSE);
    for(int i = 0; i < tierAmount; i++){
        RGUIDrawText(tierar.tierar[i].tierName, 10, scroll + ((i + 2) * 80), 30, FALSE);
        RGUIDrawText(tierar.tierar[i].tier, 10, scroll + ((i + 2) * 80) + 30, 30, FALSE);
        final = scroll + ((i + 2) * 80) + 30;
    }
    if(final == 0){
        RGUIDrawText("No data about this player found.....", 10, scroll + 100, 30, FALSE);
        final = scroll + 100;
    }
    INT button = RGUIDrawButton("Go Back", 10, final + 30, 70, 50);
    if(button == 1){
        for(int i = 0; i < tierAmount; i++){
            sprintf_s(tierar.tierar[tierAmount].tier, 5, "");
            strcpy_s(tierar.tierar[tierAmount].tierName, 10, "");
            strcpy_s(tierar.name, 16, "");
        }
        tierAmount = 0;
        ChangeState(0);
    }
}

