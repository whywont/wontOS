//
// Created by user on 1/1/24.
//
// VGA text mode video memory begins at address 0xB8000.
#define VIDEO_MEMORY (char*)0xB8000
// There are 25 lines each of 80 columns; each element takes 2 bytes.
#define MAX_ROWS 25
#define MAX_COLS 80
// The attribute byte for our default colour scheme (white-on-black).
#define WHITE_ON_BLACK 0x07

// Function to write a byte to a port (outportb).
void outportb(unsigned short port, unsigned char val) {
    asm volatile ("outb %0, %1" : : "a"(val), "Nd"(port));
}

void set_cursor(int row, int col) {
    // The device uses its control register as an index
    // to select its internal registers, of which we are
    // interested in:
    //    reg 14: which is the high byte of the cursor's offset
    //    reg 15: which is the low byte of the cursor's offset
    // Once the internal register has been selected, we may read or
    // write a byte on the data register.
    unsigned short position = (row * 80) + col;

    // Tell the VGA board we are setting the high cursor byte.
    outportb(0x3D4, 14);
    // Send the high cursor byte.
    outportb(0x3D5, position >> 8);
    // Tell the VGA board we are setting the low cursor byte.
    outportb(0x3D4, 15);
    // Send the low cursor byte.
    outportb(0x3D5, position);
}

// Function to clear the screen.
void clear_screen() {
    int screen_size = MAX_ROWS * MAX_COLS;
    int i;
    char *screen = VIDEO_MEMORY;

    for (i = 0; i < screen_size; i++) {
        // Set each character to 'space' (0x20)
        *screen++ = 0x20;
        // Set the attribute byte to white on black
        *screen++ = WHITE_ON_BLACK;
    }

    // Set hardware cursor to the top-left corner.
    // (You would need to implement the following function according to your system.)
    set_cursor(0, 0);
}

// Cursor position
unsigned int cursor_row = 0;
unsigned int cursor_col = 0;

void print_char(char character, int row, int col, char attribute_byte) {
    // Create a pointer to the start of video memory
    unsigned char *vidmem = (unsigned char*) VIDEO_MEMORY;

    // If attribute byte is zero, use the default style
    if (attribute_byte == 0)
        attribute_byte = WHITE_ON_BLACK;

    // If row and col are negative, we will print at the current cursor location
    if (row >= 0 && col >= 0) {
        cursor_row = row;
        cursor_col = col;
    } else {
        row = cursor_row;
        col = cursor_col;
    }

    // Get the video memory offset for the screen location
    int offset = (row * MAX_COLS + col) * 2; // Each cell takes 2 bytes

    // Handle newlines
    if (character == '\n') {
        cursor_row++;
        cursor_col = 0;
    } else {
        vidmem[offset] = character;
        vidmem[offset + 1] = attribute_byte;
        cursor_col++;
        // Handle end of row
        if (cursor_col >= MAX_COLS) {
            cursor_row++;
            cursor_col = 0;
        }
    }

    // Scroll the screen if needed
    if (cursor_row >= MAX_ROWS) {
        // Implement scrolling function
        // scroll();
    }

    // Update cursor position
    // update_cursor(cursor_row, cursor_col); // Similar to set_cursor in the previous example
}

void print_at(char* message, int row, int col) {
    int i = 0;
    while (message[i] != 0) {
        print_char(message[i], row, col, WHITE_ON_BLACK);
        i++;
        col++;
        // Handle the end of the row
        if (col >= MAX_COLS) {
            row++;
            col = 0;
        }
    }
}

void print(char* message) {
    print_at(message, -1, -1); // Print at current cursor location
}





// This is a simple kernel_main function
void kernel_main() {


    clear_screen();
    print("WontOS");
}
