#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

// https://leetcode.com/problems/sort-colors/description/

void sortColors_one_pass(vector<int>& nums) { 
    auto iter_l = nums.begin();
    auto iter   = nums.begin();
    auto iter_r = --nums.end();

    while(iter <= iter_r){
        if (iter < iter_l)
            iter =  iter_l;
        else if(*iter_l == 0 )
            ++iter_l;
        else if(*iter_r == 2 )
            --iter_r;
        else
        {
            if(*iter == 0)
                swap(*iter, *iter_l++);
            else if(*iter == 2)
                swap(*iter, *iter_r--);
            else 
                ++iter;
        }
    }           
}

void sortColors_two_pass(vector<int>& nums) {
    int a(0), b(0);

    std::for_each(nums.begin(), nums.end(), [&a, &b](const int &num) {
        if(num == 0)
            ++a;
        else if(num == 1)
            ++b;
        });
    
    int value = 0;     
    auto set_value = [&value](int &n){ n = value;};        
    
    std::for_each(nums.begin() , nums.begin() + a, set_value);
    
    ++value;
    std::for_each(nums.begin() + a , nums.begin() + a + b , set_value);

    ++value;
    std::for_each(nums.begin() + a + b, nums.end() , set_value);
}

int main()
{
    //Check the solution in the link above
    return 0;   
}
