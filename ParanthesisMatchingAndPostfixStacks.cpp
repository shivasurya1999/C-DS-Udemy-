/*
C++ code for paranthesis matching of (,{ and [
C++ code for converting infix to postfix expression 
C++ code for evealuating postfix expression 
*/

#include<iostream>
using namespace std;

class Stack { //Create stack with attributes size,top index and array of stack elements that are of char type 
public:
	int size;
	int top;
	char* s;
};

void push(Stack* st, char element) { //pushes element into the stack
	st->top++;
	(st->s)[st->top] = element;
}

char pop(Stack* st) { //pops element out of the stack and returns it. If stack is empty, prints there are no elements and returns null character 
	char x = '\0';
	if (st->top == -1) return x;
	else {
		x = st->s[st->top];
		st->top--;
	}
	return x;
}

bool CheckForParanthesis(Stack* st, char str[]) { //Function to check for matching paranthesis 
	for (int i = 0; i < st->size; i++) {
		if ((str[i] == '(') || (str[i] == '[') || (str[i] == '{')) {
			push(st, str[i]); //pushes left brackets into stack 
		}
		else if ((str[i] == ')') || (str[i] == ']') || (str[i] == '}')) {
			if (st->top ==-1) { //if stack is empty while looping, there are additional bracket/s to the extreme right 
				cout << "Rightmost brackets are more. Parathesis not matched." << endl;
				return 0;
			}
			else if ((str[i] - st->s[st->top] != 2)&&(str[i] - st->s[st->top] != 1)) { //Using difference in the ascii values of the brackets to know if they are matched 
				cout << "Parathesis not matched." << endl;
				return 0;
			}
			else {
				pop(st); //pops element from stack if paranthesis matched 
			}
		}
	}
	if (st->top > -1) { //if after looping, the stack still consists of elements then there are more left brackets than the right 
		cout << "Leftmost brackets are more. Paranthesis not matched." << endl;
		return 0;
	}
	return 1;
}

bool IsOperator(char c) { //checks if a character is an operator or not. Returns 1 if it is an operator. Otherwise returns 0
	if ((c == '+') || (c == '-') || (c == '*') || (c == '/')) {
		return 1;
	}
	else return 0;
}

int CheckPrecedence(char c) { //Checks and returns precedence of an operator 
	if ((c == '+') || (c == '-')) return 1;
	else if ((c == '*') || (c == '/')) return 2;
	else return 3;
}

void GivePostfixExpression(Stack* st,char str[]) { //Gives postfix expression from infix expression 
	for (int i = 0; i < st->size; i++) { //Iterate for the entire size of the string 
		if (st->top==-1) {
			push(st, str[i]); //if stack is empty push the string character into the stack 
		}
		else {
			if (CheckPrecedence(str[i]) > CheckPrecedence(st->s[st->top])) { //if precedence of the stack top element is less than the current string character 
				push(st, str[i]); //push the string character into the stack 
			}
			else {
				while (CheckPrecedence(str[i]) <= CheckPrecedence(st->s[st->top])) { //while precedence of the stack top element is greater than or equal to the current string character
					if (st->top != -1) cout << pop(st); //pop stack top element and print to screen 
					else break;
				}
				push(st, str[i]);
			}
		}
	}
	while (st->top != -1) cout << pop(st); //pop out the remaining elements from the stack and add to the output 
}

char PerformOperation(char c1, char op, char c2) { //operation 'op' is performed between c1 and c2 and the resulting value is converted into a character and returned 
	int ic1 = (int)c1-48; //converting char to int 
	int ic2 = (int)c2-48; 
	char c;
	if (op == '+') {
		cout << "adding: " << ic1 << "," << ic2 << endl;
		c = '0' + (ic1 + ic2); //converting int type result to char and returning 
		return c;
	}
	else if (op == '-') {
		cout << "subtracting: " << ic1 << "," << ic2 << endl;
		c = '0' + (ic1 - ic2);
		return c;
	}
	else if (op == '*') {
		cout << "multiplying: " << ic1 << "," << ic2 << endl;
		c = '0' + (ic1 * ic2);
		return c;
	}
	else if (op == '/') {
		cout << "Dividing: " << ic1 << "," << ic2 << endl;
		c = '0' + (ic1 / ic2);
		return c;
	}
	
}

int EvaluatePostfix(char postfix[],int length) { //given the postfix expression and the length of the expression, it is evaluated and the result is returned 
	Stack* st;
	st = new Stack;
	st->size = length-1;
	st->top = -1;
	st->s = new char[st->size];
	for (int i = 0; i<length-1; i++) {
		if (st->top == -1) { //if stack is empty, the operand is pushed into the stack 
			push(st, postfix[i]);
		}
		else if (IsOperator(postfix[i])) { //if operator is found pop out two elements from the stack and perform operation between them 
			char c1 = pop(st);
			char c2 = pop(st);
			char op = postfix[i];
			int res = PerformOperation(c2, op, c1); //Note that after c1 and c2 are popped out from the stack, operation needs to be performed between c2 and c1 (not c1 and c2) for getting the result 
			push(st, res); //pushing the result into the stack 
		}
		else {
			push(st, postfix[i]); //if postfix[i] is not an operator, it is pushed into the stack 
		}
	}
	return (pop(st)-'0'); //returning the result after subtracting the ascii value of 0 fromm the integer character ascii value 
}

int main() {
	//char str[] = "{[{(a+b)*(c+d)}]"; //Uncomment this line for paranthesis matching  
	char str[] = "3*5+6/2-4";
	Stack *st; //create stack
	st = new Stack;
	st->size = sizeof(str)/sizeof(char);
	st->s = new char[st->size]; //allocates memory to the stack array 
	st->top = -1; //by default the top index of an empty stack is -1 
	//if (CheckForParanthesis(st, str)) cout << "Paranthesis matched." << endl;  //Uncomment this line for paranthesis matching 
	GivePostfixExpression(st, str);
	/*char postfix[] = "35*62/+4-";*/
	char postfix[] = "234*+82/-";
	cout <<endl<<"The evaluation of the postfix expression is: " << EvaluatePostfix(postfix,sizeof(postfix)/sizeof(char));
}
