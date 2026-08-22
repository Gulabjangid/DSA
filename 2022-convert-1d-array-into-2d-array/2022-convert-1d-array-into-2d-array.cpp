class Solution {
public:
    vector<vector<int>> construct2DArray(vector<int>& original, int m, int n) {

        if(m*n!=original.size())  return{};

        
        vector<vector<int>> ans(m, vector<int>(n));

        int row=0;
        int col=0;

        for(int i=0;i<original.size();i++){
            ans[row][col]=original[i];
            col++;
            if(col==n){
                col=0;
                row++;
            }
        }
        return ans ;




        
    }
};