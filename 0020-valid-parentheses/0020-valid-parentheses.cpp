class Solution {
public:
    stack<char> s;
    bool isValid(string string) {
        for (int i = 0; i < string.length(); i++) {
            if (string[i] == '(' || string[i] == '{' || string[i] == '[') {
                s.push(string[i]);
            } else {
                if (s.size() == 0) {
                    return false;
                }
                if ((s.top() == '(' && string[i] == ')') ||
                    (s.top() == '[' && string[i] == ']') ||
                    (s.top() == '{' && string[i] == '}')) {
                    s.pop();
                } else {
                    return false;
                }
            }
        }
        return s.size() == 0;
    }
};