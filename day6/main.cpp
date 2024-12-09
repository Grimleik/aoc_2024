#include <iostream>
#include <string>
#include <vector>
#include <assert.h>
#include <map>
void part1()
{
	std::vector<std::string> map;
	std::string input;
	int sRow = -1, sCol = -1;
	while (std::getline(std::cin, input) && input.size() > 0)
	{
		auto it = std::find(input.begin(), input.end(), '^');
		if (it != input.end())
		{
			assert(sRow == -1 && sCol == -1);
			sRow = static_cast<int>(map.size());
			sCol = static_cast<int>(it - input.begin());
			std::cout << "Starting location: " << sRow << " " << sCol << std::endl;
		}
		map.push_back(input);
	}

	// NOTE(pf): assuming constant width of input.
	int width = static_cast<int>(map[0].size());
	int height = static_cast<int>(map.size());
	int newX = sCol, newY = sRow;
	int direction = 0;
	const std::vector<std::pair<int, int>> directions = {
		{0, -1}, // UP
		{1, 0},	 // RIGHT
		{0, 1},	 // DOWN
		{-1, 0}	 // LEFT
	};

	auto dir = directions[direction];
	map[newY].at(newX) = 'X';
	newX += dir.first;
	newY += dir.second;
	int visits = 1;
	while (newX >= 0 && newX < width &&
		   newY >= 0 && newY < height)

	{
		if (map[newY].at(newX) == '#')
		{
			// NOTE(pf): Revert previous move since the condition to check is in the while loop!
			newX -= dir.first;
			newY -= dir.second;
			direction = (direction + 1) % 4;
			dir = directions[direction];
			// std::cout << "direction change! visits made: " << visits << std::endl;
		}
		else if (map[newY].at(newX) == '.')
		{
			int dirCheck = (direction + 1) % 4;
			map[newY].at(newX) = 'X';
			++visits;
		}
		newX += dir.first;
		newY += dir.second;
	}

	// NOTE(pf): Debug map rendering.
	for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x < width; ++x)
		{
			std::cout << map[y].at(x);
		}
		std::cout << std::endl;
	}

	std::cout << "The guard visists: " << visits << " positions." << std::endl;
}

void part2()
{
	std::vector<std::string> map;
	std::string input;
	int sRow = -1, sCol = -1;
	while (std::getline(std::cin, input) && input.size() > 0)
	{
		auto it = std::find(input.begin(), input.end(), '^');
		if (it != input.end())
		{
			assert(sRow == -1 && sCol == -1);
			sRow = static_cast<int>(map.size());
			sCol = static_cast<int>(it - input.begin());
			std::cout << "Starting location: " << sRow << " " << sCol << std::endl;
		}
		map.push_back(input);
	}

	// NOTE(pf): assuming constant width of input.
	int width = static_cast<int>(map[0].size());
	int height = static_cast<int>(map.size());
	int newX = sCol, newY = sRow;
	int direction = 0;
	const std::vector<std::pair<int, int>> directions = {
		{0, -1}, // UP
		{1, 0},	 // RIGHT
		{0, 1},	 // DOWN
		{-1, 0}	 // LEFT
	};

	auto dir = directions[direction];
	map[newY].at(newX) = 'X';
	newX += dir.first;
	newY += dir.second;
	int blockers = 0;
	while (newX >= 0 && newX < width &&
		   newY >= 0 && newY < height)
	{
		char c = map[newY].at(newX);
		if (c == '#')
		{
			// NOTE(pf): Revert previous move since the condition to check is in the while loop!
			newX -= dir.first;
			newY -= dir.second;
			direction = (direction + 1) % 4;
			dir = directions[direction];
			// std::cout << "direction change! visits made: " << visits << std::endl;
		}
		else
		{
			// NOTE(pf): For the logic of placing an obstacle we have to check
			// ahead! Only do this if no obstacle isn't already there!
			int checkX = newX + dir.first, checkY = newY + dir.second;
			if (checkX >= 0 && checkX < width &&
				checkY >= 0 && checkY < height &&
				map[checkY].at(checkX) != '#' &&
				map[checkY].at(checkX) != 'O')
			{
				// NOTE(pf): Insert our 'potential blocker.
				std::map<int, std::vector<std::pair<int, int>>> directionBlockers;
				directionBlockers[direction].push_back(std::make_pair(checkX, checkY));
				int loopDirection = (direction + 1) % 4;
				auto checkDir = directions[loopDirection];
				checkX = newX + checkDir.first;
				checkY = newY + checkDir.second;
				while (checkX >= 0 && checkX < width &&
					   checkY >= 0 && checkY < height)
				{
					// NOTE(pf): Have we been here before ?
					if (directionBlockers.find(loopDirection) != directionBlockers.end())
					{
						if (std::find(directionBlockers.at(loopDirection).begin(),
									  directionBlockers.at(loopDirection).end(),
									  std::make_pair(checkX, checkY)) != directionBlockers.at(loopDirection).end())
						{
							map[newY + dir.second].at(newX + dir.first) = 'O';
							++blockers;
							// goto end;
							break;
						}
					}

					if (map[checkY].at(checkX) == '#')
					{
						if (directionBlockers.find(loopDirection) == directionBlockers.end())
						{
							directionBlockers[loopDirection] = std::vector<std::pair<int, int>>();
						}

						directionBlockers.at(loopDirection).push_back(std::make_pair(checkX, checkY));
						checkX -= checkDir.first;
						checkY -= checkDir.second;
						loopDirection = (loopDirection + 1) % 4;
						checkDir = directions[loopDirection];
					}
					checkX += checkDir.first;
					checkY += checkDir.second;
				}
			}
			map[newY].at(newX) = map[newY].at(newX) == '.' ? 'X' : map[newY].at(newX);
		}
		newX += dir.first;
		newY += dir.second;
	}

end:
	// NOTE(pf): Debug map rendering.
	for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x < width; ++x)
		{
			std::cout << map[y].at(x);
		}
		std::cout << std::endl;
	}

	std::cout << "We can place : " << blockers << " blockers." << std::endl;
}

int main(int, char **)
{
	// part1();
	part2();
}
