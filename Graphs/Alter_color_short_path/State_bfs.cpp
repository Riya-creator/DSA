//make sure to push after confirmation only not when it is making in bfs expansion 
class Solution {
public:
    vector<int> shortestAlternatingPaths(int n, vector<vector<int>>& redEdges, vector<vector<int>>& blueEdges) {
//make graph from the edge -->list(to, color);
    //color== red->0, blue->1;
        vector<vector<pair<int, int>>>g(n);

        for(int i=0; i<redEdges.size(); i++){
            g[redEdges[i][0]].push_back({redEdges[i][1], 0});
        }
        for( int i=0; i< blueEdges.size(); i++){
            g[blueEdges[i][0]].push_back({blueEdges[i][1], 1});
        }

        vector<vector<int>>dis(n,vector<int>(2,-1));
//dis-->node , color_last_used_to_reach_this

        queue<pair<int, int>>q;
        q.push({0,1});
        q.push({0,0}); 
        dis[0][0]=dis[0][1]=0;

        while(!q.empty()){
            auto [a,b]= q.front();
            q.pop();

            for( int i=0; i<g[a].size(); i++){
                auto [next, nextColor]= g[a][i];

                if(nextColor== b || dis[next][nextColor]!= -1) continue;             
                dis[next][nextColor]= dis[a][b]+1;
                q.push({next, nextColor});
            }
        }

        vector<int>ans(n,-1);

        for( int i=0; i< n; i++){
            if(dis[i][0] == -1) ans[i] = dis[i][1];
            else if(dis[i][1] == -1) ans[i] = dis[i][0];
            else ans[i] = min(dis[i][0], dis[i][1]);
        }     

        return ans;
    }
};
