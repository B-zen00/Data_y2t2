#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// Stack Node
struct Node {
    char Variable[100];
    int Number;
    int value;
    struct Node* next;
};

struct Node* top = NULL;

// Function prototypes
void pushNumber(int val);
void pushVariable(char Variable[]);
void pushExpr(char expr[]);
struct Node pop();
char peek();
int precedence(char op);
void infixtopostfix(char infix[]);

// Main function
int main() {
    int again = 1;
    char infix[100];

    while (again == 1) {
        printf("Enter infix expression: ");
        scanf("%s", infix);

        infixtopostfix(infix);
        printf("Would you like to do it again? (1 = yes, 0 = no): ");
        scanf("%d", &again);

        // again
        while (again != 1 && again != 0) {
            printf("Invalid input. Please try again.\n");
            printf("Would you like to do it again? (1 = yes, 0 = no): ");
            scanf("%d", &again);
        }
    }
    return 0;
}

// Push number function
void pushNumber(int val) {
    struct Node* n = (struct Node*)malloc(sizeof(struct Node));
    n->Number = 1;
    n->value = val;
    sprintf(n->Variable, "%d", val);
    n->next = top;
    top = n;
}
void pushVariable(char Variable[]) {
    struct Node* n = (struct Node*)malloc(sizeof(struct Node));
    n->Number = 0;
    strcpy(n->Variable, Variable);
    n->next = top;
    top = n;
}
void pushExpr(char expr[]) {
    struct Node* n = (struct Node*)malloc(sizeof(struct Node));
    n->Number = 0;
    strcpy(n->Variable, expr);
    n->next = top;
    top = n;
}

// Pop function
struct Node pop() {
    struct Node temp;
    temp.Variable[0] = '\0';

    if (top == NULL)
        return temp;

    struct Node* t = top;
    temp = *t;
    top = top->next;
    free(t);
    return temp;
}

char peek() {
    if (top == NULL)
        return '\0';
    return top->Variable[0];
}

// Check precedence
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    if (op == '^') return 3;
    return 0;
}

// Make Infix to Postfix
void infixtopostfix(char infix[]) {
    char postfix[100];
    int j = 0;
    int step = 1;

    printf("-----------------------------------\n");
    printf(" Step   Symbol    Stack    Output\n");
    printf("-----------------------------------\n");

    for (int i = 0; infix[i] != '\0'; i++) {
        char token = infix[i];

        // Operand
        if (isalnum(token)) {
            postfix[j++] = token;
        } // (
        else if (token == '(') {
            pushExpr("(");
        } // )
        else if (token == ')') {
            while (top != NULL && peek() != '(') {
                postfix[j++] = pop().Variable[0];
            }
            pop(); // remove '('
        }
        // Operator
        else {
            while (top != NULL && precedence(peek()) >= precedence(token)) {
                postfix[j++] = pop().Variable[0];
            }
            char op[2] = { token, '\0' };
            pushExpr(op);
        }

        // Print Step
        printf("%3d%8c        ", step++, token);
        struct Node* t = top;
        while (t != NULL) {
            printf("%2s", t->Variable);
            t = t->next;
        }
        if( step == 2 ){
            printf("%10.*s\n", j, postfix);
        } else {
            printf("       %.*s\n", j, postfix);
        }
    }

    // Pop remaining operators
    while (top != NULL) {
        postfix[j++] = pop().Variable[0];
    }
    postfix[j] = '\0';
    printf("-----------------------------------\n");
    printf("Postfix expression: %s\n", postfix);
}
