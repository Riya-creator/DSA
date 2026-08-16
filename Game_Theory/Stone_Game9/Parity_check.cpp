class Solution {
    //parity usage 
    //even cnt 0 :makes no change in the state 
    //alice :  smaller grp -->> cnt0 wala -->make the bob force to use opposite n loose 
    //say 1->3 n 2->4 then alice use all 3 1's then all 0 as that time bob can't even use the 2 n at end bob forces to use that only

    //for odd: need 3 more for 1 or 2(whatever is its opening type) to make the turn inverse to bob
    //first ->1 then other bound to move->2 only 
public:
    bool stoneGameIX(vector<int>& stones) {
        vector<int>cnt(3);

        for( int i=0 ; i<stones.size(); i++){
            cnt[stones[i]%3]++;
        }

        if(cnt[0] %2 ==0){
            return min(cnt[1], cnt[2])>0;
            //if both equal alice wins sure as chose first to move other one is bound
            // as alice need min one only n atleast one else use of 0 make loose
        }
        return abs(cnt[1]-cnt[2])>2; 
        //need atleast 2 more than other 
        //goes with large one
    }
};
