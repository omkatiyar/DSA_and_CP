#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

vector<string> reorderLogFiles(vector<string>& logs) {
    vector<string> letterLogs;
    vector<string> digitLogs;
    
    // Separate letter-logs and digit-logs
    for (const string& log : logs) {
        int firstSpace = log.find(' ');
        string identifier = log.substr(0, firstSpace);
        string rest = log.substr(firstSpace + 1);
        
        if (isalpha(rest[0])) {
            letterLogs.push_back(log);
        } else {
            digitLogs.push_back(log);
        }
    }
    
    // Comparator for sorting letter-logs
    auto cmp = [](const string& a, const string& b) {
        int spaceA = a.find(' ');
        int spaceB = b.find(' ');
        string idA = a.substr(0, spaceA);
        string idB = b.substr(0, spaceB);
        string logA = a.substr(spaceA + 1);
        string logB = b.substr(spaceB + 1);
        
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
