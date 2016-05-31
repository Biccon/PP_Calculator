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
	memset(expression+len, 0, sizeof(char) * 300 - len);
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

char *replaceExpression(char *exp){
	char *tempExp = (char *)calloc(sizeof(char), 300);
	char find[] = "sin/cos/exp/log";
	char *temp = (char *)malloc(sizeof(char) * 3);
	strcpy(tempExp, exp);
	temp = strtok(find, "/");
	while(temp){
		char *split = (char *)malloc(sizeof(char) * 100);
		//while(
		/*
		split = strtok(tempExp, temp);
		while(split){
			printf("%s\n", split);
			split = strtok(NULL, temp);
		}
		*/
		free(split);
		temp = strtok(NULL, "/");
	}
}
