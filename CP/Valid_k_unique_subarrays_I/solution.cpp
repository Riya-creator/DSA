class Solution {
    //space:O(n +m)
    //time: theoretically :O(n.q) but amortised to O(n+q)
public:
    vector<bool> validSubarrays(vector<int>& nums, int k, vector<vector<int>>& queries) {
        int n= nums.size(), m = queries.size();

        vector<int>prefix(n+1, 0);
        int maxVal =0;
        unordered_set<int>GlobalDistinct;

        for(int i=0 ; i<n ; i++){
            prefix[i+1] = prefix[i]^nums[i];
            GlobalDistinct.insert(nums[i]);
            maxVal = max(maxVal, nums[i]);
        }
        
        vector<bool>ans;
        ans.reserve(m);
        if(GlobalDistinct.size() <k) {
            for( int i=0; i<m; i++) ans.push_back(false);
            return ans;
        }

        vector<int>seen(maxVal+1,0);
        int query_id=0;

        map<pair<int,int>, bool>memo;//in test case repeated query

        for(const auto &v: queries){
            int l= v[0], r=v[1];
            if(memo.count({l, r})) {
                ans.push_back(memo[{l,r}]);
                continue;
            }

            if( ((r-l +1)< 2*k) || prefix[r+1]- prefix[l] != 0 || (r-l+1)%2 ==1){
                memo[{l, r}] = false;
                ans.push_back(false);
                continue;
            }

            int cnt=0;
            query_id++;
            bool valid =true;
            for( int i=l ; i<=r; i++){
                if(seen[nums[i]] != query_id){
                    seen[nums[i]] = query_id;
                    cnt++;

                    if(cnt >k){
                        valid = false;
                        break;
                    }

                    if(cnt == k && GlobalDistinct.size()<= k)
                    break;
                }
            }
            if(cnt ==k && valid){
                memo[{l,r}] = true;
                ans.push_back(true);
            }
            else {
                memo[{l,r}]= false;
                ans.push_back(false);
            }
        }
        return ans;
    }
};
