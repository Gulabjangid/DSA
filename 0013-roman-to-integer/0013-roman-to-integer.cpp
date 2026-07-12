class Solution {
public:
    int romanToInt(string s) {

        static 
        unordered_map<char, int> mp = {{'I', 1},   {'V', 5},   {'X', 10},
                                       {'L', 50},  {'C', 100}, {'D', 500},
                                       {'M', 1000}};
        int prev = 0, total = 0;
        for (int i = s.length() - 1; i >= 0; i--) {
            int curr = mp[s[i]];

            if (curr < prev)
                total -= curr;
            else
                total += curr;

            prev = curr;
        }

        return total;
    }
};