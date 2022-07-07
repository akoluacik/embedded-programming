#include <stdio.h>
void print_in_binary(int number);
int main(int argc, char const *argv[])
{
    // BIT SHIFTING
    // A = A << B // SHIFTS THE EACH BIT BY B BITS TO THE LEFT
    printf("%s%d\n", "number of arguments:", argc);
    int a = *argv[1] - '0';
    int b = *argv[2] - '0';
    printf("%s%d\n", "old a:", a);
    a <<= b;
    printf("%s%d\n", "new a:", a);
    
    // A = A >> B // SHIFTS THE EACH BIT BY B BITS TO THE RIGHT
    b = *argv[3] - '0';
    a >>= b;
    printf("%s%d\n", "new a:", a);


    // IN ORDER TO SET THE 2nd BIT OF A NUMBER:
    // USE THE FOLLOWINGS:
    
    // A = A | 4;
    // A = A | (1 << 2);
    // A |= (1 << 2); // this one is more proper
    int A = 0;
    A |= (1 << 2);
    printf("%s%d\n", "Value of A:", A);
    print_in_binary(A);


    // IN ORDER TO RESET THE 2nd BIT OF A NUMBER
    // USE THE FOLLOWINGS:

    // A = A & ~(1 << 2);
    // A = A & (~(00000100))
    // A = A & 11111011

    A = 86;
    A &= ~(1 << 2);
    printf("%s%d\n", "Value of A:", A);
    print_in_binary(A);


    // IF YOU ARE ASKED TO SET 5nd AND 6th BITS
    A = 15;
    A |= (1 << 6) | (1 << 5);
    printf("%s%d\n", "Value of A:", A);
    print_in_binary(A);
    
    // NEGATING A SPECIFIC BIT WITH XOR
    A = 13;
    A ^= (1 << 2);
    printf("%s%d\n", "Value of A:", A);
    print_in_binary(A);


    // CHECKING IF A BIT IS SET OR RESET
    A = 13;
    if( A & (1 << 3) == (1 << 3)) printf("%s\n", "The 3rd bit is set!"); 

    //  TO INCREASE THE READIBILITY, USE MACRO AS BELOW:
    // #define BIT_0 (1 << 0)
    // #define BIT_1 (1 << 1)
    // #define BIT_2 (1 << 2)
    // .
    // .
    // .
    // #define BIT_7 (1 << 7)

    // BUT IT IS BETTER TO USE DECIMAL FORMAT RATHER THAN SHIFTING OPERATORS
    // TO GET RID OF AN EASY AND UNNECESSARY OPERATION

    // #define BIT_0 1
    // #define BIT_1 2
    // #define BIT_2 4
    // .
    // .
    // .
    // #define BIT_7 128

    return 0;
}


void print_in_binary(int number) {
    
    unsigned i;
    for (i = 1 << 8; i > 0; i = i / 2)
        (number & i) ? printf("1") : printf("0");
    puts("");
}