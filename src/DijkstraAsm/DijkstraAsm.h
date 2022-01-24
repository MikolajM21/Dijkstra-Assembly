#ifdef DIJKSTRAASM_EXPORTS
#define DIJKSTRAASM_API __declspec(dllexport)
#else
#define DIJKSTRAASM_API __declspec(dllimport)
#endif

class DIJKSTRAASM_API CDijkstraAsm {
public:
	CDijkstraAsm(void);
};

extern DIJKSTRAASM_API int nDijkstraAsm;

DIJKSTRAASM_API int fnDijkstraAsm(void);