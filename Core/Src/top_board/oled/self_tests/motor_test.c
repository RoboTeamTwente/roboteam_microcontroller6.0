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
    page_set_page_name("Motor Tests!", &motor_page);
    motor_page.is_menu = true;
    add_child_to_parent(&motor_page);
    motor_test_initChildren(&motor_page);
}

void motor_test_initChildren(page_struct *parent){

    pages_set_default_values(&step_one, parent);
    step_one.id = 1112;
    page_set_page_name("0%", &step_one);
    step_one.is_test = BLOCKING_TEST;
    add_child_to_parent(&step_one);

    pages_set_default_values(&step_two, parent);
    step_two.id = 1113;
    page_set_page_name("20%", &step_two);
    step_two.is_test = BLOCKING_TEST;
    add_child_to_parent(&step_two);

    pages_set_default_values(&step_three, parent);
    step_three.id = 1114;
    page_set_page_name("40%", &step_three);
    step_three.is_test = BLOCKING_TEST;
    add_child_to_parent(&step_three);

    pages_set_default_values(&step_four, parent);
    step_four.id = 1115;
    page_set_page_name("60%", &step_four);
    step_four.is_test = BLOCKING_TEST;
    add_child_to_parent(&step_four);

    pages_set_default_values(&step_five, parent);
    step_five.id = 1116;
    page_set_page_name("80%", &step_five);
    step_five.is_test = BLOCKING_TEST;
    add_child_to_parent(&step_five);

    pages_set_default_values(&step_six, parent);
    step_six.id = 1117;
    page_set_page_name("100%", &step_six);
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

