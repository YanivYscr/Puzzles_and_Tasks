#include <iostream>
#include <vector>
#include <stdint.h>
#include <algorithm>
#include <random>
#include <functional>
#include <stack>


#define NUM_OF_TESTS 5
#define PRINT_VEC

void ZerosPosition_1(std::vector<uint32_t> &vec)
{
   
    std::cout << __func__ << std::endl;

    if (vec.begin() == vec.end())
        return;
    auto iterA = --vec.end();
    auto iterB = --vec.end();

    while (iterA >= vec.begin()) {
        *iterB = *iterA;
        if (*iterA)
            --iterB;

        --iterA;
    }

    while (iterB >= vec.begin())
        (*iterB--) = 0;
}

void ZerosPosition_2(std::vector<uint32_t> &vec)
{
    std::cout << __func__ << std::endl;

    if (vec.begin() == vec.end())
        return;

    auto iterA = --vec.end();
    auto iterB = --vec.end();

    while (iterA >= vec.begin()) {
        if (*iterA)
            *iterB-- = *iterA;

        --iterA;
    }

    if (iterA == iterB)
        return;

    while (iterB >= vec.begin())
        (*iterB--) = 0;
}

int main()
{
    std::vector<uint32_t> vec_shuffled = {0, 2, 3, 4, 5, 1, 0, 0, 4, 0, 9, 0};
    std::vector<uint32_t> vec_expected = {0, 0, 0, 0, 0, 2, 3, 4 ,5, 1, 4, 9};

    std::random_device rd;
    std::mt19937 g(rd());

    const auto shuffle_vec = [&g, &rd,vec_expected](std::vector<uint32_t> &v) {
        const std::vector<uint32_t> vec_temp = v;
        char count_out = 0;     //Just in case :)
        bool are_euqal = std::equal(v.begin(), v.end(), vec_temp.begin());
        while(are_euqal && count_out++ < 5)
           {
            std::shuffle(v.begin(), v.end(), g);
            are_euqal = std::equal(v.begin(), v.end(), vec_temp.begin());
            }

        return are_euqal;
    };

    const auto print_vec = [](const std::vector<uint32_t> &v)
    {
        std::for_each(v.begin(), v.end(), [](uint32_t n){ 
            std::cout << n << " "; });
        std::cout << std::endl;
    };

    /** Some Tests */
    auto compare_vectors = [&vec_expected](const std::vector<int>& vecA, const std::vector<int>& vecB) {
        if(vecB.size() != vec_expected.size() || vecB.size() != vec_expected.size())
            return false;
        return std::equal(vecA.begin(), vecA.end(), vecB.begin());
    };

    auto solution_checker = [print_vec, shuffle_vec, &vec_shuffled, &vec_expected](const std::function<void(std::vector<uint32_t>&)>& func_to_check ) {
        if(shuffle_vec(vec_shuffled)){
            std::cout << " suffle_vec Fails, check vectors" << std::endl;
            return false;
        }

#ifdef PRINT_VEC
        print_vec(vec_shuffled);
#endif //PRINT_VEC
        vec_expected = vec_shuffled;
        std::sort(vec_expected.begin(), vec_expected.end(), [&](uint32_t a, uint32_t b) { 
                return a == 0;
            });
#ifdef PRINT_VEC
        print_vec(vec_expected);
#endif //PRINT_VEC
        if(std::equal(vec_shuffled.begin(), vec_shuffled.end(), vec_expected.begin()) == true)
            return false;
        func_to_check(vec_shuffled);
        return std::equal(vec_shuffled.begin(), vec_shuffled.end(), vec_expected.begin());
    };

    std::stack<std::function<void(std::vector<uint32_t>&)>> func_stack;

    func_stack.push(ZerosPosition_1);
    func_stack.push(ZerosPosition_2);

    while(!func_stack.empty())
    {
        const auto current_func = func_stack.top();
        for (int i(0); i < NUM_OF_TESTS; ++i)
        {
            std::string result = solution_checker(current_func) ? "PASS" : "FAILS";
            std::cout << "TEST # " << i+1 << " " << result << std::endl;    
            std::cout << "- - - - - - - - - - - - - -\n";
        }
        std::cout << "===========================\n";
        func_stack.pop();
    }

    return 0;
}
