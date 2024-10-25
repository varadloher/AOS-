/*Write a C program to display the given message ‘n’ times. (make a use of setjmp and longjmp system call)*/ 
#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>

jmp_buf buf;

void display_message(const char *message, int n) {
    if (n <= 0) {
        longjmp(buf, 1);  // Jump back to the point of setjmp if n <= 0
    }
    printf("%s\n", message);
    display_message(message, n - 1);  // Recursive call to print the message n times
}

int main() {
    const char *message = "Hello, World!";
    int n;

    // Set the jump point
    if (setjmp(buf)) {
        printf("Finished displaying the message.\n");
        return 0;  // Exit the program if returning from longjmp
    }

    printf("Enter the number of times to display the message: ");
    scanf("%d", &n);

    display_message(message, n);

    return 0;
}

	
