#define MAX 300
typedef struct stack Stack;

struct stack
{
	double data[MAX];
	int top;

};

int checkOp(char, char);
void init_stack(Stack *s); //stack 초기화(-1)
void push(Stack *s, double value); 
double pop(Stack *s);
double top(Stack *s); //스택의 맨 위 값 출력
void print_stack(Stack *s); //스택의 상단부터 출력(하단부터로 바꿀수 있음)
int size(Stack *s);
int isEmpty(Stack *s);
int ParenMatch(char *c);

void init_stack(Stack *s)
{
	s->top= -1;
}

void push(Stack *s, double value)
{
	if (s->top >= MAX - 1)
	{
		return ;
	}
	s->data[++s->top] = value;

}

double pop(Stack *s)
{
	if (s->top < 0)
	{
		return 0;
	}
	s->data[s->top--];
	return s->data[s->top + 1];

}

double top(Stack *s)
{
	if (s->top < 0)
	{
		return 0;
	}
	return s->data[s->top];
}

int size(Stack *s)
{
	return s -> top + 1;
}

int isEmpty(Stack *s)
{
	if (s->top < 0)
	{
		return 1;
	}
	return 0;
}

void print_stack(Stack *s)
{
	int i;
	for (i = 0; i <s->top+1; i++)
	{
		printf("%lf", s->data[i]);
	}
	printf("\n");
}

int checkOp(char op1, char op2){
	if(op1 == '(')
		return op2 == ')';
	else if(op1 == '[')
		return op2 == ']';
	return 0;
}

int ParenMatch(char *c)
{
	int i;
	Stack *a = (Stack *)calloc(sizeof(Stack), 1);
	init_stack(a);
	for (i = 0; i < strlen(c); i++)
	{
		if (c[i] == '(' || c[i] == '[')
		{
			push(a,c[i]);
		}
		else if (c[i] == ')'|| c[i] == ']')
		{
			if (isEmpty(a)==1) //괄호 개수가 맞지 않음
			{
				return 0;
			}
			else
			{
				if(checkOp(top(a), c[i]) == 0){
					return 0;
				} else {
					pop(a);
				}
				
			}
		}
	}
	if (isEmpty(a)==1)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

char *getExpression(char *exp){ // 괄호 열리는 곳부터 닫히는 곧 까지 구해오는 함수
	/*
		ex)
		sin(1+ (2+3))
		sin뒤의 (1+ (2+3))를 구해주는 함수
	*/
	char *tempExp = (char *)calloc(sizeof(char), 300);
	Stack s; // ( add and push
	init_stack(&s);
	int i;
	int expLen = strlen(exp);
	int flag = 0;
	char tok;
	for(i=0; i < expLen; i++){
		tok = exp[i];
		if(flag == 0 && tok != '(')
			continue;
		else if(flag == 0 && tok == '('){
			flag = 1;
			push(&s, tok);
			sprintf(tempExp + strlen(tempExp), "%c", tok);
		} else if(flag != 0 && tok == '('){
			push(&s, tok);
			sprintf(tempExp + strlen(tempExp), "%c", tok);
		} else {
			if(isEmpty(&s))
				break;
			if(tok == ')'){
				sprintf(tempExp + strlen(tempExp), ")");
				pop(&s);
			} else {
				sprintf(tempExp + strlen(tempExp), "%c", tok);
			}
		}
	}
	if(isEmpty(&s) == 0){
		tempExp = tempExp + size(&s);
	}
	return tempExp;
}

int getIndexOutOfExpression(char *exp){
	Stack s;
	init_stack(&s);
	int i;
	int expLen = strlen(exp);
	int flag = 0;
	char tok;
	for(i=0; i<expLen; i++){
		tok = exp[i];
		if(flag == 0 && tok != '(')
			continue;
		else if(flag == 0 && tok == '('){
			flag = 1;
			push(&s, tok);
		} else if(flag != 0 && tok == '('){
			push(&s, tok);
		} else {
			if(tok == ')'){
				pop(&s);
			}
			if(isEmpty(&s))
				return i+1;
		}
	}
	return 0;
}
