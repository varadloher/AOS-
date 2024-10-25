/* demonstrate the use of atexit() function*/
#include <stdio.h>
#include <stdlib.h>

// Function to be called at exit
void goodbye() {
    printf("Goodbye! The program is ending.\n");
}

// Another function to be called at exit
void save_data() {
    printf("Saving data before exiting...\n");
}

int main() {
    // Register the functions to be called at exit
    atexit(goodbye);
    atexit(save_data);

    printf("Program is running...\n");

    // Simulating some tasks in the program
    printf("Doing some tasks...\n");

    // When the program ends, the registered functions will be called
    return 0;
}

