class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int count=0;
        int candiadate=0;
        for(int num:nums){
            if(count==0){
                candiadate=num;
            }
            if(num==candiadate){
                count++;
            }
            else{
            count--;
            }
        }
        return candiadate;
        
    }
};