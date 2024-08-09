#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>

using namespace std;

bool containsAlphabet(const string& str) {
    return any_of(str.begin(), str.end(), [](char c) {
        return isalpha(c);
    });
}

bool isLetterLog(string str){
    vector<string> tokens;
    string token;
    istringstream tokenStream(str);
    while (getline(tokenStream, token, '-')) {
        tokens.push_back(token);
    }
    //cout<<"token is "<<tokens[1]<<endl;
    if(containsAlphabet(tokens[1]))
        return true;

    return false;

}

vector<string> reorderLogFiles(vector<string>& logs) {
    vector<string> letterLogs;
    vector<string> digitLogs;
    
    // Separate letter-logs and digit-logs
    for (const string& log : logs) {
        int firstSpace = log.find(' ');
        string identifier = log.substr(0, firstSpace);
        // cout<<"identifier is "<<identifier<<" ";
        string rest = log.substr(firstSpace + 1);
        // cout<<" rest of the string is "<<rest<<" ";
        
        if (isLetterLog(log)) {
            letterLogs.push_back(log);
        } else {
            digitLogs.push_back(log);
        }
    }
    
    // Comparator for sorting letter-logs
    auto cmp = [](const string& a, const string& b) {
        // cout<<"string a is "<<a<<" and b is "<<b<<endl;
        int spaceA = a.find('-');
        int spaceB = b.find('-');
        string idA = a.substr(0, spaceA);
        string idB = b.substr(0, spaceB);
        string logA = a.substr(spaceA + 1);
        string logB = b.substr(spaceB + 1);
        // cout<<"in compare log A is "<<logA <<" and log B is "<<logB<<endl;
        
        if (logA == logB) {
            return idA < idB;
        } else {
            return logA < logB;
        }
    };
    
    // Sort the letter-logs
    sort(letterLogs.begin(), letterLogs.end(), cmp);
    
    // Combine letter-logs and digit-logs
    letterLogs.insert(letterLogs.end(), digitLogs.begin(), digitLogs.end());
    
    return letterLogs;
}
