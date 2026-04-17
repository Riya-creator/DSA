class Solution {
    //making the layer rotation:
    /*  
        Time  = O(n²)
        Space = O(1)
    */
public:
    void rotate(vector<vector<int>>& matrix) {
        int n = matrix.size();
        // process each layer (outer → inner)
        for(int i = 0; i < n/2; i++){
            // traverse elements in current layer
            for(int j = i; j < n - i - 1; j++){
                int temp = matrix[i][j]; 
                // left → top
                matrix[i][j] = matrix[n-1-j][i];
                // bottom → left
                matrix[n-1-j][i] = matrix[n-1-i][n-1-j];
                // right → bottom
                matrix[n-1-i][n-1-j] = matrix[j][n-1-i];
                // top (temp) → right
                matrix[j][n-1-i] = temp;
            }
        }
    }
};
