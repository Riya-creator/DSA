class Solution {
public:
    vector<int> findAllPeople(int n, vector<vector<int>>& meetings, int firstPerson) {
        sort(meetings.begin(), meetings.end(), [](const auto &a, const auto &b){
            return a[2]<b[2];   
        });
        set<int>know;
        know.insert(0);
        know.insert(firstPerson);

        int i=0, t=0;
        while(i< meetings.size() ){
            t= meetings[i][2];
            unordered_map<int, vector<int>>edges(n);
            unordered_set<int>people;

            while(i<meetings.size() && t== meetings[i][2]){
                auto it= meetings[i];

                edges[it[0]].push_back(it[1]);
                edges[it[1]].push_back(it[0]);

                people.insert(it[0]);
                people.insert(it[1]);
                i++;
            }

            queue<int>q;
            unordered_set<int> visited;
//to make the traversal to only the limited inclluded not all the nodes which may lead to waste of time n overlapping traversals

            for(int p:people){
                if(  know.count(p)){
                    q.push(p);
                    visited.insert(p);
                }
            }

            while(!q.empty()){
                int node = q.front();
                q.pop();
                    
                for(auto nn: edges[node]){
                    if(!visited.count(nn)){
                        visited.insert(nn);
                        know.insert(nn);
                        q.push(nn);
                    }
                }
            }
        }
        
        return vector<int>(know.begin(), know.end());
    }
};
