class Solution {
public:
    int kedans(vector<int>& nums){
        int cursum=nums[0];
        int maxsum=nums[0];

        for(int i=1;i<nums.size();i++){
            cursum = max(nums[i], cursum + nums[i]);
            maxsum=max(cursum,maxsum);
            if(cursum<0){
                cursum=0;
            }
        }
        return maxsum;
    }
    int Rkedans(vector<int>& nums){
        int cursum=nums[0];
        int minsum=nums[0];

        for(int i=1;i<nums.size();i++){
            cursum = min(nums[i], cursum + nums[i]);
            minsum=min(cursum,minsum);
        }
        return minsum;
    }
    int maxSubarraySumCircular(vector<int>& nums) {

        int maxsub=kedans(nums);

        if(maxsub < 0)
            return maxsub;
        
        int total=0;
        for(int i=0;i<nums.size();i++){
            total+=nums[i];
        }

        int rked=Rkedans(nums);
        int minisub=total-rked;

        int answer=max(minisub,maxsub);
        return answer;  
        
    }
};