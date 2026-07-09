class Solution {
public:
    double findMaxAverage(vector<int>& nums, int k) {
        int left=0;
        double avg=0;
        int count=0;
        double ans=INT_MIN;

        for(int right=0;right<nums.size();right++){
            avg+=nums[right];
            count++;
            if(left<=right && count==k){
                ans=max(ans,avg/k);
                avg-=nums[left];
                left++;
                count--;
            }
        }
        return ans;
        
    }
};