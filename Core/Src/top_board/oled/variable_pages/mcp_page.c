#include "mcp_page.h"

struct page_struct mcp_page;
static uint32_t time_last_change = 0;
char board_names[6][MAX_STRING_LENGTH];
int n_not_alive = 0;
int mcp_state = 0;

void mcp_page_init(page_struct *parent) {
    pages_set_default_values(&mcp_page, parent);
    mcp_page.id = 222;
    page_set_page_name("MCP Alive", &mcp_page);
    mcp_page.has_variables = true;
    add_child_to_parent(&mcp_page);
}

void mcp_page_update(page_struct *page) {
    if (n_not_alive == 0){
        page_put_text_in_line(&page, "All boards", 0);
        page_put_text_in_line(&page, "are alive", 1);
        page_put_text_in_line(&page, "and functioning", 2);
    } else {
        uint32_t current_time = HAL_GetTick();
        page_put_text_in_line(&page, "No signal from", 0);
        page_put_text_in_line(&page, "these board(s): ", 1);
        if (n_not_alive == 1) {
            page_put_text_in_line(&page, board_names[0], 2);
        } else if (n_not_alive == 2) {
            page_put_text_in_line(&page, board_names[0], 2);
            page_put_text_in_line(&page, board_names[1], 3);
        } else {
            //change what 2 boards are displayed every second
            if (current_time > time_last_change + 1000) {
                time_last_change = current_time;
                mcp_state++;
            }
            page_put_text_in_line(&page, board_names[mcp_state % n_not_alive], 2);
            page_put_text_in_line(&page, board_names[(mcp_state + 1) % n_not_alive], 3);
        }

    }
    
}

void mcp_page_check_alive() {
    if (!flag_KickerBoard_alive) {
        strcpy(board_names[n_not_alive], "Kicker board");
        n_not_alive++;
    }
    if (!flag_PowerBoard_alive) {
        strcpy(board_names[n_not_alive], "Power board");
        n_not_alive++;
    }
    if (!flag_DribblerBoard_alive) {
        strcpy(board_names[n_not_alive], "Dribbler board");
        n_not_alive++;
    }
}