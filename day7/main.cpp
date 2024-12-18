#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <assert.h>
#include <algorithm>
#include <chrono>

bool eat_num(std::string &s, unsigned long &outV)
{
	outV = 0;
	int it = 0;
	while (it < s.size() && (s[it] < '0' || s[it] > '9'))
		++it;

	while (it < s.size() && s[it] >= '0' && s[it] <= '9')
	{
		outV = outV * 10 + static_cast<unsigned long>(s[it] - '0');
		++it;
	}

	if (it > 0)
	{
		s = std::string(s.begin() + (it), s.end());
		return true;
	}
	return false;
}

enum class OPERAND
{
	ADD,
	MUL,
};

int concat(int upper, int lower)
{
	int result = lower;
	upper *= 10;
	while (lower >= 10)
	{
		upper *= 10;
		lower /= 10;
	}
	result += upper;
	return result;
}

bool part1_recursive(const std::vector<int> &operands, int idx, int target, int sum)
{
	int result;
	if (idx < 0)
	{
		return sum == target;
	}

	if (part1_recursive(operands, idx - 1, target, sum + operands[idx]))
		return true;
	if (part1_recursive(operands, idx - 1, target, sum * operands[idx]))
		return true;
	if (part1_recursive(operands, idx - 1, target, concat(sum, operands[idx])))
		return true;

	return false;
}

void part1and2()
{
	std::string input;
	unsigned long sum = 0;
	// assert(concat(100, 10) == 10010);
	// assert(concat(1, 100) == 1100);
	// assert(concat(20, 1) == 201);
	// assert(concat(100, 10) == 10010);
	// assert(concat(1, 1) == 11);
	// assert(concat(0, 1) == 1);
	// assert(concat(1, 0) == 10);
	while (std::getline(std::cin, input) && input.size() > 0)
	{
		std::vector<int> operands;
		unsigned long value, operand;
		eat_num(input, value);
		while (eat_num(input, operand))
		{
			operands.push_back(operand);
		}
		std::reverse(operands.begin(), operands.end());
		if (part1_recursive(operands, operands.size() - 1, value, 0))
		{
			sum += value;
		}
	}
	std::cout << "Sum is: " << sum << " ." << std::endl;
}

int main(int, char **)
{
	auto start = std::chrono::high_resolution_clock::now();
	part1and2();
	auto end = std::chrono::high_resolution_clock::now();
	double measurement = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
	std::cout << "Time: " << measurement * 0.0000001 << " s." << std::endl;
}
