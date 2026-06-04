# menu

Ascii based menu system. 

### Usage:

Menu items are structures consisting of a unique character and a unique ID integer.

```C
struct menu_item {
    const char character;
    uint8_t id;
};
```

A pointer to an array of menu items must be provided on initialisation, along with a callback function that accepts the ID and a 64-bit integer.

```C
void menu_init(const struct menu_item *contents, size_t length, void (*action_handler)(uint8_t id, uint64_t value));
```

The transport layer (serial, bluetooth, etc.) should pass data to the menu system via the menu_input function.

Menu items are activated by sending a character followed by an optional value and a newline. The menu system parses the input and calls a user-defined action handler with the corresponding menu item ID and value.

```C
void menu_input(const void *data, size_t length);
```

### Example:

```C
const struct menu_item menu_contents[] = {
    { .character = 's', .id = EVENT_START },
    { .character = 'x', .id = EVENT_STOP },
};

static void menu_callback(uint16_t id, uint64_t value) {
    printf("Menu item %d called with value: %lld", id, value);
}

menu_init(menu_contents, ARRAY_SIZE(menu_contents), menu_callback);

menu_input("s10\n", 4);
```
