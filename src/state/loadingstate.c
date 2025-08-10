#include "loadingstate.h"
#include "../rguiabs.h"


static char* animation[] = {
    "ooO",
    "Ooo",
    "oOo"
};


VOID LoadingState(){
    static int curAnim = 0;
    static double curTime;
    static bool init = false;
    if(init == false){
        curTime = GetTime();
        init = true;
    }
    char text[11] = "Loading...";
    RGUIDrawText(text, 
                    ((float)Width() / 2) - MeasureTextEx(RGUIGetFont(), text, 40, 1).x, 
                    (Height() / 2) - 120, 90, FALSE);
    RGUIDrawText(animation[curAnim], 
                    ((float)Width() / 2) - MeasureTextEx(RGUIGetFont(), animation[curAnim], 40, 1).x, 
                    (Height() / 2), 40, FALSE);
    if((GetTime() - curTime) >= 0.3){
        if(curAnim >= 2){
            curAnim = 0;
        }
        else curAnim++;
        curTime = GetTime();
    }
}