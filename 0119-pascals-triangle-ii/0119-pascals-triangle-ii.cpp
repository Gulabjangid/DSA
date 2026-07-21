class Solution {
public:
    vector<int> getRow(int rowIndex) {
   
        vector<vector<int>> result;
        for (int i = 0; i <=rowIndex; i++) {
            vector<int> row(i + 1, 1); // Fill row with 1s
            for(int j=1;j<i;j++){
                row[j]=result[i-1][j-1]+result[i-1][j];
            }
            result.push_back(row);
        }
        vector<int>ans;

        for(int i=0;i<rowIndex+1;i++){
            ans.push_back(result[rowIndex][i]);
        }
        //      for (int i = 0; i < result[rowIndex].size(); i++) {
        //     ans.push_back(result[rowIndex][i]);
        // }

        return ans;
    }
};