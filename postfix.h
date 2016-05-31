#include <ctype.h>

char *postfix(char *exp); // 후위식 변환
int cmpOpPriority(char op1, char op2); // 우선순위 비교
int getOpPriority(char op); //계산 우선순위

char *postfix(char *exp){
	Stack stack;
	
	int expLen = strlen(exp);
	char *postfix = (char *)malloc(expLen + 1);
	memset(postfix, 0, sizeof(char)*(expLen + 1));

	int i, idx = 0;
	char tok, popOp;

	init_stack(&stack);
	for(i=0; i<expLen; i++){
		tok = exp[i];
		if('0' <= tok && tok <= '9' || tok == '.')
			postfix[idx++] = tok;
		else {
			switch(tok){
				case '(':
					push(&stack, tok);
					break;
				case ')':
					while(1){
						popOp = pop(&stack);
						if(popOp == '(')
							break;
						postfix[idx++] = popOp;
					}
					break;
				case '+':
				case '-':
				case '*':
				case '/':
					while(!isEmpty(&stack) && cmpOpPriority(top(&stack), tok) >= 0)
						postfix[idx++] = pop(&stack);
					push(&stack, tok);
					break;
			}
		}
	}
	while(!isEmpty(&stack))
		postfix[idx++] = pop(&stack);

	return postfix;
}

int cmpOpPriority(char op1, char op2){
	int op1Prec = getOpPriority(op1);
	int op2Prec = getOpPriority(op2);

	if(op1Prec > op2Prec)
		return 1;
	else if(op1Prec < op2Prec)
		return -1;
	else
		return 0;
}

int getOpPriority(char op){
	switch(op){
		case '*':
		case '/':
			return 5;
		case '+':
		case '-':
			return 3;
		case '(':
			return 1;
	}
	return -1;
}
