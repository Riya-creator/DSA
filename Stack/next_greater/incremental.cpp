//dp-ish type increamental processing of the elements
//although the monotonic stack is sequential in nature
class Solution {
public:
    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {

        vector<int> ans(nums1.size(), -1);
        unordered_map<int,int> mp;
        stack<int> s;

        int n2 = nums2.size();

        int k = n2 - 1;

        mp[nums2[k]] = -1;
        s.push(k);
        k--;

        for(int i = 0; i < nums1.size(); i++){

            if(mp.find(nums1[i]) != mp.end()){
                ans[i] = mp[nums1[i]];
            }
            else{

                while(k >= 0 && nums1[i] != nums2[k]){

                    while(!s.empty() && nums2[s.top()] <= nums2[k]){
                        s.pop();
                    }

                    if(s.empty()) mp[nums2[k]] = -1;
                    else mp[nums2[k]] = nums2[s.top()];

                    s.push(k);
                    k--;
                }

                if(k >= 0 && nums1[i] == nums2[k]){

                    while(!s.empty() && nums2[s.top()] <= nums2[k]){
                        s.pop();
                    }

                    if(s.empty()) mp[nums2[k]] = -1;
                    else mp[nums2[k]] = nums2[s.top()];

                    s.push(k);
                    k--;
                }

                ans[i] = mp[nums1[i]];
            }
        }

        return ans;
    }
};
