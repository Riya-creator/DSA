class Solution {
    //time:O(n+m) n space : O(1)
    // property of increasing is used
    //from / diagonal ends only we can use as then only we have option to move to both greater n smaller else from \ we can only reach greater or smaller
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int i=matrix.size()-1 , j=0;
        while( i>=0 && j<matrix[0].size()){
            if( matrix[i][j]== target) return true;
            if( matrix[i][j]>= target){
                i--;
            }else j++;
        }
        return false;
    }
};
