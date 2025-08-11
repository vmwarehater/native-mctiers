#include "search.h"
#include "../extern/naett/naett.h"
#include "../extern/cjson/cjson.h"

#include <handleapi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../state/resultstate.h"
#include "../state/state.h"
#include <Shlwapi.h>
#include <time.h>

static char uuid[40];

BOOL FillUUID(char* username){
    char url[70];
    sprintf_s(url, 70, "https://api.mojang.com/users/profiles/minecraft/%s", username);
    naettOption* option;
    naettReq* req = 
        naettRequestWithOptions(url, 0, NULL);
    naettRes* res = naettMake(req);
    while(!naettComplete(res)){
        Sleep(1);
    }
    if(naettGetStatus(res) < 0){
        return FALSE;
    }
    int bodyLength = 0;
    const char* body = (const char*)naettGetBody(res, &bodyLength);
    printf("%s\n", body);
    cJSON *json = cJSON_Parse(body);
    cJSON *id = cJSON_GetObjectItem(json, "id");
    if(id == NULL) return FALSE;
    sprintf_s(uuid, 40, "%s", id->valuestring);
    cJSON_Delete(json);
    free((void*)body);
    return TRUE;
}

BOOL GetPlayerHead(char* username){
    char url[70];
    sprintf_s(url, 70, "https://www.mc-heads.net/avatar/%s", username);
    naettOption* option;
    naettReq* req = 
        naettRequestWithOptions(url, 0, NULL);
    naettRes* res = naettMake(req);
    while(!naettComplete(res)){
        Sleep(1);
    }
    if(naettGetStatus(res) < 0){
        return FALSE;
    }
    int bodyLength = 0;
    void* body = (void*)naettGetBody(res, &bodyLength);
    printf("head image size is %d\n", bodyLength);
    if(!PathFileExistsW(L"temp\\")){
        CreateDirectoryW(L"temp", NULL);
    }
    HANDLE hFile = CreateFileW(L"temp\\head.png", GENERIC_READ | GENERIC_WRITE, 0, NULL,
                                CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL , NULL);
    if(hFile == INVALID_HANDLE_VALUE){
        return FALSE;
    }
    BOOL result = WriteFile(hFile, body, bodyLength, NULL, NULL);
    if(result == FALSE){
        return FALSE;
    }
    CloseHandle(hFile);
    free((void*)body);
    return TRUE;
}

DWORD WINAPI SearchThreadEntry(LPVOID stuff){
    char* username = (char*)stuff;
    BOOL result = FillUUID(username);
    if(result == FALSE){
        ChangeState(3);
        return -1;
    }
    result = GetPlayerHead(username);
    if(result == FALSE){
        ChangeState(3);
        return -1;
    }
    BeginTier(username);
    char url[70];
    sprintf_s(url, 70, "https://mctiers.com/api/rankings/%s", uuid);
    naettOption* option;
    naettReq* req = 
        naettRequestWithOptions(url, 0, NULL);
    naettRes* res = naettMake(req);
    while(!naettComplete(res)){
        Sleep(1);
    }
    if(naettGetStatus(res) < 0){
        ChangeState(3);
        return -1;
    }
    int bodyLength = 0;
    const char* body = (const char*)naettGetBody(res, &bodyLength);
    printf("%s\n", body);
    cJSON *json = cJSON_Parse(body);
    cJSON *specific = NULL;
    cJSON_ArrayForEach(specific, json){
        Tiers tier;
        char res[32];
        cJSON* time = cJSON_GetObjectItem(specific, "attained");
        struct tm lt;
        time_t timet = (time_t)time->valueint;
        errno_t errres = localtime_s(&lt, &timet);
        if(errres != EINVAL){
            size_t result = _strftime_l(res, 32, "%D", &lt, NULL);
            if(result == 0){
                printf("ERROR, COULDN'T GET TIME!\n");
                sprintf_s(res, 32, "UNKNOWN");
            }
        } else {
            printf("ERROR, COULDN'T GET LOCALTIME!\n");
            sprintf_s(res, 32, "UNKNOWN");
        }
        
        sprintf_s(tier.tierName, 30, "%s (as of %s)", specific->string, res);
        cJSON* curtier = cJSON_GetObjectItem(specific, "tier");
        cJSON* horl = cJSON_GetObjectItem(specific, "pos");
        cJSON* peak_tier = cJSON_GetObjectItem(specific, "peak_tier");
        cJSON* peakhorl = cJSON_GetObjectItem(specific, "peak_pos");
        cJSON* isRetired = cJSON_GetObjectItem(specific, "retired");
        char level = horl->valueint ? 'L' : 'H';
        char peaklevel = peakhorl->valueint ? 'L' : 'H';
        sprintf_s(tier.tier, 5, "%cT%d", level, curtier->valueint);
        char retiredS[12];
        if(isRetired->valueint){
            sprintf_s(retiredS, 12, "retired");
        } else {
            sprintf_s(retiredS, 12, "still in");
        }
        sprintf_s(tier.peakTier, 30, "(peak: %cT%d, %s)", peaklevel, peak_tier->valueint, retiredS);
        PlaceTier(tier);
    }
    cJSON_Delete(json);
    free((void*)body);
    ChangeState(2);
    return 0;
}


VOID BeginSearch(char* username){
    // we don't free the handle from this, which might cause a very minor memleak
    // TODO: find a way to free the handle this function returns so we dont leak memory
    CreateThread(NULL, 0, SearchThreadEntry, (LPVOID)username, 0, 0);
}