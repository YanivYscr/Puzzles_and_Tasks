#include <iostream>
#include <string>
#include <stack>
#include <vector>


void CreateLPSArray(const std::string& pattern, std::vector<int>& lps) {
    int len = 0;
    lps[0]  = 0; // LPS[0] initialized with 0

    for(int i(1); i < pattern.size(); ++i)
        if (pattern[i] == pattern[len])
            lps[i++] = ++len;
        else if (len != 0)
            len = lps[len - 1];
        else
            lps[i++] = 0;
}

bool KMPSearch(const std::string& text, const std::string& pattern)  {
    std::vector<int> lps(pattern.size(), 0);
    
    CreateLPSArray(pattern, lps);

    int j = 0; 
    int i = 0; 

    const int str_size = text.size();
    const int pat_size = pattern.size();

    while (i < str_size + pat_size)
        if (pattern[j] == text[i % str_size]) {
            ++i;
            ++j;
            if (j == pat_size)
                return true;
        }
        else if (j != 0)
            j = lps[j - 1];
        else
            ++i;

    return false;
}

bool AreValidCircularSize(const std::string& strA, const std::string& strB)  {
        return !(strA.size() != strB.size() || strA.size() == 0);
}

bool AreCircularStrings_KMP(const std::string& strA, const std::string& strB)  {
    if(!AreValidCircularSize(strA, strB))
        return false;

    return KMPSearch(strA,strB);
}

bool AreCircularStrings_Naive(const std::string& strA, const std::string& strB)  {
    if(!AreValidCircularSize(strA, strB))
        return false;

    auto IsSubString = [&strA, &strB](size_t i) -> bool  {
        for(int j(0); j < strA.size(); ++j)
            if(strA[j] != strB[(j+i)%strA.size()])
                return false;
        return true;
    };

    /** Starting the naive circular check   */
    for (int i(0); i < strA.size(); ++i)
        if(IsSubString(i))
            return true;
        
    return false;
}

void AreCircularStrings_Check(const std::string& strA, const std::string& strB, bool expected) {   
    if (AreCircularStrings_Naive(strA, strB) == expected)
        std::cout << "AreCircularStrings_Naive:\t SUCCESS" << std::endl;
    else
        std::cout << "AreCircularStrings_Naive: FAIL for " << strA << " : " << strB << " expected: " << static_cast<int>(expected) << std::endl;

    if (AreCircularStrings_KMP(strA, strB) == expected)
        std::cout << "AreCircularStrings_KMP:\t\t SUCCESS" << std::endl;
    else
        std::cout << "AreCircularStrings_KMP: FAIL for " << strA << " : " << strB << " expected: " << static_cast<int>(expected) << std::endl;
}

void UpdateStackWithTestCases(std::stack<std::pair<std::pair<std::string, std::string>, bool>> &stack_test_cases) {
        // Insert test cases
    stack_test_cases.push({{"a"       , "a"    }, true});
    stack_test_cases.push({{""        , ""     }, false});
    stack_test_cases.push({{"abcde"   , "deabc"}, true});
    stack_test_cases.push({{"abcde"   , "edcba"}, false});
    stack_test_cases.push({{"hello"   , "hello"}, true});
    stack_test_cases.push({{"aaaaa"   , "aaaaa"}, true});
    stack_test_cases.push({{"xyz"     , "zxy"  }, true});
    stack_test_cases.push({{"abcdefgh", "hgfedcba"}, false});
    stack_test_cases.push({{"ababab"      , "bababa"}, true});
    stack_test_cases.push({{"abcd"        , "abc"}, false}); // Invalid size
    stack_test_cases.push({{"yanivjordan" , "jordanyaniv"    }, true});
    stack_test_cases.push({{"abcdefghijklmnopqrst", "stabcdefghijklmnopqr"}, true});
}

void TestsCircularStrings() {
    std::stack<std::pair<std::pair<std::string, std::string>, bool>> testCases;
    UpdateStackWithTestCases(testCases);

    while (!testCases.empty()) {
        std::string str_A = testCases.top().first.first;
        std::string str_B = testCases.top().first.second;
        bool expected     = testCases.top().second;
        AreCircularStrings_Check(str_A, str_B, testCases.top().second);

        testCases.pop();
    }
}

int main() {

    TestsCircularStrings();

    return 0;
}
