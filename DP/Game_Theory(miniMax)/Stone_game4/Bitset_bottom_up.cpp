class Solution {
    //taking the loosing state then making the wins out of that 
public:
    static constexpr int MAX = 100000;
    inline static bitset<MAX + 1> dp;
    //static so shared for all object
    //time :O(max root max) that also fr first time

    
    inline static bool init = []() {//lamda function
        for (int i = 0; i <= MAX; i++) {
            if (dp.test(i)) continue;//if win continue
            for (int j = 1; j * j <= MAX - i; j++)///loose then make all the ahead possiblity as win as loose +sq value = win
                dp.set(i + j * j);
        }
        
        return false;
    }();//this () makes it call instantly before the winner function called

    bool winnerSquareGame(int n) { return dp.test(n); }
};
