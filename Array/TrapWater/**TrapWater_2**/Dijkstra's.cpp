class Solution {
/* here we get to know that dp woon't work here as we need to max from the gloal solution not the local minimum or so
here we cann't make the prefix max arrays then will make the PATHS THAT MAY BEND 
5 5 5 5
5 1 5 5
5 2 2 1
5 5 5 5
*/
public:
//DIJKSTRA's algo
    int trapRainWater(vector<vector<int>>& heightMap) {
        int n= heightMap.size(), m= heightMap[0].size(), water =0;
        vector<vector<bool>>vis(n, vector<bool>(m, false));
        priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>>pq;
        //get smallest 'HEIGHT' reached till now as then only 'CONSTRAINT FLOW' occur correctly
        //as in case of moving on smallest path if got anything large then switch path right

        for( int i=0; i< n; i++){
            for( int j=0;j< m; j++){
                if( i==0 ||j==0 ||i==n-1 || j==m-1){
                    vis[i][j]=true;
                    pq.push({heightMap[i][j], {i, j}});
                }
            }
        }
//taking values of boundaries to take the lowest possible constraint

        vector<pair<int, int>>direction= {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};

        while(!pq.empty()){
            auto [height, dd]= pq.top();
            int x= dd.first, y= dd.second;
            pq.pop();
            
            for( auto [dx, dy]: direction ){
                int nx= x-dx, ny= y- dy;

                if( nx >=0 && nx< n && ny>= 0 && ny<m && !vis[nx][ny]){
                    vis[nx][ny]= true;

                    if( heightMap[nx][ny]< height){
                        water+= height- heightMap[nx][ny];
                    }

                    pq.push({max(height, heightMap[nx][ny]), {nx, ny}});
//pushing constraint of the max height possible form this index to the next ones
//then make traverse from the lowest height from these
                }
            }
        }
        return water;
    }
};
