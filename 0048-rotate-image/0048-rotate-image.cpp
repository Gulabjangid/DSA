class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {

        int n=matrix.size();

        //Transpose
        for(int i=0;i<n;i++){
            for(int j=i;j<n;j++){
                swap(matrix[i][j],matrix[j][i]);
            }
        }
        
        //reverse
        for(int i=0;i<n;i++){
            int top=0;
            int bottom=n-1;
            while(top<bottom){
                swap(matrix[i][top],matrix[i][bottom]);
                top++;
                bottom--;
            }
        }



    }
};