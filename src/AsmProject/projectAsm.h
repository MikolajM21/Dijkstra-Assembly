/*
JÊZYKI ASEMBLEROWE
Projekt: Alogrytm Dijkstry
Wyznacza najkrótsz¹ trasê miêdzy zadanymi miastami (wierzcho³kami grafu)
Miko³aj Malich
Rok akademicki 2021/2022
*/

#pragma once
#include "timer.h"
#include "windows.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <deque>
#include <utility>
#include <map>
#include <thread>
#include <time.h>
#include <shared_mutex>

extern int threadsNr, timeCounted;
extern bool cppDll, asmDll;
extern std::string fileRoads, filePaths, fileResults;

typedef HRESULT(CALLBACK* LPFNDLLFUNC)(int*, float*, float*, float*, int*, int*, double*, int*);

namespace {
	std::map < std::pair < std::string, std::string>, double> roads;
	std::deque < std::pair < std::string, std::string>> paths;
	std::map < std::string, std::pair<int, std::pair < float, std::string >>> summits;
	std::deque<std::pair<std::string, std::pair<std::string, float>>> result;
	std::map < std::pair < std::string, std::string>, double>::iterator itRoads;
	std::map < std::string, std::pair <int, std::pair < float, std::string >>> ::iterator itSummits;
	std::vector<std::thread> threadsVector;
	Timer algorithmTimer;
	}
	
int runProgram();
bool loadRoads(std::string& fileRoads, std::map< std::pair < std::string, std::string>, double>& roads);
bool loadPaths(std::string& filePaths, std::deque < std::pair < std::string, std::string>>& paths);
bool checkResultsFile(std::string& fileResults);
void findSummits(std::map< std::pair < std::string, std::string>, double>& roads, std::map < std::string, std::pair<int, std::pair < float, std::string >>>& summits, std::map < std::string, std::pair <int, std::pair < float, std::string >>> ::iterator& itSummits, std::map < std::pair < std::string, std::string>, double>::iterator& itRoads);
void threadHelper(bool cppDll, std::string pathsFirst, std::map< std::pair < std::string, std::string>, double> roads, std::map < std::string, std::pair<int, std::pair < float, std::string >>> summits, std::string fileResults, std::string pathsSecond, std::deque<std::pair<std::string, std::pair<std::string, float>>> result, std::map < std::string, std::pair <int, std::pair < float, std::string >>> ::iterator itSummits);
void dijkstra(bool cppDll, std::string pathsFirst, std::map< std::pair < std::string, std::string>, double> roads, std::map < std::string, std::pair<int, std::pair < float, std::string >>>& summits);
void saveResult(std::string fileResults, std::map < std::string, std::pair<int, std::pair < float, std::string >>> summits, std::string pathsFirst, std::string pathsSecond, std::deque<std::pair<std::string, std::pair<std::string, float>>> result, std::map < std::string, std::pair <int, std::pair < float, std::string >>> ::iterator itSummits);
bool rewriteResult(std::map < std::string, std::pair<int, std::pair < float, std::string >>> summits, std::string pathsFirst, std::string pathsSecond, std::deque<std::pair<std::string, std::pair<std::string,float>>>& result, std::map < std::string, std::pair <int, std::pair < float, std::string >>> :: iterator itSummits);
void deleteStructures(std::map< std::pair < std::string, std::string>, double>& roads, std::map < std::string, std::pair<int, std::pair < float, std::string >>>& summits, std::deque < std::pair < std::string, std::string>>& paths);