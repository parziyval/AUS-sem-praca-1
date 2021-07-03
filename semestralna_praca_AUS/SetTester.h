#pragma once
#include "Mnozina.h"
#include "TimeMeasurement.h"

const int polomerMnoziny = 50000;
class SetTester
{
private:
	TimeMeasurement* stopky;
	char scenar;
	int pocetOp = 0;
	int podielVloz = 0;
	int podielOdober = 0;
	int podielPatri = 0;
	int podielZjednotenie = 0;
	int podielPrienik = 0;
	int podielRozdiel = 0;
public:
	SetTester();
	~SetTester();
	void spustiTestyJednej(std::string nazovSuboru, int pOp = 0, 
		int pVloz = 0, int pOdober = 0, int pPatri = 0);
private:
	void vloz(int prvok, Mnozina* mnozina);
	void odober(int prvok, Mnozina* mnozina);
	void patri(int prvok, Mnozina* mnozina);

	void zjednotenie();
	void prienik();
	void rozdiel();

	void zapis(std::ofstream* zapisovac, std::string nazovInstr, int size);
};

inline SetTester::SetTester()
{
	stopky = new TimeMeasurement();
}

inline SetTester::~SetTester()
{
	delete stopky;
}

inline void SetTester::spustiTestyJednej(std::string nazovSuboru, int pOp, int pVloz, int pOdober, int pPatri)
{
	nazovSuboru = nazovSuboru + ".csv";
	std::cout << "Zapisujem do " << nazovSuboru;

	srand(time(0));
	std::ofstream* zapisovac = new std::ofstream(nazovSuboru);
	std::string nazovInstr;
	stopky->reset();
	Mnozina* mnozina = nullptr;
	for (int i = 0; i < polomerMnoziny; i+=100)
	{
		mnozina = new Mnozina(-i, i);
		int prvok = mnozina->getMin() + rand() % mnozina->getMax() + 1;
		mnozina->vloz(prvok);
		zapis(zapisovac, "vloz", mnozina->size());
		mnozina->odober(prvok);
		zapis(zapisovac, "odober", mnozina->size());
		mnozina->patriDoMnoziny(prvok);
		zapis(zapisovac, "patri", mnozina->size());
		delete mnozina;
	}

	std::cout << "      hotovo" << std::endl;

	delete zapisovac;
}

inline void SetTester::vloz(int prvok, Mnozina* mnozina)
{
	stopky->start();
	mnozina->vloz(prvok);
	stopky->stop();

}

inline void SetTester::odober(int prvok, Mnozina* mnozina)
{
	stopky->start();
	mnozina->odober(prvok);
	stopky->stop();
}

inline void SetTester::patri(int prvok, Mnozina* mnozina)
{
	stopky->start();
	mnozina->patriDoMnoziny(prvok);
	stopky->stop();
}

inline void SetTester::zapis(std::ofstream* zapisovac, std::string nazovInstr, int size)
{
	(*zapisovac) << nazovInstr;
	(*zapisovac) << ";";
	(*zapisovac) << size;
	(*zapisovac) << ";";
	(*zapisovac) << stopky->elapsed().count();
	(*zapisovac) << "\n";

	stopky->reset();
}


