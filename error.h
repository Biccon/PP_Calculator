static int dot = 0;

int Registe_Right(LinkedList *list, char *exp){
    int i;
    int length = strlen(exp);
    char tok;

    for(i=0;i<length;i++){
        tok = exp[i];
        if(tok == '[')
        {   
            Node *NewNode = list -> head -> next;
            char temp[10];
            int j;
            temp[0] = exp[++i];
            while(NewNode != list -> tail){
                if(strcmp(temp, NewNode -> name) == 0)
                    return true;
                NewNode = NewNode -> next;
            }   
            return false;
        }   
    }   
    return true;
}

int isNumberExpression(char *exp){
	int numberExpression = false;
	int expLen = strlen(exp);
	int i;
	char tok;
	for(i=0;i<expLen;i++){
		tok = exp[i];
		if(('0' <= tok && tok <= '9') || tok == '.')
			continue;
		else
			return false;
	}
	return numberExpression;
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
            char *number = (char*)calloc(sizeof(char), 100); 
            while(('0' <= temp && temp <= '9' || temp == '.') || temp == '(' || temp == ')' || temp == '-' || temp == '+'){ // 다른 문자가 나올 때까지가 / 연산 뒤에 나오는 숫  자
                sprintf(number + strlen(number), "%c", temp); // calc와 같은 방식으로 n[]에 char로 tok를 넣는다
                i++;
                temp = exp[i]; // i++
            }
			number = postfix(number);

			printf("%s\n", number)
            double totalNum = calc(number); //atof(number);
			printf("Num : %lf\n", totalNum);
			printf("%s\n", number);
            if(totalNum == 0)
                return true;
        }   
            //  if('0' <= tok && tok <= '9' )
    }   
    return false;
}

int hasError(char *exp){
    return (!(isExpRight(exp) && hasOperatorBetweenNumber(exp) && !isDivZero(exp))) || (strcmp(exp, "error") == 0);
}

int hasOperatorBetweenNumber(char * exp) {
    int expLen = strlen(exp);
    char *transexp = (char *)malloc(expLen+1);
    int i, temp;
    int flag = 0; //flag = -1이면 return 0
    int idx = 0;
    char tok;
    
    for(i = 0; i < expLen; i++) {
        tok = exp[i];
        if('0' <= tok && tok <= '9') {
            transexp[idx++] = '|'; //숫자 구분
            temp = tok;
            while('0' <= temp && temp <= '9' || temp == '.') {
                transexp[idx++] = temp;
                i++;
                temp = exp[i];
            }
            transexp[idx++] = '|';
			i--;
        }
        else {
            transexp[idx++] = tok;
        }
    } //여기까지 ㅣ숫자ㅣ수식만듬
    
    for(i = 0; i < idx; i++) {
        if(i == idx-1)
            break; //i+1은 idx에 포함되지 않으므로
        if(transexp[i] == '|' && transexp[i+1] == '(') //ㅣ숫자ㅣ(숫자)
            flag = -1;
        if(transexp[i] == ')' && transexp[i+1] == '|') //(숫자)ㅣ숫자ㅣ
            flag = -1;
        if(transexp[i] == ')' && transexp[i+1] == '(') //(숫자)(숫자)
            flag = -1;
        if(transexp[i] == ']' && transexp[i+1] == '[') //[x][x]
            flag = -1;
        if('0' <= transexp[i] && transexp[i] <= '9' && transexp[i+1] == '[') //숫자[x]
            flag = -1;
        if(transexp[i] == ']' && '0' <= transexp[i+1] && transexp[i+1] <= '9') //[x]숫자
            flag = -1;
    }
    
    if(flag == -1)
        return 0;
    else
        return 1;
    
}

int isExpRight(char *exp)
{
   int i, j;
   int k;
   dot = 0;
   int num = 0;
   int open_num = 0;
   int close_num = 0;
   int length = strlen(exp);
   int error = false;
   char tok;
   Stack stack;

   init_stack(&stack);

   for (i = 0; i < length; i++)
   {
      tok = exp[i];
      if (tok == ' ')
      {
         continue;
      }
      else if (tok == '+' || tok == '-'||tok=='*'||tok=='/')
      {
         if (i == 0)
         {
            return false;
         }
         else if (i == length - 1)
         {
            return false;
         }
         else
         {
            char temp = exp[i - 1]; 
            if (tok == ' ')
            {
               continue;
            }
            else if (temp=='(')
            {
               init_stack(&stack);
               num = 0;

               if (tok == '*' || tok == '/')
               {
                  return false;
               }
               char temp2 = exp[i+1];
               if (temp2 == '(')
               {
                  i++;
                  if(onlyNumber(i, exp) == 0)
                  {
                     char temp3 = exp[i + 1];
                     if (temp3 == ')')
                     {
                        return false;
                     }
                     else if (dot >= 2)
                     {
                        return false;
                     }
                     continue;
                  }
                  else
                  {   
                     char temp3 = exp[i + 1];
                     while (temp3 != ')')
                     {
                        if (open_num != 0)
                        {
                           i++;
                           temp3 = exp[i + 1];
                        }
                        if (temp3== '(')
                        {
                           open_num++;
                        }
                        i++;
                        temp3 = exp[i + 1];
                     }
                     
                     i++;
                     char temp4 = exp[i + 1];
                     if (temp3 == ')'&&temp4==')')
                     {
                        return true;

                     }
                     return false;
                  }
               }
               else if (temp2 == '[')
               {
                  i++;
                  tok = exp[i + 1];
                  char temp3 = exp[i + 3];
                  if (temp3 == '+' || temp3 == '-'||temp3=='/'||temp3=='*')
                  {
                     return false;
                  }
                  continue;
               }
               while (temp2 != ')')
               {
                  
                  init_stack(&stack);
                  num = 0;
                  if (('0' <= temp2&&temp2 <= '9')||temp2=='.')
                  {
                     if (temp2 == '.')
                     {
                        dot++;
                        if (dot >= 2)
                        {
                           return false;
                        }
                     }
                     push(&stack, temp2);
                     i++;
                     temp2 = exp[i + 1];
                     num++;
                  }
                  else if (temp2 == '+' || temp2 == '-' || temp2 == '*' || temp2 == '/')
                  {
                     return false;
                  }
               }
               if (size(&stack) == 0)
               {
                  return false;
               }
               else if (num == size(&stack))
               {
                  continue;
               }
            }
            else if ('0' <= temp&&temp <= '9')
            {
               char temp2 = exp[i + 1];
               if ('0' <= temp2&&temp2 <= '9')
               {
                  continue;
               }
               else if (temp2 == ')')
               {
                  return false;
               }
               else if (temp2 == '(')
               {
                  i++;
                  continue;
               }
            }
            else if (temp == ')') 
            {
               char temp2 = exp[i + 1];
               if ('0' <= temp2&&temp2 <= '9')
               {
                  continue;
               }
               if (temp2 == '(')
               {
                  i++; 
                  if (onlyNumber(i, exp) == 0)
                  {
                     char temp3 = exp[i + 1];
                     if (temp3 == ')')
                     {
                        return false;
                     }
                     else if (dot >= 2)
                     {
                        return false;
                     }
                     continue;
                  }
               }
            }
            else if (temp == ']') 
            {
               char temp2 = exp[i + 1];
               if (temp2 == '(')
               {
                  i++;
                  continue;
               }
               continue;
            }
            else
            {
               return false;
            }
         }
      }
   }
   return true;
}


int onlyNumber(int i, char *exp)
{
   int length = strlen(exp);
   char tok;
   dot = 0;
   int num = 0;
   Stack stack;
   init_stack(&stack);

   for (i; i < length; i++)
   {
      tok = exp[i];
      if (tok == ' ')
      {
         continue;
      }
      else if (tok == '(')
      {
         char temp2 = exp[i - 1];
         char temp = exp[i + 1];
      
         while (temp != ')')
         {
            if (('0' <= temp&&temp <= '9')||temp=='.')
            {
               if (temp == '.')
               {
                  dot++;
                  if (dot >= 2)
                  {
                     return false;
                  }
               }
               push(&stack, temp);
               num++;
            }
            else if (temp == '+' || temp == '-' || temp == '*' || temp == '/')
            {
               num++;
            }
            i++;
            temp = exp[i + 1];
         }
         if (size(&stack) == 0)
         {
            return false;
         }
         else if (num == size(&stack))
         {
            return false;
         }
         else
         {
            continue;
         }
      }
   }
   return true;
            
}
