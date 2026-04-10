


#include <stdio.h>
#include <ctype.h>
#include <string.h>

char input[100];
int pos = 0;


void E();
void T();
void F();

void match(char expected) {
    if (input[pos] == expected) {
        pos++;
    } else {
        printf("Error: unexpected symbol %c\n", input[pos]);
    }
}


void E() {
    T();
    while (input[pos] == '+' || input[pos] == '-') {
        char op = input[pos];
        match(op);
        T();
        printf("%c", op);   // SDT action
    }
}

void T() {
    F();
    while (input[pos] == '*' || input[pos] == '/') {
        char op = input[pos];
        match(op);
        F();
        printf("%c", op);   // SDT action
    }
}

void F() {
    if (input[pos] == '(') {
        match('(');
        E();
        match(')');
    }
    else if (input[pos] == '-') {   // unary minus
        match('-');
        F();
        printf("~");   // use ~ for unary minus
    }
    else if (isalnum(input[pos])) {   // id
        printf("%c", input[pos]);
        pos++;
    }
    else {
        printf("Error: invalid character %c\n", input[pos]);
    }
}

int main() {
    printf("Enter infix expression: ");
    scanf("%s", input);

    printf("Postfix expression: ");
    E();

    printf("\n");
    return 0;
}