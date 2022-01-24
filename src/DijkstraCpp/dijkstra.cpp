/*
JÊZYKI ASEMBLEROWE
Projekt: Alogrytm Dijkstry
Wyznacza najkrótsz¹ trasê miêdzy zadanymi miastami (wierzcho³kami grafu)
Miko³aj Malich
Rok akademicki 2021/2022
*/

#define dijkstra __declspec(dllexport)
#include "pch.h"
#include "dijkstra.h"

void dijkstraPart(int* size, float* min, float* tmp, float* dist, int* visited, int* u, double* graph, int* prev)
{
	int x = 0;
	while (x != *size)
	{
		*min = *tmp;
		for (int j = 0; j < *size; j++)
		{
			if (*(dist + j) <= *min && *(visited + j) != 1)
			{
				*u = j;
				*min = *(dist + j);
			}
		}

		for (int v = 0; v < *size; v++)
		{
			if (*(graph + *u * *size + v) > 0 && *(visited + v) != 1)
			{
				//relaksacja
				if ((*(dist + *u) + *(graph + *u * *size + v)) < *(dist + v))
				{
					*(dist + v) = *(graph + *u * *size + v);
					*(prev + v) = *u;
				}
			}
		}
		*(visited + *u) = 1;
		x++;
	}
}