#include "searchstate.h"
#include "state.h"
#include "../rguiabs.h"
#include "../search/search.h"
#include <stdio.h>

char searchBuffer[17];

VOID SearchState(){
    static BOOL edit = TRUE;
    RGUIDrawText("Search for a player", 10, 10, 50, FALSE);
    INT box = RGUIDrawTextBox(searchBuffer, 10, 80, Width() - 20, 40, 30, edit);
    if(strlen(searchBuffer) >= 17){
        sprintf_s(searchBuffer, 17, "");
    }
    INT button = RGUIDrawButton("Search", 10, 140, 150, 50);
    RGUIDrawText("Star The Github Repo!\nhttps://github.com/vmwarehater/native-mctiers", 
                            10, Height() - 80,30, FALSE);
    if(button == 1 || IsKeyPressed(KEY_ENTER)){
        ChangeState(1);
        BeginSearch(searchBuffer);
    }
}