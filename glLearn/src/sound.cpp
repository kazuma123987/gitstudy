#include "tool.h"
#include "sound.h"
FMODSOUND *InitSound()
{
    FMODSOUND *s = (FMODSOUND *)malloc(sizeof(FMODSOUND));
    s->channel = NULL;
    s->sound = NULL;
    return s;
}
void deleteSound(FMODSOUND *s)
{
    FMOD_Sound_Release(s->sound);
    free(s);
}
void FMODMUSIC::init()
{
    FMOD_RESULT result = FMOD_System_Create(&system, FMOD_VERSION);
    if (result != FMOD_OK)
    {
        fputs("\nfailed to create system", stderr);
        return;
    }
    result = FMOD_System_Init(system, 32, FMOD_INIT_NORMAL, NULL);
    if (result != FMOD_OK)
    {
        fputs("\nfailed to init system", stderr);
        FMOD_System_Release(system);
        return;
    }
}
void FMODMUSIC::loadMusic(FMODSOUND *s, const char *bgm)
{
    FMOD_RESULT result = FMOD_System_CreateSound(system, bgm, FMOD_DEFAULT, NULL, &s->sound);
    if (result != FMOD_OK)
        fputs("\nfailed to load the music", stderr);
}
void FMODMUSIC::playMusic(FMODSOUND *s, bool share_flag)
{

    FMOD_RESULT result;
    static int isplaying;
    FMOD_Channel_IsPlaying(s->channel, &isplaying);
    if (!isplaying)
    {
        result = FMOD_System_PlaySound(system, s->sound, NULL, FALSE, &s->channel);
        if (result != FMOD_OK)
            fputs("\nfailed to play music", stderr);
    }
    else if (share_flag)
    {
        result = FMOD_System_PlaySound(system, s->sound, NULL, FALSE, &sharedChannel);
        if (result != FMOD_OK)
            fputs("\nfailed to play music", stderr);
    }
}
void FMODMUSIC::setSoundMode(FMOD_MODE mode, FMODSOUND *s)
{
    FMOD_Sound_SetMode(s->sound, mode);
}
void FMODMUSIC::set3DPosition(FMODSOUND *s, float x, float y, float z)
{
    if (s != NULL)
    {
        FMOD_VECTOR pos;
        pos.x = x;
        pos.y = y;
        pos.z = z;
        FMOD_Channel_Set3DAttributes(s->channel, &pos, NULL);
    }
}
void FMODMUSIC::updateSystem()
{
    FMOD_System_Update(system);
}
void FMODMUSIC::systemFree()
{
    FMOD_System_Release(system);
}