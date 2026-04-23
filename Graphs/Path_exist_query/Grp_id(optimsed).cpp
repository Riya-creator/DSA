class Solution {
   /*earlier one:: “Let me dynamically connect nodes”

    optimsed->current_one:: “Let me label regions in one sweep”*/
public:
//replace dsu-->grp id's
//time :O(nlogn +q)
//space: (max(n, queries.size()));
    vector<bool> pathExistenceQueries(int n, vector<int>& nums, int maxDiff, vector<vector<int>>& queries) {
        vector<pair<int,int>>v;
        for(int i=0; i<n; i++ ){
            v.push_back({nums[i], i});
        }

        sort(v.begin(), v.end());
        vector<int>grps(n);
        int grp=0;
        grps[v[0].second]=grp;//start of the grp as need to make a type of clusters here 

        for(int i=1; i<n; i++){
            if(v[i].first -v[i-1].first <=maxDiff){
                grps[v[i].second]= grp;
            }else{
                grp++;
                grps[v[i].second]= grp;
            }
        }
        vector<bool>ans;
        for(auto q:queries){
            if(grps[q[0]]== grps[q[1]]) ans.push_back(true);
            else ans.push_back(false);
        }
        return ans;
    }
};
/*works only when:
Connectivity depends on sorted order
Condition is based on difference/threshold

When this fails

❌ If:

Graph is arbitrary (not value-based)
Connections are not transitive via sorting
Dynamic updates happen

👉 Then DSU is safer*/
