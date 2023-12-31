#ifndef _SOUND_H_
#define _SOUND_H_
typedef struct FMODSOUND
{
    FMOD_SOUND *sound;
    FMOD_CHANNEL *channel;
} FMODSOUND;
FMODSOUND *InitSound();
void deleteSound(FMODSOUND *s);
class FMODMUSIC
{
public:
    FMOD_SYSTEM *system;
    void init();
    void loadMusic(FMODSOUND *s, const char *bgm);
    void playMusic(FMODSOUND *s, bool share_flag = false);
    void setSoundMode(FMOD_MODE mode, FMODSOUND *s);
    void set3DPosition(FMODSOUND *s, float x, float y, float z);
    void updateSystem();
    void systemFree();

private:
    FMOD_CHANNEL *sharedChannel;
};
#endif