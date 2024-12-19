#include <iostream>
#include <map>
#include <vector>
#include <string>

struct location_data
{
	int x, y;
};

void part1()
{
	int width, height = 0;
	std::map<char, std::vector<location_data>> antenna_pairs;
	std::string input;
	std::vector<std::string> dbgMap;
	while (std::getline(std::cin, input) && input.size() > 0)
	{
		width = 0;
		for (auto &c : input)
		{
			if (c != '.' && c != '#')
			{
				antenna_pairs[c].push_back({width, height});
			}
			++width;
		}
		std::string dbgString(width, '.');
		dbgMap.push_back(dbgString);
		++height;
	}

	int dbgHeight = 0;
	int dbgWidth = 0;
	int uniqueLocations = 0;
	for (auto &antennaData : antenna_pairs)
	{
		dbgWidth = 0;
		for (int i = 0; i < antennaData.second.size(); ++i)
		{
			dbgWidth++;
			for (int j = i + 1; j < antennaData.second.size(); ++j)
			{
				auto &a1 = antennaData.second[i];
				auto &a2 = antennaData.second[j];
				int diffx = a1.x - a2.x;
				int diffy = a1.y - a2.y;
				// NOTE(pf): Going 'down' in y but x can be either +/-.
				if ((a1.x + diffx) >= 0 && (a1.x + diffx) < width && (a1.y + diffy) >= 0)
				{
					if (dbgMap[a1.y + diffy].at(a1.x + diffx) != '#')
					{
						dbgMap[a1.y + diffy].at(a1.x + diffx) = '#';
						++uniqueLocations;
					}
				}
				if ((a2.x - diffx) >= 0 && (a2.x - diffx) < width && (a2.y - diffy) < height)
				{
					if (dbgMap[a2.y - diffy].at(a2.x - diffx) != '#')
					{
						dbgMap[a2.y - diffy].at(a2.x - diffx) = '#';
						++uniqueLocations;
					}
				}
			}
		}
		dbgHeight++;
	}

	for (auto &line : dbgMap)
	{
		std::cout << line << std::endl;
	}

	std::cout << "There are " << uniqueLocations << " unique locations." << std::endl;
}

void part2()
{
	int width, height = 0;
	std::map<char, std::vector<location_data>> antenna_pairs;
	std::string input;
	std::vector<std::string> dbgMap;
	while (std::getline(std::cin, input) && input.size() > 0)
	{
		width = 0;
		for (auto &c : input)
		{
			if (c != '.' && c != '#')
			{
				antenna_pairs[c].push_back({width, height});
			}
			++width;
		}
		std::string dbgString(width, '.');
		dbgMap.push_back(dbgString);
		++height;
	}

	int dbgHeight = 0;
	int dbgWidth = 0;
	int uniqueLocations = 0;
	for (auto &antennaData : antenna_pairs)
	{
		dbgWidth = 0;
		for (int i = 0; i < antennaData.second.size(); ++i)
		{
			dbgWidth++;
			for (int j = i + 1; j < antennaData.second.size(); ++j)
			{
				auto &a1 = antennaData.second[i];
				auto &a2 = antennaData.second[j];
				int diffx = a1.x - a2.x;
				int diffy = a1.y - a2.y;
				int locX = a1.x;
				int locY = a1.y;

				// NOTE(pf): Going 'down' in y but x can be either +/-.
				while (locX >= 0 && locX < width && locY >= 0 && locY < height)
				{
					if (dbgMap[locY].at(locX) != '#')
					{
						dbgMap[locY].at(locX) = '#';
						++uniqueLocations;
					}
					locX += diffx;
					locY += diffy;
				}

				locX = a2.x;
				locY = a2.y;
				while (locX >= 0 && locX < width && locY >= 0 && locY < height)
				{
					if (dbgMap[locY].at(locX) != '#')
					{
						dbgMap[locY].at(locX) = '#';
						++uniqueLocations;
					}
					locX -= diffx;
					locY -= diffy;
				}

			}
		}
		dbgHeight++;
	}

	for (auto &line : dbgMap)
	{
		std::cout << line << std::endl;
	}

	std::cout << "There are " << uniqueLocations << " unique locations." << std::endl;
}

int main(int, char **)
{
	// part1();
	part2();
	return 0;
}
