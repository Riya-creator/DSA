class Solution {
public:
    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
        vector<int> ans(nums1.size(), -1);//must take a vector with fixed sixe and intialized as then space complexity is reduced
        stack<int> stk;
        unordered_map<int, int> mp;
        for(int i=nums2.size()-1; i>=0; i--){
            while( !stk.empty() && nums2[stk.top()]<nums2[i]){
                stk.pop();
            }
            if(!stk.empty()){
                mp[nums2[i]]= nums2[stk.top()];
            }
            stk.push(i);
        }
    for(int i=0; i<nums1.size(); i++){
        if( mp.find(nums1[i])!= mp.end()){
            ans[i]= mp[nums1[i]];
        }
    }
    return ans;
    }
};
