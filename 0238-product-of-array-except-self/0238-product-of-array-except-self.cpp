class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int n = nums.size();
        vector<int> r(n, 1); // Pre-allocate size n, initialized to 1
        
        // Step 1: Calculate prefix products (everything to the left)
        int leftProduct = 1;
        for(int i = 0; i < n; i++) {
            r[i] = leftProduct;
            leftProduct *= nums[i];
        }
        
        // Step 2: Calculate suffix products (everything to the right)
        int rightProduct = 1;
        for(int i = n - 1; i >= 0; i--) {
            r[i] *= rightProduct; // Combine left and right products
            rightProduct *= nums[i];
        }
        
        return r;
    }
};
