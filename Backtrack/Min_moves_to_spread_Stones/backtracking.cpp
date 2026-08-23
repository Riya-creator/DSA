class Solution {
    //fix destination in each move as target is to fill 0 only
    //time: O(n!) but here fixed so O(1)
    //space::O(1)
public:
    int minimumMoves(vector<vector<int>>& grid) {
        //think: select both (from n where) 
        int r=-1, c=-1;
        for( int i=0; i<grid.size(); i++){//first 0 found 
            for(int j=0; j<grid[0].size(); j++){
                if(grid[i][j]==0) {
                    r=i;
                    c= j;
                    break;
                }
            }
        }

        if(r==-1){
            return 0;
        }

        int ans =1e9;

        for(int i=0; i<grid.size(); i++){
            for(int j=0; j<grid[0].size(); j++){
                if(grid[i][j]>1){
                    int steps= abs(i-r) +abs(c-j);//manhattan distance 
                    //equal to steps moved to reach
                    grid[i][j]--;
                    grid[r][c]++;
                    ans = min(ans, minimumMoves(grid) + steps);
                    grid[i][j]++;
                    grid[r][c]--;
                }
            }
        }
        return ans;
    }
};
