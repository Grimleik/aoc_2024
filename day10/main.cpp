#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <Windows.h>
#include <chrono>

#define DEBUG_RENDER 1
#define DEAD_END (-1)
std::map<std::pair<int, int>, std::set<int>> cachedData;

void trail_search(std::pair<int, int> &idx, int w, int h, const std::vector<std::string> &map)
{
	const std::vector<std::pair<int, int>> directions = {
		{-1, 0},
		{0, 1},
		{1, 0},
		{0, -1}};

	for (int i = 0; i < 4; ++i)
	{
		int newY = idx.first + directions[i].first;
		int newX = idx.second + directions[i].second;
		if (newX >= 0 && newX < w &&
			newY >= 0 && newY < h)
		{
			int slope = map[newY][newX] - map[idx.first][idx.second];
			if (slope == 1)
			{
				if (map[newY][newX] == '9')
				{
					cachedData[idx].insert(newY * w + newX);
				}
				else
				{
					auto neighbourIdx = std::make_pair(newY, newX);
					auto &cache = cachedData[neighbourIdx];
					if (cache.size() == 0)
					{
						trail_search(neighbourIdx, w, h, map);
					}

					if (cache.size() == 1 && *cache.begin() == DEAD_END)
					{
						continue;
					}
					cachedData[idx].insert(
						cachedData[neighbourIdx].begin(),
						cachedData[neighbourIdx].end());
				}
			}
		}
	}
	// All neighbours leads to nothing ? Mark as 'dead end'
	if (cachedData[idx].size() == 0)
	{
		cachedData[idx].insert(DEAD_END);
	}
}

int main(int, char **)
{
	auto start = std::chrono::high_resolution_clock::now();

	std::string input;
	std::vector<std::string> trailMap;
	std::vector<std::pair<int, int>> startingLocs;
	int height = 0, width;
	while (std::getline(std::cin, input) && input.size() > 0)
	{
		std::string trailLine;
		width = 0;
		for (auto &c : input)
		{
			int token = c - '0';
			if (token >= 0 && token <= 9)
			{
				if (token == 0)
					startingLocs.push_back({height, width});
				trailLine += (token + '0');
			}
			else
			{
				trailLine += '.';
			}
			++width;
		}
		trailMap.push_back(trailLine);
		++height;
	}

	int totalScore = 0;
	for (auto &sl : startingLocs)
	{
		trail_search(sl, width, height, trailMap);
		std::cout << "Trail score: " << cachedData[sl].size() << std::endl;
		totalScore += static_cast<int>(cachedData[sl].size());
	}

#if DEBUG_RENDER
	height = 0;
	int i = 0;
	for (auto &line : trailMap)
	{
		width = 0;
		for (auto &el : line)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
			if (std::find(startingLocs.begin(), startingLocs.end(), std::make_pair(height, width)) != startingLocs.end())
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), i);
				if ((i + 1) == 7)
					++i;
				++i;
				if(i > 15)
					i = 0;
			}
			std::cout << cachedData[std::make_pair(height, width)].size();
			++width;
		}
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		std::cout << std::endl;
		++height;
	}
#endif
	std::cout << "Total score: " << totalScore << " ." << std::endl;

	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::milli> elapsed = end - start;
	std::cout << "Elapsed time: " << elapsed.count() << " ms" << std::endl;
}
