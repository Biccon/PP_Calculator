#define TRUE true
#define FALSE false
#define true 1
#define false 0

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "stack.h"
#include "linkedlist.h"
#include "error.h"
#include "postfix.h"
LinkedList *reg;
#include "calc.h"

void init(LinkedList *list);
int get_size(LinkedList *list);
int Get_ListCount();

Node *add_before(Node *node, char *name, double data);
Node *add_last(LinkedList *list, char *name, double data);

void remove_node(Node *node);

Node *Find_Node_By_Index(LinkedList *list, int i); 
Node *get_node_by_name(LinkedList *list, char *name);
int Get_NodeIndex(LinkedList *list, Node *node);

void printList(LinkedList *list);


int main(int argc, char **argv){
	reg = (LinkedList*)malloc(sizeof(LinkedList));
	while(1){
		init(reg);
		printf("Input Expression (종료 EXIT 계산 CAL)\n");
		char *exp;
		exp = inputExpression();
		if(strcmp(exp, "EXIT") == 0)
			break;
		if(!ParenMatch(exp)){
			printf("괄호 쌍이 맞지 않음\n");
		} else {
			exp = assignExpression(exp);
			exp = replaceRegister(reg, exp);
			exp = replaceExpression(exp);
			//printf("%d %d %d\n", isExpRight(exp), hasOperatorBetweenNumber(exp), isDivZero(exp));
			if(hasError(exp)){
				printf("에러 발생\n");
			} else {
				exp = postfix(exp);
				printf("결과값 = %lf\n", calc(exp));
			}
		}
	}
}
