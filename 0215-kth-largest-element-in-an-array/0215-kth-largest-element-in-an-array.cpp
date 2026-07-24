class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        sort(nums.begin(),nums.end());
        int kth=0;
        for(int i=0;i<=nums.size()-k;i++){
            kth=nums[i];
        }
        return kth;
        
    }
};