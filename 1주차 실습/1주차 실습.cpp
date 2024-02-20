#include<iostream>
using namespace std;

template <typename T>
class Stack {
private:
    int top_idx, capacity;
    T* stack;
public:
    Stack(int size) {//생성자
        capacity = size;
        stack = new T[capacity];
        top_idx = -1;
    };
    ~Stack() { delete stack; };//소멸자
    bool isFull() {
        if (top_idx == capacity - 1) return 1;
        else return 0;
    };
    bool isEmpty() {
        if (top_idx == -1)return 1;
        else return 0;
    };
    T pop() {
        if (isEmpty() == 1)//예외
            return NULL;
        top_idx--;
        return stack[top_idx + 1];
    };
    T top() {
        if (isEmpty() == 1)
            return NULL;
        return stack[top_idx];
    };
    void push(T element) {
        if (isFull() == 1)
            return;
        top_idx++;
        stack[top_idx] = element;
    };
};

int getOpPriority(char op) {
    switch (op) {
    case '(': case ')': return 0;
    case '+': case '-': return 1;
    case '*': case '/': return 2;
    }
    return -1;
}

// 중위표기식을 후위표기식으로 변환하는 함수
string infixToPostfix(string s) {
    Stack<char> stack(100);         // 연산자를 담는 stack
    string postfixExpression = "";  // 후위표기식 결과를 저장하는 변수

    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/') {  // 연산자
            if (stack.isEmpty()) {
                stack.push(s[i]);
            }
            else {
                // 현재 연산자 우선순위보다 stack의 top 연산자 우선순위가 높을때 까지 pop 후 현재 연산자 push
                while (!stack.isEmpty() && getOpPriority(s[i]) <= getOpPriority(stack.top())) {
                    postfixExpression.push_back(stack.pop());
                }
                stack.push(s[i]);
            }
        }
        else if (s[i] == '(') {  // 왼쪽괄호
            stack.push(s[i]);
        }
        else if (s[i] == ')') {  // 오른쪽괄호
            // 왼쪽괄호 위에 쌓여있는 모든 연산자 pop 후 왼쪽괄호 삭제
            while (stack.top() != '(') {
                postfixExpression.push_back(stack.pop());
            }
            stack.pop();
        }
        else {  // 피연산자
            postfixExpression.push_back(s[i]);
        }
    }
    // 스택의 남은 연산자를 모두 pop
    while (!stack.isEmpty()) {
        postfixExpression.push_back(stack.pop());
        // 코드 작성
    }
    return postfixExpression;
}

double calculatePostfix(string s) {
    Stack<int> stack(100);               // 피연산자 stack

    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/') {  // 연산자
            int a = stack.pop();
            int b = stack.pop();
            if (s[i] == '+') {
                stack.push(a + b);
            }
            else if (s[i] == '-') {
                stack.push(b - a);
            }
            else if (s[i] == '*') {
                stack.push(a * b);
            }
            else {
                stack.push(b / a);
            }
        }
        else {
            stack.push(s[i] - '0');
        }
    }

    return stack.top();
}

int main() {
    string s = infixToPostfix("6+7*((4/2)+1)*2");
    cout << s << endl;
    double a = calculatePostfix(s);
    cout << a << endl;

    return 0;
}