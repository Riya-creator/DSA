class Solution {
    //time: O(n * root m)
        //space: O(root m)
    void handle(unordered_map<int,int>&prime, int nums, bool remove ){
        for( int i=2; i*i<=nums; i++){
            if(nums%i==0){//O(root m)
                if( !remove){
                    prime[i]++;
                }else {
                    prime[i]--;
                    if( prime[i]<=0) prime.erase(i);
                    
                }

                while(nums%i==0 ){ 
                    //also make deletion of any of its factor
                    nums/= i;
                }
            } 
        }
        if(nums>1){
            if( !remove)
                prime[nums]++;
            else{
                prime[nums]--;
                if(prime[nums]==0) prime.erase(nums);
            }
            
        }
    }

public:
    int longestSubarray(vector<int>& nums, int k) {
        unordered_map<int, int>prime;

        int i=0, j=0,n = nums.size(), ans =0;

        while(i<=j && j<n){
            handle( prime, nums[j],  false);
            
            while( prime.size()>k){
                handle(prime, nums[i++], true);
            }

            ans = max( ans, j-i+1);
            j++;
        }

        return ans;
    }
};
