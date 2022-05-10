#ifndef PARAMS_h
#define PARAMS_h

#define WIFI_LED 2 // D4 (built in LED)
#define WIFI_MODE_SELECTOR 9 // SD2
#define COMM_LED 16 // D0 (built in LED)
#define L_MOTOR_SPEED 5 // D1
#define L_MOTOR_FWD 4 // D2
#define L_MOTOR_BWD 0 // D3
#define R_MOTOR_SPEED 13 // D7
#define R_MOTOR_FWD 14 // D5
#define R_MOTOR_BWD 12 // D6

#define PWM_FREQUENCY 1000 // Hz
#define PWM_RANGE 100
#define PWM_DUTY_CYCLE_PER_LEVEL 10 // % per level

#define SPEED_CHANGE_STEP 1 // % per cycle  !!! USE ONLY 1, 2, 5 or 10 to avoid oscillation near zero !!!
#define SPEED_CHANGE_FREQUENCY 250 // Hz

#define SERVER_PORT 80

#define REQUEST_TIMEOUT 2000 // ms
#define COMM_LED_BLINK_DURATION 50 // ms

#endif
