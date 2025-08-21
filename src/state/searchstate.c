#include "searchstate.h"
#include "state.h"
#include "../rguiabs.h"
#include "../search/search.h"
#include <handleapi.h>
#include <libloaderapi.h>
#include <minwindef.h>
#include <stdio.h>
#include <shellapi.h>
#include <winuser.h>

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
    // fun easter eggs =)
    INT about = RGUIDrawButton("What does this do?", 10 + 150, 140, 150, 50);
    // really bad code pls ignore its for an easter egg
    if(about == 1 && strcmp("ShellAbout", searchBuffer) == 0){
        HWND h = (HWND)GetWindowHandle();
        HINSTANCE hIns = GetModuleHandleW(NULL);
        HICON icon = LoadIconW(hIns, L"DEFAULTICON");
        ShellAboutW(h, L"Native Mctiers", 
            L"Copyright Najib Ahmed, All Rights Reserved", 
            icon);
        CloseHandle(h);
        CloseHandle(hIns); 
    }
    // bruhslsksnjsnjksnsjklnsjnjsklsnjl
    if(about == 1 && strcmp("weloveasecret", searchBuffer) == 0){
        ChangeState(4);
    }
}