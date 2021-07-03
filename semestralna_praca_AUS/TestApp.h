#pragma once
#include "../structures/heap_monitor.h"
#include "ListTester.h"
#include "Konstanty.h"

class TestApp
{
public:
	TestApp();
	~TestApp();

	void spusti();
	void spustiVyberTabulky();
private:
	void spustiVyberScenaraList();
	void spustiTestyListov(char scenar,int pOp, int pVloz, int pZrus, int pSpristupni, int pIndexPrvku);
	void nastavVlastnyScenarList();
	void zapisTestdoSuboruList(int pOp, int pVloz, int pZrus, int pSpristupni, int pIndexPrvku);
	void nacitajTestZoSuboruList();

	
	void opravCin();

};

