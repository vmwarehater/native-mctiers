#include "rguiabs.h"
#include "extern/raylib/raylib.h"

#define RAYGUI_IMPLEMENTATION
#include "extern/raylib/raygui.h"


VOID RGUIInit(){
    GuiLoadStyle("resources\\styles\\style_genesis.rgs");
}

VOID RGUIDrawText(const PCHAR text, INT x, INT y, FLOAT fontSize, BOOL isError){
    Vector2 pos = {x, y};
    Color color;
    if(isError) color = RED;
    else color = GetColor(GuiGetStyle(TEXT, TEXT_COLOR_NORMAL));
    DrawTextEx(GuiGetFont(), text, pos, fontSize, 1, color);
}

Color RGUIGetBackgroundColor(){
    return GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR));
}

INT RGUIDrawButton(const PCHAR text, INT x, INT y, INT width, INT height){
    Rectangle pos = {x, y, width, height};
    return GuiButton(pos, text);
}

INT RGUIDrawTextBox(const PCHAR text, INT x, INT y, INT width, INT height, FLOAT fontSize, BOOL editMode){
    Rectangle pos = {x, y, width, height};
    return GuiTextBox(pos, text, fontSize, editMode);
}

INT Width(){
    return GetScreenWidth();
}

INT Height(){
    return GetScreenWidth();
}