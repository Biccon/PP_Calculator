#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"
#include "postfix.h"
#include "calc.h"
#define PI 3.14159265359
#define TRUE true
#define FALSE false
#define true 1
#define false 0
int errorCheck(char *exp){
	// 
	int p = ParenMatch(exp);
	if(p == 0)
		return 0;
	
	return 1;
}
int main(int argc, char **argv){
	char *exp;
	exp = inputExpression();
	if(errorCheck(exp)){
		exp = postfix(exp);
		printf("%lf\n", calc(exp));
		printf("%s\n", exp);
	} else {
		printf("에러\n");
	}
	//printf("%d\n", ParenMatch(temp));
	//assignExpression(temp);
	//printf("%s\n", postfix(temp));
	//replaceExpression(temp);
	//printf("%s\n", temp);
}
