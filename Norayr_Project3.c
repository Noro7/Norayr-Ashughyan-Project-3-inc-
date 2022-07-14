#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

        char currentOperand[10];
        int length = 0;
        int finalOperand = 0;

typedef struct
{
    int depth;
    int name;
    char value[10];
}

operand;
operand operands[20];

bool is_operator(char operator) {
        return operator== '*';
        return operator== '/';
        return operator== '+';
        return operator== '-';
}

void createOperand() {
    if (strlen(currentOperand) != 0) {
        operand op;
        op.name = finalOperand + 1;
        op.depth = length;
        strcpy(op.value, currentOperand);

        operands[finalOperand] = op;

        memset(currentOperand, 0, sizeof currentOperand);

        finalOperand++;
    }
}

void createLink(FILE *fileptr, int name1, int name2) {
    fprintf(fileptr, "\tn%d -> n%d ;\n", name1, name2);
}

void createElement(FILE *fileptr, operand op) {
    fprintf(fileptr, "\tn%d ;\n\tn%d [label=\"%s\"] ;\n", op.name, op.name, op.value);
}


int main(int argc, char *argv[])
{
    char input[] = "\n";

    int current = 0;
    while (current < strlen(input)) {
        switch (input[current]) {
            case ' ':
                break;
            case '(':
                length++;
                break;
            case ')':
                createOperand();
                length--;
                break;
            default:
                if (is_operator(input[current])) {
                    strncat(currentOperand, &input[current], 1);
                }
        }

        current++;
    }

FILE *file;
file = fopen(argv[1], "w");

        fprintf(file, "%s", "digraph D {\n");

        int i = 0;
        bool ended = false;
        while (!ended && i < sizeof operands / 20) {
            if (operands[i].depth == 0) {
                ended = true;
                break;
            }

            createElement(file, operands[i]);

            if (i > 0) {
                if (operands[i].depth == operands[i - 1].depth)
                {
                    createLink(file, operands[i - 2].name, operands[i].name);
                }
                else if (operands[i].depth > operands[i - 1].depth)
                {
                    createLink(file, operands[i - 1].name, operands[i].name);
                }
                else if (operands[i].depth < operands[i - 1].depth)
                {
                    for (int j = i - 1; j > 0; j--)
                    {
                        if (operands[j].depth == operands[i].depth)
                        {
                            createLink(file, operands[j - 1].name, operands[i].name);
                            break;
                        }
                    }
                }
            }

            i++;
        }

        fprintf(file, "%s", "}");
        fclose(file);
i;}
