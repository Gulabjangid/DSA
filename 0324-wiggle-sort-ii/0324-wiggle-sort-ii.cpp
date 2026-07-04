class Solution {
public:
    void wiggleSort(vector<int>& nums) {

        int n=nums.size();

        sort(nums.begin(), nums.end());
        int st = 0;
        int end = nums.size() - 1;
        int mid = (n+1) / 2;
        vector<int> A(mid);
        vector<int> B(n - mid);
        for (int i = 0; i < mid; i++) {
            A[i] = nums[i];
        }
        for (int i = mid; i < n; i++) {
            B[i-mid] = nums[i];
        }
        reverse(B.begin(), B.end());
        reverse(A.begin(),A.end());
        int a = 0, b = 0;
        for (int i = 0; i < n; i++) {
            if (i % 2 == 0) {
                nums[i] = A[a++];
            } else {
                nums[i] = B[b++];
            }
        }
    
    }
};