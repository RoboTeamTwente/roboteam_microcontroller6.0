#include "info_menu.h"

struct page_struct general_info;
struct page_struct time_page;
struct page_struct mcp_page;
struct page_struct encoder_values;

/**
 * @brief initialize the pages that are the children of info menu
 * @note constraint for children of info menu: 20 < id < 30 
*/
void info_menu_initChildren(page_struct *parent) {
    pages_set_default_values(&general_info);
    general_info.id = 21;
    strcpy(general_info.page_name, "General");
    general_info.parent = parent;
    add_child_to_parent(&general_info);
    general_info_init(&general_info);

    pages_set_default_values(&time_page);
    time_page.id = 22;
    strcpy(time_page.page_name, "Robot time");
    time_page.parent = parent;
    time_page.has_variables = true;
    add_child_to_parent(&time_page);

    pages_set_default_values(&mcp_page);
    mcp_page.id = 23;
    strcpy(mcp_page.page_name, "MCP Alive");
    mcp_page.parent = parent;
    mcp_page.has_variables = true;
    add_child_to_parent(&mcp_page);

    pages_set_default_values(&encoder_values);
    encoder_values.id = 24;
    strcpy(encoder_values.page_name, "Encoder");
    strcpy(encoder_values.line0, "LF:0");
    strcpy(encoder_values.line1, "RF:0");
    strcpy(encoder_values.line2, "LB:0");
    strcpy(encoder_values.line3, "RB:0");
    encoder_values.parent = parent;
    encoder_values.has_variables = true;
    add_child_to_parent(&encoder_values);
}