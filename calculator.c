#define TRUE true
#define FALSE false
#define true 1
#define false 0

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"
#include "error.h"
#include "postfix.h"
#include "calc.h"
#define PI 3.14159265359

int main(int argc, char **argv){
	char *exp;
	exp = inputExpression();
	trim(exp); 
	printf("%s\n", exp);
	if(!ParenMatch(exp)){
		printf("괄호 쌍이 맞지 않음\n");
	} else {
//		exp = assignExpression(exp);
		exp = replaceExpression(exp);
		printf("%s\n", exp);
		printf("%d %d %d\n", isExpRight(exp), hasOperatorBetweenNumber(exp), isDivZero(exp));
		if(!hasError(exp)){
			exp = postfix(exp);
			printf("결과값 = %lf\n", calc(exp));
		} else {
			printf("에러 발생\n");
		}
	}
}
