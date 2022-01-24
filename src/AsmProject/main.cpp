/*
J�ZYKI ASEMBLEROWE
Projekt: Alogrytm Dijkstry
Wyznacza najkr�tsz� tras� mi�dzy zadanymi miastami (wierzcho�kami grafu)
Miko�aj Malich
Rok akademicki 2021/2022
*/

#include "pch.h"
#include "windows.h"
#include "Form1.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThread]

int main() {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Application::Run(gcnew DijkstraAssembly::Form1()); 
	return 0;
}