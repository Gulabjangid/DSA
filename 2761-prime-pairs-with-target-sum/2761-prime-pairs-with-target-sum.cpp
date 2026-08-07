class Solution {
public:
    vector<vector<int>> findPrimePairs(int n) {

        // Storing the Primes in set first
        unordered_map<int,int> mp;

        vector<bool> isPrime(n, true);
        if (n <= 2)
            return {};
int count=0;
        for (int i = 2; i < n; i++) {
            if (isPrime[i]) {
                
                mp.insert({i,count});
                count++;
                for (int j = i * 2; j < n; j = j + i) {
                    isPrime[j] = false;
                }
            }
        }

        // Exracting the pairs
        vector<vector<int>> ans;
        for (auto it : mp) {
            int first = it.first;
            int second = n - first; //irst+second=n

            if (second >= first && mp.count(second)) {
                ans.push_back({first, second});
            }
        }
        sort(ans.begin(),ans.end());
        return ans;
    }
};