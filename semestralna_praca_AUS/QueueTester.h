#pragma once
#include "../structures/heap_monitor.h"
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include "../structures/priority_queue/priority_queue.h"
#include "../structures/priority_queue/priority_queue_list.h"
#include "TimeMeasurement.h"
#include "Konstanty.h"

const int maxPriorita = 10000;
const int queuePocetPrvkovZac = 0;

template<typename T>
class QueueTester
{
private:
	TimeMeasurement* stopky;
	char scenar;
	int pocetOp = 0;
	int podielVloz = 0;
	int podielVyber = 0;
	int podielUkaz = 0;
public:
	QueueTester();
	~QueueTester();
	void spustiTesty(structures::PriorityQueueList<T>* queue, std::string nazovSuboru, 
		char scenar,int pOp = 0, int pVloz = 0, int pvyber = 0, int pUkaz = 0);
private:
	void vloz(T& data, structures::PriorityQueueList<T>* queue);

	void vyber(structures::PriorityQueueList<T>* queue);

	void ukaz(structures::PriorityQueueList<T>* queue);

	void nastavScenar(char scenar, int pOp = 0, int pVloz = 0, int pVyber = 0, int pUkaz = 0);

	void zapis(std::ofstream* zapisovac, std::string nazovInstr, int size);
};

template<typename T>
inline QueueTester<T>::QueueTester()
{
	stopky = new TimeMeasurement();
}

template<typename T>
inline QueueTester<T>::~QueueTester()
{
	delete stopky;
}

template<typename T>
inline void QueueTester<T>::spustiTesty(structures::PriorityQueueList<T>* queue, std::string nazovSuboru, char scenar, int pOp, int pVloz, int pVyber, int pUkaz)
{
	switch (scenar)
	{
	case 'A': nastavScenar('A'); break;
	case 'B': nastavScenar('B'); break;
	case 'C': nastavScenar('C'); break;
	default: nastavScenar('V', pOp, pVloz, pVyber, pUkaz); break;
	}

	nazovSuboru = nazovSuboru + scenar + ".csv";
	std::cout << "Zapisujem do " << nazovSuboru;

	srand(time(0));
	std::ofstream* zapisovac = new std::ofstream(nazovSuboru);
	std::string nazovInstr;
	stopky->reset();
	queue->clear();

	for (int i = 0; i < queuePocetPrvkovZac; i++)
	{
		T obj;
		queue->push(rand() % maxPriorita + 1, obj); 
	}


	int i = 0;
	while (i < pocetOp)
	{
		nazovInstr = "";
		int random = 1 + rand() % 100;

		if (random <= podielVloz) //vloz
		{
			T obj;
			vloz(obj, queue);
			nazovInstr = "Vloz";
		}
		else if (random <= (podielVloz + podielVyber)) { //vyber
			if (queue->size() != 0)
			{
				vyber(queue);
			}
			nazovInstr = "Vyber";
		}
		else { //ukaz
			if (queue->size() != 0)
			{
				ukaz(queue);
				nazovInstr = "Ukaz";
			}
		}

		if (nazovInstr != "") //ak sa vykonala nejaka operacia
		{
			zapis(zapisovac, nazovInstr, queue->size());
			i++;
		}

	}
	std::cout << "      hotovo" << std::endl;

	delete zapisovac;
}




template<typename T>
inline void QueueTester<T>::vloz(T& data,structures::PriorityQueueList<T>* queue)
{
	stopky->start();
	queue->push(rand() % maxPriorita, data);
	stopky->stop();
}

template<typename T>
inline void QueueTester<T>::vyber(structures::PriorityQueueList<T>* queue)
{
	stopky->start();
	queue->pop();
	stopky->stop();
}

template<typename T>
inline void QueueTester<T>::ukaz(structures::PriorityQueueList<T>* queue)
{
	stopky->start();
	queue->peek();
	stopky->stop();
}

template<typename T>
inline void QueueTester<T>::nastavScenar(char scenar,int pOp, int pVloz, int pVyber, int pUkaz)
{
	switch (scenar)
	{
	case 'A':
		this->pocetOp = queueAPocetOp;
		this->podielVloz = queueAPodielVloz;
		this->podielVyber = queueAPodielVyber;
		this->podielUkaz = queueAPodielUkaz;
		break;
	case 'B':
		this->pocetOp = queueBPocetOp;
		this->podielVloz = queueBPodielVloz;
		this->podielVyber = queueBPodielVyber;
		this->podielUkaz = queueBPodielUkaz;
		break;
	case 'C':
		this->pocetOp = queueCPocetOp;
		this->podielVloz = queueCPodielVloz;
		this->podielVyber = queueCPodielVyber;
		this->podielUkaz = queueCPodielUkaz;
		break;
	default:
		this->pocetOp = pOp;
		this->podielVloz = pVloz;
		this->podielVyber = pVyber;
		this->podielUkaz = pUkaz;
		break;
	}
	
}

template<typename T>
inline void QueueTester<T>::zapis(std::ofstream* zapisovac, std::string nazovInstr, int size)
{
	(*zapisovac) << nazovInstr;
	(*zapisovac) << ";";
	(*zapisovac) << size;
	(*zapisovac) << ";";
	(*zapisovac) << stopky->elapsed().count();
	(*zapisovac) << "\n";

	stopky->reset();
}

//template<typename T>
//inline void QueueTester<T>::otestujVlozenie(std::string nazovSuboru, structures::PriorityQueueList<T>* queue, int pocet)
//{
//	nazovSuboru += "_vloz_";
//	nazovSuboru += pocet;
//	nazovSuboru += ".csv";
//	std::ofstream* zapisovac = new std::ofstream(nazovSuboru);
//	std::string nazovInstr;
//	for (int i = 0; i < pocet; i++)
//	{
//		T obj;
//		vloz(obj, queue);
//		nazovInstr = "Vloz";
//	}
//	zapis(zapisovac, nazovInstr, queue->size());
//	delete zapisovac;
//}


