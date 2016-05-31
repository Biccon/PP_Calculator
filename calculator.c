#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"
#include "postfix.h"
#include "calc.h"
#define PI 3.14159
int main(){
	char *temp;
	temp = inputExpression();
	printf("%d\n", ParenMatch(temp));
	//assignExpression(temp);
//	printf("%s\n", postfix(temp));
	//replaceExpression(temp);
}
