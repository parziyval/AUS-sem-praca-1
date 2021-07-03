#pragma once
#include "../structures/heap_monitor.h"
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include "TimeMeasurement.h"
#include "../structures/list/list.h"
#include "../structures/list/array_list.h"
#include "../structures/list/linked_list.h"
#include "Konstanty.h"

const int listPocetPrvkovZac = 500;
template<typename T>
class ListTester
{
private:
	TimeMeasurement* stopky;
	char scenar;
	int pocetOp = 0;
	int podielVloz = 0;
	int podielZrus = 0;
	int podielSpristupni = 0;
	int podielIndexPrvku = 0;
public:
	ListTester();
	~ListTester();
	void spustiTesty(structures::List<T>* list, std::string nazovSuboru, 
						char scenar, int pOp = 0, int pVloz = 0, int pZrus = 0, int pSpristupni = 0, int pIndexPrvku = 0);

	void vlozPrvy(structures::List<T>* list, std::string nazovSuboru, std::ofstream* zapisovac);
	void vlozPosledny(structures::List<T>* list, std::string nazovSuboru, std::ofstream* zapisovac);
	void vlozNaIndex(structures::List<T>* list, std::string nazovSuboru, std::ofstream* zapisovac);
	
	void zrusPrvy(structures::List<T>* list, std::string nazovSuboru, std::ofstream* zapisovac);
	void zrusPosledny(structures::List<T>* list, std::string nazovSuboru, std::ofstream* zapisovac);
	void zrusNaIndexe(structures::List<T>* list, std::string nazovSuboru, std::ofstream* zapisovac);

	void spristupni(structures::List<T>* list, std::string nazovSuboru, std::ofstream* zapisovac);
	void nastav(structures::List<T>* list, std::string nazovSuboru, std::ofstream* zapisovac);
	void indexPrvku(structures::List<T>* list, std::string nazovSuboru, std::ofstream* zapisovac);
private:
	void vlozNaIndex(T& data, int index, structures::List<T>* list);
	void zrusNaIndexe(int index, structures::List<T>* list);
	void spristupni(int index, structures::List<T>* list);
	void nastav(int index, T& data, structures::List<T>* list);
	int indexPrvku(T& prvok, structures::List<T>* list);

	void nastavScenar(char scenar, int pOp = 0, int pVloz = 0, int pZrus = 0, int pSpristupni = 0, int pIndexPrvku = 0);
	void zapis(std::ofstream* zapisovac, std::string nazovInstr, int size_);
};

template<typename T>
inline ListTester<T>::ListTester()
{
	stopky = new TimeMeasurement();
}

template<typename T>
inline ListTester<T>::~ListTester()
{
	delete stopky;
}

template<typename T>
inline void ListTester<T>::spustiTesty(structures::List<T>* list, std::string nazovSuboru, char scenar, int pOp, int pVloz, int pZrus, int pSpristupni, int pIndexPrvku)
{
	switch (scenar)
	{
	case 'A': nastavScenar('A'); break;
	case 'B': nastavScenar('B'); break;
	case 'C': nastavScenar('C'); break;
	default: nastavScenar('V', pOp, pVloz, pZrus, pSpristupni, pIndexPrvku); break;
	}

	nazovSuboru = nazovSuboru + scenar + ".csv";
	std::cout << "Zapisujem do: " << nazovSuboru;

	srand(time(0));
	std::ofstream* zapisovac = new std::ofstream(nazovSuboru);
	std::string nazovInstr;
	stopky->reset();
	list->clear();

	for (int i = 0; i < listPocetPrvkovZac; i++)
	{
		T obj;
		list->add(obj);
	}

	
	int i = 0;
	while (i < pocetOp)
	{
		nazovInstr = "";
		int random = 1 + rand() % 100; //podiel zo sto percent

		if (random <= podielVloz)
		{

			int operacia = rand() % 3;
			int index;

			if (operacia == 0) //vloz prvy
			{
				index = 0;
				nazovInstr = "Vloz prvy";
			}
			else if (operacia == 1) { //vloz posledny
				index = list->size();
				nazovInstr = "Vloz posledny";
			}
			else { //vloz na index
				if (list->size() != 0)
				{
					index = rand() % list->size();
				}
				else {
					index = 0;
				}
				nazovInstr = "Vloz na index";
			}
			T obj;
			vlozNaIndex(obj, index, list);

		}
		else if (random <= (podielVloz + podielZrus)) { //zrus
			if (list->size() != 0)
			{
				int operacia = rand() % 3;
				int index;
				if (operacia == 0) //zrus prvy
				{
					index = 0;
					nazovInstr = "Zrus prvy";
				}
				else if (operacia == 1) { //zrus posledny
					index = list->size() - 1;
					nazovInstr = "Zrus posledny";
				}
				else { //zrus na indexe
					index = rand() % list->size();
					nazovInstr = "Zrus na indexe";
				}
				zrusNaIndexe(index, list);
			}

		}
		else if (random <= (podielVloz + podielZrus + podielSpristupni)) { //spristupni,nastav
			if (list->size() != 0)
			{
				int operacia = rand() % 2;
				int index = rand() % list->size();
				if (operacia == 0) //spristupni
				{
					spristupni(index, list);
					nazovInstr = "Spristupni";
				}
				else { //nastav
					T obj;
					nastav(index, obj, list);
					nazovInstr = "Nastav";
				}
			}
		}
		else { //indexPrvku
			if (list->size() != 0)
			{
				nazovInstr = "Index prvku";
				int index = rand() % list->size();
				T prvok = (*list)[index];
				indexPrvku(prvok, list);
			}
		}

		if (nazovInstr != "") //ak sa vykonala nejaka operacia
		{
			zapis(zapisovac, nazovInstr, list->size());
			i++;
		}
	}
	
	std::cout << "      hotovo" << std::endl;

	delete zapisovac;

}

template<typename T>
inline void ListTester<T>::vlozPrvy(structures::List<T>* list, std::string nazovSuboru, std::ofstream* zapisovac)
{
	nazovSuboru = nazovSuboru + "VlozPrvy.csv";
	zapisovac->open(nazovSuboru);
	list->clear();
	srand(time(0));
	for (int i = 0; i < 10000; i++)
	{
		int obj = rand() % 10000;
		stopky->start();
		list->insert(obj,0);
		stopky->stop();
		zapis(zapisovac, "Vloz prvy", list->size());
	}
	zapisovac->close();
}

template<typename T>
inline void ListTester<T>::vlozPosledny(structures::List<T>* list, std::string nazovSuboru, std::ofstream* zapisovac)
{
	nazovSuboru = nazovSuboru + "VlozPosledny.csv";
	zapisovac->open(nazovSuboru);
	list->clear();
	srand(time(0));
	for (int i = 0; i < 10000; i++)
	{
		int obj = rand() % 10000;
		stopky->start();
		list->add(obj);
		stopky->stop();
		zapis(zapisovac, "Vloz posledny", list->size());
	}
	zapisovac->close();
}

template<typename T>
inline void ListTester<T>::vlozNaIndex(structures::List<T>* list, std::string nazovSuboru, std::ofstream* zapisovac)
{
	nazovSuboru = nazovSuboru + "VlozNaIndex.csv";
	zapisovac->open(nazovSuboru);
	list->clear();
	srand(time(0));
	list->add(1);
	for (int i = 0; i < 10000; i++)
	{
		int obj = rand() % 10000;
		stopky->start();
		list->insert(obj, rand() % list->size());
		stopky->stop();
		zapis(zapisovac, "Vloz na index", list->size());
	}
	zapisovac->close();
}

template<typename T>
inline void ListTester<T>::zrusPrvy(structures::List<T>* list, std::string nazovSuboru, std::ofstream* zapisovac)
{
	list->clear();
	for (size_t i = 0; i < 10001; i++)
	{
		list->add(1);
	}
	nazovSuboru = nazovSuboru + "ZrusPrvy.csv";
	zapisovac->open(nazovSuboru);
	srand(time(0));
	for (int i = 0; i < 10000; i++)
	{
		int obj = rand() % 10000;
		stopky->start();
		list->removeAt(0);
		stopky->stop();
		zapis(zapisovac, "Zrus prvy", list->size());
	}
	zapisovac->close();
}

template<typename T>
inline void ListTester<T>::zrusPosledny(structures::List<T>* list, std::string nazovSuboru, std::ofstream* zapisovac)
{
	list->clear();
	for (size_t i = 0; i < 10001; i++)
	{
		list->add(1);
	}
	nazovSuboru = nazovSuboru + "ZrusPosledny.csv";
	zapisovac->open(nazovSuboru);
	srand(time(0));
	for (int i = 0; i < 10000; i++)
	{
		stopky->start();
		list->removeAt(list->size() - 1);
		stopky->stop();
		zapis(zapisovac, "Zrus posledny", list->size());
	}
	zapisovac->close();
}

template<typename T>
inline void ListTester<T>::zrusNaIndexe(structures::List<T>* list, std::string nazovSuboru, std::ofstream* zapisovac)
{
	list->clear();
	for (size_t i = 0; i < 10001; i++)
	{
		list->add(1);
	}
	nazovSuboru = nazovSuboru + "ZrusNaIndexe.csv";
	zapisovac->open(nazovSuboru);
	srand(time(0));
	for (int i = 0; i < 10000; i++)
	{
		int index = rand() % list->size();
		stopky->start();
		list->removeAt(index);
		stopky->stop();
		zapis(zapisovac, "Zrus na indexe", list->size());
	}
	zapisovac->close();
}

template<typename T>
inline void ListTester<T>::spristupni(structures::List<T>* list, std::string nazovSuboru, std::ofstream* zapisovac)
{
	list->clear();
	nazovSuboru = nazovSuboru + "Spristupni.csv";
	zapisovac->open(nazovSuboru);
	srand(time(0));
	list->add(1);
	for (size_t i = 0; i < 1000; i++)
	{
		list->add(rand() % 10000);
		int index = rand() % list->size();
		stopky->start();
		(*list)[index];
		stopky->stop();
		zapis(zapisovac, "Spristupni", list->size());
	}
	zapisovac->close();
}

template<typename T>
inline void ListTester<T>::nastav(structures::List<T>* list, std::string nazovSuboru, std::ofstream* zapisovac)
{
	list->clear();
	nazovSuboru = nazovSuboru + "Nastav.csv";
	zapisovac->open(nazovSuboru);
	srand(time(0));
	list->add(1);
	for (size_t i = 0; i < 10000; i++)
	{
		list->add(rand() % 10000);
		int index = rand() % list->size();
		stopky->start();
		(*list)[index] = rand() % 10000;
		stopky->stop();
		zapis(zapisovac, "Nastav", list->size());
	}
	zapisovac->close();
}

template<typename T>
inline void ListTester<T>::indexPrvku(structures::List<T>* list, std::string nazovSuboru, std::ofstream* zapisovac)
{
	list->clear();
	nazovSuboru = nazovSuboru + "indexPrvku.csv";
	zapisovac->open(nazovSuboru);
	srand(time(0));
	list->add(1);
	for (size_t i = 0; i < 10000; i++)
	{
		list->add(rand() % 10000);
		int index = rand() % list->size();
		int prvok = (*list)[index];
		stopky->start();
		list->getIndexOf(prvok);
		stopky->stop();
		zapis(zapisovac, "IndexPrvku", list->size());
	}
	zapisovac->close();
}

template<typename T>
inline void ListTester<T>::vlozNaIndex(T& data, int index, structures::List<T>* list)
{
	stopky->start();
	list->insert(data, index);
	stopky->stop();
}

template<typename T>
inline void ListTester<T>::zrusNaIndexe(int index, structures::List<T>* list)
{
	stopky->start();
	list->removeAt(index);
	stopky->stop();
}

template<typename T>
inline void ListTester<T>::spristupni(int index, structures::List<T>* list)
{
	stopky->start();
	(*list)[index];
	stopky->stop();
}

template<typename T>
inline void ListTester<T>::nastav(int index, T& data, structures::List<T>* list)
{
	stopky->start();
	(*list)[index] = data;
	stopky->stop();
}

template<typename T>
inline int ListTester<T>::indexPrvku(T& prvok, structures::List<T>* list)
{
	stopky->start();
	int index = list->getIndexOf(prvok);
	stopky->stop();
	return index;
}

template<typename T>
inline void ListTester<T>::nastavScenar(char scenar, int pOp, int pVloz, int pZrus, int pSpristupni, int pIndexPrvku)
{
	switch (scenar)
	{
	case 'A':
		this->pocetOp = listAPocetOp;
		this->podielVloz = listAPodielVloz;
		this->podielZrus = listAPodielZrus;
		this->podielSpristupni = listAPodielSpristupni;
		this->podielIndexPrvku = listAPodielIndexPrvku;
		break;
	case 'B':
		this->pocetOp = listBPocetOp;
		this->podielVloz = listBPodielVloz;
		this->podielZrus = listBPodielZrus;
		this->podielSpristupni = listBPodielSpristupni;
		this->podielIndexPrvku = listBPodielIndexPrvku;
		break;
	case 'C':
		this->pocetOp = listCPocetOp;
		this->podielVloz = listCPodielVloz;
		this->podielZrus = listCPodielZrus;
		this->podielSpristupni = listCPodielSpristupni;
		this->podielIndexPrvku = listCPodielIndexPrvku;
		break;
	default:
		this->pocetOp = pOp;
		this->podielVloz = pVloz;
		this->podielZrus = pZrus;
		this->podielSpristupni = pSpristupni;
		this->podielIndexPrvku = pIndexPrvku;
		break;
	}
}

template<typename T>
inline void ListTester<T>::zapis(std::ofstream* zapisovac, std::string nazovInstr, int size_)
{
	(*zapisovac) << nazovInstr;
	(*zapisovac) << ";";
	(*zapisovac) << size_;
	(*zapisovac) << ";";
	(*zapisovac) << stopky->elapsed().count();
	(*zapisovac) << "\n";

	stopky->reset();
}
