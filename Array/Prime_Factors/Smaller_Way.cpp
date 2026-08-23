void PrimeFactors(unordered_map<int,int>& prime, int nums, bool remove) {
        for(int i = 2; i * i <= nums; i++) {
            if(nums % i == 0) {
                if(!remove) prime[i]++;
                else {
                    prime[i]--;
                    if(prime[i] == 0) prime.erase(i);
                }

                while(nums % i == 0)//covering all its factors
                    nums /= i;
            }
        }

        if(nums > 1) {
            if(!remove) prime[nums]++;
            else {
                prime[nums]--;
                if(prime[nums] == 0) prime.erase(nums);
            }
        }
    }
//time:O(root nums)
