#pragma once
#include "../structures/heap_monitor.h"
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include "TimeMeasurement.h"
#include "../structures/table/table.h"
#include "../structures/table/sequence_table.h"
#include "../structures/table/sorted_sequence_table.h"
#include "../structures/table/binary_search_tree.h"
#include "../structures/table/treap.h"
#include "../structures/table/hash_table.h"

#define tableAPocetOp 100000
#define tableAPodielVloz 30
#define tableAPodielSpristupni 60
#define tableAPodielOdstran 10

#define tableBPocetOp 100000
#define tableBPodielVloz 45
#define tableBPodielSpristupni 10
#define tableBPodielOdstran 45

#define tableCPocetOp 100000
#define tableCPodielVloz 30 //70
#define tableCPodielSpristupni 40 //15
#define tableCPodielOdstran 30 //15

template<typename K,typename T>
class TableTester
{
private:
	TimeMeasurement* stopky;
	char scenar;
	int pocetOp = 0;
	int podielVloz = 0;
	int podielZrus = 0;
	int podielSpristupni = 0;
public:
	TableTester();
	~TableTester();
	void spustiTesty(structures::Table<K, T>* table, std::string nazovSuboru,
		char scenar, int pOp = 0, int pVloz = 0 , int pSpristupni = 0, int pZrus = 0);

	void vloz(T& data, K& kluc, structures::Table<K, T>* table);
	void odstran(K& kluc, structures::Table<K, T>* table);
	void spristupni(K& kluc, structures::Table<K, T>* table);

	void vykonajVlozenieXKrat(structures::Table<K, T>* table, std::string nazovSuboru, int pocetOperacii);
	void vykonajZrusenieXKrat(structures::Table<K, T>* table, std::string nazovSuboru, int pocetOperacii);
	void vykonajPristupXKrat(structures::Table<K, T>* table, std::string nazovSuboru, int pocetOperacii);

	void nastavScenar(char scenar, int pOp = 0, int pVloz = 0, int pSpristupni = 0, int pZrus = 0);
	void zapis(std::ofstream* zapisovac, std::string nazovInstr, int size_);
};

template<typename K, typename T>
inline TableTester<K, T>::TableTester()
{
	stopky = new TimeMeasurement();
}

template<typename K, typename T>
inline TableTester<K, T>::~TableTester()
{
	delete stopky;
}

template<typename K, typename T>
inline void TableTester<K, T>::spustiTesty(structures::Table<K, T>* table, std::string nazovSuboru, char scenar, int pOp, int pVloz, int pSpristupni, int pZrus)
{
	switch (scenar)
	{
	case 'A': nastavScenar('A'); break;
	case 'B': nastavScenar('B'); break;
	case 'C': nastavScenar('C'); break;
	default: nastavScenar('V', pOp, pVloz, pZrus, pSpristupni); break;
	}

	nazovSuboru = nazovSuboru + scenar + ".csv";
	std::cout << "Zapisujem do: " << nazovSuboru;

	srand(time(0));


	std::ofstream zapisovac(nazovSuboru);
	std::string nazovInstr;

	table->clear();
	stopky->reset();
	int i = 0;
	while (i < pocetOp)
	{
		nazovInstr = "";
		int random = 1 + rand() % 100; //podiel zo sto percent
		K kluc = rand();

		if (random <= podielVloz) //vloz
		{
			if (!table->containsKey(kluc))
			{
				T obj;
				nazovInstr = "Vloz";
				vloz(obj, kluc, table);
			}

		}
		else if (random <= (podielVloz + podielSpristupni)) { //spristupni
			if (table->containsKey(kluc) && !table->isEmpty())
			{
				nazovInstr = "Spristupni";
				spristupni(kluc, table);
			}
		}
		else { //odstran
			if (table->containsKey(kluc) && !table->isEmpty())
			{
				nazovInstr = "Odstran";
				odstran(kluc, table);
			}
		}

		if (nazovInstr != "") //ak sa vykonala nejaka operacia
		{
			zapis(&zapisovac, nazovInstr, table->size());
			i++;
		}
	}

	std::cout << "      hotovo" << std::endl;

	zapisovac.close();
}



template<typename K, typename T>
inline void TableTester<K, T>::vloz(T& data, K& kluc, structures::Table<K, T>* table)
{
	stopky->start();
	table->insert(kluc, data);
	stopky->stop();
}

template<typename K, typename T>
inline void TableTester<K, T>::odstran(K& kluc, structures::Table<K, T>* table)
{
	stopky->start();
	table->remove(kluc);
	stopky->stop();
}

template<typename K, typename T>
inline void TableTester<K, T>::spristupni(K& kluc, structures::Table<K, T>* table)
{
	stopky->start();
	table[kluc];
	stopky->stop();
}

template<typename K, typename T>
inline void TableTester<K, T>::vykonajVlozenieXKrat(structures::Table<K, T>* table, std::string nazovSuboru, int pocetOperacii)
{
	nazovSuboru = nazovSuboru + "Vlozenie" + std::to_string(pocetOperacii) + "krat.csv";
	std::cout << nazovSuboru;
	std::ofstream zapisovac(nazovSuboru);
	table->clear();
	srand(time(0));
	int i = 0;
	while (i < pocetOperacii)
	{
		stopky->reset();
		K kluc = rand();
		if (!table->containsKey(kluc))
		{
			T obj;
			stopky->start();
			table->insert(kluc, obj);
			stopky->stop();
			zapis(&zapisovac, "Vloz", table->size());
			i++;
		}
	}
	zapisovac.close();
	std::cout << "         hotovo\n";
}

template<typename K, typename T>
inline void TableTester<K, T>::vykonajZrusenieXKrat(structures::Table<K, T>* table, std::string nazovSuboru, int pocetOperacii)
{
	table->clear();
	for (int i = 0; i < pocetOperacii; i++)
	{
		T obj;
		table->insert(i, obj);
	}

	nazovSuboru = nazovSuboru + "Zrusenie" + std::to_string(pocetOperacii) + "krat.csv";
	std::cout << nazovSuboru;
	std::ofstream zapisovac(nazovSuboru);
	for (int i = 0; i < pocetOperacii; i++)
	{
		stopky->reset();
		stopky->start();
		table->remove(i);
		stopky->stop();
		zapis(&zapisovac, "Zrus", table->size());
		
	}
	zapisovac.close();
	std::cout << "         hotovo\n";
}

template<typename K, typename T>
inline void TableTester<K, T>::vykonajPristupXKrat(structures::Table<K, T>* table, std::string nazovSuboru, int pocetOperacii)
{
	nazovSuboru = nazovSuboru + "Pristup" + std::to_string(pocetOperacii) + "krat.csv";
	std::cout << nazovSuboru;
	std::ofstream zapisovac(nazovSuboru);

	table->clear();
	srand(time(NULL));
	int velkost;
	for (int i = 0; i < pocetOperacii; i++)
	{
		T obj;
		table->insert(i, obj);
		velkost = table->size();
		stopky->reset();
		stopky->start();
		table[rand() % velkost];
		stopky->stop();
		zapis(&zapisovac, "Spristupni", table->size());
	}

	zapisovac.close();
	std::cout << "         hotovo\n";
}


template<typename K, typename T>
inline void TableTester<K, T>::nastavScenar(char scenar, int pOp, int pVloz, int pSpristupni, int pZrus)
{
	switch (scenar)
	{
	case 'A':
		this->pocetOp = tableAPocetOp;
		this->podielVloz = tableAPodielVloz;
		this->podielSpristupni = tableAPodielSpristupni;
		this->podielZrus = tableAPodielOdstran;
		break;
	case 'B':
		this->pocetOp = tableBPocetOp;
		this->podielVloz = tableBPodielVloz;
		this->podielSpristupni = tableBPodielSpristupni;
		this->podielZrus = tableBPodielOdstran;
		break;
	case 'C':
		this->pocetOp = tableCPocetOp;
		this->podielVloz = tableCPodielVloz;
		this->podielSpristupni = tableCPodielSpristupni;
		this->podielZrus = tableCPodielOdstran;
		break;
	default:
		this->pocetOp = pOp;
		this->podielVloz = pVloz;
		this->podielSpristupni = pSpristupni;
		this->podielZrus = pZrus;
		break;
	}
}

template<typename K, typename T>
inline void TableTester<K, T>::zapis(std::ofstream* zapisovac, std::string nazovInstr, int size_)
{
	(*zapisovac) << nazovInstr;
	(*zapisovac) << ";";
	(*zapisovac) << size_;
	(*zapisovac) << ";";
	(*zapisovac) << stopky->elapsed().count();
	(*zapisovac) << "\n";

	stopky->reset();
}
