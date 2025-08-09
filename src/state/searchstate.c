#include "searchstate.h"
#include "state.h"
#include "../rguiabs.h"
#include "../search/search.h"
char searchBuffer[16];

VOID SearchState(){
    static BOOL edit = TRUE;
    INT box = RGUIDrawTextBox(searchBuffer, 10, 10, Width() - 20, 40, 30, edit);
    INT button = RGUIDrawButton("Search", 10, 60, 70, 50);
    if(button == 1 || box == TRUE){
        ChangeState(1);
        BeginSearch(searchBuffer);
    }
}