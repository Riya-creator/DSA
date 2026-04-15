class Solution {
    //like  shortest path(made with conditions) in graph -->bfs
public:
    int minJumps(vector<int>& arr) {
        int n= arr.size(), ans =0;
        if(n==1) return 0;

        unordered_map<int, vector<int>>mp;
        for( int i=0; i< n; i++){
            mp[arr[i]].push_back(i);
        }

        queue<int>q;
        q.push(0);
        vector<bool>visit(n);
        visit[0]= true;

        while(!q.empty()){
            int s= q.size();

            while(s--){
                int i= q.front();
                q.pop();

                if(i==n-1) return ans;

                if(i>0 && visit[i-1]==false) {
                    visit[i-1]= true;
                    q.push(i-1);
                } 

                if(i<n-1 && visit[i+1] == false){
                    visit[i+1] = true;
                    q.push(i+1);
                }

                for(int ind : mp[arr[i]]){
                    if(visit[ind]== false){
                        visit[ind]= true;
                        q.push(ind);
                    }
                }
                //IMPORTANT:remove to avoid reprocessing
                mp.erase(arr[i]);

            }
            ans++;
        }
        return -1;
    }
};
//time n space:O(N)
