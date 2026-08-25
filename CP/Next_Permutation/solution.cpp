class Solution {
    //time: O(n)
    //space:O(1)
public:
    void nextPermutation(vector<int>& nums) {
        int pivot =-1, n= nums.size();

        for(int i=n-2; i >=0 ; i--){// found place to make change
            if(nums[i] < nums[i+1]){
                pivot =i;
                break;
            }
        }

        if(pivot != -1){
            for(int i=n-1; i>pivot; i-- ){
                if(nums[i]>nums[pivot]){
                    swap(nums[i], nums[pivot]);//swapped next possible candidate
                    //as next highest at end is going to come here
                    break;
                }
            }
        }

        return reverse(nums.begin() +pivot+1, nums.end());
//made the largest number till now as last of pivot changed that with next max then need to reverse that decreasing sequence ahead to inccreasing only
    }
};
