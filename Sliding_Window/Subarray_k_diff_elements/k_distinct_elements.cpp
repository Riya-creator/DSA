class Solution {
    //in "ans" we add the total subarray possible ending at the index "j"
    int atMostK(vector<int> &nums, int k){
        unordered_map<int, int>mp;
        int i=0, j=0, ans =0;
        for( int j=0; j< (int)nums.size(); j++){
            mp[nums[j]]++;
            while((int) mp.size()>k && i<=j){
                mp[nums[i]]--;
                if(mp[nums[i]]==0) mp.erase(nums[i]);
                i++;
            }
            ans += j-i+1;// we don't see if it meet size of k just adding it up making it cover for all upto k 
        }
        return ans;
    }
public:
    int subarraysWithKDistinct(vector<int>& nums, int k) {
        //always think in this way to make the subtractionf or such type of questions
        return atMostK(nums, k) - atMostK(nums, k-1);
    }
};
//time: O(n)
//space: O(k) 
