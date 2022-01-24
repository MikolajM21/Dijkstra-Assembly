/*
J�ZYKI ASEMBLEROWE
Projekt: Alogrytm Dijkstry
Wyznacza najkr�tsz� tras� mi�dzy zadanymi miastami (wierzcho�kami grafu)
Miko�aj Malich
Rok akademicki 2021/2022
*/

#pragma once
#ifdef DIJKSTRACPP_EXPORTS
#define DIJKSTRACPP_API __declspec(dllexport)
#else
#define DIJKSTRACPP_API __declspec(dllimport)
#endif

extern "C" DIJKSTRACPP_API void dijkstraPart(int* size, float* min, float* tmp, float* dist, int* visited, int* u, double* graph, int* prev);