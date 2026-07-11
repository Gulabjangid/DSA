class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& mat) {
        int row = mat.size();
        int col = mat[0].size();
        vector<int> ans;
        int str = 0;
        int enr = row - 1;
        int stc = 0;
        int enc = col - 1;

        while (str <= enr && stc <= enc) {
            // right-->
            for (int i = stc; i <= enc; i++) {
                ans.push_back(mat[str][i]);
            }
            str++;
            // down
            for (int i = str; i <= enr; i++) {
                ans.push_back(mat[i][enc]);
            }
             enc--;
            // left
            if (str <= enr) {
                for (int i = enc; i >= stc; i--) {
                    ans.push_back(mat[enr][i]);
                }
            }
            // up
            if (stc <= enc) {
                for (int i = enr-1; i >= str; i--) {
                    ans.push_back(mat[i][stc]);
                }
            }
            stc++;

           
            enr--;
        }
        return ans;
    }
};