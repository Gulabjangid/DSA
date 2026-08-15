class Solution {
public:
    int secondHighest(string s) {

        int second = -1;
        int largest = -1;

        for (char c : s) {
            if (isdigit(c)) {
                int digit = c - '0';

                if (digit > largest) {
                    second = largest;
                    largest = digit;
                }
                 else if(digit > second && digit != largest){
                    second = digit;
                }
            }
        }
        return second;
    }
};