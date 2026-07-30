class Solution {
public:
    static bool cmp(pair<string, int> &a, pair<string, int> &b) {
        if (a.second == b.second)
            return a.first < b.first;      // lexicographically smaller first
        return a.second > b.second;        // higher frequency first
    }

    vector<string> topKFrequent(vector<string>& words, int k) {
        unordered_map<string, int> mp;

        for (string s : words)
            mp[s]++;

        vector<pair<string, int>> v;

        for (pair<string, int> p : mp)
            v.push_back(p);

        sort(v.begin(), v.end(), cmp);

        vector<string> ans;

        for (int i = 0; i < k; i++)
            ans.push_back(v[i].first);

        return ans;
    }
};