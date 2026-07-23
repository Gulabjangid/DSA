class Solution {
public:
    vector<string> findRepeatedDnaSequences(string s) {

        unordered_set<string> mp;
        unordered_set<string> ans;

        if(s.length()<10){
            return {};
        }

        for(int i=0;i<=s.length()-10;i++){
            string window=s.substr(i,10);

            if(mp.find(window)!=mp.end()){
                ans.insert(window);
            }
            else{
                mp.insert(window);
            }

        }
        return vector<string>(ans.begin(),ans.end());

        
    }
};