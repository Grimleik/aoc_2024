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
int check_adj_numbers(bool up, int prev, int next)
{
	int diff = next - prev;
	if (diff == 0)
	{
		return 1;
	}
	else if (up && diff < 0)
	{
		return 2;
	}
	else if (!up && diff > 0)
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
			b = next - prev;
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

		// NOTE(pf): Start by going down then up.
		bool safe = true;
		int dbgValues[4] = {-1, 0, -1, 0};
		for (int dir = 0; dir < 2; ++dir)
		{
			safe = true;
			int prev, next;
			int allowedErrorLevels = 1;
			i = 1;
			next = report[0];
			if (check_adj_numbers(dir, report[0], report[1]))
			{
				i = 2;
				allowedErrorLevels = 0;
				// safe = false;
				// continue;

				next = report[0];
				dbgValues[dir * 2] = 1;
				if (check_adj_numbers(dir, report[0], report[2]))
				{
					next = report[1];
					dbgValues[dir * 2] = 0;
				}
			}

			for (; i < report.size(); ++i)
			{
				prev = next;
				next = report[i];
				status = check_adj_numbers(dir, prev, next);
				if (status)
				{
					if (allowedErrorLevels > 0)
					{
						/* NOTE(pf): Error handling merge of 29 26 28 27 26
						 * should eliminate 26, we need to check:

						 * 29 26, 26 27 ERROR, 29 27 good tho! skip 26 NOT 27
						 * which leads to 26 27 ERROR.
						 */

						--allowedErrorLevels;
						dbgValues[dir * 2] = i;
						next = report[max(i - 1, 0)];
						if (i < (report.size() - 1) && check_adj_numbers(dir, prev, report[i + 1]))
						{
							dbgValues[dir * 2] = i - 1;
							next = report[i];
							if (i < 1 || check_adj_numbers(dir, report[i - 2], report[i]))
							{
								safe = false;
								break;
							}
						}
						continue;
					}
					else
					{
						safe = false;
						break;
					}
				}
			}

			dbgValues[(dir * 2) + 1] = i;
			if (safe)
				break;
		}
		int allowedIdx = dbgValues[1] > dbgValues[3] ? dbgValues[0] : dbgValues[2];
		int problem = dbgValues[1] > dbgValues[3] ? dbgValues[1] : dbgValues[3];
		if (safe)
		{
			++safeReports;
		}

		int yesbox = 0;
		std::cout << "Report " << reportIdx << ": ";
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
		if (safe)
			std::cout << std::endl;
		else
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5);
			std::cout << " < UNSAFE! " << std::endl;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		}

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		++reportIdx;
	}

	std::cout << "Safe reports: " << safeReports << std::endl;
}

void part2New()
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

		int up = 0, down = 0, sizeErrors = 0, allowedIdx = INT32_MAX, next = report[0], prev, dirErrors = 0;
		/* NOTE(pf): Special case initial 3:

			* If there is a direction change within the first two moves we need
			  to identify which one we should use and which one we should skip.

		 */
		for (i = 1; i < report.size(); ++i)
		{
			prev = next;
			next = report[i];
			int status = next - prev;
			bool error = false;
			if (status == 0 || abs(status) > 3)
			{
				++sizeErrors;
				error = true;
			}
			else if (status > 0)
			{
				++up;
				if (down > 0)
				{
					++dirErrors;
					error = true;
					--up;
					--down;
				}
			}
			else if (status < 0)
			{
				++down;
				if (up > 0)
				{
					++dirErrors;
					error = true;
					--down;
					--up;
				}
			}
			if (error)
			{
				allowedIdx = min(i, allowedIdx);
				next = report[i - 1]; // NOTE(pf): This index gave an error, jump over it!
				if ((sizeErrors + dirErrors) > 1)
				{
					break;
				}
			}
		}

		int problem = i;
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
		if (problem >= report.size())
		{
			safeReports++;
			std::cout << std::endl;
		}
		else
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5);
			std::cout << " < UNSAFE! " << std::endl;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		}

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	}

	std::cout << "Safe reports: " << safeReports << std::endl;
}

int main(int, char **)
{
	// part1();
	part2();
	// 681 WRONG.
	// 688 WRONG.
	// 691 WRONG ?
	// part2New();
	return 0;
}
