class Solution {
public:
    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
        vector<int> ans(nums1.size(), -1);
//must take a vector with fixed sixe and intialized as then space complexity is reduced
        int k;
        for(int i=0; i<nums1.size(); i++){
            for(int j=0; j<nums2.size(); j++){
                if( nums1[i]==nums2[j]){
                    for( k=j+1; k<nums2.size(); k++){
                        if(nums2[k]>nums2[j]){
                            ans[i]= nums2[k];
                            break;
                        }
                    }
                }
        }
    }
    return ans;
    }
};
