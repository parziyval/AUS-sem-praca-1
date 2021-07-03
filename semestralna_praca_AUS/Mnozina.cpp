#include "Mnozina.h"



Mnozina::Mnozina(int min, int max)
{
	this->min = min;
	this->max = max;
	if (max >= min)
	{
		mnozina = new Array<unsigned long long>((max - min) / velkostLL + 1);
		for (int i = 0; i < mnozina->size(); i++)
		{
			(*mnozina)[i] = 0;
		}
	}
	else
	{
		throw std::logic_error("Max musi byt viac ako min!");
	}
}

Mnozina::Mnozina(const Mnozina& other)
{
	*this = other;
}

Mnozina::~Mnozina()
{
	delete mnozina;
	mnozina = nullptr;
	min = 0;
	max = 0;
}

Mnozina& Mnozina::operator=(const Mnozina& other)
{
	if (min == other.min && max == other.max)
	{
		if (this != &other)
		{
			delete mnozina;
			mnozina = new Array<unsigned long long>(*other.mnozina);
			min = other.min;
			max = other.max;
		}
		return *this;
	}
	else
	{
		throw std::logic_error("Rozdielna velkost bazy");
	}

}

bool Mnozina::isEmpty()
{
	for (int i = 0; i < mnozina->size(); i++)
	{
		if ((*mnozina)[i] != 0)
		{
			return false;
		}
	}
	return true;
}

int Mnozina::size() const
{
	int velkost = 0;
	for (int i = 0; i < mnozina->size(); i++)
	{
		unsigned long long blok = (*mnozina)[i];
		velkost += bitset<velkostLL>(blok).count();
	}
	return velkost;
}

bool Mnozina::patriDoMnoziny(int prvok)
{
	if (min <= prvok <= max)
	{
		int indexBloku = (prvok - min) / velkostLL;
		unsigned long long blok = (*mnozina)[indexBloku];

		int indexPrvku = (prvok - min) % velkostLL;

		unsigned long long maska = 1;
		maska = maska << indexPrvku;
		if ((blok & maska) == 0)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	else
	{
		return false;
	}

}

void Mnozina::vloz(int prvok)
{
	if (min <= prvok <= max)
	{
		if (!patriDoMnoziny(prvok))
		{
			int indexBloku = (prvok - min) / velkostLL;
			int indexPrvku = (prvok - min) % velkostLL;

			unsigned long long maska = 1;
			maska = maska << indexPrvku;

			(*mnozina)[indexBloku] = (*mnozina)[indexBloku] ^ maska; //binarny XOR
		}

	}
	else
	{
		throw std::logic_error("Prvok nie je v mnozine <min,max>!");
	}


}

void Mnozina::odober(int prvok)
{
	if (min <= prvok <= max)
	{
		if (patriDoMnoziny(prvok))
		{
			int indexBloku = (prvok - abs(min)) / velkostLL;

			int indexPrvku = (prvok - abs(min)) % velkostLL;

			unsigned long long maska = ULLONG_MAX - 1;
			maska = !(maska << indexPrvku);

			(*mnozina)[indexBloku] = ((*mnozina)[indexBloku]) & maska; //binarny AND
		}
	}
	else
	{
		throw std::logic_error("Prvok nie je v mnozine <min,max>!");
	}
}

bool Mnozina::operator==(Mnozina& other)
{
	if (min == other.min && max == other.max)
	{
		for (int i = 0; i < mnozina->size(); i++)
		{
			if ((*mnozina)[i] != (*other.mnozina)[i])
			{
				return false;
			}
		}
		return true;
	}
	else
	{
		throw std::logic_error("Rozdielna velkost bazy");
	}

}

bool Mnozina::jePodmnozinou(Mnozina& other)
{
	if (min == other.min && max == other.max)
	{
		for (int i = 0; i < mnozina->size(); i++)
		{
			unsigned long long pom = (*mnozina)[i] & (*other.mnozina)[i];
			if (pom != (*other.mnozina)[i])
			{
				return false;
			}
		}
		return true;
	}
	else
	{
		throw std::logic_error("Rozdielna velkost bazy");
	}
}

Mnozina& Mnozina::operator|(Mnozina& other)
{
	if (min == other.min && max == other.max)
	{
		for (int i = 0; i < mnozina->size(); i++)
		{
			(*mnozina)[i] = (*mnozina)[i] | (*other.mnozina)[i];
		}
		return *this;
	}
	else
	{
		throw std::logic_error("Rozdielna velkost bazy");
	}
}

Mnozina& Mnozina::operator&(Mnozina& other)
{
	if (min == other.min && max == other.max)
	{
		for (int i = 0; i < mnozina->size(); i++)
		{
			(*mnozina)[i] = (*mnozina)[i] & (*other.mnozina)[i];
		}
		return *this;
	}
	else
	{
		throw std::logic_error("Rozdielna velkost bazy");
	}
}

Mnozina& Mnozina::operator-(Mnozina& other)
{
	if (min == other.min && max == other.max)
	{
		for (int i = 0; i < mnozina->size(); i++)
		{
			(*mnozina)[i] = (*mnozina)[i] & ~((*other.mnozina)[i]);
		}
		return *this;
	}
	else
	{
		throw std::logic_error("Rozdielna velkost bazy");
	}
}

void Mnozina::vypisMnozinu()
{
	unsigned long long pom;
	unsigned long long maska;
	for (int i = 0; i < mnozina->size(); i++)
	{
		maska = 1;
		for (int j = 0; j < velkostLL; j++)
		{
			pom = (*mnozina)[i] & maska;
			maska = maska << 1;
			if (pom != 0)
			{
				cout << i * velkostLL + j << endl;
			}
		}
	}
}
