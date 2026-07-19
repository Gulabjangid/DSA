class Solution {
public:
    int trap(vector<int>& height) {
        int n = height.size();
        if (n <= 2)
            return 0;
        int lmax = height[0];
        int rmax = height[n - 1];

        int low = 1;
        int high = n - 2;

        int ans = 0;

        while (low <= high) {
            lmax = max(lmax, height[low]);
            rmax = max(rmax, height[high]);

            if (lmax < rmax) {
                ans += lmax - height[low];
                low++;

            } else {
                ans += rmax - height[high];
                high--;
            }
        }
        return ans;
    }
};