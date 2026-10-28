#include <iostream>
#include <string>
#include <stack>

using namespace std;

bool isOperand(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9');
}

int precedence(char op) {
    if (op == '^') return 3;
    if (op == '*' || op == '/') return 2;
    if (op == '+' || op == '-') return 1;
    return 0;
}

bool isRightAssociative(char op) {
    return op == '^';
}

string infixToPostfix(const string &s) {
    string result = "";
    stack<char> st;

    for (size_t i = 0; i < s.length(); i++) {
        char c = s[i];
        if (isOperand(c)) {
            result += c;
        } else if (c == '(') {
            st.push(c);
        } else if (c == ')') {
            while (!st.empty() && st.top() != '(') {
                result += st.top();
                st.pop();
            }
            if (!st.empty()) {
                st.pop();
            }
        } else {
            while (!st.empty() && st.top() != '(') {
                if (precedence(c) < precedence(st.top()) ||
                   (precedence(c) == precedence(st.top()) && !isRightAssociative(c))) {
                    result += st.top();
                    st.pop();
                } else {
                    break;
                }
            }
            st.push(c);
        }
    }

    while (!st.empty()) {
        result += st.top();
        st.pop();
    }

    return result;
}

int main() {
    string s;
    while (cin >> s) {
        cout << infixToPostfix(s) << endl;
    }
    return 0;
}
