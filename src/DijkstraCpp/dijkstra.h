/*
JÊZYKI ASEMBLEROWE
Projekt: Alogrytm Dijkstry
Wyznacza najkrótsz¹ trasê miêdzy zadanymi miastami (wierzcho³kami grafu)
Miko³aj Malich
Rok akademicki 2021/2022
*/

#pragma once
#ifdef DIJKSTRACPP_EXPORTS
#define DIJKSTRACPP_API __declspec(dllexport)
#else
#define DIJKSTRACPP_API __declspec(dllimport)
#endif

extern "C" DIJKSTRACPP_API void dijkstraPart(int* size, float* min, float* tmp, float* dist, int* visited, int* u, double* graph, int* prev);