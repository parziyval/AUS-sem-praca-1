#include "../structures/heap_monitor.h"
#include <iostream>
#include <fstream>
#include "TestApp.h"
#include "ListTester.h"
#include "Konstanty.h"
#include "../structures/table/table.h"
#include "../structures/table/sequence_table.h"
#include "../structures/table/sorted_sequence_table.h"
#include "../structures/table/binary_search_tree.h"
#include "../structures/table/treap.h"
#include "../structures/table/hash_table.h"
#include "TableTester.h"


#define MOZNOST_SORTED_TAB 1
#define MOZNOST_BIN_STROM 2
#define MOZNOST_TREAP 3
#define MOZNOST_HASH_TAB 4

TestApp::TestApp()
{
}

TestApp::~TestApp()
{
}

void TestApp::spusti()
{
	bool koniec = false;
	std::cout << "Zadajte cislo ADT, ktoru chcete testovat:\n1) Zoznam\n";
	int moznost;
	do
	{
		std::cin >> moznost;
		switch (moznost)
		{
		case 1:
			spustiVyberScenaraList();
			koniec = true;
			break;
		default:
			std::cout << "Zadali ste neplatnu moznost. Skuste to znova: ";
			opravCin();
			break;
		}
	} while (!koniec);
}

void TestApp::spustiVyberScenaraList()
{
	std::cout << "Vyberte scenar alebo stlacte 0 pre spustenie dialogu na nastavenie scenara alebo ine cele cislo pre nacitanie scenara zo suboru\n";
	std::cout << "1) Scenar A: \n";
	std::cout << "\tPocet operacii: " << listAPocetOp << "\n";
	std::cout << "\tPodiel operacii Vloz: " << listAPodielVloz<< "\n";
	std::cout << "\tPodiel operacii Zrus: " << listAPodielZrus << "\n";
	std::cout << "\tPodiel operacii Spristupni/Nastav: " << listAPodielSpristupni<< "\n";
	std::cout << "\tPodiel operacii IndexPrvku: " << listAPodielIndexPrvku << "\n";
	std::cout << "2) Scenar B: \n";
	std::cout << "\tPocet operacii: " << listBPocetOp << "\n";
	std::cout << "\tPodiel operacii Vloz: " << listBPodielVloz << "\n";
	std::cout << "\tPodiel operacii Zrus: " << listBPodielZrus << "\n";
	std::cout << "\tPodiel operacii Spristupni/Nastav: " << listBPodielSpristupni << "\n";
	std::cout << "\tPodiel operacii IndexPrvku: " << listBPodielIndexPrvku << "\n";
	std::cout << "3) Scenar C: \n";
	std::cout << "\tPocet operacii: " << listCPocetOp << "\n";
	std::cout << "\tPodiel operacii Vloz: " << listCPodielVloz << "\n";
	std::cout << "\tPodiel operacii Zrus: " << listCPodielZrus << "\n";
	std::cout << "\tPodiel operacii Spristupni/Nastav: " << listCPodielSpristupni << "\n";
	std::cout << "\tPodiel operacii IndexPrvku: " << listCPodielIndexPrvku << "\n";
	int moznost = 0;
	bool koniec = false;
	std::cin >> moznost;
	switch (moznost)
	{
	case 1:
		spustiTestyListov('A',listAPocetOp, listAPodielVloz, listAPodielZrus, listAPodielSpristupni, listAPodielIndexPrvku);
		break;
	case 2:
		spustiTestyListov('B',listBPocetOp, listBPodielVloz, listBPodielZrus, listBPodielSpristupni, listBPodielIndexPrvku);
		break;
	case 3:
		spustiTestyListov('C',listCPocetOp, listCPodielVloz, listCPodielZrus, listCPodielSpristupni, listCPodielIndexPrvku);
		break;
	case 0:
		nacitajTestZoSuboruList();
		break;
	default:
		nastavVlastnyScenarList();
		break;
	}
}

void TestApp::spustiTestyListov(char scenar,int pOp, int pVloz, int pZrus, int pSpristupni, int pIndexPrvku)
{
	ListTester<int>* tester = new ListTester<int>();
	structures::ArrayList<int>* al = new structures::ArrayList<int>();
	structures::LinkedList<int>* ll = new structures::LinkedList<int>();
	structures::LinkedList<int>* dcll = new structures::LinkedList<int>();

	tester->spustiTesty(al, "array_list", scenar, pOp, pVloz, pZrus, pSpristupni, pIndexPrvku);
	tester->spustiTesty(ll, "linked_list", scenar, pOp, pVloz, pZrus, pSpristupni, pIndexPrvku);
	tester->spustiTesty(dcll, "doubly_circular_linked_list", scenar, pOp, pVloz, pZrus, pSpristupni, pIndexPrvku);

	delete tester;
	delete al;
	delete ll;
	delete dcll;
}

void TestApp::nastavVlastnyScenarList()
{
	bool koniec = false;
	bool koniecVloz = false;
	bool koniecZrus = false;
	bool koniecSprist = false;
	bool koniecPocetOp = false;
	int pocetOp;
	int podielVloz;
	int podielZrus;
	int podielSpristupni;
	int podielIndexPrvku;
	while (!koniec)
	{
		std::cout << "Zadajte pocet operacii vacsi alebo rovny ako 1, ktore sa maju vykonat: ";
		while (!koniecPocetOp)
		{
			std::cin >> pocetOp;
			if (pocetOp >= 1)
			{
				koniecPocetOp = true;
			}
			else {
				std::cout << "\nZadajte pocet operacii vacsi alebo rovny ako 1!: ";
			}
		}
		
		std::cout << "Zadajte podiel operacii Vloz (mensi alebo rovny 100): ";
		while (!koniecVloz)
		{
			std::cin >> podielVloz;
			if (podielVloz >= 0 && podielVloz <= 100)
			{
				koniecVloz = true; 
			}
			else {
				std::cout << "\nZadajte podiel operacii z intervalu <0;100>!: ";
			}
		}

		if (podielVloz == 100)
		{
			std::cout << "\nNastavujem podiel Zrus na 0\n";
			podielZrus = 0;
			std::cout << "Nastavujem podiel Spristupni na 0\n";
			podielSpristupni = 0;
			std::cout << "Nastavujem podiel Index prvku na 0\n";
			podielIndexPrvku = 0;
			break;
		}

		std::cout << "Zadajte podiel operacii Zrus: ";
		while (!koniecZrus)
		{
			std::cin >> podielZrus;
			if (podielZrus >= 0 && podielZrus <= (100 - podielVloz) && podielZrus <= podielVloz)
			{
				koniecZrus = true;
			}
			else {
				std::cout << "\nZadajte podiel operacii z intervalu <0;100-podielVloz> a mensi alebo rovny ako podiel operacii Vloz! :";
			}
		}

		if (podielVloz + podielZrus == 100)
		{
			std::cout << "\nNastavujem podiel Spristupni na 0\n";
			podielSpristupni = 0;
			std::cout << "Nastavujem podiel Index prvku na 0\n";
			podielIndexPrvku = 0;
			break;
		}

		std::cout << "Zadajte podiel operacii Spristupni: ";
		while (!koniecSprist)
		{
			std::cin >> podielSpristupni;
			if (podielSpristupni >= 0 && podielSpristupni <= (100 - (podielVloz + podielZrus)))
			{
				koniecSprist = true;
			}
			else {
				std::cout << "\nZadajte podiel operacii z intervalu <0;100-(podielVloz+podielZrus)>!";
			}
		}

		std::cout << "\nNastavujem podiel Index prvku na " << (100 - podielVloz - podielZrus - podielSpristupni) << "\n";
		podielIndexPrvku = 100 - podielVloz - podielZrus - podielSpristupni;
		koniec = true;
	}
	std::cout << "\nVlastny scenar prehlad:\n";
	std::cout << "\tPocet operacii: " << pocetOp << "\n";
	std::cout << "\tPodiel operacii Vloz: " << podielVloz << "\n";
	std::cout << "\tPodiel operacii Zrus: " << podielZrus << "\n";
	std::cout << "\tPodiel operacii Spristupni/Nastav: " << podielSpristupni << "\n";
	std::cout << "\tPodiel operacii IndexPrvku: " << podielIndexPrvku << "\n";
	std::cout << "Prajete si scenar ulozit do suboru? [Y/N]: ";
	bool koniecUlozenie = false;
	char ulozenie;
	std::cin >> ulozenie;
	while (!koniecUlozenie)
	{
		if (ulozenie == 'Y' || ulozenie == 'y')
		{
			zapisTestdoSuboruList(pocetOp, podielVloz, podielZrus, podielSpristupni, podielIndexPrvku);
			koniecUlozenie = true;
		}
		else if (ulozenie == 'N' || ulozenie == 'n')
		{
			koniecUlozenie = true;
		}
		else {
			std::cout << "Zadali ste neplatnu moznost. Skuste to znova: ";
		}
	}
	spustiTestyListov('V',pocetOp, podielVloz, podielZrus, podielSpristupni, podielIndexPrvku);
}

void TestApp::zapisTestdoSuboruList(int pOp, int pVloz, int pZrus, int pSpristupni, int pIndexPrvku)
{
	std::string nazovSuboru;
	std::cout << "Zadajte nazov suboru: ";
	std::cin >> nazovSuboru;
	std::ofstream zapisovac(nazovSuboru);
	zapisovac << "list\n";
	zapisovac << pOp << "\n";
	zapisovac << pVloz << "\n";
	zapisovac << pZrus << "\n";
	zapisovac << pSpristupni << "\n";
	zapisovac << pIndexPrvku << "\n";
	zapisovac.close();
}

void TestApp::nacitajTestZoSuboruList()
{	
	std::string nazovADT;
	int pocetOp;
	int podielVloz;
	int podielZrus;
	int podielSpristupni;
	int podielIndexPrvku;
	std::string nazovSuboru;
	std::ifstream citac;

	bool koniec = false;
	do
	{
		std::cout << "\nZadajte nazov suboru: ";
		std::cin >> nazovSuboru;
		citac.open(nazovSuboru);
		if (citac.is_open())
		{
			citac >> nazovADT;
			citac >> pocetOp;
			citac >> podielVloz;
			citac >> podielZrus;
			citac >> podielSpristupni;
			citac >> podielIndexPrvku;
			if (nazovADT == "list" && pocetOp >= 1 &&
				(podielVloz >= 0 && podielVloz <=100) && 
				(podielZrus >= 0 && podielZrus <=100) &&
				podielZrus <= podielVloz &&
				(podielSpristupni >= 0 && podielSpristupni <= 100) &&
				(podielIndexPrvku >= 0 && podielIndexPrvku <= 100) &&
				(podielVloz + podielZrus + podielSpristupni + podielIndexPrvku) == 100) 
			{
					koniec = true;
					spustiTestyListov('S',pocetOp, podielVloz, podielZrus, podielSpristupni, podielIndexPrvku);
			}
			else
			{
				std::cout << "Boli precitane neplatne udaje. Skuste zadat iny nazov suboru.";
				citac.close();

			}
		}
		else {
			std::cout << "Subor sa nepodarilo otvorit\n";
		}
	} while (!koniec);
	
}

void TestApp::spustiVyberTabulky()
{
	bool koniec = false;
	int moznost;
	std::string nazovSuboru = "";
	TableTester<int, std::string>* tester = new TableTester<int, std::string>();

	std::cout << "Zadajte cislo tabulky, ktoru chcete testovat:\n1) Utriedena sekvencna tabulka\n2) Binarny vyhladavaci strom\n3) Treap\n4) Hash tabulka\n";
	structures::Table<int, std::string>* tabulka = nullptr;
	do
	{
		std::cin >> moznost;
		switch(moznost)
		{
		case MOZNOST_SORTED_TAB:
			tabulka = new structures::SortedSequenceTable<int, std::string>();
			nazovSuboru = "UtriedenaSekvencnaTab";
			koniec = true;
			break;
		case MOZNOST_BIN_STROM:
			tabulka = new structures::BinarySearchTree<int, std::string>();
			nazovSuboru = "BinVyhladavaciStrom";
			koniec = true;
			break;
		case MOZNOST_TREAP:
			tabulka = new structures::Treap<int, std::string>();
			nazovSuboru = "Treap";
			koniec = true;
			break;
		case MOZNOST_HASH_TAB:
			tabulka = new structures::HashTable<int, std::string>();
			nazovSuboru = "HashTab";
			koniec = true;
			break;
		default:
			std::cout << "Zadali ste neplatnu moznost. Skuste to znova: ";
			opravCin();
			break;
		}

		if (tabulka != nullptr)
		{
			tester->spustiTesty(tabulka, nazovSuboru, 'A');
			tester->spustiTesty(tabulka, nazovSuboru, 'B');
			tester->spustiTesty(tabulka, nazovSuboru, 'C');
		}
	} while (!koniec);

	delete tabulka;
	delete tester;
}

void TestApp::opravCin()
{
	std::cin.clear(); //clear bad input flag
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard input
}


