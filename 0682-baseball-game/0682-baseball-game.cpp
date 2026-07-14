class Solution {
public:
    int calPoints(vector<string>& operations) {
        int ans=0;
        stack<int> s;
        for(int i=0;i<operations.size();i++){
            if(operations[i]=="C"){
                s.pop();
            }
            else if(operations[i]=="D"){
                s.push(2*s.top());
            }
            else if(operations[i]=="+"){
                int first=s.top();
                s.pop();
                int second=s.top();
                s.push(first);
                s.push(first+second);
            }
            else{
                s.push(stoi(operations[i]));
            }
            
        }
        while(!s.empty()){
            ans+=s.top();
            s.pop();
        }
        return ans ;
    }

};