/*
** EPITECH PROJECT, 2026
** Cartridge
** File description:
** sound_manager
*/

#ifndef SOUND_MANAGER_H
    #define SOUND_MANAGER_H

    #include <stdint.h>

    #define TRUE 1
    #define FALSE 0

    #define NB_CHANNEL 4

    typedef enum {
        SND_PLAYING,
        SND_RESTING,
        SND_NEXT_NOTE,
        SND_OFF
    } snd_state_t;

    typedef struct {
        const uint8_t *music;
        uint8_t idx;
        uint8_t channel;
        snd_state_t state;
        uint8_t play;
        uint8_t rest;
        uint8_t loop;
        uint8_t volume;
    } sound_t;

    void sound_init(void);
    void sound_start(sound_t *snd, uint8_t channel,
        const uint8_t *music, uint8_t loop, uint8_t volume);
    void sound_update(sound_t *snd);
    void reset_sound(sound_t *sound);
    void sound_channel1(
        uint8_t b0, uint8_t b1, uint8_t b2, uint8_t b3, uint8_t b4);
    void sound_channel2(uint8_t b1, uint8_t b2, uint8_t b3, uint8_t b4);
    void sound_channel3(
        uint8_t b0, uint8_t b1, uint8_t b2, uint8_t b3, uint8_t b4);
    void sound_channel4(uint8_t b1, uint8_t b2, uint8_t b3, uint8_t b4);
    void mute_channel(uint8_t channel);

#endif