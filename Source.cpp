#include <iostream>
#include <string>
using namespace std;	
bool expressionCheck(string);
int paraAdder(string);
string infixToPostfix(string);
float Evaluate(string expression);
bool palindrome(string);

template<typename T>
class Stack {
private:
	T* stackPtr;
	int capacity;
	int top;

	void resize() {
		capacity *= 2;
		T* temp = new T[capacity];

		for (int i = 0; i < top; i++) {

			temp[i] = stackPtr[i];
		}
		delete[]stackPtr;
		stackPtr = nullptr;
		stackPtr = temp;
		temp = nullptr;
	};

public:
	Stack<T>() {
		capacity = 1;
		top = 0;
		stackPtr = new T[capacity];
	};
	void push(T val) {
		if (isFull()) {
			resize();
		}
		stackPtr[top++] = val;
	};
	bool isFull() {

		return (capacity == top);
	};
	bool isEmpty() {

		return (top == 0);
	};
	T pop() {

		if (!isEmpty()) {
			return stackPtr[--top];
		}

		else {
			cout << "Stack is empty" << endl;
			return -1;
		}
	};
	T show() {
		return stackPtr[top - 1];
	};

};

int main() {


	//string word = "do geese see god";

	//if (palindrome(word)) {
	//	cout << "palindrome" << endl;
	//}

	//string expression = "(2+3/{4+(5)})";

	string infix = "A*Z+X-Y*(B+C)/D";

	cout << infixToPostfix(infix) << endl;

	cout << "hello" << endl;;

	//string expression = "9/3+6";
	//string postFix = infixToPostfix(expression);

	//cout << postFix << endl;

	//float result = Evaluate(postFix);
	//cout << result << endl;

	//string expression = "()))((";

	//cout << expressionCheck(expression);
	//cout << paraAdder(expression);

	return 0;
}

bool expressionCheck(string exp) {

	Stack<char> bracket;
	char x;


	

	for (int i : exp) {

		if (i == '(' || i == '{' || i == '[') {

			bracket.push(i);
		}

		else if (i == ')' || i == '}' || i == ']' && !bracket.isEmpty() ){

			x = bracket.show();

			if (x == '(' && i == ')') {
				bracket.pop();
			}
			else if (x == '{' && i == '}') {
				bracket.pop();
			}
			else if (x == '[' && i == ']') {
				bracket.pop();
			}
			else 
				return false;
		}
	}

	return bracket.isEmpty();
}

int paraAdder(string exp) {

	Stack<char> stack;
	int total = 0;
	int inc = 0;

	for (int i = 0; i < exp.length(); i++)
	{
		if (exp[i] == '(') {

			stack.push(exp[i]);
			total++;
		}
		else if (exp[i] == ')' && !stack.isEmpty() ){

			stack.pop();
			total--;
		}
		else if (exp[i] == ')') {

			inc++;
		}
	}

	if (!stack.isEmpty()) {

		inc += total;
	}

	return inc;
}

string infixToPostfix(string exp) {

	Stack<char> opStack;

	char temp;
	string result = "";

	for (int i : exp) {

		if (i >= 40 && i <= 47) {

			if (!opStack.isEmpty()) {

				if (i == ')') {

					while (opStack.show() != '(') {

						temp = (char)opStack.pop();
						
						result = result + temp;
					}
					opStack.pop();
				}
			}

			if (!opStack.isEmpty()) {

				if (i == '+' || i == '-') {

					while ((opStack.show() != '(') && !opStack.isEmpty()) {

						temp = (char)opStack.pop();
						result = result + temp;
					}

					opStack.push(i);
					continue;
				}
			}

			if (!opStack.isEmpty()) {

				if (i == '/' || i == '*') {

					if (opStack.show() == '/' || opStack.show() == '*') {

						temp = (char)opStack.pop();
						result = result + temp;
					}

					opStack.push(i);
					continue;
				}
			}
			
			if (i != ')')
				opStack.push(i);

		}

		else {

			result = result + char(i);
		}
	}


	while (!opStack.isEmpty()) {

		temp = (char)opStack.pop();
		result = result + temp;
	}


	return result;
}

float postFixEvaluate(string expression) {

	Stack<char> opStack;
	float x;
	float a, b;

	for (int i : expression) {


		if (i == '+' || i == '-' || i == '*' || i == '/' || i == '^') {

			//x = opStack.show();

			b = opStack.pop() - '0';
			a = opStack.pop() - '0';

			switch (i) {
			case '+': {

				x = a + b;
				cout << x << endl;
				opStack.push(x + '0');

				continue;
				break;
			}
			case '-': {

				x = a - b;
				opStack.push(x + '0');

				continue;
				break;
			}			
			case '*': {

				x = a * b;
				opStack.push(x + '0');

				continue;
				break;
			}			
			case '/': {

				x = a / b;
				opStack.push(x + '0');

				continue;
				break;
			}			
			case '^': {

				x = a * b;
				opStack.push(x + '0');

				continue;
				break;
			}
			}
		}

		opStack.push(i);
	}

	return opStack.pop() - '0';
}

bool palindrome(string expression) {

	Stack<char> stack;
	char x;
	string newString = "";


	for (int i = 0; i < expression.length(); i++) {

		if (expression[i] != ' ' && expression[i] != '\'' && expression[i] != ',') {

			newString = newString + expression[i];
		}
	}

	int length = newString.length() / 2;

	for (int i = 0; i < length; i++) {

			stack.push(newString[i]);
	}

	if (newString.length() % 2 == 0) {

		for (int i = length; i < newString.length(); i++) {

			x = stack.pop();

			if (newString[i] != x) {

				return 0;
			}
		}
	}
	else {

		for (int i = length + 1; i < newString.length(); i++) {

			x = stack.pop();

			if (newString[i] != x) {

				return 0;
			}
		}
	}

	return 1;
}