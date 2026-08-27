class Solution {
    //time O(n*26)
    //space O(26)
public:
    string lexGreaterPermutation(string s, string target) {
        map<char,int> mp;
        for(char c:s) mp[c]++;

        string ans="";

        for(int i=0; i<target.size(); i++){
            auto it=mp.lower_bound(target[i]);

            if(it==mp.end()) break;

            ans+=it->first;
            if(--it->second==0) mp.erase(it);

            if(ans[i]>target[i]){
                for(auto x:mp)
                    ans+=string(x.second,x.first);
                return ans;
            }
        }

      //for the cases where greedy is struck or fail like where the same taken character block possiblities ahead
      //eg : ab 
        for(int i=ans.size()-1; i>=0; i--){
            mp.clear();

            for(char c:s) mp[c]++;
            for(int j=0; j<i; j++){
                if(--mp[ans[j]]==0) mp.erase(ans[j]);
            }

            auto it=mp.upper_bound(target[i]);

            if(it==mp.end()) continue;

            ans=target.substr(0,i)+it->first;
            if(--it->second==0) mp.erase(it);

            for(auto x:mp)
                ans+=string(x.second,x.first);

            return ans;
        }

        return "";
    }
};
