#define ll long long
//time: O(N^3) 
class Solution {
    //key things->duplicates n negative included
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        sort(nums.begin(), nums.end());
//sort is not done only when need to return the index as well else help to skip duplicates without extra space

        int n= nums.size();

        vector<vector<int>>ans;
        for( int i=0; i<n ; i++){

            if(i>0 && nums[i]== nums[i-1]) continue;//removing the duplicates
            
            for( int j=i+1; j< n; j++){

                if( j>i+1 && nums[j]== nums[j-1]) continue;//agr current wala i+1 y usse bda index th n in value same h then skip
                ll remain= (ll)target- (ll)nums[i]- (ll)nums[j];
                int l=j+1,r= n-1;
                while(l<r){
                    ll sum= nums[l]+ nums[r];

                    if(sum == remain){
                        ans.push_back({nums[i], nums[j], nums[l], nums[r]});

                        while(l<r && nums[l]== nums[l+1]) l++;
                        while(r>l && nums[r]== nums[r-1]) r--;
                        l++;
                        r--;
                    } else if(sum<remain) l++;
                    else r--;
                }
            }
        }
        return ans;
    }
};
