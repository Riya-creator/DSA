class Solution {
    //shortest path -->dijiikstra's whith the distance as muliplication
public:
    double maxProbability(int n, vector<vector<int>>& edges, vector<double>& succProb, int start_node, int end_node) {
        if(edges.size()==0) return 0.0;
        vector<vector<pair<double,double>>>adj(n);
        //node1-> node2, prob
        for( int i=0 ; i<edges.size(); i++){
            adj[edges[i][0]].push_back({ succProb[i], edges[i][1]});
            adj[edges[i][1]].push_back({ succProb[i], edges[i][0]});
        }
        priority_queue<pair<double, int>>pq;
        //prob -->max
        pq.push({1.0,start_node});

        vector<double>prob(n,0.0);
        prob[start_node] = 1.0;

        while(!pq.empty()){
            auto [p, nn]= pq.top();
            pq.pop();

            if(nn == end_node) return p;

            if(prob[nn]> p) continue;

            for( auto &v: adj[nn]){
                double pr= v.first, ne= v.second;

                if(pr*p >prob[ne]){
                    prob[ne]= pr*p;
                    pq.push({prob[ne], ne});
                }
            }
        }
        return prob[end_node];
    }
};
//time: O(E log V)
// Space = O(V + E)
