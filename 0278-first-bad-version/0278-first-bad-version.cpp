// The API isBadVersion is defined for you.
// bool isBadVersion(int version);

class Solution {
public:
    int firstBadVersion(int n) {

        int a = 0;
        int b = n;
        int ans;

        while (a < b) {
            int mid = a + (b - a) / 2;

            if(!isBadVersion(mid) && isBadVersion(mid-1) ){
                ans=mid-1;
            }
            if (isBadVersion(mid)) {
                a = mid + 1;
            } else {
                b = mid - 1;
            }
        }
        return ans;
    }
};