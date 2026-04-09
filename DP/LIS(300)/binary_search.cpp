class Solution {
    //time:o(nlogn)
    //space:O(n)
public:
    int lengthOfLIS(vector<int>& nums) {
//tail[i]== store the min possible value of integer to form the lis of lenght i+1 
        vector<int>tail;
        for(int n:nums){
            auto it= lower_bound(tail.begin(), tail.end(), n);
//to find the index where it is greter or equal to n
            if( it == tail.end() )
            tail.push_back(n);
//not found-> extend lis length count
            else{
                *it= n;
// if somewhere found -->replace as thenn more chance to expand
            }
        }
        return tail.size();
//max possible size that can be reached 
    }; 
};
