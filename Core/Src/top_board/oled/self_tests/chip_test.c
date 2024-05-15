#include "chip_test.h"
#include "robot.h"

struct page_struct chip_three_five_ms;
struct page_struct chip_four_five_ms;
struct page_struct chip_five_five_ms;
struct page_struct chip_six_five_ms;


void chip_test_initChildren(page_struct *parent) {
    pages_set_default_values(&chip_three_five_ms);
    chip_three_five_ms.id = 1321;
    strcpy(chip_three_five_ms.page_name, "3.5 m/s");
    chip_three_five_ms.parent = parent;
    chip_three_five_ms.is_test = BLOCKING_TEST;
    chip_three_five_ms.has_variables = false;
    add_child_to_parent(&chip_three_five_ms);

    pages_set_default_values(&chip_four_five_ms);
    chip_four_five_ms.id = 1322;
    strcpy(chip_four_five_ms.page_name, "4.5 m/s");
    chip_four_five_ms.parent = parent;
    chip_four_five_ms.is_test = BLOCKING_TEST;
    chip_four_five_ms.has_variables = false;
    add_child_to_parent(&chip_four_five_ms);

    pages_set_default_values(&chip_five_five_ms);
    chip_five_five_ms.id = 1323;
    strcpy(chip_five_five_ms.page_name, "5.5 m/s");
    chip_five_five_ms.parent = parent;
    chip_five_five_ms.is_test = BLOCKING_TEST;
    chip_five_five_ms.has_variables = false;
    add_child_to_parent(&chip_five_five_ms);

    pages_set_default_values(&chip_six_five_ms);
    chip_six_five_ms.id = 1324;
    strcpy(chip_six_five_ms.page_name, "6.5 m/s");
    chip_six_five_ms.parent = parent;
    chip_six_five_ms.is_test = BLOCKING_TEST;
    chip_six_five_ms.has_variables = false;
    add_child_to_parent(&chip_six_five_ms);
}

void chip_shoot_run(float speed){
    start_of_test(); // Display that we are running a test
    MCP_Chip chip = {0};
    MCP_ChipPayload payload = {0};
    chip.shootPower = speed;
    encodeMCP_Chip(&payload, &chip);
    MCP_Send_Message(&hcan1, &payload, chipHeader, MCP_KICKER_BOARD);
    HAL_Delay(500);
    end_of_test();

}
