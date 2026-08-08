class Solution {
public:
    bool isSameAfterReversals(int num) {
        int rev=0;
        int og=num;
        while(num!=0){
            int digit=num%10;
            rev=rev*10+digit;
            num=num/10;
        }
        int drev=0;
        while(rev!=0){
            int digit=rev%10;
            drev=drev*10+digit;
            rev=rev/10;
        }

        if(drev==og){
            return true;
        }
        return false;
    }
};