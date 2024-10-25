/* write a c prog to demonstrate the difference between behaviour that can be seen with */
#include <stdio.h>
#include <setjmp.h>

// Global variable
int global_var = 1;

// Static variable
static int static_var = 1;

// Volatile variable
volatile int volatile_var = 1;

jmp_buf buffer;

void demonstrate_variables() {
    // Automatic (local) variable
    int auto_var = 1;

    // Register variable
    register int reg_var = 1;

    printf("Before longjmp:\n");
    printf("  Global Variable: %d\n", global_var);
    printf("  Static Variable: %d\n", static_var);
    printf("  Automatic Variable: %d\n", auto_var);
    printf("  Register Variable: %d\n", reg_var);
    printf("  Volatile Variable: %d\n", volatile_var);

    // Change the values of all variables
    global_var++;
    static_var++;
    auto_var++;
    reg_var++;
    volatile_var++;

    // Use longjmp to go back to the setjmp point
    longjmp(buffer, 1);  // Jump back to setjmp with return value 1

    // This code won't be reached because of longjmp
    printf("This will never print.\n");
}

int main() {
    if (setjmp(buffer) == 0) {
        // First time setjmp is called
        printf("Calling demonstrate_variables()...\n");
        demonstrate_variables();
    } else {
        // After longjmp, execution continues here
        printf("\nAfter longjmp:\n");
        printf("  Global Variable: %d\n", global_var);
        printf("  Static Variable: %d\n", static_var);
        printf("  Volatile Variable: %d\n", volatile_var);

        // Automatic and register variables are lost after longjmp
        // They are not preserved across function calls or jumps.
        printf("  Automatic Variable and Register Variable are not preserved after longjmp.\n");
    }

    return 0;
}

