#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char input[100];
int pos = 0;
int tempCount = 1;


struct Quad {
    char op[5];
    char arg1[10];
    char arg2[10];
    char result[10];
} quad[100];

int quadIndex = 0;


char* newTemp() {
    char *temp = (char*)malloc(10);
    sprintf(temp, "t%d", tempCount++);
    return temp;
}


char* copyStr(char *str) {
    char *res = (char*)malloc(20);
    strcpy(res, str);
    return res;
}


char* E();
char* T();
char* F();


char* E() {
    char *left = T();

    while (input[pos] == '+' || input[pos] == '-') {
        char op[2];
        op[0] = input[pos++];
        op[1] = '\0';

        char *right = T();
        char *temp = newTemp();

        strcpy(quad[quadIndex].op, op);
        strcpy(quad[quadIndex].arg1, left);
        strcpy(quad[quadIndex].arg2, right);
        strcpy(quad[quadIndex].result, temp);
        quadIndex++;

        left = temp;
    }
    return left;
}


char* T() {
    char *left = F();

    while (input[pos] == '*' || input[pos] == '/' || input[pos] == '%') {
        char op[2];
        op[0] = input[pos++];
        op[1] = '\0';

        char *right = F();
        char *temp = newTemp();

        strcpy(quad[quadIndex].op, op);
        strcpy(quad[quadIndex].arg1, left);
        strcpy(quad[quadIndex].arg2, right);
        strcpy(quad[quadIndex].result, temp);
        quadIndex++;

        left = temp;
    }
    return left;
}


char* F() {
    if (input[pos] == '(') {
        pos++;
        char *val = E();
        if (input[pos] == ')') pos++;
        return val;
    }
    else if (isalnum(input[pos])) {
        char buffer[20];
        int i = 0;

        while (isalnum(input[pos])) {
            buffer[i++] = input[pos++];
        }
        buffer[i] = '\0';

        return copyStr(buffer);
    }
    else {
        printf("Error at position %d\n", pos);
        exit(1);
    }
}


int main() {
    printf("Enter expression: ");
    scanf("%s", input);

    char *res = E();

    printf("\nQuadruples:\n");
    printf("Op\tArg1\tArg2\tResult\n");

    for (int i = 0; i < quadIndex; i++) {
        printf("%s\t%s\t%s\t%s\n",
               quad[i].op,
               quad[i].arg1,
               quad[i].arg2,
               quad[i].result);
    }

    printf("\nFinal Result stored in: %s\n", res);

    return 0;
}