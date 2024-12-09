#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>

bool eat_num(std::string &s, int &outV)
{
    outV = 0;
    int it = 0;
    while (it < s.size() && (s[it] < '0' || s[it] > '9'))
        ++it;

    while (it < s.size() && s[it] >= '0' && s[it] <= '9')
    {
        outV = outV * 10 + static_cast<int>(s[it] - '0');
        ++it;
    }

    if (it > 0)
    {
        s = std::string(s.begin() + (it), s.end());
        return true;
    }
    return false;
}

void part1()
{
    std::string input;
    while (std::getline(std::cin, input) && input.size() > 0)
    {
        std::vector<int> operands;
        // std::unordered_map<
        int value, operand, sum = 0;
        eat_num(input, value);
        while (eat_num(input, operand))
        {
            operands.push_back(operand);
        }

        // Brute Force
        for (int i = 0; i < operands.size(); ++i)
        {
            for (int j = i + 1; j < operands.size(); ++j)
            {
            }
        }
        // TODO: DP

        std::cout << "Sum is: " << sum << " ." << std::endl;
    }
}

int main(int, char **)
{

    part1();
}
