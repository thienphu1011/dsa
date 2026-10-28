#include <iostream>
#include <string>
#include <stack>

using namespace std;

bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

string postfixToInfix(const string &postfix) {
    stack<string> st;

    for (size_t i = 0; i < postfix.length(); i++) {
        char c = postfix[i];
        if (isOperator(c)) {
            if (st.size() < 2) return "";
            string op2 = st.top();
            st.pop();
            string op1 = st.top();
            st.pop();
            string exp = "(" + op1 + c + op2 + ")";
            st.push(exp);
        } else {
            st.push(string(1, c));
        }
    }

    if (!st.empty()) {
        return st.top();
    }
    return "";
}

int main() {
    string s;
    while (cin >> s) {
        cout << postfixToInfix(s) << endl;
    }
    return 0;
}
