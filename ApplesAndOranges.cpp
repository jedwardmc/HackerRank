#include <cstdio>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdarg>

/*** Apple and Oranges
 *** - name: Jasper Fitzgerald-Cherry
 *** - date: 03.03.2019
 *** - description:
 *** Inspired by a problem on the site HackerRank.
 ***/

using namespace std;

class Region {
    int start = 0;              /* equivalent to s - the start point */
    int end   = 0;              /* equivalent to t - the end point   */
public:
    void set_start(int s) { start = s; }
    void set_end(int t) {   end = t;   }
    int get_start() const { return start; }
    int get_end() const  { return end;   }
};

class Tree {
    string type  = "";          /* state what type of tree this is here   */
    int location = 0;           /* tree is assumingly placed at one point */
    int count    = 0;           /* how many fruit are on a particular tree */
public:
    void set_location(int l) { location = l; }
    int get_location() const { return location; }
    void set_fruit_count(int c) { count = c; }
    int get_fruit_count() const { return count; }
};

Region region;          /* fixed location where house is located */
Tree atree, otree;      /* individual trees outside the property */

bool Predicate(const char &x, const char &y) {
    return x == y and x == ' ';
}

vector<string> split_string(string input_string) {
    
    /*
     * this was copied from hacker-rank - don't know who wrote it
     * but credit to them and thanks to them for helping me create this
     * program.
     */
    
    string::iterator new_end = unique(input_string.begin(), input_string.end(), Predicate);
    
    input_string.erase(new_end, input_string.end());
    
    while (input_string[input_string.length() - 1] == ' ') {
        input_string.pop_back();
    }
    
    vector<string> splits;
    char delimiter = ' ';
    
    size_t i = 0;
    size_t pos = input_string.find(delimiter);
    
    while (pos != string::npos) {
        splits.push_back(input_string.substr(i, pos - i));
        
        i = pos + 1;
        pos = input_string.find(delimiter, i);
    }
    
    splits.push_back(input_string.substr(i, min(pos, input_string.length()) - i + 1));
    
    return splits;
}

void fruit_count(Region* r, Tree* t1, Tree* t2, vector<int> f1, vector<int> f2) {
    
    int t1_count = 0;               /* counts occurrences of tree 1 */
    int t2_count = 0;               /* counts occurrences of tree 2 */
    
    int sk = r->get_start();        /* start point for a region */
    int tk = r->get_end();          /* end point for a region   */
    int ak = t1->get_location();    /* the location for tree 1  */
    int bk = t2->get_location();    /* the location for tree 2  */
    int mk = t1->get_fruit_count(); /* the count of m for t1    */
    int nk = t2->get_fruit_count(); /* the count of n for t2    */
    
    /* m and n could both be different from length of f1 and f2 - check */
    if(mk != f1.size() || nk != f2.size()) {
        printf("M and N should match size of integer arrays\n");
    }
    
    /* add the values of f1 to the location for tree 1 */
    for(int i=0; i < mk; i++) {
        f1[i] += ak;
        
        /* check whether values are in range of s and t */
        
        if (f1[i] >= sk && f1[i] <= tk) {
            t1_count++;
        }
        
    }
    
    /* add the values of f2 to the location for tree 2 */
    for(int i=0; i < nk; i++) {
        f2[i] += bk;
        
        /* check whether values are in range of s and t */
        if(f2[i] >= sk && f2[i] <= tk) {
            t2_count++;
        }
    }

    /* print the final results for both tree 1 and tree 2 */
    printf("%d\n", t1_count);
    printf("%d\n", t2_count);
}


int main() {
    
    /* get the values for start point and end point */
    string st_temp;
    getline(cin, st_temp);
    vector<string> st = split_string(st_temp);
    int s = std::stoi(st[0]);
    int t = std::stoi(st[1]);
    
    /* get values for the location of tree 1 and tree 2 */
    string ab_temp;
    getline(cin, ab_temp);
    vector<string> ab = split_string(ab_temp);
    int a = std::stoi(ab[0]);
    int b = std::stoi(ab[1]);
    
    /* get the length of distances for tree 1 and tree 2 */
    string mn_temp;
    getline(cin, mn_temp);
    vector<string> mn = split_string(mn_temp);
    int m = std::stoi(mn[0]);
    int n = std::stoi(mn[1]);
    
    /* put distances for tree 1 into a vector array */
    string da_temp;
    getline(cin, da_temp);
    vector<string> apples_temp = split_string(da_temp);
    vector<int> apples(m);
    
    for (int i = 0; i < m; i++) {
        int a_item = std::stoi(apples_temp[i]);
        apples[i] = a_item;
    }
    
    /* put distances for tree 2 into a vector array */
    string do_temp;
    getline(cin, do_temp);
    vector<string> oranges_temp = split_string(do_temp);
    vector<int> oranges(n);
    
    for (int i=0; i < n; i++) {
        int o_item = std::stoi(oranges_temp[i]);
        oranges[i] = o_item;
    }
    
    
    /* set all values to perform the final count function */
    
    
    /* set region bounds - this is where the house is located */
    region.set_start(s);
    region.set_end(t);
    
    /* set tree location - assume that each tree is located on one point */
    atree.set_location(a);
    otree.set_location(b);
    
    /* set the count for the apple and orange trees - m and n */
    atree.set_fruit_count(m);
    otree.set_fruit_count(n);
    

    /* now we perform the final step and voila */
    fruit_count(&region, &atree, &otree, apples, oranges);
    return 0;
}
