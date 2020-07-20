#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<string> split(string data);

bool Predicate(const char &x, const char &y) {
    return x == y and x == ' ';
}

void miniMaxSum(vector<int> arr) {
    long long int left = 0, right = 0;
    
    for (int le=0; le < arr.size()-1; ++le) {
         left += arr[le];
    }
  
    for (int ri=arr.size(); ri >= 1; --ri) {
         right += arr[ri]; 
    }
    
    cout << left << " " << right << endl; 
} 


int main() {
    
    vector<int> arr(5); 
    string temp;
  
    bool running = true;
    
    while (running) {
        cout << "MiniMaxSum v1.0: 21 July 2020" << endl;
        cout << "Enter a maximum of 5 integers below: " << endl;
        getline(cin, temp);
        
        // split the data and then check it
        vector<string> temp_vec = split(temp);
        
        if (temp_vec.size() <= 5 && temp_vec.size() > 0) {
             for (int ii=0; ii < 5; ++ii) {
                 int i_temp = stoi(temp_vec[ii]); 
                 arr[ii] = i_temp; 
            }
            miniMaxSum(arr); 
            running = false; 
        } else {
            cout << "ERROR: you put in the incorrect number of elements." << endl;
        }
    }
    
    return 0;
}

// a means of breaking apart strings and placing in vectors
// ref: HackerRank 
vector<string> split(string data) {
    string::iterator new_end = unique(data.begin(), data.end(), Predicate);
    
    data.erase(new_end, data.end());
    
    
    while (data[data.length() - 1] == ' ') {
        data.pop_back();
    }
    
    
    vector<string> splittedString;
    char delimiter = ' ';
    
    
    size_t i = 0;
    size_t pos = data.find(delimiter);
    
    while (pos != string::npos) {
        splittedString.push_back(data.substr(i, pos - i));
        
        i = pos + 1;
        pos = data.find(delimiter, i);
        
    }
    
    splittedString.push_back(data.substr(i, min(pos, data.length()) - i + 1));
    
    return splittedString;

}
