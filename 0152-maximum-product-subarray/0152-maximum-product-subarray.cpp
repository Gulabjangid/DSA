class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int maxp=nums[0];
        int minp=nums[0];
        int ans=nums[0];
        for(int i=1;i<nums.size();i++){
            int num=nums[i];
            int  newminp=min({num,minp*num,maxp*num});
            int newmaxp=max({num,maxp*num,minp*num});

            maxp=newmaxp;
            minp=newminp;
            
            ans=max(ans,maxp);

        }
        return ans ;
        
    }
};