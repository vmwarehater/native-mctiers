#include "state.h"
#include "../rguiabs.h"

VOID ErrorState(){
    RGUIDrawText("Couldn't Find Player!", 10, 10, 40, true);
    INT button = RGUIDrawButton("Go Back", 10, 60, 70, 50);
    if(button == 1){
        ChangeState(0);
    }
}