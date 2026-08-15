class Solution {
public:
    int secondHighest(string s) {
        int frist = -1;
        int second = -1;
        for (char c : s) {
            if (isdigit(c)) {
                int val = c - '0';

                if (val > frist) {
                    second = frist;
                    frist = val;
                } else if (val > second && val != frist) {
                    second = val;
                }
            }
        }
        return second;
    }
};