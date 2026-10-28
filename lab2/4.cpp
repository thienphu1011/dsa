#include <iostream>
#include <string>
#include <vector>
#include <stack>

using namespace std;

bool isOperator(const string &token) {
    return token == "+" || token == "-" || token == "*" || token == "/";
}

double applyOp(double op1, double op2, const string &op) {
    if (op == "+") return op1 + op2;
    if (op == "-") return op1 - op2;
    if (op == "*") return op1 * op2;
    if (op == "/") return op1 / op2;
    return 0;
}

vector<string> tokenize(const string &line) {
    vector<string> tokens;
    size_t i = 0;
    while (i < line.length()) {
        while (i < line.length() && (line[i] == ' ' || line[i] == '\t')) {
            i++;
        }
        if (i >= line.length()) break;
        size_t start = i;
        while (i < line.length() && line[i] != ' ' && line[i] != '\t') {
            i++;
        }
        tokens.push_back(line.substr(start, i - start));
    }
    if (tokens.size() == 1 && tokens[0].length() > 1 && !(tokens[0][0] >= '0' && tokens[0][0] <= '9')) {
        vector<string> singleChars;
        for (size_t k = 0; k < tokens[0].length(); k++) {
            singleChars.push_back(string(1, tokens[0][k]));
        }
        return singleChars;
    }
    return tokens;
}

double parseNumber(const string &s) {
    double res = 0.0;
    size_t i = 0;
    bool negative = false;
    if (!s.empty() && s[0] == '-') {
        negative = true;
        i = 1;
    }
    while (i < s.length() && s[i] >= '0' && s[i] <= '9') {
        res = res * 10.0 + (s[i] - '0');
        i++;
    }
    if (i < s.length() && s[i] == '.') {
        i++;
        double factor = 0.1;
        while (i < s.length() && s[i] >= '0' && s[i] <= '9') {
            res += (s[i] - '0') * factor;
            factor *= 0.1;
            i++;
        }
    }
    return negative ? -res : res;
}

int main() {
    string line;
    while (getline(cin, line)) {
        if (line.empty()) continue;
        vector<string> tokens = tokenize(line);
        if (tokens.empty()) continue;
        stack<double> st;
        for (int i = int(tokens.size()) - 1; i >= 0; i--) {
            if (isOperator(tokens[i])) {
                if (st.size() < 2) break;
                double op1 = st.top();
                st.pop();
                double op2 = st.top();
                st.pop();
                st.push(applyOp(op1, op2, tokens[i]));
            } else {
                st.push(parseNumber(tokens[i]));
            }
        }
        if (!st.empty()) {
            cout << st.top() << endl;
        }
    }
    return 0;
}
