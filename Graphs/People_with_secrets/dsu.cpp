class Solution {
    //main logic:
// group → check → propagate → reset
    class DSU{
        public:
        vector<int>parent;

        DSU(int n){
            parent.resize(n);
            for( int i=0; i< n; i++) parent[i]= i;
        }

        int find(int v){
            if(parent[v]== v) return v;
            parent[v] = find(parent[v]);
            return parent[v];
        }

        void  unite(int a , int b){
            int pa= find(a), pb= find(b);
            if ( pa != pb ) parent[pa]= pb;
        }

        void reset(int a){
            parent[a]=a;
        }
    };
public:
    vector<int> findAllPeople(int n, vector<vector<int>>& meetings, int firstPerson) {
        sort(meetings.begin(), meetings.end(), [](const auto &a, const auto &b){
            return a[2] < b[2];
        });

        vector<bool>know(n, false);
        know[0]= true;
        know[firstPerson]= true;

        DSU d(n);
        d.unite(0,firstPerson);     
        int i=0;
        while( i < meetings.size() ){
            int t = meetings[i][2];
            unordered_set<int>s;
            vector<pair<int, int>>curmeet;

            while(i<meetings.size() && meetings[i][2]==t){
                s.insert(meetings[i][0]);
                s.insert(meetings[i][1]);
                curmeet.push_back({meetings[i][0], meetings[i][1]});
                d.unite(meetings[i][0], meetings[i][1]);
                i++;    
            }

            unordered_map<int, vector<int>>cmp;
            //to make the comparision by parent for the connected componentes using the set from main dsu as map
            for(int p:s){
                cmp[d.find(p)].push_back(p);
            }

            for(auto &it : cmp){
                bool secret= false;
                for(auto p : it.second){
                    if(know[p]==true){
                        secret=true;
                        break;
                    }
                }

                if(secret){
                    for(int p: it.second){
                        know[p]= true;
                    }
                }else{
                    for(int p:it.second){
                        d.reset(p);
                    }
                }
            }
        }
        vector<int>ans;
        for(int i=0; i<n; i++){
            if(know[i]) ans.push_back(i);
        }
        return ans;
    }
};
