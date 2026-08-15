class Solution {
    int LOG=1 ;// to store max jumps from a node 
    int find(vector<vector<int>>& jumps, int u, int v) {
        if(u == v) // same node
            return 0;

        int ans = 0;

        for(int k = LOG - 1; k >= 0; k--) {
            if(jumps[u][k] < v) {// stoping at one step way from destination as then we can have a safety check for the ans
                u = jumps[u][k];
                ans += (1 << k);// as we jump for 2 powers only
            }
        }

        if(jumps[u][0] >= v)//> :cover case when for loop doesn't work
            return ans + 1;

        return -1;// if can't reach or overgo that index
    }   
public:
    vector<int> pathExistenceQueries(int n, vector<int>& nums, int maxDiff, vector<vector<int>>& queries) {
        vector<pair<int ,int>>sor;

        for(int i=0; i<n; i++){
            sor.push_back({nums[i], i});
        }
        sort(sor.begin(), sor.end());

        vector<int>pos(n);
        for (int i=0 ;i<n; i++){
            pos[sor[i].second] = i;
        } 

        while( ( 1 << LOG ) <= n) LOG++;

        vector<vector<int>>jumps(n, vector<int>(LOG));
//jumps[i][0] = farthest sorted index reachable from i in one jump
        vector<int>ans;

        int j = 0;

        for(int i = 0; i < n; i++) {
            if(j < i)
             j = i;

            while(j + 1 < n && sor[j + 1].first - sor[i].first <= maxDiff) {
                j++;
            }

            jumps[i][0] = j;
        }

        for(int k=1; k<LOG ; k++){
            for(int i=0; i < n; i++){
                jumps[i][k] = jumps[jumps[i][k-1]][k-1];//binary lifting recurrence
                //bcs: 2 raise to power can make any number
                //also find complexity reduces
            }
        }

        for(int i=0 ;i <queries.size(); i++){
            int u= pos[queries[i][0]],v = pos[queries[i][1]];
            if(u>v) swap( u, v );
            ans.push_back(find(jumps, u ,v));
        }

        return ans;
    }
};
