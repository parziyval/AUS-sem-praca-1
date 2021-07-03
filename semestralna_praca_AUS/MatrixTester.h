#pragma once
#include "../structures/heap_monitor.h"
#include <iostream>
#include <fstream>
#include "matrix.h"
#include "VytvaracMatic.h"
#include "TimeMeasurement.h"


const int maxRozmerRiadky = 2000;
const int maxRozmerStlpce = 2000;
template<typename T>
class MatrixTester
{
private:
	TimeMeasurement* stopky;
public:
	MatrixTester();
	~MatrixTester();
	void otestujScitanie(VytvaracMatic<T>* vytvarac,std::string nazovSuboru);

	void otestujNasobenie(VytvaracMatic<T>* vytvarac, std::string nazovSuboru);
};

template<typename T>
inline MatrixTester<T>::MatrixTester()
{
	stopky = new TimeMeasurement();
}

template<typename T>
inline MatrixTester<T>::~MatrixTester()
{
	delete stopky;
}

template<typename T>
inline void MatrixTester<T>::otestujScitanie(VytvaracMatic<T>* vytvarac,std::string nazovSuboru)
{
	nazovSuboru += "_scitanie.csv";
	std::cout << "Zapisujem do: ";
	std::cout << nazovSuboru;
	std::ofstream* zapisovac = new std::ofstream(nazovSuboru);
	for (int m = 50; m < maxRozmerRiadky; m+=100)
	{
		for (int n = 50; n < maxRozmerStlpce; n+=100)
		{
			stopky->reset();
			std::cout << "m = " << m;
			std::cout << " n = " << n;
			structures::Matrix<T>* m1 = vytvarac->vytvorMaticu(m, n, 5);
			structures::Matrix<T>* m2 = vytvarac->vytvorMaticu(m, n, 5);
			structures::Matrix<T>*m3 = vytvarac->vytvorMaticu(m1->getRowCount(), m1->getColCount(), 0);
			stopky->start();
			for (int i = 0; i < m1->getRowCount(); i++)
			{
				for (int j = 0; j < m1->getColCount(); j++)
				{					
					m3->setItemAt(i, j, m1->getItemAt(i, j) + m2->getItemAt(i, j));

				}
			}
			stopky->stop();
			delete m1;
			delete m2;
			delete m3;
			(*zapisovac) << stopky->elapsed().count();
			(*zapisovac) << ";";
			std::cout << " ";
			std::cout << stopky->elapsed().count();
			std::cout << "\n";
		}
		(*zapisovac) << "\n";
	}
	std::cout << nazovSuboru ;
	std::cout << "    hotovo";
	delete zapisovac;
}

template<typename T>
inline void MatrixTester<T>::otestujNasobenie(VytvaracMatic<T>* vytvarac, std::string nazovSuboru)
{

	nazovSuboru += "_nasobenie.csv";
	std::cout << "Zapisujem do: ";
	std::cout << nazovSuboru;
	std::ofstream* zapisovac = new std::ofstream(nazovSuboru);
	for (int m = 50; m < maxRozmerRiadky; m += 100)
	{
		for (int n = 50; n < maxRozmerStlpce; n += 100)
		{
			stopky->reset();
			std::cout << "m = " << m;
			std::cout << " n = " << n;
			structures::Matrix<T>* m1 = vytvarac->vytvorMaticu(m, n, 5);
			structures::Matrix<T>* m2 = vytvarac->vytvorMaticu(n, m, 5);
			structures::Matrix<T>* m3 = vytvarac->vytvorMaticu(m1->getRowCount(), m2->getColCount(), 0);
			stopky->start();
			for (int i = 0; i < m1->getRowCount(); i++)
			{
				for (int j = 0; j < m2->getColCount(); j++)
				{
					for (int k = 0; k < m2->getRowCount(); k++)
					{
						m3->setItemAt(i, j, m3->getItemAt(i, j) + (m1->getItemAt(i, k) * m2->getItemAt(k, j)));
					}
				}
			}
			stopky->stop();
			delete m1;
			delete m2;
			delete m3;
			(*zapisovac) << stopky->elapsed().count();
			(*zapisovac) << ";";
			std::cout << " ";
			std::cout << stopky->elapsed().count();
			std::cout << "\n";
		}
		(*zapisovac) << "\n";
	}
	std::cout << nazovSuboru;
	std::cout << "    hotovo";
	delete zapisovac;
}
