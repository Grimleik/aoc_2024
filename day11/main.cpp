#include <iostream>
#include <string>
#include <vector>
#include <assert.h>

// #define DEBUG_RENDER
typedef unsigned long long line_t;

line_t calculate_digits(line_t value)
{
	line_t result = 1;
	while ((value = (line_t)(value * 0.1)) > 0)
		++result;
	return result;
}

void part1_integer()
{
	line_t input;
	std::vector<line_t> line;
	while (std::cin >> input)
	{
		line.push_back(input);
		if (std::cin.peek() == '\n')
			break;
	}
	// std::cout << "Enter blinks: ";
	line_t blinks = 25;
	line_t prevSize = line.size();
	// std::cin >> blinks;
	for (line_t i = 0; i < blinks; ++i)
	{
		for (line_t j = 0; j < line.size(); ++j)
		{
			line_t el = line[j];
			if (el == 0)
			{
				line[j] = 1;
			}
			else
			{
				line_t digits = calculate_digits(el);
				if ((digits % 2) == 0)
				{
					line_t upperHalf = el;
					line_t iterations = (line_t)(digits * 0.5);
					while (iterations--)
					{
						upperHalf = (line_t)(upperHalf * 0.1);
					}
					line_t upperHalfZerod = (line_t)(upperHalf * pow(10, (line_t)(digits * 0.5)));
					line_t lowerHalf = el - upperHalfZerod;
					assert((upperHalfZerod + lowerHalf) == el);
					line[j] = upperHalf;
					line.insert(line.begin() + j + 1, lowerHalf);
					line[j + 1] = lowerHalf;
					++j;
				}
				else
				{
					line_t prev = line[j];
					line[j] *= 2024;
					assert(line[j] > prev);
				}
			}
		}
		assert(prevSize < line.size());
		prevSize = (line_t)line.size();
// Inbetween these: HIGH:226775  LOW:175342/167412

#ifdef DEBUG_RENDER
		for (auto &el : line)
		{
			std::cout << el << ", ";
		}
		std::cout << std::endl;
#endif
	}
	std::cout << "Stones: " << line.size() << " ." << std::endl;
}

void part1_string()
{
	line_t input;
	std::vector<line_t> initData;
	while (std::cin >> input)
	{
		initData.push_back(input);
		if (std::cin.peek() == '\n')
			break;
	}

	char tmp[256];
	std::vector<std::string> line;
	for (auto &el : initData)
	{
		_itoa_s(el, tmp, 10);
		line.push_back(std::string(tmp));
	}

#define BLINKS 25

	for (int i = 0; i < BLINKS; ++i)
	{
		for (int j = 0; j < line.size(); ++j)
		{
			auto &el = line[j];
			if (el == "0")
				el = "1";
			else if ((el.size() % 2) == 0)
			{
				int halfDigit = (int)(el.size() * 0.5);
				_itoa_s(atoi(el.substr(0, halfDigit).c_str()), tmp, 10);
				std::string sub1 = tmp;
				_itoa_s(atoi(el.substr(halfDigit, el.size()).c_str()), tmp, 10);
				std::string sub2 = tmp;
				el = sub1;
				line.insert(line.begin() + j + 1, sub2);
				++j;
			}
			else
			{
				_itoa_s(atoi(el.c_str()) * 2024, tmp, 10);
				el = std::string(tmp);
			}
		}
	}
	// for (int i = 0; i < line.size() - 1; ++i)
	// {
	// 	std::cout << line[i] << ", ";
	// }
	// std::cout << line[line.size() - 1] << std::endl << std::endl;

	std::cout << "Ans: " << line.size() << " ." << std::endl;
}

int main(int, char **)
{
	part1_integer();
	// part1_string();
}
