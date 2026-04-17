class Solution {
//very beautifully made :
//time:O(n^2) {as transpose:n2/2 then same for the reverse}
//can check by hand movement 
public:
    void rotate(vector<vector<int>>& matrix) {
        if( matrix.size()==1) return ;
        int n=matrix.size();
//transpose + reverse rows--->rotation 90 degree
        for( int i=0; i< n; i++){
            for( int j=i+1; j<n; j++){
                swap(matrix[i][j], matrix[j][i]);
            }
        }

        for(int i=0; i< n; i++){
            for(int j=0; j< n/2; j++){
                swap(matrix[i][n-1-j], matrix[i][j]);
            }
        }
    }
};
