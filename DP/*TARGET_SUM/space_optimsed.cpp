class Solution {
    //space  optimised
    //time:O(N*k)
    //space:O(k)
public:
    int findTargetSumWays(vector<int>& nums, int target) {
        int sum=0;
        for( int n: nums) sum+=n;
        if( sum- target <0|| (sum-target)%2==1) return 0;
        int s2= (sum-target)/2;
        
        vector<int>cur(s2+1, 0), prev(s2+1, 0);
        cur[0]=1;
        for( int i=0; i< nums.size(); i++){
            prev= cur;
            for( int j=0; j< s2+1; j++){
                cur[j]= prev[j];

                if (nums[i] <= j )
                cur[j]+= prev[j-nums[i]];
            }
        }
        return cur[s2];
    }
};
