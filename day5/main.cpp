#include <iostream>
#include <chrono>
#include <vector>
#include <map>
#include <string>
#include <sstream>

void part1()
{
    std::map<int, std::vector<int>> rules;
    // First, read in all rules.
    std::string input;
    while (std::getline(std::cin, input) && input.size() > 0 && input[0] != '\n')
    {
        std::stringstream ss(input);
        std::getline(ss, input, '|');
        int mark = std::stoi(input);
        std::getline(ss, input, '|');
        int rule = std::stoi(input);
        rules[mark].push_back(rule);
    }

    std::vector<int> prev;
    int sum = 0;
    input.clear();
    while (std::getline(std::cin, input) && input.size() > 0 && input[0] != '\n')
    {
        std::stringstream ss(input);
        bool validInput = true;
        while (std::getline(ss, input, ',') && validInput)
        {
            int mark = std::stoi(input);
            if (rules.find(mark) != rules.end())
            {
                for (auto &p : prev)
                {
                    auto &match = rules.at(mark);
                    if (std::find(match.begin(), match.end(), p) != match.end())
                    {
                        validInput = false;
                        break;
                    }
                }
            }

            prev.push_back(mark);
        }
        if (validInput)
        {
            sum += prev[(int)floor(prev.size() * 0.5f)];
        }
        prev.clear();
    }
    std::cout << "Part 1: " << sum << " ." << std::endl;
}

void part2()
{
    std::map<int, std::vector<int>> rules;
    // First, read in all rules.
    std::string input;
    while (std::getline(std::cin, input) && input.size() > 0 && input[0] != '\n')
    {
        std::stringstream ss(input);
        std::getline(ss, input, '|');
        int mark = std::stoi(input);
        std::getline(ss, input, '|');
        int rule = std::stoi(input);
        rules[mark].push_back(rule);
    }

    std::vector<int> prev;
    int sum = 0;
    input.clear();
    while (std::getline(std::cin, input) && input.size() > 0 && input[0] != '\n')
    {
        std::stringstream ss(input);
        bool validInput = true;
        while (std::getline(ss, input, ','))
        {
            int mark = std::stoi(input);
            if (rules.find(mark) != rules.end())
            {
                auto &match = rules.at(mark);
                // std::vector<int>::iterator find = match.end();
                int idx = 0;
                for (auto &p : prev)
                {
                    if (std::find(match.begin(), match.end(), p) != match.end())
                    {
                        validInput = false;
                        break;
                    }
                    ++idx;
                }
                prev.insert(prev.begin() + idx, mark);
            }
            else
            {
                prev.push_back(mark);
            }
        }

        if (!validInput)
        {
            sum += prev[(int)floor(prev.size() * 0.5f)];
        }
        prev.clear();
    }
    std::cout << "Part 2: " << sum << " ." << std::endl;
}

int main(int, char **)
{
    auto start = std::chrono::high_resolution_clock::now();

    // part1();
    part2();

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "Timer: " << duration.count() << std::endl;
    // part2();
}
