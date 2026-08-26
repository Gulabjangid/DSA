class Solution {
public:
    vector<int> findMissingAndRepeatedValues(vector<vector<int>>& grid) {
        long long n = grid.size();
        long long N = n * n;

        long long sum = 0, sum2 = 0;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                long long val = grid[i][j];
                sum += val;
                sum2 += val * val;
            }
        }

        long long S  = (N * (N + 1)) / 2;
        long long S2 = (N * (N + 1) * (2 * N + 1)) / 6;

        long long diff = sum - S;              // x - y
        long long sumxy = (sum2 - S2) / diff;  // x + y

        long long x = (diff + sumxy) / 2;      // repeated
        long long y = x - diff;                // missing

        return {(int)x, (int)y};
    }
};