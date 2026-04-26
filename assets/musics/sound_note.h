/*
** EPITECH PROJECT, 2026
** Cartridge
** File description:
** sound_note
*/

#ifndef SOUNDNOTE_H
    #define SOUNDNOTE_H

    #include <stdint.h>

    #define SND_FRAMES_NONE 0
    #define SND_FRAMES_THIRTYSEC 2
    #define SND_FRAMES_SIXTEENTH 4
    #define SND_FRAMES_EIGHT 8
    #define SND_FRAMES_QUARTER 16
    #define SND_FRAMES_HALF 32
    #define SND_FRAMES_WHOLE 64

    enum {
        NONE = 0,
        THIRTYSEC,
        SIXTEENTH,
        EIGHT,
        QUARTER,
        HALF,
        WHOLE,
    };

    #define PN NONE
    #define PT THIRTYSEC
    #define PS SIXTEENTH
    #define PE EIGHT
    #define PQ QUARTER
    #define PH HALF
    #define PW WHOLE

    #define RN NONE
    #define RT THIRTYSEC
    #define RS SIXTEENTH
    #define RE EIGHT
    #define RQ QUARTER
    #define RH HALF
    #define RW WHOLE

    enum {
        Silent = 0,
        C2, Cs2, D2, Ds2, E2, F2, Fs2, G2, Gs2, A2, As2, B2,
        C3, Cs3, D3, Ds3, E3, F3, Fs3, G3, Gs3, A3, As3, B3,
        C4, Cs4, D4, Ds4, E4, F4, Fs4, G4, Gs4, A4, As4, B4,
        C5, Cs5, D5, Ds5, E5, F5, Fs5, G5, Gs5, A5, As5, B5,
        C6, Cs6, D6, Ds6, E6, F6, Fs6, G6, Gs6, A6, As6, B6,
        C7, Cs7, D7, Ds7, E7, F7, Fs7, G7, Gs7, A7, As7, B7,
        END
    };

    extern uint16_t note_freq[];
    extern uint8_t duration_frames[];

#endif
