class Solution {
public:
    bool isvalid(vector<vector<int>>& grid,int n, int row, int col, int val) {

        
        if(row>=n||row<0||col>=n||col<0||grid[row][col]!=val){

            return false;

        }

        if(val==(n*n)-1){

            return true;

        }
        
        int ans1=isvalid(grid,n,row-2,col+1,val+1);
        int ans2=isvalid(grid,n,row-2,col-1,val+1);
        int ans3=isvalid(grid,n,row+2,col+1,val+1);
        int ans4=isvalid(grid,n,row+2,col-1,val+1);
        int ans5=isvalid(grid,n,row-1,col+2,val+1);
        int ans6=isvalid(grid,n,row+1,col+2,val+1);
        int ans7=isvalid(grid,n,row-1,col-2,val+1);
        int ans8=isvalid(grid,n,row+1,col-2,val+1);

        return ans1||ans2||ans3||ans4||ans5||ans6||ans7||ans8;


    }
    bool checkValidGrid(vector<vector<int>>& grid) {
        int n = grid.size();
        return isvalid(grid,n, 0, 0, 0);
    }
};
