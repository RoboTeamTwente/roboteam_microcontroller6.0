#include "mcp_page.h"

struct page_struct mcp_page;
static uint32_t time_last_change = 0;
char board_names[6][MAX_STRING_LENGTH];
int n_not_alive = 0;
int mcp_state = 0;

void mcp_page_init(page_struct *parent) {
        pages_set_default_values(&mcp_page);
    mcp_page.id = 222;
    strcpy(mcp_page.page_name, "MCP Alive");
    mcp_page.parent = parent;
    mcp_page.has_variables = true;
    add_child_to_parent(&mcp_page);
}

void mcp_page_update(page_struct *page) {
    if (n_not_alive == 0){
        strcpy(page->line0, "All boards");
        strcpy(page->line1, "are alive");
        strcpy(page->line2, "and functioning");
    } else {
        uint32_t current_time = HAL_GetTick();
        strcpy(page->line0, "No signal from");
        strcpy(page->line1, "these board(s): ");
        if (n_not_alive == 1) {
            strcpy(page->line2, board_names[0]);
        } else if (n_not_alive == 2) {
            strcpy(page->line2, board_names[0]);
            strcpy(page->line3, board_names[1]);
        } else {
            //change what 2 boards are displayed every second
            if (current_time > time_last_change + 1000) {
                time_last_change = current_time;
                mcp_state++;
            }
            strcpy(page->line2, board_names[mcp_state % n_not_alive]);
            strcpy(page->line3, board_names[(mcp_state + 1) % n_not_alive]);
        }

    }
    
}

void mcp_page_check_alive() {
    if (!kickerBoard_alive) {
        strcpy(board_names[n_not_alive], "Kicker board");
        n_not_alive++;
    }
    if (!powerBoard_alive) {
        strcpy(board_names[n_not_alive], "Power board");
        n_not_alive++;
    }
    if (!dribblerBoard_alive) {
        strcpy(board_names[n_not_alive], "Dribbler board");
        n_not_alive++;
    }
}