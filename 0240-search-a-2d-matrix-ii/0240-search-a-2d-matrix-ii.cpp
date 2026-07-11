class Solution {
public:
    bool searchMatrix(vector<vector<int>>& mat, int tar) {
        if (mat.empty() || mat[0].empty())
            return false; // Handle empty edge case

        int row = mat.size();
        int col = mat[0].size();

        int r = 0;
        int c = col-1;

        while (r < row && c >= 0) {
            if (mat[r][c] == tar) {
                return true;
            } else if (mat[r][c] > tar) {
                c--;
            } else {
                r++;
            }
        }
        return false;
    }
};