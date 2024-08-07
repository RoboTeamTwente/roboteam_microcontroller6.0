#include "rem_page.h"

//linked list
typedef struct rem_node {
    uint64_t timestamp;
    struct rem_node * next;
} rem_node_t;

page_struct rem_page;
rem_node_t * head = NULL;
uint64_t lastAddedValue = 0;
uint8_t rem_node_size = 0;

void rem_page_remove_timestamps();

// Implenentations

void rem_page_init(page_struct *parent) {
    pages_set_default_values(&rem_page, parent);
    rem_page.id = 223;
    page_set_page_name("REM info", &rem_page);
    rem_page.has_variables = true;
    add_child_to_parent(&rem_page);
}

void rem_page_update(page_struct *page) {
    rem_page_remove_timestamps();
    page_put_text_in_line(&page, "Incoming", 0);
    char temp[MAX_STRING_LENGTH];
    sprintf(temp, "REM_Commands: %d", rem_node_size);
    page_put_text_in_line(&page, temp, 1);
}

void rem_page_add_timestamp(uint64_t recieved_time) {
    if (recieved_time == lastAddedValue) return;
    if (head == NULL) {
        head = (rem_node_t *) malloc(sizeof(rem_node_t));
        head->timestamp = recieved_time;
        head->next = NULL;
        rem_node_size = 1;
        lastAddedValue = recieved_time;
    } else if (rem_node_size < 100) { // prevent overflow

        // add new node at end of linked list
        rem_node_t * current = head;
        while(current->next != NULL) {
            current = current->next;
        }

        current->next = (rem_node_t *) malloc(sizeof(rem_node_t));
        current->next->timestamp = recieved_time;
        current->next->next = NULL;

        rem_node_size += 1;
        lastAddedValue = recieved_time;
    }
}

void rem_page_remove_timestamps() {
    while (head != NULL && head->timestamp + 100 < unix_timestamp) {
        rem_node_t * next_node = head->next;
        free(head);
        head = next_node;

        rem_node_size -= 1;
    }
}