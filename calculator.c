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

int isDivZero(char *exp){ //바꾸기 전 expression을 검사하는 함수
	int expLen = strlen(exp);
	int i;
	int divZero = false;
	char tok;
	for(i=0;i<expLen;i++){
		tok = exp[i];
		if(tok == ' ')
			continue;
		if(tok == '/'){ // 나누기 연산이 나왔을 때
			char temp = exp[++i]; //다음 문자를 temp에 넣어본다
			char number[30] = "";
			while(('0' <= temp && temp <= '9' || temp == '.')){ // 다른 문자가 나올 때까지가 / 연산 뒤에 나오는 숫	자
				if(temp == ' ') // 공백은 넘기고
					continue;
				char n[1];
				sprintf(n, "%c", temp); // calc와 같은 방식으로 n[]에 char로 tok를 넣는다
				strcat(number, n);
				i++;
				temp = exp[i]; // i++
			}
			printf("%s\n", number);
			double totalNum = atof(number);
			if(totalNum == 0)
				return true;
		}
			//	if('0' <= tok && tok <= '9' )
	}
	return false;
}

int errorCheck(char *exp){
	// 
	int p = ParenMatch(exp);
	if(p == false) // matching이 false하면
		return false; // 실패
	int r = isExpRight(exp);
	if(r == false)
		return false;
	int h = hasOperatorBetweenNumber(exp);
	if(h == false)
		return false;
	// divZero는 식이 변환 된 후에 구해야 함
	// 변환되지 않은 식에서는 [x]이나 sin/cos/log/exp와 같은 식이 있으므로
	// replaceExpression이후에 divZero 오류 검사를 해줘야 할 것
	//int divZero = isDivZero(exp);
	//if(divZero == true) // div by zero이 true이면
	//	return false; // 실패
	// 
	return true;
}

int main(int argc, char **argv){
	char *exp;
	exp = inputExpression();
//	exp = postfix(exp);
//	printf("%lf\n", calc(exp));
	//printf("%s\n", exp);
	//if(errorCheck(exp)){
		//printf("%s\n", exp);
		exp = replaceExpression(exp);
		if(strcmp(exp, "divZero") == 0){
			printf("divZero\n");
			exit(1);
		}
		exp = postfix(exp);
		//char *temp = getExpression(exp);
		//printf("%s\n", temp);
		printf("%lf\n", calc(exp));
//	} else {
//		printf("에러\n");
//	}
	//printf("%d\n", ParenMatch(temp));
	//assignExpression(temp);
	//printf("%s\n", postfix(temp));
	//replaceExpression(temp);
	//printf("%s\n", temp);
}
