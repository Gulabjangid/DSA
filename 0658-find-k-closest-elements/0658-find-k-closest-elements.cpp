class Solution {
public:
    vector<int> findClosestElements(vector<int>& arr, int k, int x) {

        vector<vector<int>> ans;
        for (int i = 0; i < arr.size(); i++) {
            int distance = abs(x - arr[i]);
            ans.push_back({distance, arr[i]});
        }

        sort(ans.begin(), ans.end());

        vector<int> output;

        for (int i = 0; i < k; i++) {
            output.push_back(ans[i][1]);
        }
sort(output.begin(),output.end());
        return output;
    }
};