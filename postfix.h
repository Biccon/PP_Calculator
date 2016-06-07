#include <ctype.h>

char *postfix(char *exp); // 후위식 변환
int cmpOpPriority(char op1, char op2); // 우선순위 비교
int getOpPriority(char op); //계산 우선순위

char *postfix(char *exp){
    Stack stack;
    
    int expLen = strlen(exp);
    char *postfix = (char *)calloc(sizeof(char), expLen + 100);
    int sign = -1;

    int i, idx = 0;
    char tok, popOp;
    
    init_stack(&stack);
    for(i=0; i<expLen; i++){
        tok = exp[i];
        if('0' <= tok && tok <= '9'){// 숫자가 나오면
            postfix[idx++] = '|'; // 그자리에 |를 넣어서 숫자임을 구분하자
			if(sign == 0){
				postfix[idx++] = '+';
			} else if(sign == 1){
				postfix[idx++] = '-';
			}
			sign = -1;
            int temp = tok; //현재 숫자를 temp에넣어두고
            while('0' <= temp && temp <= '9' || temp == '.'){
                postfix[idx++] = temp;
                i++; // 다음숫자로 넘어가기 위해서
                temp = exp[i];
            }
            postfix[idx++] = '|';
            i--; // while에서 i++하고 for에서 i++해주면 두번 커지므로 연산자가 씹힘 따라서 i--해줘야 딱 적당!
        } else {
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
					if(exp[i-1] == '(' && '0' <= exp[i+1] && exp[i+1] <= '9'){// && !isEmpty(&stack)){
						if(tok == '+')
							sign = 0;
						else if(tok == '-')
							sign = 1;
						break;
					}
                case '*':
                case '/':
                    while(!isEmpty(&stack) && cmpOpPriority(top(&stack), tok) >= 0){
                        postfix[idx++] = pop(&stack);
                    }
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
    int op1Order = getOpPriority(op1);
    int op2Order = getOpPriority(op2);
    
    if(op1Order > op2Order)
        return 1;
    else if(op1Order < op2Order)
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
