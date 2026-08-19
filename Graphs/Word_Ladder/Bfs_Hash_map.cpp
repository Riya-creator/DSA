class Solution {
//implicit graph 
//time: O(nl)
    long long solve(unordered_map<string, bool>&s, string &starting, string des){
//BFS :: as neeed to see at each level 
//dfs may may make many recomputation n at last seee for the optimal solution but here we get the one at traversal time only
        queue<string>q;
        q.push(starting);
        int ans =1;
        
        while(!q.empty()){
            int n = q.size();

            for( int i=0; i< n; i++){
                string start = q.front();
                q.pop();
                if(s[start] )  continue;//imp else complexity hike
                s[start] = true;

                for( auto &ch : start){
                    char original = ch;
                    for( ch = 'a'; ch <= 'z' ; ch++){
                        
                        if(s.count(start) && s[start] ==false){
                            if(start == des) return ans+1;
                            //as inc happen after the level traversal
                            q.push(start);
                        }
                    }
                    ch = original;
                }
            }
            ans++;
        }

        return 0;
    }
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        int n = wordList.size();

        unordered_map<string, bool> s; //no set work as we need to mark if visited
        //else infinite loop 
        //-1 unvisited , -2 = visted but no ans yet

        s[beginWord] = false;
        for(string w: wordList){
            s[w] =false;
        }
        if(!s.count(endWord) )return 0;

        return solve(s, beginWord, endWord);
    }
};
