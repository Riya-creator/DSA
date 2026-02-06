//lc 15
//need to delete the duplicates from 3 places: while 1st -> in 2Sum from left n right
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> ans;
        sort(nums.begin(), nums.end());
        int n= nums.size(), l ,r, last= INT_MIN, target;
        for( int i=0; i< n; i++){
            while(i<n && nums[i]==last) i++;
            if( i== n) break; 
            last = nums[i];
            target= 0- last;
            l=i+1, r= n-1;
            int check;
            while(l<r){
                check= target- nums[l] - nums[r];
                if( check==0){
                    int f= nums[l], s= nums[r];
                    ans.push_back({last,f, s});

                    while( l<r && nums[l] ==f ) l++;
                    while( r>l && nums[r]== s) r--;
                }
                else if( check >0) l++;
                else r--;
            }
        }
        return ans;
    }
};
