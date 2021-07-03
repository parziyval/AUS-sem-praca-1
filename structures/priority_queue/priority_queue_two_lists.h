#pragma once

#include "priority_queue.h"
#include "priority_queue_limited_sorted_array_list.h"
#include "../list/linked_list.h"
#include <cmath>

namespace structures
{
	/// <summary> Prioritny front implementovany dvojzoznamom. </summary>
	/// <typeparam name = "T"> Typ dat ukladanych v prioritnom fronte. </typepram>
	/// <remarks> Implementacia efektivne vyuziva prioritny front implementovany utriednym ArrayList-om s obmedzenou kapacitou a LinkedList. </remarks>
	template<typename T>
	class PriorityQueueTwoLists : public PriorityQueue<T>
	{
	public:
		PriorityQueueTwoLists();
		/// <summary> Konstruktor. </summary>
		PriorityQueueTwoLists(int defaultCapacity);

		PriorityQueueTwoLists(const PriorityQueueTwoLists<T>& other);
		~PriorityQueueTwoLists();

		Structure* clone() const override;

		/// <summary> Operator priradenia. </summary>
		/// <param name = "other"> Prioritny front, z ktoreho ma prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa tento prioritny front nachadza po priradeni. </returns>
		PriorityQueue<T>& operator=(const PriorityQueue<T>& other) override;

		/// <summary> Operator priradenia. </summary>
		/// <param name = "other"> Prioritny front implementovany dvojzoznamom, z ktoreho ma prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa tento prioritny front nachadza po priradeni. </returns>
		PriorityQueueTwoLists<T>& operator=(const PriorityQueueTwoLists<T>& other);

		/// <summary> Vrati pocet prvkov v prioritnom fronte implementovanom dvojzoznamom. </summary>
		/// <returns> Pocet prvkov v prioritnom fronte implementovanom dvojzoznamom. </returns>
		size_t size() const override;

		/// <summary> Vymaze obsah prioritneho frontu implementovaneho dvojzoznamom. </summary>
		void clear() override;

		void push(const int priority, const T& data) override;

		/// <summary> Odstrani prvok s najvacsou prioritou z prioritneho frontu implementovaneho dvojzoznamom. </summary>
		/// <returns> Odstraneny prvok. </returns>
		/// <exception cref="std::logic_error"> Vyhodena, ak je prioritny front implementovany dvojzoznamom prazdny. </exception>  
		T pop() override;

		/// <summary> Vrati adresou prvok s najvacsou prioritou. </summary>
		/// <returns> Adresa, na ktorej sa nachadza prvok s najvacsou prioritou. </returns>
		/// <exception cref="std::logic_error"> Vyhodena, ak je prioritny front implementovany dvojzoznamom prazdny. </exception>  
		T& peek() override;

		/// <summary> Vrati kopiu prvku s najvacsou prioritou. </summary>
		/// <returns> Kopia prvku s najvacsou prioritou. </returns>
		/// <exception cref="std::logic_error"> Vyhodena, ak je prioritny front implementovany dvojzoznamom prazdny. </exception>  
		const T peek() const override;

		/// <summary> Vrati prioritu prvku s najvacsou prioritou. </summary>
		/// <returns> Priorita prvku s najvacsou prioritou. </returns>
		/// <exception cref="std::logic_error"> Vyhodena, ak je prioritny front implementovany dvojzoznamom prazdny. </exception>  
		int peekPriority() const override;
	
	private:
		/// <summary> Smernik na prioritny front ako implementovany utriednym ArrayList-om s obmedzenou kapacitou . </summary>
		/// <remarks> Z pohladu dvojzoznamu sa jedna o kratsi utriedeny zoznam. </remarks>
		PriorityQueueLimitedSortedArrayList<T>* shortList_;

		/// <summary> Smernik na dlhsi neutriedeny zoznam. </summary>
		LinkedList<PriorityQueueItem<T>*>* longList_;

		/// <summary> Defaultn· kapacita. </summary>
		int defaultCapacity = 4;

		/// <summary> True ak je TwoList s defaultnou veækosùou shortListu. </summary>
		bool isDefault;
	};

	template<typename T>
	PriorityQueueTwoLists<T>::PriorityQueueTwoLists() :
		shortList_(new PriorityQueueLimitedSortedArrayList<T>()),
		longList_(new LinkedList<PriorityQueueItem<T>*>())
	{
		this->isDefault = false;
	}

	template<typename T>
	PriorityQueueTwoLists<T>::PriorityQueueTwoLists(int defaultCapacity) :
		shortList_(new PriorityQueueLimitedSortedArrayList<T>()),
		longList_(new LinkedList<PriorityQueueItem<T>*>())
	{
		shortList_->trySetCapacity(defaultCapacity);
		this->isDefault = true;
	}

	template<typename T>
	PriorityQueueTwoLists<T>::PriorityQueueTwoLists(const PriorityQueueTwoLists<T>& other) :
		PriorityQueueTwoLists<T>()
	{
		*this = other;
	}

	template<typename T>
	PriorityQueueTwoLists<T>::~PriorityQueueTwoLists()
	{

		for (PriorityQueueItem<T>* item : *this->longList_)
		{
			delete item;
		}
		this->longList_->clear();

		delete shortList_;
		delete longList_;
	}

	template<typename T>
	Structure * PriorityQueueTwoLists<T>::clone() const
	{
		return new PriorityQueueTwoLists<T>(*this);
	}

	template<typename T>
	PriorityQueue<T>& PriorityQueueTwoLists<T>::operator=(const PriorityQueue<T>& other)
	{
		return *this = dynamic_cast<const PriorityQueueTwoLists<T>&>(other);
	}

	template<typename T>
	PriorityQueueTwoLists<T>& PriorityQueueTwoLists<T>::operator=(const PriorityQueueTwoLists<T>& other)
	{
		//TODO 06: PriorityQueueTwoLists
		throw std::exception("PriorityQueueTwoLists<T>::operator=: Not implemented yet.");
	}

	template<typename T>
	size_t PriorityQueueTwoLists<T>::size() const
	{
		return this->shortList_->size() + this->longList_->size();
	}

	template<typename T>
	void PriorityQueueTwoLists<T>::clear()
	{
		this->shortList_->clear();
		this->longList_->clear();
	}

	template<typename T>
	void PriorityQueueTwoLists<T>::push(const int priority, const T & data)
	{
		if (this->longList_->size() == 0 || this->shortList_->minPriority() > priority) {
			if (this->shortList_->size() == this->shortList_->capacity()) {
				if (this->shortList_->minPriority() > priority) {
					PriorityQueueItem<T>* removed = this->shortList_->pushAndRemove(priority, data);
					this->longList_->add(removed);
				}
				else {
					this->longList_->add(new PriorityQueueItem<T>(priority, data));
				}
			}
			else {
				this->shortList_->push(priority, data);
			}	
		}
		else {
			this->longList_->add(new PriorityQueueItem<T>(priority, data));
		}
	}

	template<typename T>
	T PriorityQueueTwoLists<T>::pop()
	{
		if (this->shortList_->size() <= 1 && this->longList_->size() != 0) {
		//////////////////////////////////////////////////////////////////////////
		///KAPACITA
			if (!this->isDefault) {
				int kapacita = (int)round(sqrt(this->longList_->size()));
				if (kapacita > defaultCapacity) {
					this->shortList_->trySetCapacity(kapacita);
				}
				else {
					this->shortList_->trySetCapacity(defaultCapacity);
				}
			}	
		//////////////////////////////////////////////////////////////////////////

		//////////////////////////////////////////////////////////////////////////
		///POP Prvku
			T pop = this->shortList_->pop();
		//////////////////////////////////////////////////////////////////////////

		//////////////////////////////////////////////////////////////////////////
		///UPRAVA SHORTLIST / LONGLIST, RETURN POP
			LinkedList<PriorityQueueItem<T>*>* pomocnyZoznam = new LinkedList<PriorityQueueItem<T>*>;
			while (this->longList_->size() > 0) {
				PriorityQueueItem<T>* deleted = this->longList_->removeAt(0);

				T data = deleted->accessData();
				int priorityDeleted = deleted->getPriority();

				if (this->shortList_->size() == this->shortList_->capacity()) {
					if (priorityDeleted < this->shortList_->minPriority()) {
						PriorityQueueItem<T>* pushedOut;
						pushedOut = this->shortList_->pushAndRemove(deleted->getPriority(), deleted->accessData());
						if (pushedOut != nullptr) {
							pomocnyZoznam->add(pushedOut);
						}
						delete deleted;
					}
					else {
						pomocnyZoznam->add(new PriorityQueueItem<T>(priorityDeleted, data));
						delete deleted;
					}
				}
				else {
					this->shortList_->push(deleted->getPriority(), deleted->accessData());
					delete deleted;
				}
			}
			delete longList_;
			longList_ = pomocnyZoznam;
			
			return pop;			
		}
		//////////////////////////////////////////////////////////////////////////

		//////////////////////////////////////////////////////////////////////////
		///AK SHORTLIST MA VIAC AKO 1 PRVOK
		else {
			return this->shortList_->pop();
		}
		//////////////////////////////////////////////////////////////////////////

		throw std::logic_error("Dvojzoznam je prazdny!");
	}

	template<typename T>
	T & PriorityQueueTwoLists<T>::peek()
	{
		if (this->shortList_->size() > 0) {
			return (*this->shortList_).peek();
		}
		else {
			throw std::logic_error("Dvojzoznam je prazdny!");
		}
	}


	template<typename T>
	const T PriorityQueueTwoLists<T>::peek() const
	{
		if (this->shortList_->size() > 0) {
			return this->shortList_->peek();
		}
		else {
			throw std::logic_error("Dvojzoznam je prazdny!");
		}
	}

	template<typename T>
	int PriorityQueueTwoLists<T>::peekPriority() const
	{
		if (this->shortList_->size() > 0) {
			return this->shortList_->maxPriority();
		}
		else {
			throw std::logic_error("Dvojzoznam je prazdny!");
		}
	}

}