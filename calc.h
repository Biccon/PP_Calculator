#include <math.h>
char *trim(char *input);
char *inputExpression();
char *assignExpression(char *exp);
double calc(char *exp);
double calculate(char *operator, char *expression);
char *replaceExpression(char *exp);
double stringToDouble(char *exp);
char *substr(const char* input, int offset, int len);

double stringToDouble(char *exp){
	return atof(exp);
}

char* substr (const char* input, int offset, int len) {
	char *dest = (char*)malloc(sizeof(char) * (strlen(input)+1));
	int input_len = strlen (input);

	if (offset + len > input_len){
		return NULL;
	}

	strncpy (dest, input + offset, len);
	return dest;
}

char *trim(char *input) {
	char *dst = input, *src = input;
	char *end;

	while (isspace((unsigned char)*src)) {
	  ++src;
	}

	end = src + strlen(src) - 1;
	while (end > src && isspace((unsigned char)*end)) {
	  *end-- = 0;
	}

	if (src != dst) {
	  while ((*dst++ = *src++));
	}

	return input;
}

char *replaceAll(char *s, const char *olds, const char *news) {
  char *result, *sr;
  size_t i, count = 0;
  size_t oldlen = strlen(olds); if (oldlen < 1) return s;
  size_t newlen = strlen(news);


  if (newlen != oldlen) {
    for (i = 0; s[i] != '\0';) {
      if (memcmp(&s[i], olds, oldlen) == 0) count++, i += oldlen;
      else i++;
    }
  } else i = strlen(s);


  result = (char *) malloc(i + 1 + count * (newlen - oldlen));
  if (result == NULL) return NULL;


  sr = result;
  while (*s) {
    if (memcmp(s, olds, oldlen) == 0) {
      memcpy(sr, news, newlen);
      sr += newlen;
      s  += oldlen;
    } else *sr++ = *s++;
  }
  *sr = '\0';

  return result;
}

char *inputExpression(){
	char *expression = (char *)calloc(sizeof(char), 300);
	char *isCal;
	char *isExit;
	while (1) {
		char *input = (char *)malloc(sizeof(char) * 100);
		scanf("%s", input); // 사용자 입력
		strcat(expression, trim(input)); // 입력받은 수식을 뒤에 갖다 붙인다
		free(input);
		
		isCal = strstr(expression, "CAL");
		isExit = strstr(expression, "EXIT");
		
		if (isCal != NULL || isExit != NULL){  //CAL이 포함되어있으면 while문 종료
			break;
		}
	}
	if(isExit != NULL){ // Exit가 입력 받아졌고
		if(isCal == NULL || isCal > isExit) // CAL이 입력되어있지 않거나, EXIT가 CAL보다 앞에 있는 경우
			return "EXIT"; // EXIT리턴
	}
	int len = strlen(expression) - strlen(strstr(expression, "CAL"));
	memset(expression+len, 0, sizeof(char) * 300 - len); // 식 뒤 부분을 null로 만들다
	return expression; // 식 반환 및 공백 제거
}

char *replaceRegister(LinkedList *list, char *exp){
	char *tempExp = (char*)malloc(sizeof(char) * 300);
	strcpy(tempExp, exp);
	int length = strlen(exp);
	int i;
	char tok;
	for(i=0;i<length;i++){
		tok = exp[i];
		if(tok == '['){
			char *name = (char*)malloc(sizeof(char)*2);
			sprintf(name, "%c", exp[++i]);
			Node *tempNode = get_node_by_name(list, name);
			if(tempNode != NULL){
				char oldData[10];
				char replaceData[50];
				sprintf(oldData, "[%c]", exp[i]);
				sprintf(replaceData, "%lf", tempNode -> data);
				tempExp = replaceAll(tempExp, oldData, replaceData);
			}
		}
	}
	return tempExp;
}
char *assignExpression(char *exp){
	char *tempExp = exp;
	char *pos;
	while((pos = strstr(tempExp, "->"))){ // -> 포함하고있을때 나눠야함
		char *expression = substr(tempExp, 0, strlen(tempExp) - strlen(pos)); // -> 이전의 식
		char *temp = substr(pos + strlen("->"), 0, 3);
		
		if(temp == NULL)
			return "error";
		else {
			// assign 변수 이름 유효성 체크
			if(*(temp) == '[' && *(temp+2) == ']' && 'a' <= *(temp+1) && *(temp+1) <= 'z'){
				char *name = (char*)malloc(sizeof(char)*2);
				sprintf(name, "%c", *(temp+1));
				
				// check register expression에 정의되지 않은 register이 쓰인 경우 오류
				if(!Registe_Right(reg, expression))
					return "error";
				expression = replaceRegister(reg, expression);
				expression = replaceExpression(expression);
				if(hasError(expression))
					return "error";
				else {
					expression = postfix(expression);
					add_last(reg, name, calc(expression));
					tempExp = pos + strlen("->") + 3;
				}
			} else {
				return "error";
			}
		}
	}
	return tempExp;
}

double calc(char *exp){
	Stack stack;
	int expLen = strlen(exp);
	int i;
	char tok; 
	double op1, op2;
	
	init_stack(&stack);

	for(i=0; i<expLen; i++){
		tok = exp[i];
		if(tok == '|'){
			char temp = exp[++i]; // 일단 temp에 |다음 문자하나를 넣어준다. 다음문자도 |이면 while을 들어가지 않음
			char number[30] = "";
			while(temp != '|'){
				char n[1];
				sprintf(n, "%c", temp);
				// 숫자를 문자열로 만들어야지 임시저장 number char배열에 strcat시켜줄 수 있다.
				// 따라서 char n[2]를 만들고 거기에 sprintf를 이용하여 문자형으로 숫자를 저장
				strcat(number, n);
				i++;
				temp = exp[i];
			}
			push(&stack, atof(number));
		} else {
			op2 = pop(&stack);
			op1 = pop(&stack);

			switch(tok){
				case '+':
					push(&stack, op1+op2);
					break;
				case '-':
					push(&stack, op1-op2);
					break;
				case '*':
					push(&stack, op1*op2);
					break;
				case '/':
					push(&stack, op1/op2);
					break;
			}
		}
	}
	return pop(&stack);
}

double calculate(char *operator, char *expression){
	double result = calc(expression);
	if(strcmp(operator, "sin") == 0){
		result = sin(result);
	} else if(strcmp(operator, "cos") == 0){
		result = cos(result);
	} else if(strcmp(operator, "exp") == 0){
		result = exp(result);
	} else if(strcmp(operator, "log") == 0){
		result = log(result);
	}

	return result;
}

char *replaceExpression(char *exp){
	char *tempExp = (char *)calloc(sizeof(char), 300);
	char *ops = (char*)malloc(sizeof(char) * 16);
	char *oper;
	strcpy(tempExp, exp);
	strcpy(ops, "sin/cos/exp/log");
	// 기존 방식은 strtok로 해줬는데 재귀로 하면서 strtok(NULL, "/")할때 문제가 발생했다. 해결해주기위해서 각자 다른 포인터를 사용
	// 각기 다른 포인터를 사용함으로써 재귀호출이 되어도 그것에 상관이 없게 되었음
	while((oper = substr(ops, 0, 3))){
		char *subExp;
		while((subExp = strstr(tempExp, oper))){
			int tmpIndex = getIndexOutOfExpression(subExp);
			char *formula = (char *)calloc(sizeof(char), 100);
			formula = getExpression(subExp);
			formula = replaceExpression(formula);
			
			if(strcmp(formula, "") == 0 || strcmp(formula, "()") == 0 || hasError(formula))
				return "error";
			else if(strcmp(oper, "log") == 0 && atof(substr(formula, 1, strlen(formula) -2)) <= 0)
				return "error";
			
			formula = postfix(formula);
			double result = calculate(oper, formula);

			char *lastExp = (char *)calloc(sizeof(char), 100);
			strcpy(lastExp, subExp + tmpIndex);
			memset(subExp, 0, strlen(subExp));
			
			sprintf(subExp, "(%lf)", result);
			sprintf(subExp + strlen(subExp), "%s", lastExp);
		}
		ops = ops + 4;
	}
	return tempExp;
}
