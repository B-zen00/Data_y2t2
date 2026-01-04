#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

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
struct Node pop();
void postfixtoanswer(char postfix[]);

// Main function 
int main() {
    int again = 1;
    char postfix[100];
    while (again == 1){
        printf("Enter postfix expression: ");
        scanf("%s", postfix);

        postfixtoanswer(postfix);
        printf("Would you like to do it again? (1 = yes, 0 = no): ");
        scanf("%d", &again);
        while(again != 1 && again != 0){
            // again
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

// Push variable function
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
    if (top == NULL) return temp;
    struct Node* t = top;
    temp = *t;
    top = top->next;
    free(t);
    return temp;
}

// Make Postfix to Answer 
void postfixtoanswer(char postfix[]) {
    int step = 1;

    printf("----------------------------\n");
    printf("  Step   Symbol   stack\n");
    printf("----------------------------\n");

    for (int i = 0; postfix[i] != '\0'; i++) {

        if(isalnum(postfix[i])){
            // Number 
            if (isdigit(postfix[i])) {
                pushNumber(postfix[i]-'0');
            }
            // Variable
            else{
                char temp[2] = { postfix[i], '\0' };
                pushVariable(temp);
            }
        }else {
            // Operator
            struct Node x1 = pop();
            struct Node x2 = pop();

            // Operator Number
            if (x1.Number && x2.Number) {
                int result;
                switch (postfix[i]) {
                    case '+': result = x2.value + x1.value; break;
                    case '-': result = x2.value - x1.value; break;
                    case '*': result = x2.value * x1.value; break;
                    case '/': result = x2.value / x1.value; break;
                    case '^': result = pow(x2.value, x1.value); break;
                }
                pushNumber(result);
            }
            // Operator Variable
            else {
                char newVariable[100];
                sprintf(newVariable, "(%s%c%s)", x2.Variable, postfix[i], x1.Variable);
                pushVariable(newVariable);
            }
        }

        // Print stack
        printf("%4d%8c       ", step++, postfix[i]);

        struct Node* t = top;
        char arr[20][100];
        int count = 0;

        while (t != NULL) {
            strcpy(arr[count++], t->Variable);
            t = t->next;
        }

        for (int j = count - 1; j >= 0; j--) {
            if (j == 0)
                 printf("%s", arr[j]);
            else
                printf("%s,", arr[j]);
        }
        printf("\n");
        
    }
    printf("----------------------------\n");

    struct Node ans = pop();
    printf("Answer = %s\n", ans.Variable);
}
