#include <iostream>
#include <vector>
#include <string>
/* THOUGHT
    * When reading in the input, create a numeric vector, 0, 1, 2, 3, 4 for
     0: Miss, 1: X ... and create a kernel for finding this instead of
     comparisions ?
*/

void part1()
{
    std::string word = "XMAS";
    std::vector<std::string> inputs;
    std::string input;
    // NOTE(pf): First fetch all input..
    while (std::getline(std::cin, input))
    {
        inputs.push_back(input);
        input = "";
    }
    //::cout << inputs.size() << std::endl;
    int w = (int)inputs[0].length();
    int h = (int)inputs.size();
    int i, j;
    // Then we loop the fetched input. Whenever we find X/S we start our search
    // trying to create a (x)MA/AM(s) from there.
    // NOTE(pf): Currently just stops here ???
    int count = 0;
    std::vector<std::pair<int, int>> indices;
    for (j = 0; j < h; ++j)
    {
        for (i = 0; i < w; ++i)
        {
            std::string &str = inputs[j];
            auto mark = str.at(i);
            int state = 0;
            if ((i + 3) < w)
                state |= 4;
            if ((j + 3) < h)
                state |= 2;
            if (state == 6)
                state |= 1;
            if ((i - 3) >= 0 && (j - 3) >= 0)
                state |= 8;
            if ((i + 3) < w && (j - 3) >= 0)
                state |= 16;
            if ((i - 3) >= 0 && (j + 3) < h)
                state |= 32;

            if (mark == 'X')
            {
                if ((state & 4) &&
                    inputs[j][i + 1] == 'M' &&
                    inputs[j][i + 2] == 'A' &&
                    inputs[j][i + 3] == 'S')
                {
                    indices.push_back(std::make_pair(j, i));
                    indices.push_back(std::make_pair(j, i + 1));
                    indices.push_back(std::make_pair(j, i + 2));
                    indices.push_back(std::make_pair(j, i + 3));
                    ++count;
                }
                if ((state & 2) &&
                    inputs[j + 1][i] == 'M' &&
                    inputs[j + 2][i] == 'A' &&
                    inputs[j + 3][i] == 'S')
                {

                    indices.push_back(std::make_pair(j, i));
                    indices.push_back(std::make_pair(j + 1, i));
                    indices.push_back(std::make_pair(j + 2, i));
                    indices.push_back(std::make_pair(j + 3, i));
                    ++count;
                }
                if ((state & 1) &&
                    inputs[j + 1][i + 1] == 'M' &&
                    inputs[j + 2][i + 2] == 'A' &&
                    inputs[j + 3][i + 3] == 'S')
                {

                    indices.push_back(std::make_pair(j, i));
                    indices.push_back(std::make_pair(j + 1, i + 1));
                    indices.push_back(std::make_pair(j + 2, i + 2));
                    indices.push_back(std::make_pair(j + 3, i + 3));
                    ++count;
                }

                if ((state & 16) &&
                    inputs[j - 1][i + 1] == 'M' &&
                    inputs[j - 2][i + 2] == 'A' &&
                    inputs[j - 3][i + 3] == 'S')
                {

                    indices.push_back(std::make_pair(j, i));
                    indices.push_back(std::make_pair(j - 1, i + 1));
                    indices.push_back(std::make_pair(j - 2, i + 2));
                    indices.push_back(std::make_pair(j - 3, i + 3));
                    ++count;
                }
            }
            else if (mark == 'S')
            {
                if ((state & 4) &&
                    inputs[j][i + 1] == 'A' &&
                    inputs[j][i + 2] == 'M' &&
                    inputs[j][i + 3] == 'X')
                {

                    indices.push_back(std::make_pair(j, i));
                    indices.push_back(std::make_pair(j, i + 1));
                    indices.push_back(std::make_pair(j, i + 2));
                    indices.push_back(std::make_pair(j, i + 3));
                    ++count;
                }
                if ((state & 2) &&
                    inputs[j + 1][i] == 'A' &&
                    inputs[j + 2][i] == 'M' &&
                    inputs[j + 3][i] == 'X')
                {

                    indices.push_back(std::make_pair(j, i));
                    indices.push_back(std::make_pair(j + 1, i));
                    indices.push_back(std::make_pair(j + 2, i));
                    indices.push_back(std::make_pair(j + 3, i));
                    ++count;
                }
                if ((state & 1) &&
                    inputs[j + 1][i + 1] == 'A' &&
                    inputs[j + 2][i + 2] == 'M' &&
                    inputs[j + 3][i + 3] == 'X')
                {

                    indices.push_back(std::make_pair(j, i));
                    indices.push_back(std::make_pair(j + 1, i + 1));
                    indices.push_back(std::make_pair(j + 2, i + 2));
                    indices.push_back(std::make_pair(j + 3, i + 3));
                    ++count;
                }

                if ((state & 16) &&
                    inputs[j - 1][i + 1] == 'A' &&
                    inputs[j - 2][i + 2] == 'M' &&
                    inputs[j - 3][i + 3] == 'X')
                {

                    indices.push_back(std::make_pair(j, i));
                    indices.push_back(std::make_pair(j - 1, i + 1));
                    indices.push_back(std::make_pair(j - 2, i + 2));
                    indices.push_back(std::make_pair(j - 3, i + 3));
                    ++count;
                }
            }
        }
    }

    int allowed = 0;
    for (j = 0; j < h; ++j)
    {
        for (i = 0; i < w; ++i)
        {
            if (std::find(indices.begin(), indices.end(), std::make_pair(j, i)) != indices.end())
            {
                std::cout << inputs[j][i];
            }
            else
                std::cout << ".";
        }
        std::cout << std::endl;
    }

    std::cout << "Count is: " << count << " ." << std::endl;
}

void part2()
{
    std::string word = "XMAS";
    std::vector<std::string> inputs;
    std::string input;
    // NOTE(pf): First fetch all input..
    while (std::getline(std::cin, input) && input.size() > 0)
    {
        inputs.push_back(input);
        input.clear();
    }
    //::cout << inputs.size() << std::endl;
    int w = (int)inputs[0].length();
    int h = (int)inputs.size();
    int i, j;
    // Then we loop the fetched input. Whenever we find X/S we start our search
    // trying to create a (x)MA/AM(s) from there.
    // NOTE(pf): Currently just stops here ???
    int count = 0;
    std::vector<std::pair<int, int>> indices;
    for (j = 1; j < (h - 1); ++j)
    {
        for (i = 1; i < (w - 1); ++i)
        {
            std::string &str = inputs[j];
            auto mark = str.at(i);
            if (mark == 'A')
            {
                int counter = 0;
                if (inputs[j - 1][i - 1] == 'M' &&
                    inputs[j + 1][i + 1] == 'S')
                {
                    ++counter;
                }

                if (inputs[j - 1][i - 1] == 'S' &&
                    inputs[j + 1][i + 1] == 'M')
                {
                    ++counter;
                }

                if (inputs[j - 1][i + 1] == 'M' &&
                    inputs[j + 1][i - 1] == 'S')
                {
                    ++counter;
                }

                if (inputs[j - 1][i + 1] == 'S' &&
                    inputs[j + 1][i - 1] == 'M')
                {
                    ++counter;
                }

                if (counter >= 2)
                {
                    indices.push_back(std::make_pair(j - 1, i - 1));
                    indices.push_back(std::make_pair(j - 1, i + 1));
                    indices.push_back(std::make_pair(j + 1, i + 1));
                    indices.push_back(std::make_pair(j + 1, i - 1));
                    indices.push_back(std::make_pair(j, i));
                    ++count;
                }
            }
        }
    }

    int allowed = 0;
    for (j = 0; j < h; ++j)
    {
        for (i = 0; i < w; ++i)
        {
            if (std::find(indices.begin(), indices.end(), std::make_pair(j, i)) != indices.end())
            {
                std::cout << inputs[j][i];
            }
            else
                std::cout << ".";
        }
        std::cout << std::endl;
    }

    std::cout << "Count is: " << count << " ." << std::endl;
}

int main(int, char **)
{
    // part1(); // 2418 to low.
    part2();
}
