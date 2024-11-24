#include <iostream>
#include <string>
#include <map>
#include <stack>
#include <functional>
#include <utility>


// You are given a description of a two-lane road in which two strings, L1 and L2, respectively 
// represent the first and the second lane, each lane consisting of N segments of equal length.
// The K-th segment of the first lane is represented by L1[K] and the K-th segment of the second lane is represented by L2[K],where denotes a smooth segment of road and 'x denotes a segment containing potholes.
// Cars can drive over segments with potholes, but it is rather uncomfortable.
// Therefore, a project to repair as many potholes as possible was submitted.
// At most one contiguous stretch of each lane may be repaired at a time.
// For the time of reparation those stretches will be closed to traffic.
// How many road segments with potholes can be repaired given that the road must be kept open (in other words, stretches of roadworks must not prevent travel from one end of the road to the other)?
// Write a function: class Solution public int solstion(string 11, string 12); } that, given two strings L1 and 12 of length N, returns the maximum number of segments with potholes that can be repaired.
// Examples: 
//      1. Given L1..xxxx" and L2 = "x.x.x..", your function should return 4.It is possible to repair three potholes in the first lane and the first pothole in the second lane without closing the road to traffic.second lane without closing the road to traffic. 
//      2. Given L1xxxx" and L2="xxxxxx", your function should retum 6. 
//      3. Given L1 = "xxxxxx" and L2 = "x..x", your function should return 5. 
//      4. Given L1"xx" and L2="x", your function should return 2. Write an efficient algorithm for the following assumptions: N is an integer within the range [1..200,000); strings L1 and L2 consist only of the characters and/or "


int Potholes_Iterator(const std::string& L1, const std::string &L2){
    int leftA = 0 ,rightA = 0;
    int leftB = 0 ,rightB = 0;

    for(auto it_A = L1.begin(), it_B = L2.begin(); it_A != L1.end() && it_B != L2.end(); ++it_A, ++it_B){
        rightA += (*it_A) == 'X' ? 1 : 0;
        rightB += (*it_B) == 'X' ? 1 : 0;
    }
      
    int result = 0;

    for(auto itA = L1.begin(), itB = L2.begin(); itA != L1.end() && itB != L2.end(); ++itA, ++itB ) {
        rightA -= (*itA) == 'X' ? 1 : 0;
        rightB -= (*itB) == 'X' ? 1 : 0;
        result  = std::max(result, leftA + rightB);
        result  = std::max(result, leftB + rightA);
        leftA  += (*itA) == 'X' ? 1 : 0;
        leftB  += (*itB) == 'X' ? 1 : 0;
    }
    
    return result;

}

int Potholes_Indexes(const std::string & L1, const std::string & L2) {
    int leftA = 0, rightA = 0;
    int leftB = 0, rightB = 0;

    // Count initial potholes in both lanes
    for (const char& c : L1) 
        rightA += (c == 'X');

    for (const char& c : L2)
        rightB += (c == 'X');

    int result = 0;

    // Iterate through both lanes simultaneously
    for (size_t i = 0; i < L1.size(); ++i) {
        rightA -= (L1[i] == 'X');
        rightB -= (L2[i] == 'X');

        // Calculate the maximum potholes that can be repaired
        result = std::max(result, leftA + rightB);
        result = std::max(result, leftB + rightA);

        leftA += (L1[i] == 'X');
        leftB += (L2[i] == 'X');
    }

    return result;
}

int main(){
   
    std::map<int,std::pair<std::string, std::string>> map_poth_tests;
    
    map_poth_tests[4] = std::make_pair("..XX.X." ,"X.X.X..");
    map_poth_tests[6] = std::make_pair(".XXX...X", "..X.XXXX");
    map_poth_tests[5] = std::make_pair("XXXXXX"  ,"X.X.X.");
    map_poth_tests[2] = std::make_pair("X...X"   ,"..X..");

    std::stack<std::function<int(const std::string& L1, const std::string &L2)>> s_functions;
    s_functions.push(Potholes_Iterator);
    s_functions.push(Potholes_Indexes);
    while(!s_functions.empty())
    {     
        for (auto const &it : map_poth_tests)
            if (s_functions.top()(it.second.first, it.second.second) == it.first)
                std::cout << it.first << " " << "OK"  << std::endl;
            else
                std::cout << it.first << " " << "FAIL" << std::endl;

        s_functions.pop();

        if(!s_functions.empty())
            std::cout << "==================" << std::endl;
    }
    return 0;
}
