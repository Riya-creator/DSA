class Solution {
public:
    int findNumberOfLIS(vector<int>& nums) {
        vector<int> length(nums.size(), 1), count(nums.size(), 1);

        int max_l=1;
        for (int i = 1; i < nums.size(); i++) {
            for (int j = i-1; j > -1; j--) {
                if (nums[j] < nums[i]) {
                    if (length[i] < length[j] + 1) {
                        length[i] = (length[j] + 1);
                        max_l= max(length [i], max_l);
                        count[i] = count[j];
                    } else if (length[i] == length[j] + 1) {
                        count[i] += count[j];
                    }
                } 
            }
        }
        int max_c=0;
        for(int i=0; i<nums.size(); i++){
            if(length[i]==max_l) max_c+=count[i];
        }
        return max_c;
    }
};
/*length[i]= max length of lis formed using i'th element
count[i]= number of lis of corresponding length that can be formed

time: O(n^2)
space:O(n)*/
