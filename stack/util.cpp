#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include "stack.hpp"

using namespace std;

bool checkParentheses(const string& line, const vector<pair<char,char>>& pairs){
    //TODO
    Stack<char> parentheses;

    // 빈 string 도 true로 return.
    if (line.length() == 0)
    {
        return true;
    }
    
    for (auto c : line)
    {
        // time complexity 괜찮나?
        for (auto p : pairs)
        {   
            if (c == p.first)
            {   
                parentheses.push(c);
            } else if(c == p.second) {
                
                if (parentheses.isEmpty() || parentheses.top() != p.first)
                {
                    return false;
                }
                parentheses.pop();
                
            } else {
                // 그냥 지나가
            }
        }
        
    }
    
    if (!parentheses.isEmpty())
    {
        return false;
    }
    

    return true;
}

bool isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

int pref(char c) {

    if (c == '*' || c == '/')
    {
        return 2;
    }

    if (c == '+' || c == '-')
    {
        return 1;
    }

    // '(' 일 경우.
    return 0;
}

string infixToPostfix(const string& line) {

    //Stack<float> numbers;
    Stack<char> operators;
    
    string postfix_notation;
    size_t sz = 0;
    size_t count = 0;

    for (int i = 0; i < int(line.length()); i++)
    {
        char c = line[i];
        // number 일 경우 바로 stack에 넣는다.
        // -2 같은 경우도 처리할 수 있어야함.
        if (c == '(') {
            operators.push(c);
            sz++;
        } else if (c == ')') {

            while (operators.top() != '(')
            {
                postfix_notation.push_back(operators.top());
                postfix_notation.append(" ");
                operators.pop();
            }
            operators.pop();
            sz++;
        } else if (isOperator(c)) { // 연산자들

            // unary operator ( 부호 )
            if ((c == '+' || c == '-') && (line[i - 1] == '('))
            {
                count += sz;
                float num = stof(line.substr(i), &sz);
                i = count + sz - 1;

                postfix_notation.append(to_string(num));
                postfix_notation.append(" ");
                sz--;
            } else if (operators.isEmpty())
            {
                operators.push(c);
            } else if (pref(c) > pref(operators.top()))
            {
                operators.push(c);
            } else {

                while (pref(c) <= pref(operators.top()))
                {
                    postfix_notation.push_back(operators.top());
                    postfix_notation.append(" ");
                    operators.pop();
                }
                operators.push(c);
            }
            sz++;
        } else { // 숫자
            // 현재 숫자가 있는 index
            count += sz;
            float num = stof(line.substr(count), &sz);
            // 숫자가 끝나는 index
            i = count + sz - 1;
            
            postfix_notation.append(to_string(num));
            postfix_notation.append(" ");
        }
        
    }

    while (!operators.isEmpty())
    {
        postfix_notation.push_back(operators.top());
        postfix_notation.append(" ");
        operators.pop();
    }
    
    cout << postfix_notation << endl;
    return postfix_notation;
}


float calculate(const string& line){
    //TODO
    Stack<float> numbers;
    //Stack<char> operators;

    string postfix_notation = infixToPostfix(line);
    size_t sz = 0;
    size_t count = 0;
    
    for (int i = 0; i < int(postfix_notation.length()); i++)
    {
        if (postfix_notation[i] == ' ')
        {
            sz++;
        } else if (isOperator(postfix_notation[i])) {

            // 부호를 나타내는 + 나 - 인 경우,
            if ((postfix_notation[i] == '+' || postfix_notation[i] == '-') && (isdigit(postfix_notation[i+1]) || postfix_notation[i+1] == '.'))
            {
                count += sz;
                float num = stof(postfix_notation.substr(count), &sz);
                i = count + sz - 1;

                numbers.push(num);
            } else {
                float n1 = numbers.pop();
                float n2 = numbers.pop();

                float a;

                switch (postfix_notation[i])
                {
                case '+':
                    a = n2 + n1;
                    break;
                
                case '-':
                    a = n2 - n1;
                    break;

                case '*':
                    a = n2 * n1;
                    break;

                case '/':
                    a = n2 / n1;
                    break;

                default:
                    break;
                }

                numbers.push(a);
                sz++;
                }
            
        } else {
            count += sz;
            float num = stof(postfix_notation.substr(count), &sz);
            i = count + sz - 1;
            
            numbers.push(num);
        }
    }
    
    float answer = numbers.top();
    numbers.pop();

    return answer;
}