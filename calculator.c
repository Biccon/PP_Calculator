#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define PI 3.141592653586

char *inputExpression();
char *splitExpression(char *exp);
char *inputExpression(){
	char *expression = (char *)calloc(sizeof(char), 300);
	char *isCal;
	char *isExit;
	while (1) {
		char *input = (char *)malloc(sizeof(char) * 30);
		scanf("%s", input); // 사용자 입력
		strcat(expression, input); // 입력받은 수식을 뒤에 갖다 붙인다
		free(input);
		
		isCal = strstr(expression, "CAL");
		isExit = strstr(expression, "EXIT");
		
		if (isCal != NULL || isExit != NULL){  //CAL이 포함되어있으면 while문 종료
			break;
		}
	}
	if(isExit != NULL){
		if(isCal == NULL || isCal > isExit)
			return "EXIT";
	}
	return expression;	//printf("%s\n", expression);`// while문 종료 후 수식 오류 확인
}

char *splitExpression(char *exp){
	char *tempExp = exp;
	while(tempExp && strstr(tempExp, "->")){ // -> 포함하고있을때 나눠야함
		char tempList[2][30];
		int temp = strlen(tempExp) - strlen(strstr(tempExp, "->"));
		strncpy(tempList[0], tempExp, temp);
		strncpy(tempList[1], tempExp + temp + strlen("->"), 3);
		tempExp = tempExp + temp + strlen("->") + 3;
		// register에 assign해주면 끝
		// 
		//tempExp = NULL;//temp;
	}
}

double calc(char *exp){
	return 1;//PI + 44;
}

double calculate(char *operator, char *expression){
	if(strcmp(operator, "sin") == 0){
		return sin(calc(expression));
	} else if(strcmp(operator, "cos") == 0){
		return cos(calc(expression));
	} else if(strcmp(operator, "exp") == 0){
		return exp(calc(expression));
	} else if(strcmp(operator, "log") == 0){
		return log(calc(expression));
	}
}

void replaceExpression(char *exp){
	
}

int main(){
	char *temp;
	temp = inputExpression();
	temp = splitExpression(temp);
	char input[30];
	printf("%lf", calculate("exp", "1+3"));
}
