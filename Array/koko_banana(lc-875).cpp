class Solution {
    bool possible(int mid, vector<int>& piles, int h){
        long long count=0;
        for( int i=0; i< piles.size(); i++){
            count += (piles[i] +mid -1) /mid;
        }
        return count<=h;
    }
public:
    int minEatingSpeed(vector<int>& piles, int h) {
        int low =1, high= INT_MIN, ans= high;
        for( int i=0; i< piles.size(); i++){
            if( high < piles[i]) high = piles[i];
        }
        ans = high;
        while( high>=low){
            int mid= low+ (high -low)/2;

            if( possible(mid, piles, h)) {
                ans = mid;
                high = mid-1;
            }else {
                low = mid+1;
            }
        }
        return ans;
    }
};
