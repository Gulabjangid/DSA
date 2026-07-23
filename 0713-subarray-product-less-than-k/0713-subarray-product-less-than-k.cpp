class Solution {
public:
    int numSubarrayProductLessThanK(vector<int>& nums, int k) {

        int count=0;

        for (int i = 0; i < nums.size(); i++) {

            vector<int> temp;

            long long prod = 1;

            for (int j = i; j < nums.size(); j++) {

                prod *= nums[j];

                if (prod < k) {
                    temp.push_back(nums[j]);
                    count++;
                } else {
                    break;
                }
            }
        }
        return count;
    }
};