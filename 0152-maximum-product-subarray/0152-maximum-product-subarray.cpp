class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int G = nums[0];
        int minprod = nums[0];
        int maxprod = nums[0];

            for (int i = 1; i < nums.size(); i++) {
            int ans = nums[i];
            int Tempmin = min({ans, ans * minprod, ans * maxprod});
            int Tempmax = max({ans, ans * minprod, ans * maxprod});


            maxprod = Tempmax;
            minprod = Tempmin;

            G = max(G, maxprod);
        }
        return G;
    }
};