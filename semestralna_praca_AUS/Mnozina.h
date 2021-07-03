#pragma once
#include <iostream>
#include <bitset>
#include "../structures/array/array.h"
#include "../structures/heap_monitor.h"


using namespace structures;
using namespace std;

const int velkostLL = sizeof(unsigned long long)*8;


class Mnozina
{
private:
	int min;
	int max;

	Array<unsigned long long>* mnozina;

public:
	Mnozina(int min, int max);
	Mnozina(const Mnozina& other);
	~Mnozina();

	Mnozina& operator=(const Mnozina& other);

	bool isEmpty();
	int size() const;
	bool patriDoMnoziny(int prvok);
	void vloz(int prvok);
	void odober(int prvok);

	bool operator==(Mnozina& other);
	bool jePodmnozinou(Mnozina& other);

	int getMin() { return min; }
	int getMax() { return max; }

	//Zjednotenie mnozin
	Mnozina& operator|(Mnozina& other);
	//Prienik mnozin
	Mnozina& operator&(Mnozina& other);
	//Rozdiel mnozin
	Mnozina& operator-(Mnozina& other);

	void vypisMnozinu();
};