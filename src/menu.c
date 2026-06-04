/**
 * menu.c: Ascii based menu system. 
 * 
 * Menu items are selected by sending a character followed by an optional value. 
 * The menu system parses the input and calls a user-defined action handler with 
 * the corresponding menu item ID and value.
 * 
 * Tom Clayton 2025
 * 
 */

#include "menu.h"
#include "readline.h"
#include <stdlib.h> 
#include <stdbool.h>

#define BUFFER_SIZE 32

static const struct menu_item *menu_items;
static size_t n_items;
static void (*action_handler)(uint8_t id, uint64_t value) = NULL;
static bool invalid = false;
static char buffer[BUFFER_SIZE];
static int buffer_pos = 0;

/*
 * Parse a command string and execute the corresponding menu action if valid.
 *
 * @param command: A null-terminated string containing the command to parse.
 *                  The first character is the menu item character, followed by an optional numeric value.
 * 
 * @return 0 on success, -1 if the command was invalid or not found.
 */
int parse(const char *command);


void menu_init(const struct menu_item *items, size_t length, void (*handler)(uint8_t id, uint64_t value))
{
    menu_items = items;
    n_items = length;
    action_handler = handler;
}

void menu_input(const void *data, size_t length)
{
    const char *bytes = (const char *)data;

    for (size_t i=0; i<length; i++) {
        switch (bytes[i]){
            case '\r':
                break;
            case '\n': 
                buffer[buffer_pos] = '\0';
                buffer_pos = 0;
                if (invalid){
                    invalid = false;
                } else {
                    parse(buffer);
                }
                break;
            default:
                if (!invalid && buffer_pos < BUFFER_SIZE-1){
                    buffer[buffer_pos++] = bytes[i];
                } else {
                    invalid = true;
                }
        }
    }
}

int parse(const char *command)
{
    if (command[0] == '\0') {
        return -1;
    }

    char key = command[0];
    uint64_t value = 0;

    if (command[1] != '\0') {
        char *endptr = NULL;
        long long parsed = strtoll(&command[1], &endptr, 10);
        if (*endptr == &command[1] || *endptr != '\0' || parsed < 0 || parsed > UINT64_MAX) {
            return -1;
        } 
        value = (uint64_t)parsed;
    }
    
    for (size_t i=0; i<n_items; i++) {
        if (menu_items[i].character == key) {
            if (action_handler) {
                action_handler(menu_items[i].id, value);
            }
            return 0;
        }
    }

    return -1;
}

