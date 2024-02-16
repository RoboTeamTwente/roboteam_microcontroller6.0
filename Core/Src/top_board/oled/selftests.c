#include "selftests.h"

void run_test(page_struct *page) {
    switch (page->id)    {
    case 111:
        buzzer_test_run();
        break;
    
    default:
        break;
    }   
}