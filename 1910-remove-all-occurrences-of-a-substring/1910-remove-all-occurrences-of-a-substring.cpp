class Solution {
public:
    string removeOccurrences(string s, string part) {
        int n=part.size();
        while(s.find(part)!=string::npos){
            int p=s.find(part);
            s.erase(p,n);
        }
        return s;
        
    }
};