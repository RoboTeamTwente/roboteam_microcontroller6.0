#include "motor_test.h"

struct page_struct motor_page;
struct page_struct step_one;
struct page_struct step_two;
struct page_struct step_three;
struct page_struct step_four;
struct page_struct step_five;
struct page_struct step_six;

void motor_test_initChildren(page_struct *parent);

void motor_test_init(page_struct *parent){

    pages_set_default_values(&motor_page, parent);
    motor_page.id = 1111;
    strcpy(motor_page.page_name, "Motor Tests!");
    motor_page.is_menu = true;
    add_child_to_parent(&motor_page);
    motor_test_initChildren(&motor_page);
}

void motor_test_initChildren(page_struct *parent){

    pages_set_default_values(&step_one, parent);
    step_one.id = 1112;
    strcpy(step_one.page_name, "0.0");
    step_one.is_test = BLOCKING_TEST;
    add_child_to_parent(&step_one);

    pages_set_default_values(&step_two, parent);
    step_two.id = 1113;
    strcpy(step_two.page_name, "0.2");
    step_two.is_test = BLOCKING_TEST;
    add_child_to_parent(&step_two);

    pages_set_default_values(&step_three, parent);
    step_three.id = 1114;
    strcpy(step_three.page_name, "0.4");
    step_three.is_test = BLOCKING_TEST;
    add_child_to_parent(&step_three);

    pages_set_default_values(&step_four, parent);
    step_four.id = 1115;
    strcpy(step_four.page_name, "0.6");
    step_four.is_test = BLOCKING_TEST;
    add_child_to_parent(&step_four);

    pages_set_default_values(&step_five, parent);
    step_five.id = 1116;
    strcpy(step_five.page_name, "0.8");
    step_five.is_test = BLOCKING_TEST;
    add_child_to_parent(&step_five);

    pages_set_default_values(&step_six, parent);
    step_six.id = 1117;
    strcpy(step_six.page_name, "1.0");
    step_six.is_test = BLOCKING_TEST;
    add_child_to_parent(&step_six);


}


void speedMotor_OLED(float per){
    start_of_test();
    wheels_Unbrake();

    wheels_SetSpeed_PWM(RF, per);
    wheels_SetSpeed_PWM(RB, per);
    wheels_SetSpeed_PWM(LB, per);
    wheels_SetSpeed_PWM(LF, per);

    HAL_Delay(500);
    end_of_test();

}

