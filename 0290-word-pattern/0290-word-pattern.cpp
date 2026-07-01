class Solution {
public:
    bool wordPattern(string pattern, string s) {

        // String ko words me convert karne ke liye
        stringstream ss(s);
        vector<string> words;
        string word;

        while(ss >> word) {
            words.push_back(word);
        }

        // Pattern ke chars aur words ki count same honi chahiye
        if(pattern.size() != words.size())
            return false;

        // pattern char -> word mapping
        unordered_map<char, string> mp1;

        // word -> pattern char reverse mapping
        unordered_map<string, char> mp2;

        for(int i = 0; i < pattern.size(); i++) {

            char c = pattern[i];
            string w = words[i];

            // Agar char pehle se mapped hai aur same word nahi hai
            if(mp1.count(c) && mp1[c] != w)
                return false;

            // Agar word pehle se kisi aur char se mapped hai
            if(mp2.count(w) && mp2[w] != c)
                return false;

            // Mapping store karo
            mp1[c] = w;
            mp2[w] = c;
        }

        return true;
    }
};