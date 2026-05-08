#include <gb/gb.h>
#include "sound_manager.h"
#include "sound_note.h"

void sound_init(void)
{
    NR52_REG = 0x80;
    NR50_REG = 0x77;
    NR51_REG = 0xFF;
}

void sound_start(sound_t *snd, uint8_t channel,
    const uint8_t *music, uint8_t loop, uint8_t volume)
{
    snd->music = music;
    snd->idx = 0;
    snd->channel = channel;
    snd->state = SND_NEXT_NOTE;
    snd->play = 0;
    snd->rest = 0;
    snd->loop = loop;
    snd->volume = volume;
}

static void play_note(uint8_t channel, uint8_t note_id, uint8_t volume)
{
    uint16_t freq = note_freq[note_id];
    uint8_t n3 = (uint8_t)(freq & 0xFF);
    uint8_t n4 = (uint8_t)(freq >> 8) | 0x80;
    uint8_t env = ((volume >> 4) & 0x0F) << 4;
    uint8_t v2 = (volume >> 6) & 0x03;
    uint8_t wave_vol = v2 << 5;

    if (v2 != 0)
        wave_vol = (4 - v2) << 5;
    if (channel == 1)
        sound_channel1(0x80, 0x80, env, n3, n4);
    if (channel == 2)
        sound_channel2(0x80, env, n3, n4);
    if (channel == 3)
        sound_channel3(0x80, 0x0, wave_vol, n3, n4);
}


void mute_channel(uint8_t channel)
{
    if (channel == 1)
        NR12_REG = 0x00;
    if (channel == 2)
        NR22_REG = 0x00;
    if (channel == 3)
        NR32_REG = 0x00;
    if (channel == 4)
        NR42_REG = 0x00;
}

static void sound_playing(sound_t *sound)
{
    sound->play--;
    if (sound->play == 0) {
        if (sound->rest == 0) {
            sound->state = SND_NEXT_NOTE;
            return;
        }
        mute_channel(sound->channel);
        sound->state = SND_RESTING;
    }
}

static void sound_resting(sound_t *sound)
{
    sound->rest--;
    if (sound->rest == 0)
        sound->state = SND_NEXT_NOTE;
}

static void sound_play(sound_t *sound)
{
    uint8_t play = sound->music[sound->idx];
    uint8_t rest = 0;
    uint8_t note = 0;

    if (play == END) {
        if (sound->loop) {
            reset_sound(sound);
            play = sound->music[sound->idx];
        } else {
            sound->state = SND_OFF;
            mute_channel(sound->channel);
            return;
        }
    }
    sound->idx++;
    rest = sound->music[sound->idx++];
    note = sound->music[sound->idx++];
    sound->play = duration_frames[play];
    sound->rest = duration_frames[rest];
    if (note != Silent)
        play_note(sound->channel, note, sound->volume);
    sound->state = SND_PLAYING;
}

void sound_update(sound_t *sound)
{
    if (sound->music == NULL || sound->state == SND_OFF)
        return;
    if (sound->state == SND_PLAYING)
        return sound_playing(sound);
    if (sound->state == SND_RESTING)
        return sound_resting(sound);
    sound_play(sound);
}

void reset_sound(sound_t *sound)
{
    sound->idx = 0;
    sound->state = SND_NEXT_NOTE;
    sound->play = 0;
}

void sound_channel1(uint8_t b0, uint8_t b1, uint8_t b2, uint8_t b3, uint8_t b4)
{
    NR10_REG=b0;
    NR11_REG=b1;
    NR12_REG=b2;
    NR13_REG=b3;
    NR14_REG=b4;
}

void sound_channel2(uint8_t b1, uint8_t b2, uint8_t b3, uint8_t b4)
{
    NR21_REG=b1;
    NR22_REG=b2;
    NR23_REG=b3;
    NR24_REG=b4;
}

void sound_channel3(uint8_t b0, uint8_t b1, uint8_t b2, uint8_t b3, uint8_t b4)
{
    NR30_REG=b0;
    NR31_REG=b1;
    NR32_REG=b2;
    NR33_REG=b3;
    NR34_REG=b4;
}

void sound_channel4(uint8_t b1, uint8_t b2, uint8_t b3, uint8_t b4)
{
    NR41_REG=b1;
    NR42_REG=b2;
    NR43_REG=b3;
    NR44_REG=b4;
}