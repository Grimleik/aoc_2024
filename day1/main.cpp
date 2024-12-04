#include <vector>
#include <map>
#include <algorithm>
#include <iostream>

static void part1()
{
    int inputList = 0;
    std::vector<int> inputs[2];
    std::vector<int> *activeInput = &inputs[0];
    int input = 0;
    while(std::cin >> input) {
        activeInput->push_back(input);
        inputList = (inputList + 1) % 2;
        activeInput = &inputs[inputList];
    }

    // PART 1
    std::sort(inputs[0].begin(), inputs[0].end());    
    std::sort(inputs[1].begin(), inputs[1].end());
    int sum = 0;
    for(int i = 0; i < inputs[0].size(); ++i)
    {
        sum += abs(inputs[0][i] - inputs[1][i]);
    }
    std::cout << sum << std::endl;
}

static void part2()
{
    std::vector<int> left;
    std::map<int, int> right;
    int input = 0;
    bool leftSide = true;
    while(std::cin >> input) {
        if(leftSide) {
            left.push_back(input);
        } else {
            right[input] = right[input] + 1;
        }
        leftSide = !leftSide;
    }

    int sum = 0;
    for(auto &i : left) 
    {
        sum += right[i] * i;
    }
    std::cout << sum << std::endl;
}

int main(int, char**){
    // part1();
    part2();
}
