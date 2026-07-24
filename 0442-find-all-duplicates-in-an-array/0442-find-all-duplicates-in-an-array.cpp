class Solution {
public:
    vector<int> findDuplicates(vector<int>& nums) {
        unordered_set<int> visited;
        vector<int> ans;
        for(int num:nums){
            if (visited.count(num)){
                ans.push_back(num);
            }
            visited.insert(num);
        }
        return ans;

        
    }
};