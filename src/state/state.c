#include "state.h"
#include "eastereggstate.h"
#include "loadingstate.h"
#include "resultstate.h"
#include "searchstate.h"
#include "errorstate.h"



// yes a single variable holds the entire state
static UINT8 curState = 0;





VOID RenderStates(){
    switch(curState){
        case 0: 
            SearchState();
            break;
        case 1:
            LoadingState();
            break;
        case 2:
            ResultState();
            break;
        case 3:
            ErrorState();
            break;
        case 4:
            EasterEggState();
            break;
        default:
            ChangeState(0);
            break;
    }
}

VOID ChangeState(UINT8 state){
    curState = state;
}


UINT8 GetState(){
    return curState;
}