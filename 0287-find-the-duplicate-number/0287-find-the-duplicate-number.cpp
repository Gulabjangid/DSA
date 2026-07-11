class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        unordered_set<int> mp;
        for(int val:nums){
            if(mp.find(val)!=mp.end()){
                return val;
            }
            mp.insert(val);
        }
        return -1;

        
    }
};