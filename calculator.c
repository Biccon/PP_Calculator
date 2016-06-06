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

int main(int argc, char **argv){
	char *exp;
	exp = inputExpression();
	printf("%s\n", exp);
	if(!ParenMatch(exp)){
		printf("괄호 쌍이 맞지 않음\n");
	} else {
		/*
			exp = assignExpression(exp); // 를 해준 뒤에 할당 오류가 발생하지 않았는지 check
			
		*/
		exp = replaceExpression(exp);
		printf("%s\n", exp);
		printf("%d %d %d\n", isExpRight(exp), hasOperatorBetweenNumber(exp), isDivZero(exp));
		if(hasError(exp)){
			printf("에러 발생\n");
		} else {
			exp = postfix(exp);
			printf("결과값 = %lf\n", calc(exp));
		}
	}
}
