class Solution {
public:
    int networkBecomesIdle(vector<vector<int>>& edges, vector<int>& p) {
        int n= p.size(),ans=0 ;
        vector<vector<int>>adj(n);

        for( int i=0; i< edges.size(); i++){
            adj[edges[i][0]].push_back(edges[i][1]);
            adj[edges[i][1]].push_back(edges[i][0]);
        }

        vector<int>dis(n, -1);
        queue<int>q;
        q.push(0);
        dis[0]=0;

        while(!q.empty()){
            int ind= q.front();
            q.pop();

            for( int i=0; i< adj[ind].size(); i++){
                if( dis[adj[ind][i]]!=-1) continue;
                dis[adj[ind][i]]= dis[ind]+1;
                q.push(adj[ind][i]);
            }
        }

        for( int i=1; i< n; i++){
            int fd= 2*dis[i];
            if(p[i]>= fd ) ans= max(ans, fd );
            else{
                //only care fro last message arrival time taken
                int last= ((fd-1)/p[i])*p[i];
                ans= max(ans, last+fd);
            }
        }
        return ans+1;
//+1 because network becomes idle after last reply is received
    }
};
//time n space: O(n+e)
