#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <numeric>
#include <cmath>
#include <string>
#include <stack>
#include <sstream>


int main() {
    std::map<std::string, int> prio;
    prio["+"] = 1;
    prio["-"] = 1;
    prio["*"] = 2;
    prio["/"] = 2;
    prio["**"] = 3;
    prio["("] = -1;
    prio[")"] = -1;

    while (true) {
        std::string str, nstr = "", polStr = "";
        std::stringstream ss;

        std::getline(std::cin, str);
        std::stack<char> tp; tp.push(' ');

        for (int i = 0; i < str.size(); i++) {
            if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/') {
                if (i == 0 || i == str.size() - 1) {
                    std::cout << "WRONG" << std::endl;
                    return 0;
                }
                else if (str[i - 1] == '*' && str[i] == '*') {
                    nstr.pop_back();
                    nstr.push_back(str[i]);
                    nstr.push_back(' ');
                }
                else if (tp.top() == '(' && str[i] == '-') {
                    nstr.push_back(str[i]);
                }
                else {
                    nstr.push_back(' ');
                    nstr.push_back(str[i]);
                    nstr.push_back(' ');
                }
            }
            else if (47 < static_cast<int>(str[i]) && static_cast<int>(str[i]) < 58 || str[i] == '.') {
                nstr.push_back(str[i]);
            }
            else if (str[i] == '(') {
                tp.push(str[i]);
                nstr.push_back(' ');
                nstr.push_back(str[i]);
                nstr.push_back(' ');
            }
            else if (str[i] == ')') {
                if (tp.top() == ' ') {
                    std::cout << "WRONG" << std::endl;
                    return 0;
                }
                else {
                    nstr.push_back(' ');
                    nstr.push_back(str[i]);
                    nstr.push_back(' ');
                    tp.pop();
                }
            }
            else if (str[i] == ' ') {
                nstr.push_back(' ');
            }
            else {
                std::cout << "WRONG" << std::endl;
                return 0;
            }
        }

        if (tp.top() != ' ') {
            std::cout << "WRONG" << std::endl;
            return 0;
        }

        ss << nstr;

        //std::cout << nstr << std::endl;

        std::string s;
        std::stack<std::string> a;
        bool prevNum = false, prevOp = false;
        while (ss >> s) {
            //cout << s << ' ';
            if (s == "+" || s == "-" || s == "*" || s == "**" || s == "/") {
                if (!a.empty()) {
                    if ((a.top() == "+" || a.top() == "-" || a.top() == "*" || a.top() == "(" || a.top() == "**" || a.top() == "/") && prevOp) {
                        std::cout << "WRONG" << std::endl;
                        return 0;
                    }
                    while (!a.empty()) {
                        if (prio[s] > prio[a.top()]) {
                            break;
                        }
                        polStr += a.top() + " ";
                        a.pop();
                    }
                }
                a.push(s);

                prevNum = false;
                prevOp = true;
            }
            else if (s == "(" || s == ")") {
                if (s == ")") {
                    if ((a.top() == "+" || a.top() == "-" || a.top() == "*" || a.top() == "**" || a.top() == "/") && prevOp) {
                        std::cout << "WRONG" << std::endl;
                        return 0;
                    }
                    while (a.top() != "(") {
                        polStr += a.top() + " ";
                        a.pop();
                    }
                    a.pop();
                }
                else {
                    a.push(s);
                    prevNum = false;
                    prevOp = true;
                }
            }
            else {
                if (prevNum) {
                    std::cout << "WRONG" << std::endl;
                    return 0;
                }
                polStr += s + " ";

                prevNum = true;
                prevOp = false;
            }
        }

        while (!a.empty()) {
            polStr += a.top() + ' ';
            a.pop();
        }

        //cout << polStr << endl;

        std::stack<double> b;
        ss.clear();
        ss << polStr;
        while (ss >> s) {
            if (s == "+" || s == "-" || s == "*" || s == "**" || s == "/") {
                double t1, t2;
                t2 = b.top();
                b.pop();
                t1 = b.top();
                b.pop();
                if (s == "+") {
                    b.push(t1 + t2);
                }
                else if (s == "-") {
                    b.push(t1 - t2);
                }
                else if (s == "*") {
                    b.push(t1 * t2);
                }
                else if (s == "/") {
                    b.push(t1 / t2);
                }
                else if (s == "**") {
                    b.push(pow(t1, t2));
                }
            }
            else {
                b.push(stod(s));
            }
        }
        std::string res = std::to_string(b.top());
        std::cout << res << std::endl;

    }
    return 0;
}