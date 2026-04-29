class Solution {
    class dsu{
        public:
            vector<int>parent, rank;
            dsu(int n){
                parent.resize(n+1);
                rank.resize(n+1, 0);
                for(int i=0;i<n+1; i++)
                parent[i]=i;
            }

            int find(int node){
                if(parent[node]== node) return node;
                return parent[node]= find(parent[node]);
            }

            void unite(int a, int b){
                int pa= find(a), pb= find(b);

                if(pa==pb){
                    return;
                }

                if(rank[pa]>rank[pb]){
                    parent[pb]= pa;
                }
                else if(rank[pa]<rank[pb]){
                    parent[pa]= pb;
                }else{
                    rank[pa]++;
                    parent[pb]= pa;
                }
            }

    };
public:
    int minScore(int n, vector<vector<int>>& roads) {
        dsu d(n);
        for( auto &r : roads){
            d.unite(r[0], r[1]);
        }
        int p= d.find(1);//IMP:: as there might be changed order in roads thenn it may lead to some other value of parent for start node as well
        int ans=INT_MAX;

        for(auto &r: roads){
            if(d.find(r[0])==p){
                ans= min(ans, r[2]);
            }
        }
        return ans; 
    }
};
