#include <iostream>
#include <string>
#include <map>
#include <stack>
#include <functional>
#include <utility>


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
