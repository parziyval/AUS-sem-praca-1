#include "../structures/heap_monitor.h"
#include "../structures/list/array_list.h"
#include "../structures/list/linked_list.h"
#include "../structures/priority_queue/priority_queue_list.h"
#include "../structures/priority_queue/heap.h"
#include "../structures/priority_queue/priority_queue_sorted_array_list.h"
#include "../structures/list/DoublyCircularLinkedList.h"
#include "../structures/table/hash_table.h"
#include "implicit_matrix.h"
#include "explicit_matrix.h"
#include "Mnozina.h"
#include "Konstanty.h"
#include "VytvaracMatic.h"
#include "VytvaracSuvislychMatic.h"
#include "VytvaracNesuvislychMatic.h"
#include "TestApp.h"
#include "QueueTester.h"
#include "ListTester.h"
#include "MatrixTester.h"
#include "TimeMeasurement.h"
#include "TableTester.h"
#include <fstream>

void testujListy() {
	ListTester<int>* tester = new ListTester<int>();
	structures::ArrayList<int>* al = new structures::ArrayList<int>();
	structures::LinkedList<int>* ll = new structures::LinkedList<int>();
	structures::DoublyCircularLinkedList<int>* dcll = new structures::DoublyCircularLinkedList<int>();
	tester->spustiTesty(al, "array_list", 'A');
	tester->spustiTesty(ll, "linked_list", 'A');
	tester->spustiTesty(dcll, "DoublyCircularLinkedList", 'A');
	tester->spustiTesty(al, "array_list", 'B');
	tester->spustiTesty(ll, "linked_list", 'B');
	tester->spustiTesty(dcll, "DoublyCircularLinkedList", 'B');
	tester->spustiTesty(al, "array_list", 'C');
	tester->spustiTesty(ll, "linked_list", 'C');
	tester->spustiTesty(dcll, "DoublyCircularLinkedList", 'C');

	delete tester;
	delete al;
	delete ll;
	delete dcll;
}

void testujMatice() {
	VytvaracMatic<int>* vn = new VytvaracNesuvislychMatic<int>();
	VytvaracMatic<int>* vs = new VytvaracSuvislychMatic<int>();
	MatrixTester<int>* tester = new MatrixTester<int>();
	tester->otestujScitanie(vn,"NesuvislaMatica");
	tester->otestujScitanie(vs,"SuvislaMatica");

	tester->otestujNasobenie(vs, "SuvislaMatica");
	tester->otestujNasobenie(vn, "NesuvislaMatica");

	delete vn;
	delete vs;
	delete tester;
}

void testujQueue() {
	structures::PriorityQueueSortedArrayList<int>* al = new structures::PriorityQueueSortedArrayList<int>();
	structures::Heap<int>* halda = new structures::Heap<int>();
	QueueTester<int>* tester = new QueueTester<int>();
	tester->spustiTesty(halda, "Heap", 'A');
	tester->spustiTesty(halda, "Heap", 'B');
	tester->spustiTesty(halda, "Heap", 'C');
	tester->spustiTesty(al, "PriorityQueueSortedArrayList", 'A');
	tester->spustiTesty(al, "PriorityQueueSortedArrayList", 'B');
	tester->spustiTesty(al, "PriorityQueueSortedArrayList", 'C');
	
	/*tester->spustiTesty(halda, "PriorityQueueHeap", 'V',100000,100,0,0);
	tester->spustiTesty(halda, "PriorityQueueHeap", 'P',10000,0,100,0);
	tester->spustiTesty(halda, "PriorityQueueHeap", 'U',10000,0,0,100);*/
	/*tester->spustiTesty(halda, "PriorityQueueHeap", 'B');
	tester->spustiTesty(halda, "PriorityQueueHeap", 'C');*/

	delete al;
	delete halda;
	delete tester;

}


void testujCasZlozitostiListov() {
	ListTester<int>* tester = new ListTester<int>();
	structures::ArrayList<int>* al = new structures::ArrayList<int>();
	structures::LinkedList<int>* ll = new structures::LinkedList<int>();
	structures::DoublyCircularLinkedList<int>* dcll = new structures::DoublyCircularLinkedList<int>();
	std::ofstream* zapisovac = new std::ofstream();

	tester->vlozPrvy(al, "ArrayList",zapisovac);
	tester->vlozNaIndex(al, "ArrayList",zapisovac);
	tester->vlozPosledny(al, "ArrayList",zapisovac);
	tester->zrusPrvy(al, "ArrayList",zapisovac);
	tester->zrusNaIndexe(al, "ArrayList",zapisovac);
	tester->zrusPosledny(al, "ArrayList",zapisovac);
	tester->spristupni(al, "ArrayList",zapisovac);
	tester->nastav(al, "ArrayList",zapisovac);
	tester->indexPrvku(al, "ArrayList",zapisovac);

	tester->vlozPrvy(ll, "LinkedList", zapisovac);
	tester->vlozNaIndex(ll, "LinkedList", zapisovac);
	tester->vlozPosledny(ll, "LinkedList", zapisovac);
	tester->zrusPrvy(ll, "LinkedList", zapisovac);
	tester->zrusNaIndexe(ll, "LinkedList", zapisovac);
	tester->zrusPosledny(ll, "LinkedList", zapisovac);
	tester->spristupni(ll, "LinkedList", zapisovac);
	tester->nastav(ll, "LinkedList", zapisovac);
	tester->indexPrvku(ll, "LinkedList", zapisovac);

	tester->vlozPrvy(ll, "CircularLinkedList", zapisovac);
	tester->vlozNaIndex(ll, "CircularLinkedList", zapisovac);
	tester->vlozPosledny(ll, "CircularLinkedList", zapisovac);
	tester->zrusPrvy(ll, "CircularLinkedList", zapisovac);
	tester->zrusNaIndexe(ll, "CircularLinkedList", zapisovac);
	tester->zrusPosledny(ll, "CircularLinkedList", zapisovac);
	tester->spristupni(ll, "CircularLinkedList", zapisovac);
	tester->nastav(ll, "CircularLinkedList", zapisovac);
	tester->indexPrvku(ll, "CircularLinkedList", zapisovac);

	delete tester;
	delete al;
	delete ll;
	delete dcll;
}

void testujZlozitostiTabuliek() 
{ 
	TableTester<int, std::string>* tester = new TableTester<int, std::string>;
	structures::SortedSequenceTable<int, std::string>* sst = new structures::SortedSequenceTable<int, std::string>();
	structures::BinarySearchTree<int, std::string>* bst = new structures::BinarySearchTree<int, std::string>();
	structures::Treap<int, std::string>* treap = new structures::Treap<int, std::string>();
	structures::HashTable<int, std::string>* hashTab = new structures::HashTable<int, std::string>();

	tester->vykonajVlozenieXKrat(sst, "UtriedenaSekvTab", 10000);
	tester->vykonajVlozenieXKrat(bst, "BinVyhladavaciStrom", 10000);
	tester->vykonajVlozenieXKrat(treap, "Treap", 10000);
	tester->vykonajVlozenieXKrat(hashTab, "HashTab", 10000);

	tester->vykonajZrusenieXKrat(sst, "UtriedenaSekvTab", 10000);
	tester->vykonajZrusenieXKrat(bst, "BinVyhladavaciStrom", 10000);
	tester->vykonajZrusenieXKrat(treap, "Treap", 10000);
	tester->vykonajZrusenieXKrat(hashTab, "HashTab", 10000);

	tester->vykonajPristupXKrat(sst, "UtriedenaSekvTab", 10000);
	tester->vykonajPristupXKrat(bst, "BinVyhladavaciStrom", 10000);
	tester->vykonajPristupXKrat(treap, "Treap", 10000);
	tester->vykonajPristupXKrat(hashTab, "HashTab", 10000);

	delete tester;
	delete sst;
	delete bst;
	delete treap;
	delete hashTab;
}


void spustiApp() {
	TestApp* app = new TestApp();
	app->spusti();
	delete app;
}

void spustiAppTabulky() {
	TestApp* app = new TestApp();
	app->spustiVyberTabulky();
	delete app;
}


int main() {
	initHeapMonitor();	

	//testujListy();

	//spustiApp();

	//testujQueue();

	//testujMatice();

	spustiAppTabulky();

	//testujZlozitostiTabuliek();

	//structures::SortedSequenceTable<int, int>* test = new structures::SortedSequenceTable<int, int>();
	//for (size_t i = 0; i < 100; i++)
	//{
	//	test->insert(i, i);
	//}

	return 0;
}
