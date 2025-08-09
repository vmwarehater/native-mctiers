#include "search.h"
#include "../extern/naett/naett.h"
#include "../extern/cjson/cjson.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../state/resultstate.h"
#include "../state/state.h"

static char uuid[40];

BOOL FillUUID(char* username){
    char url[70];
    sprintf_s(url, 70, "https://api.mojang.com/users/profiles/minecraft/%s", username);
    naettOption* option;
    naettReq* req = 
        naettRequestWithOptions(url, 0, NULL);
    naettRes* res = naettMake(req);
    while(!naettComplete(res)){
        #ifdef _WIN32
        _sleep(100);
        #elif 
        #include <unistd.h>
        sleep(1);
        #endif
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

DWORD WINAPI SearchThreadEntry(LPVOID stuff){
    char* username = (char*)stuff;
    BOOL result = FillUUID(username);
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
        #ifdef _WIN32
        _sleep(100);
        #elif 
        #include <unistd.h>
        sleep(1);
        #endif
    }
    if(naettGetStatus(res) < 0){
        ChangeState(3);
        return -1;
    }
    int bodyLength = 0;
    const char* body = (const char*)naettGetBody(res, &bodyLength);
    printf("%s\n", body);
    printf("?\n");
    cJSON *json = cJSON_Parse(body);
    cJSON *specific = NULL;
    printf("?\n");
    cJSON_ArrayForEach(specific, json){
        Tiers tier;
        sprintf_s(tier.tierName, 10, "%s", specific->string);
        cJSON* curtier = cJSON_GetObjectItem(specific, "tier");
        cJSON* horl = cJSON_GetObjectItem(specific, "pos");
        char level = horl->valueint ? 'H' : 'L';
        sprintf_s(tier.tier, 5, "%cT%d", level, curtier->valueint);
        PlaceTier(tier);
    }
    cJSON_Delete(json);
    free((void*)body);
    ChangeState(2);
    return 0;
}


VOID BeginSearch(char* username){
    CreateThread(NULL, 0, SearchThreadEntry, (LPVOID)username, 0, 0);
}