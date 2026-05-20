class Solution {
    //constraints to check:
    //1. single parent 
    //2. no cycle gives us like then we may have descendent ambiguity
    //now there can be several possiblities for the removal of the node lead to that we use the union for this
    int find(int u, vector<int>&parent){
        if(parent[u]==u) return u;
        else  parent[u]= find(parent[u], parent);
        return parent[u];
    }

    bool unite(int u, int v , vector<int>&parent){
        int pu= find(u, parent), pv= find(v, parent);
        if(pu== pv) return false;
        parent[pv]=pu;
        return true;
    }
public:
    vector<int> findRedundantDirectedConnection(vector<vector<int>>& edges) {
        int n= edges.size();
        // make the indegree for checking more than 1
        vector<int> parent(n+1, 0);
        vector<int> can1, can2;

        for(int i=0; i< n; i++){
            int u= edges[i][0], v= edges[i][1];
            if(parent[v]==0){
                parent[v]= u;
            }else{
                can1 = {u, v};
                can2 = {parent[v], v};
                edges[i][1]=0;
            }
        }
        //got possible link where node has 2 parents or 2 incoming edges
        
        for(int i=0 ;i <n + 1; i++) parent[i] =i;
        for(auto e: edges){
            int u= e[0], v= e[1];
            if(v==0) continue;

            if(!unite(u,v, parent)){
                if(can2.empty()) return e;
                //this is empty for only cycle but no 2 parent case
                return can2;
            }
//if this node is not correct if removed then make try to remove other one
        }
        return can1;
    }
};
