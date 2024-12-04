#include <iostream>
#include <vector>
#include <string>
#include <windows.h>

#define PRINT 1
#if PRINT

#define DBG_OUTPUT(x) \
    std::cout << x << std::endl

#else

#define DBG_OUTPUT(x)

#endif

/*
 * Returns status code:
 * 0: success
 * 1: failure, diff 0.
 * 2: failure, swap from inc to dec.
 * 3: failure, swap from dec to inc.
 * >=4: failure too large, nr returned.
 */
int check_adj_numbers(int prevOrder, int prev, int next)
{
    int diff = next - prev;
    if (diff == 0)
    {
        return 1;
    }
    else if (prevOrder > 0 && diff < 0)
    {
        return 2;
    }
    else if (prevOrder < 0 && diff > 0)
    {
        return 3;
    }
    else if (abs(diff) > 3)
    {
        return abs(diff);
    }
    return 0;
}

void part1()
{
    int safeReports = 0;
    int reportIdx = 0;
    std::string line;
    std::vector<int> report;
    while (std::getline(std::cin, line) && line.size() > 0)
    {
        int i, j = 0;
        int status = 0;
        int integer = 0;
        report.clear();
        for (i = 0; i < line.size(); ++i)
        {
            if (line[i] == ' ')
            {
                report.push_back(integer);
                integer = 0;
            }
            else
            {
                integer = integer * 10 + static_cast<int>(line[i] - '0');
            }
        }
        if (integer)
            report.push_back(integer);

        int prev = report[0];
        int next = prev;
        int b = 0;
        bool safe = true;
        for (i = 1; safe && i < report.size(); ++i)
        {
            prev = next;
            next = report[i];
            status = check_adj_numbers(b, prev, next);
            if (status)
            {
                safe = false;
                break;
            }
            b = prev - next;
        }

        if (safe)
        {
            DBG_OUTPUT("Report " << reportIdx << " is safe.");
            ++safeReports;
        }
        else
        {
            DBG_OUTPUT("Report " << reportIdx << " is unsafe @"
                                 << i << " status " << status << ".");
        }
        ++reportIdx;
    }

    std::cout << "Safe reports: " << safeReports << std::endl;
}

void part2()
{
    int safeReports = 0;
    int reportIdx = 0;
    std::string line;
    std::vector<int> report;
    while (std::getline(std::cin, line) && line.size() > 0)
    {
        int i, j = 0;
        int status = 0;
        int integer = 0;
        report.clear();
        for (i = 0; i < line.size(); ++i)
        {
            if (line[i] == ' ')
            {
                report.push_back(integer);
                integer = 0;
            }
            else
            {
                integer = integer * 10 + static_cast<int>(line[i] - '0');
            }
        }
        if (integer)
            report.push_back(integer);

        int prev = report[0];
        int next = prev;
        int prevOrder = report[1] - report[0];
        bool safe = true;
        int allowedErrorLevels = 1;
        int allowedIdx = -1;
        for (i = 1; i < report.size(); ++i)
        {
            prev = next;
            next = report[i];
            status = check_adj_numbers(prevOrder, prev, next);
            if (status)
            {
                if (status < 4 && allowedErrorLevels > 0)
                {
                    allowedIdx = i - 1;
                    --allowedErrorLevels;
                    next = report[max(i - 1, 0)];
                    continue;
                }
                else
                {
                    safe = false;
                    break;
                }
            }
            prevOrder = next - prev;
        }

        if (safe)
        {
            // DBG_OUTPUT("Report " << reportIdx << " is safe.");
            ++safeReports;
        }
        else
        {
            // DBG_OUTPUT("Report " << reportIdx << " is unsafe @"
            //                      << i << " status " << status << ".");
        }

        int problem = i;
        int yesbox = 0;
        for (i = 0; i < report.size(); ++i)
        {
            if (i == allowedIdx)
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
            }
            else if (i == problem)
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
            }
            else
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
            }
            std::cout << report[i] << " ";
        }
        std::cout << std::endl;

        ++reportIdx;
    }

    std::cout << "Safe reports: " << safeReports << std::endl;
}

int main(int, char **)
{
    // part1();

    // 672 <
    // 679 !
    // 706 >
    part2();
    return 0;
}
