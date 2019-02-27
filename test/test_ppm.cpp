//
// Created by CmST0us on 2019/2/27.
//

#include <iostream>
#include <chrono>
#include <stdio.h>
#include <wiringPi.h>

#define CHANNEL_MAX (2000)
#define CHANNEL_MIN (1000)
#define LOW_TIME (300)
#define PPM_FRAME_TIME (20000)

#define PPM_PIN (7)
#define PPM_CHANNEL_COUNT (9)

int main(int argc, char *argv[]) {

    wiringPiSetup();
    pinMode(PPM_PIN, OUTPUT);
    digitalWrite(PPM_PIN, HIGH);
    // channel
    int channel[PPM_CHANNEL_COUNT] = {
            1000,   // C1
            1000,   // C2
            1000,   // C3
            1000,   // C4

            1000,   // C5
            1000,   // C6
            1000,   // C7
            1000,   // C8
            1000,   // SYNC
    };

    while (1) {
        int ppmUsTime = 0;
        for (int i = 0; i < PPM_CHANNEL_COUNT; ++i) {
            digitalWrite(PPM_PIN, LOW);
            delayMicroseconds(LOW_TIME);
            ppmUsTime += LOW_TIME;
            digitalWrite(PPM_PIN, HIGH);
            int highUsTime = channel[i] - LOW_TIME;
            delayMicroseconds(highUsTime);
            ppmUsTime += highUsTime;
        }
        delayMicroseconds(PPM_FRAME_TIME - ppmUsTime);
    }

    return 0;
}