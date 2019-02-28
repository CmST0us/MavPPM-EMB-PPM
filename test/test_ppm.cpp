//
// Created by CmST0us on 2019/2/27.
//

#include <iostream>
#include <chrono>
#include <stdio.h>
#include <wiringPi.h>
#include <softServo.h>
#include <softPwm.h>
#include <pthread.h>
#include <sched.h>

#include <linux/rtc.h>
#include <sys/ioctl.h>
#include <sys/time.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>


#define CHANNEL_MAX (2000)
#define CHANNEL_MIN (1000)
#define LOW_TIME (400)
#define PPM_FRAME_TIME (20000)

#define PPM_PIN (7)
#define PPM_CHANNEL_COUNT (8)

#define RTC_PPM_LOW_FREQ (2500)
#define RTC_PPM_HIGH_FREQ(X) (1000000 / (X))

void *testPPM(void *dummy) {
    struct sched_param param ;

    param.sched_priority = sched_get_priority_max (SCHED_RR) ;
    pthread_setschedparam (pthread_self (), SCHED_RR, &param) ;

    struct sched_param sched ;
    memset (&sched, 0, sizeof(sched)) ;

    sched.sched_priority = sched_get_priority_max (SCHED_RR) ;
    sched_setscheduler (0, SCHED_RR, &sched) ;

    pinMode(PPM_PIN, OUTPUT);
    digitalWrite(PPM_PIN, HIGH);
    // channel
    int channel[PPM_CHANNEL_COUNT] = {
            1500,   // C1
            1500,   // C2
            1500,   // C3
            1500,   // C4

            1500,   // C5
            1500,   // C6
            1500,   // C7
            1500,   // C8
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
    return NULL;
}

void testThreadServo() {
    pinMode(PPM_PIN, OUTPUT);
    softServoSetup(PPM_PIN, -1, -1, -1, -1, -1, -1, -1);
    softServoWrite(PPM_PIN, 1600);

    sleep(10000);
}

void testThreadPWM() {
    pinMode(PPM_PIN, SOFT_PWM_OUTPUT);
    softPwmCreate(PPM_PIN, 0, 200);
    softPwmWrite(PPM_PIN, 15);
    sleep(10000);
};


void testThreadPPM() {
    pthread_t thread;
    pthread_create(&thread, NULL, testPPM, NULL);
    pthread_join(thread, NULL);
}

void testPWNChannel() {
    int channelPin[PPM_CHANNEL_COUNT] = {
        7,
        0,
        2,
        3,
        12,
        13,
        14
    };

    for (int i = 0; i < PPM_CHANNEL_COUNT; ++i) {
        pinMode(channelPin[i], SOFT_PWM_OUTPUT);
//        softPwmCreate()
    }
}

inline void rtcSleep(int fd, int freq) {
    if(ioctl(fd, RTC_IRQP_SET, freq) < 0)
    {
        perror("ioctl(RTC_IRQP_SET)");
        close(fd);
        exit(errno);
    }
    unsigned long data = 0;
    if(read(fd, &data, sizeof(unsigned long)) < 0)
    {
        perror("read");
        close(fd);
        exit(errno);
    }
}

void RTCPPM() {
    struct sched_param param ;

    param.sched_priority = sched_get_priority_max (SCHED_RR) ;
    sched_setscheduler (0, SCHED_RR, &param) ;
    pthread_setschedparam (pthread_self (), SCHED_RR, &param) ;

    int channel[PPM_CHANNEL_COUNT] = {
            1500,   // C1
            1500,   // C2
            1500,   // C3
            1500,   // C4

            1500,   // C5
            1000,   // C6
            1000,   // C7
            1000,   // C8
    };

    bool state = false;
    unsigned long i = 0;

    int retval = 0;
    int fd = open ("/dev/rtc", O_RDONLY);

    if(fd < 0)
    {
        perror("open");
        exit(errno);
    }

    /* Enable periodic interrupts */
    if(ioctl(fd, RTC_PIE_ON, 0) < 0)
    {
        perror("ioctl(RTC_PIE_ON)");
        close(fd);
        exit(errno);
    }

    digitalWrite(PPM_PIN, HIGH);
    for(i = 0; 1; i++)
    {
        int channelTime = 0;
        for (int j = 0; j < PPM_CHANNEL_COUNT; ++j) {
            // first down edge
            digitalWrite(PPM_PIN, LOW);
            rtcSleep(fd, RTC_PPM_HIGH_FREQ(LOW_TIME));
            channelTime += LOW_TIME;

            digitalWrite(PPM_PIN, HIGH);
            int highTime = channel[j] - LOW_TIME;
            rtcSleep(fd, RTC_PPM_HIGH_FREQ(highTime));
            channelTime += highTime;
        }
        digitalWrite(PPM_PIN, LOW);
        rtcSleep(fd, RTC_PPM_LOW_FREQ);
        digitalWrite(PPM_PIN, HIGH);
        rtcSleep(fd, RTC_PPM_HIGH_FREQ(PPM_FRAME_TIME - channelTime));
    }
    /* Disable periodic interrupts */
    ioctl(fd, RTC_PIE_OFF, 0);
    close(fd);
}

int main(int argc, char *argv[]) {
    wiringPiSetup();
//    testThreadPPM();
//    testThreadPPM();
    testThreadServo();
//    testPWNChannel();
//    RTCPPM();
    return 0;
}