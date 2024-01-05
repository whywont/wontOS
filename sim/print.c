//
// Created by user on 1/4/24.
//
#include <stdio.h>
#include <string.h>

#define MAX_ROWS 25
#define MAX_COLS 80
#define WHITE_ON_BLACK 0x07

unsigned char simulated_vga[MAX_ROWS][MAX_COLS][2]; // [Character][Attribute]

void outportb(unsigned short port, unsigned char val) {
    // Simulate I/O port interaction - does nothing in simulation
}

void set_cursor(int row, int col) {
    // Simulate cursor setting - does nothing in simulation
}

void clear_screen() {
    for (int i = 0; i < MAX_ROWS; i++) {
        for (int j = 0; j < MAX_COLS; j++) {
            simulated_vga[i][j][0] = ' ';
            simulated_vga[i][j][1] = WHITE_ON_BLACK;
        }
    }
}

void print_char(char character, int row, int col, char attribute_byte) {
    // Bounds checking omitted for brevity
    simulated_vga[row][col][0] = character;
    simulated_vga[row][col][1] = attribute_byte;
}

void print_at(char* message, int row, int col) {
    for (size_t i = 0; i < strlen(message); i++) {
        print_char(message[i], row, col + i, WHITE_ON_BLACK);
    }
}

void print(char* message) {
    print_at(message, 0, 0); // Start at the top-left corner for simplicity
}

void kernel_main() {
    clear_screen();
    print("WontOS");
    // Print the simulated VGA buffer to the terminal
    for (int i = 0; i < MAX_ROWS; i++) {
        for (int j = 0; j < MAX_COLS; j++) {
            putchar(simulated_vga[i][j][0]);
        }
        putchar('\n');
    }
}

int main() {
    kernel_main();
    return 0;
}