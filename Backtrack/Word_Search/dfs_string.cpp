class Solution {
    bool check( vector<vector<char>>&board, string& word, int ind, int r, int c, vector<vector<bool>>&dp){
        if( ind== word.size()) return true;
        if(r== board.size() || c== board[0].size() || r==-1 ||c==-1) return false;
        if(dp[r][c]) return false;
        if( board[r][c]==word[ind]){
            dp[r][c]= true;
            if( check(board, word, ind+1, r+1, c, dp) )
            return true;
            if( check( board, word, ind+1, r, c+1, dp)) return true;
            if(check(board, word, ind+1, r, c-1, dp)) return true;
            if(check(board, word, ind+1, r-1, c, dp)) return true;
            dp[r][c]= false;
        }
        return false;
    }
public:
    bool exist(vector<vector<char>>& board, string &word) {
        vector<vector<bool>>dp(board.size(), vector<bool>(board[0].size(), false));
        for( int i=0; i< board.size(); i++){
            for( int j=0; j< board[0].size(); j++){
                if( check(board, word, 0, i, j, dp)) return true;
            }
        }
        return false;
    }
};
//Time Complexity: O(N *M *3^L), where N * M is the board size and L is the length of the word. We have 3 choices at each step (excluding the cell we just came from).
//Space Complexity: O(L + (N * M)). You use O(L) for the recursion stack and O(N * M) for the dp (visited) matrix.
