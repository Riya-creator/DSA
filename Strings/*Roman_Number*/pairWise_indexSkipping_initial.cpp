//this treats the roman number as local comparison problem, not n pattern matching 

class Solution {
    //kind of memory creation
//production level special making of the memory like we can do in robots (here hardcode)
//can be increamental or live memory as we can add a function to make that learn( update the map) from there live
    static map<char, int>mp;
public:
    int romanToInt(string s) {
        int  curr=0,i;    
        for(  i=0; i< s.size()-1; i++){
            if(mp[s[i]]<mp[s[i+1]]){
                curr+= (mp[s[i+1]]- mp[s[i]]);
                i++;
            }else curr+= mp[s[i]];
        }
        if(i==s.size()-1) curr+=mp[s[i]];
        return curr;
    }
};
map<char, int>Solution::mp= {
    {'I' ,1}, 
    {'V', 5},
    {'C', 100},
    {'D', 500}, 
    {'M', 1000}, 
    {'X', 10},
    {'L', 50}
};
// Time: O(n)
 // space:O(1)// hardcode
