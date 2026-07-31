class Solution {
public:
    void expand(string &s, int left, int right, int &start, int &maxLen) {
        int n = s.size();

        while (left >= 0 && right < n && s[left] == s[right]) {
            int currLen = right - left + 1;

            if (currLen > maxLen) {
                maxLen = currLen;
                start = left;
            }

            left--;
            right++;
        }
    }

    string longestPalindrome(string s) {
        int n = s.size();

        if (n <= 1)
            return s;

        int start = 0;
        int maxLen = 1;

        for (int i = 0; i < n; i++) {
            expand(s, i, i, start, maxLen);      // Odd length
            expand(s, i, i + 1, start, maxLen);  // Even length
        }

        return s.substr(start, maxLen);
    }
};