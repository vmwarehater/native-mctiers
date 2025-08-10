#include "state.h"
#include "../rguiabs.h"

VOID ErrorState(){
    RGUIDrawText("Error\n\nCouldn't Find Player!", 10, 10, 40, true);
    INT button = RGUIDrawButton("Go Back", 10, 150, 70, 50);
    if(button == 1){
        ChangeState(0);
    }
}