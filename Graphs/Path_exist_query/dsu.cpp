//at first may seem that diff n ans but twist lie what if there is more diss in node but can be reached from the intermediate path in them
//time:O(nlogn +q)
//space: O(max(n, queries.size()))
//path possible: dsu
class Solution {

    int findParent(int n, vector<int>&p){
        if(p[n]==n) return n;
        else p[n]= findParent(p[n], p);
        return p[n];
    }

    void unite(int a, int b, vector<int>&p){
        int pa= findParent(a, p), pb= findParent(b, p);
        if(pa!=pb) p[pa]=pb;
    }
public:
    vector<bool> pathExistenceQueries(int n, vector<int>& nums, int maxDiff, vector<vector<int>>& queries) {
        vector<bool>ans;
        vector<int>parent(n);
        for(int i=0; i<n; i++) parent[i]=i;

        vector<pair<int, int>>v;//storing cost to make , index of node

        for(int i=0; i<n ;i++){
            v.push_back({nums[i],i});
        }

        sort(v.begin(), v.end());
        //so that smallest diff possible with each node may be cheched rest all are made by unite 

        for(int i=1; i<n; i++){
            if(v[i].first- v[i-1].first <=maxDiff)//condition for this question
            unite(v[i].second,v[i-1].second, parent);
        }

        for(auto q:queries){
            if(findParent(q[0], parent) != findParent(q[1],parent))
                ans.push_back(false);
            else ans.push_back(true);
        }

        return ans;
    }
};
