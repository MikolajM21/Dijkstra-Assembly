/*
JÊZYKI ASEMBLEROWE
Projekt: Alogrytm Dijkstry
Wyznacza najkrótsz¹ trasê miêdzy zadanymi miastami (wierzcho³kami grafu)
Miko³aj Malich
Rok akademicki 2021/2022
*/

#pragma once
#include "pch.h"
#include "projectAsm.h"

int threadsNr = std::thread::hardware_concurrency();
int timeCounted = 0;
bool cppDll, asmDll = false;
std::string fileRoads, filePaths, fileResults = "";
std::shared_mutex myLock;

int runProgram()
{
	try
	{
		if (loadRoads(fileRoads, roads))
		{
			if (loadPaths(filePaths, paths))
			{
				if (checkResultsFile(fileResults))
				{
					findSummits(roads, summits, itSummits, itRoads);
					int x = 0;
					algorithmTimer.start();
					while (x < paths.size())
					{
						for (int i = 0; i < threadsNr; i++)
						{
							if (x < paths.size()) 
							{
								threadsVector.push_back(std::thread(threadHelper, std::ref(cppDll), std::ref(paths[x].first), std::ref(roads), std::ref(summits), std::ref(fileResults), std::ref(paths[x].second), std::ref(result), std::ref(itSummits)));
								x++;
							}
							else
							{
								i = 65;
							}
						}
						for (std::thread& temp : threadsVector)
						{
							temp.join();
						}
						threadsVector.clear();
					}
					algorithmTimer.stop();
					timeCounted = algorithmTimer.getTime();
				}
				else
				{
					return 3;
				}
			}
			else
			{
				return 2;
			}
		}
		else
		{
			return 1;
		}
	}
	catch (...) 
	{
		return 4;
	}
	deleteStructures(roads, summits, paths);
	threadsVector.clear();
	return 0;
}
bool loadRoads(std::string& fileRoads, std::map< std::pair < std::string, std::string>, double>& roads)
{
	std::fstream file1;
	file1.open(fileRoads, std::ios::in);
	if (file1.good())
	{
		std::string city1, city2;
		double distance;
		while (!file1.eof())
		{
			file1 >> city1 >> city2 >> distance;
			roads.insert(make_pair(make_pair(city1, city2), distance));
		}
		file1.close();
		return true;
	}
	else
	{
		return false;
	}
}
bool loadPaths(std::string& filePaths, std::deque < std::pair < std::string, std::string>>& paths)
{
	std::fstream file1;
	file1.open(filePaths, std::ios::in);
	if (file1.good())
	{
		std::string startCity, finalCity;
		while (!file1.eof())
		{
			file1 >> startCity >> finalCity;
			paths.push_back(make_pair(startCity, finalCity));
		}
		file1.close();
		return true;
	}
	else
	{
		return false;
	}
}
bool checkResultsFile(std::string& fileResults)
{
	std::ofstream file1;
	file1.open(fileResults);
	if (file1.good())
	{
		file1.close();
		return true;
	}
	else
	{
		return false;
	}
}
void findSummits(std::map< std::pair < std::string, std::string>, double>& roads, std::map < std::string, std::pair<int, std::pair < float, std::string >>>& summits, std::map < std::string, std::pair <int, std::pair < float, std::string >>> ::iterator& itSummits, std::map < std::pair < std::string, std::string>, double>::iterator& itRoads)
{
	itRoads = roads.begin();
	auto itS2 = itSummits;
	summits.emplace(make_pair(itRoads->first.first, std::make_pair(0, std::make_pair(0, "0"))));
	for (const auto& elem : roads)
	{
		itSummits = itS2 = summits.begin();
		for (const auto& elementS : summits)
		{
			if (elementS.first != elem.first.first)
			{
				itSummits++;
			}
			if (elementS.first != elem.first.second)
			{
				itS2++;
			}
		}
		if (itSummits == summits.end())
		{
			summits.emplace(std::make_pair(elem.first.first, std::make_pair(0, std::make_pair(0, "0"))));
		}
		if (itS2 == summits.end())
		{
			summits.emplace(std::make_pair(elem.first.second, std::make_pair(0, std::make_pair(0, "0"))));
		}
	}
}
void threadHelper(bool cppDll, std::string pathsFirst, std::map< std::pair < std::string, std::string>, double> roads, std::map < std::string, std::pair<int, std::pair < float, std::string >>> summits, std::string fileResults, std::string pathsSecond, std::deque<std::pair<std::string, std::pair<std::string, float>>> result, std::map < std::string, std::pair <int, std::pair < float, std::string >>> ::iterator itSummits) 
{
			dijkstra(cppDll, pathsFirst, roads, summits);
			saveResult(fileResults, summits, pathsFirst, pathsSecond, result, itSummits);
			result.clear();
}
void dijkstra(bool cppDll, std::string pathsFirst, std::map< std::pair < std::string, std::string>, double> roads, std::map < std::string, std::pair<int, std::pair < float, std::string >>>& summits) 
{
	for (auto& elementS : summits)
	{
		if (elementS.first == pathsFirst)
		{
			elementS.second.second.first = 0;
		}
		else
		{
			elementS.second.second.first = std::numeric_limits<float>::infinity();
		}
		elementS.second.second.second = "0";
	}

	int size = summits.size();
	float tmp = std::numeric_limits<float>::infinity();
	float min;
	float* dist = new float[size];
	std::fill(dist, dist + size, tmp);
	int* prev = new int[size];
	std::fill(prev, prev + size, -1);
	int* visited = new int[size]();
	double* graph = new double[size * size]();
	int i = 0, j = 0, u = 0;

	for (const auto& elemSummit : summits)
	{
		for (const auto& elemRoad : roads)
		{
			if (elemRoad.first.first == elemSummit.first)
			{
				j = 0;
				for (const auto& elemTmp : summits)
				{
					if (elemRoad.first.second == elemTmp.first)
					{
						*(graph + i * size + j) = elemRoad.second;
					}
					j++;
				}
			}
		}
		if (elemSummit.first == pathsFirst)
		{
			*(dist + i) = 0;
		}
		i++;
	}
	
	if (cppDll)
	{
		HINSTANCE lib = ::LoadLibrary(TEXT("DijkstraCpp.dll"));
		if (lib != NULL)
		{
			typedef int (*ptr)(int*, float*, float*, float*, int*, int*, double*, int*);
			ptr funPtr = reinterpret_cast<ptr>(::GetProcAddress(lib, "dijkstraPart"));
			if (funPtr != NULL)
			{
				funPtr(&size, &min, &tmp, dist, visited, &u, graph, prev);
			}
		}
	}
	else
	{
		HINSTANCE hDLL = LoadLibrary(L"DijkstraAsm");
		LPFNDLLFUNC lpfnDllFunc1;
		if (NULL != hDLL)
		{
			lpfnDllFunc1 = (LPFNDLLFUNC)GetProcAddress(hDLL, "dijkstraPart");
			if (NULL != lpfnDllFunc1) {
				lpfnDllFunc1(&size, &min, &tmp, dist, visited, &u, graph, prev);
			}
		}
	}

	i = 0;
	for (auto& elem : summits)
	{
		j = 0;
		elem.second.second.first = *(dist + i);
		for (auto& elemTmp : summits)
		{
			if (j == *(prev + i))
			{
				elem.second.second.second = elemTmp.first;
			}
			else if(*(prev + i) == -1)
			{
				elem.second.second.second = "0";
			}
			j++;
		}
		i++;
	}

	for (auto& elementW : summits)
	{
		elementW.second.first = 0;
	}

	delete[] dist;
	delete[] prev;
	delete[] visited;
	delete[] graph;
}
bool rewriteResult(std::map < std::string, std::pair<int, std::pair < float, std::string >>> summits, std::string pathsFirst, std::string pathsSecond, std::deque<std::pair<std::string, std::pair<std::string, float>>>& result, std::map < std::string, std::pair <int, std::pair < float, std::string >>> ::iterator itSummits)
{
	std::string city;
	itSummits = summits.begin();
	for (auto tmp : summits)
	{
		if (tmp.first == pathsSecond)
		{
			break;
		}
		itSummits++;
	}
	if (itSummits == summits.end())
	{
		return false;
	}
	result.push_front(make_pair(itSummits->second.second.second, make_pair(itSummits->first, itSummits->second.second.first)));
	city = itSummits->second.second.second;
	while (city != pathsFirst)
	{
		if (itSummits->second.second.second == "0")
		{
			return false;
		}
		for (itSummits = summits.begin(); itSummits->first != city; itSummits++) {}
		result.push_front(make_pair(itSummits->second.second.second, make_pair(itSummits->first, itSummits->second.second.first)));
		city = itSummits->second.second.second;
	}
	return true;
}
void saveResult(std::string fileResults, std::map < std::string, std::pair<int, std::pair < float, std::string >>> summits, std::string pathsFirst, std::string pathsSecond, std::deque<std::pair<std::string, std::pair<std::string, float>>> result, std::map < std::string, std::pair <int, std::pair < float, std::string >>> ::iterator itSummits)
{
	std::ofstream file1;
	bool finished = false;
	while (!finished) 
	{
		if (!file1.is_open()) 
		{
			std::lock_guard<std::shared_mutex> guard(myLock);
			file1.open(fileResults, std::ios_base::app);
			file1 << std::endl << "Trasa: " << pathsFirst << " --> " << pathsSecond;
			if (rewriteResult(summits, pathsFirst, pathsSecond, result, itSummits))
			{
				double sum = 0;
				for (const auto& elem : result)
				{
					sum += elem.second.second;
				}
				file1 << " (" << sum << "km):" << std::endl;
				for (const auto& elem : result)
				{
					file1 << elem.first << " --> " << elem.second.first << " " << elem.second.second << std::endl;
				}
				finished = true;
				file1.close();
			}
			else
			{
				file1 << std::endl << "TRASA NIEMOZLIWA DO WYZNACZENIA" << std::endl;
				finished = true;
				file1.close();
			}
		}
	}
	file1.close();
	result.clear();
}
void deleteStructures(std::map< std::pair < std::string, std::string>, double>& roads, std::map < std::string, std::pair<int, std::pair < float, std::string >>>& summits, std::deque < std::pair < std::string, std::string>>& paths)
{
	roads.clear();
	summits.clear();
	paths.clear();
}