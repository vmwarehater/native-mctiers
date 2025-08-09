#ifndef RGUIABS_H_INCLUDED
#define RGUIABS_H_INCLUDED




#include "typedef.h"

#include "extern/raylib/raylib.h"
#include "extern/raylib/raygui.h"

VOID RGUIInit();

VOID RGUIDrawText(const PCHAR text, INT x, INT y, FLOAT fontSize, BOOL isError);
Color RGUIGetBackgroundColor();
INT RGUIDrawButton(const PCHAR text, INT x, INT y, INT width, INT height);
INT RGUIDrawTextBox(const PCHAR text, INT x, INT y, INT width, INT height, FLOAT fontSize, BOOL editMode);
INT Width();
INT Height();


#endif