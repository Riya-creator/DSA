class Solution {
    //time:O(n)
    //space:O(t)
public:
    string minWindow(string s, string t) {
        if(s.size() < t.size()) return "";

        unordered_map<char,int> need, use;

        for(char c : t) need[c]++;

        int total = t.size();
        int i = 0, minlen = s.size()+1, ans = -1;

        for(int j = 0; j < s.size(); j++){
            char c = s[j];

            if(need.count(c)){
                use[c]++;

                if(use[c] <= need[c])
                    total--;
            }

            while(total == 0){
                //here valid state for window is total =0 not the next starting point foundation 
                //shrink at valid state that is total=0
                if(j - i + 1 < minlen){
                    minlen = j - i + 1;
                    ans = i;
                }

                char x = s[i];

                if(need.count(x)){
                    use[x]--;

                    if(use[x] < need[x])
                        total++;
                }

                i++;
            }
        }

        return ans == -1 ? "" : s.substr(ans, minlen);
    }
};
