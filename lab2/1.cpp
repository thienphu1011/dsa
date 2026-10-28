#include <iostream>
#include <string>
#include <stack>

using namespace std;

bool isMatching(char open, char close) {
    if (open == '(' && close == ')') return true;
    if (open == '{' && close == '}') return true;
    if (open == '[' && close == ']') return true;
    return false;
}

bool isBalanced(const string &s) {
    stack<char> st;
    for (char c : s) {
        if (c == '(' || c == '{' || c == '[') {
            st.push(c);
        } else if (c == ')' || c == '}' || c == ']') {
            if (st.empty()) {
                return false;
            }
            char top = st.top();
            st.pop();
            if (!isMatching(top, c)) {
                return false;
            }
        }
    }
    return st.empty();
}

int main() {
    string s;
    while (cin >> s) {
        if (isBalanced(s)) {
            cout << "Balanced" << endl;
        } else {
            cout << "Not balanced" << endl;
        }
    }
    return 0;
}
