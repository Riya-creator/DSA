class Solution {
    bool check( vector<vector<char>>&board, string& word, int ind, int r, int c){
        if( ind== word.size()) return true;

        if(r>= board.size() || c>= board[0].size() || r<0 ||c<0 || word[ind]!= board[r][c]) return false;

        if( board[r][c]==word[ind]){
            char cdd= board[r][c];
            board[r][c]= '#';

            if( check(board, word, ind+1, r+1, c) )return true;
            if( check( board, word, ind+1, r, c+1)) return true;
            if(check(board, word, ind+1, r, c-1)) return true;
            if(check(board, word, ind+1, r-1, c)) return true;

            board[r][c]= cdd;
        }

        return false;
    }
public:
    bool exist(vector<vector<char>>& board, string &word) {
        //Optimization1: if words in string is more then return false;
        if( word.size()> board.size()* board[0].size()) return false;

        //optimization2: frequency Pruning
        //frequency of char in the word is more than in board then false
        unordered_map<char, int>b,w;
        for(auto &row:board) 
            for(char &col: row) b[col]++;
        for( char wf: word) w[wf]++;
        for(auto &[ch, count]:w){
            if(b[ch]<count) return false;
        }
        //optimizationn3: directional prunnning 
        //rarest character in start
        if(b[word[0]]>b[word[word.size()-1]])
        reverse(word.begin(), word.end());

        for( int i=0; i< board.size(); i++){
            for( int j=0; j< board[0].size(); j++){
                if( check(board, word, 0, i, j)) return true;
            }
        }

        return false;
    }
};
//Time Complexity: Still O(M *N*3^L) in the worst case
// Space Complexity:O(L)
