/*
 * menu.h: Ascii based menu system. 
 * 
 * Menu items are selected by sending a character followed by an optional integer value. 
 * The menu system parses the input and calls a user-defined action handler with 
 * the corresponding menu item ID and value.
 * 
 * Tom Clayton 2025
 * 
 */


#ifndef MENU_H
#define MENU_H

#include <stdint.h>
#include <stddef.h>

/*
 * menu_item: A single item in the menu 
 *
 * character: The character that selects the menu item.
 * id: A unique identifier for the menu item, passed to the action handler when selected.
 */
struct menu_item {
    const char character;
    uint8_t id;
};

/*
 * Initialise the menu system.
 *
 * @param contents: Pointer to an array of menu_item structures that define the menu.
 * @param length: The number of items in the contents array.
 * @param action_handler: A function pointer to the function that will handle menu selections. 
 *                         Must accept a uint16_t item ID and a uint64_t value as parameters. 
 */
void menu_init(const struct menu_item *contents, size_t length, void (*action_handler)(uint8_t id, uint64_t value));

/*
 * Receive and process input data for the menu system. Call action handler if a valid menu command is detected. 
 * 
 * @param data: Pointer to the input data (e.g. characters from a serial interface).
 * @param length: The length of the input data in bytes.
 */
void menu_input(const void *data, size_t length);

#endif /* MENU_H */
