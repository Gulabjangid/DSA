class Solution {
public:
    bool search(vector<vector<int>>& mat,int target,int mid){
        int st=0;
        int end=mat[mid].size()-1;
        while(st<=end){
            int midr=st+(end-st)/2;
            if(mat[mid][midr]==target){
                return true;
            }
            else if(mat[mid][midr]<target){
                st=midr+1;
            }
            else{
                end=midr-1;

            }
        }
        return false;
    }
    bool searchMatrix(vector<vector<int>>& mat, int target) {
        int m=mat.size();
        int n=mat[0].size();
        int str=0;
        int enr=m-1;
        while(str<=enr){
            int mid=str+(enr-str)/2;
            if(target>=mat[mid][0] && target<=mat[mid][n-1]){
                return search(mat,target,mid);
            }
            else if(target<mat[mid][0]){
                enr=mid-1;
            }
            else{
                str=mid+1;
            }
        }
        return false;
    }
};