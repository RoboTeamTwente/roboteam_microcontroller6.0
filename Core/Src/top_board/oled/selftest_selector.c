#include "selftest_selector.h"

void run_test(page_struct *page) {
    if (test_is_finished) {
        return;
    }

    switch (page->id) {
        case 111:
            buzzer_test_run();
            break;
        case 1122:
            wheel_twitch_run();
            break;
        case 1111:
            motor_test_initChildren(&page);
            break;
        case 1112:
            speedMotor_OLED(0.0f);
            break;
        case 1113:
            speedMotor_OLED(0.2f);
            break;
        case 1114:
            speedMotor_OLED(0.4f);
            break;
        case 1115:
            speedMotor_OLED(0.6f);
            break;
        case 1116:
            speedMotor_OLED(0.8f);
            break;
        case 1117:
            speedMotor_OLED(1.0f);
            break;
        case 1511:
            system_test_run();
            break;
        case 1311: 
            kicker_shoot_run(1.5f);
            break;
        case 1312: 
            kicker_shoot_run(3.5f);
            break;
        case 1313: 
            kicker_shoot_run(4.5f);
            break;
        case 1314: 
            kicker_shoot_run(6.5f);
            break;
        case 1315:
            kicker_discharge();
            break;
        case 1316:
            kicker_changeState(true);
            break;
        case 31:
            drain_battery_run(18.0f);
            break;
        case 32:
            drain_battery_run(23.0f);
            break;
        case 33:
            drain_battery_run(23.5f);
            break;
        case 34:
            drain_battery_run(24.0f);
            break;
        case 35:
            drain_battery_run(24.5f);
            break;
        default:
            break;
    }   
}