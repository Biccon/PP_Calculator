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

void trim(char *input)
{
   char *dst = input, *src = input;
   char *end;

   // Skip whitespace at front...
   //
   while (isspace((unsigned char)*src))
   {
      ++src;
   }

   // Trim at end...
   //
   end = src + strlen(src) - 1;
   while (end > src && isspace((unsigned char)*end))
   {
      *end-- = 0;
   }

   // Move if needed.
   //
   if (src != dst)
   {
      while ((*dst++ = *src++));
   }
}

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

int hasError(char *exp){
	return !(isExpRight(exp) && hasOperatorBetweenNumber(exp) && !isDivZero(exp));
}


int main(int argc, char **argv){
	char *exp;
	exp = inputExpression();
	trim(exp); 
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
