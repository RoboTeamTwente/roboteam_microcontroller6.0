#ifndef INC_MCP_PAGE_H_
#define INC_MCP_PAGE_H_

#include "pages.h"
#include "robot.h"

void mcp_page_init(page_struct *parent);
void mcp_page_update(page_struct *page);
void mcp_page_check_alive();

#endif /* INC_MCP_PAGE_H_ */