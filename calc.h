char *inputExpression();
char *assignExpression(char *exp);
double calc(char *exp);
double calculate(char *operator, char *expression);
char *replaceExpression(char *exp);
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
	if(isExit != NULL){ // Exit가 입력 받아졌고
		if(isCal == NULL || isCal > isExit) // CAL이 입력되어있지 않거나, EXIT가 CAL보다 앞에 있는 경우
			return "EXIT"; // EXIT리턴
	}
	int len = strlen(expression) - strlen(strstr(expression, "CAL"));
	strncpy(expression, expression, len);
	memset(expression+len, 0, sizeof(char) * 300 - len); // 식 뒤 부분을 null로 만들다
	return expression; // 식 반환
}

char *assignExpression(char *exp){
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
	Stack stack;
	int expLen = strlen(exp);
	int i;
	char tok; 
	double op1, op2;
	
	// 연산을 위한 stack.
	// 연산 기호도 정수형으로 나타나므로(char형) double로 나타난 값과 같을 수 있음을 이용하여
	// 소숫점 연산을 위해 스택을 char형에서 double형으로 바꿈.
	// 사실 double짜리 스택을 새로 만들 수도 있겠ㅇ지만 어짜피 char -> double로의 casting에는 문제가 없으므로
	// 스택의 자료형을 double로 바꾼 것.
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
				printf("%s\n", number);
				i++;
				temp = exp[i];
			}
			printf("%s\n", number);
			printf("%lf\n", atof(number));
			push(&stack, atof(number));
			// tok == |이고 exp[i+1]도 바로 |인 경우가 있을 숭 ㅣㅆ나? 있으면 오류
		} else {
			op2 = pop(&stack);
			printf("op2 : %lf\n", op2);
			op1 = pop(&stack);
			printf("op1 : %lf\n", op1);

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

char *replaceExpression(char *exp){
	char *tempExp = (char *)calloc(sizeof(char), 300);
	char find[] = "sin/cos/exp/log";
	char *temp = (char *)malloc(sizeof(char) * 3);
	strcpy(tempExp, exp);
	temp = strtok(find, "/");
	while(temp){
		char *split = (char *)malloc(sizeof(char) * 100);
		
		split = strtok(tempExp, temp);
		while(split){
				
			printf("%s\n", split);
			split = strtok(NULL, temp);
		}
		
		free(split);
		temp = strtok(NULL, "/");
	}
}
