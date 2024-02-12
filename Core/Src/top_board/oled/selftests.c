#include "selftests.h"

void run_test(page_struct *page) {
    switch (page->id)    {
    case 111:
        buzzer_Play_RickRoll();
        HAL_Delay(2000);
        break;
    
    default:
        break;
    }   
}