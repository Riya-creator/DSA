// this sis correct logically: but recursion stalk overflow as well as we get many places visited before the one needed in actual
class Solution {
    bool search( vector<vector<int>>& matrix, int target, int i, int j, vector<vector<bool>>&visit){
        if( i ==  (int)matrix.size()|| j== (int) matrix[0].size()) return false;
        if( visit[i][j]) return false;
        if( matrix[i][j] == target) return  true;
        if( matrix[i][j]> target) return false;
        visit[i][j] = true;
        return search(matrix, target, i+1, j, visit) ||search(matrix, target, i, j+1, visit);
    }
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        vector<vector<bool>> visit(matrix.size(), vector<bool>(matrix[0].size(), false));
        return search ( matrix, target, 0, 0, visit);
    }
};
