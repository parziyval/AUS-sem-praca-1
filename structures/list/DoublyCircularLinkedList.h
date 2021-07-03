#pragma once

#include "list.h"
#include "../structure_iterator.h"
#include "../ds_routines.h"

namespace structures
{

	/// <summary> Prvok jednostranne zretazeneho zoznamu. </summary>
	/// <typeparam name = "T"> Typ dat ukladanych v prvku. </typepram>
	template<typename T>
	class DCLinkedListItem : public DataItem<T>
	{
	public:
		/// <summary> Konstruktor. </summary>
		/// <param name = "data"> Data, ktore uchovava. </param>
		DCLinkedListItem(T data);

		/// <summary> Kopirovaci konstruktor. </summary>
		/// <param name = "other"> Prvok jednstranne zretazeneho zoznamu, z ktoreho sa prevezmu vlastnosti.. </param>
		DCLinkedListItem(const DCLinkedListItem<T>& other);

		/// <summary> Destruktor. </summary>
		~DCLinkedListItem();

		/// <summary> Getter nasledujuceho prvku zretazeneho zoznamu. </summary>
		/// <returns> Nasledujuci prvok zretazeneho zoznamu. </returns>
		DCLinkedListItem<T>* getNext();
		DCLinkedListItem<T>* getPrevious();

		/// <summary> Setter nasledujuceho prvku zretazeneho zoznamu. </summary>
		/// <param name´= "next"> Novy nasledujuci prvok zretazeneho zoznamu. </param>
		void setNext(DCLinkedListItem<T>* next);
		void setPrevious(DCLinkedListItem<T>* previous);
	private:
		/// <summary> Nasledujuci prvok zretazeneho zoznamu. </summary>
		DCLinkedListItem<T>* next_;
		DCLinkedListItem<T>* prev_;
	};

	/// <summary> Jednostranne zretazeny zoznam. </summary>
	/// <typeparam name = "T"> Typ dat ukladanych v zozname. </typepram>
	template<typename T>
	class DoublyCircularLinkedList : public List<T>
	{
	public:
		/// <summary> Konstruktor. </summary>
		DoublyCircularLinkedList();

		/// <summary> Kopirovaci konstruktor. </summary>
		/// <param name = "other"> DoublyCircularLinkedList, z ktoreho sa prevezmu vlastnosti. </param>
		DoublyCircularLinkedList(const DoublyCircularLinkedList<T>& other);

		/// <summary> Destruktor. </summary>
		~DoublyCircularLinkedList();

		/// <summary> Operacia klonovania. Vytvori a vrati duplikat zoznamu. </summary>
		/// <returns> Ukazovatel na klon struktury. </returns>
		Structure* clone() const override;

		/// <summary> Vrati pocet prvkov v zozname. </summary>
		/// <returns> Pocet prvkov v zozname. </returns>
		size_t size() const override;

		/// <summary> Operator priradenia. </summary>
		/// <param name = "other"> Zoznam, z ktoreho ma prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa tento zoznam nachadza po priradeni. </returns>
		List<T>& operator=(const List<T>& other) override;

		/// <summary> Operator priradenia. </summary>
		/// <param name = "other"> Zoznam, z ktoreho ma prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa tento zoznam nachadza po priradeni. </returns>
		DoublyCircularLinkedList<T>& operator=(const DoublyCircularLinkedList<T>& other);

		/// <summary> Vrati adresou prvok na indexe. </summary>
		/// <param name = "index"> Index prvku. </param>
		/// <returns> Adresa prvku na danom indexe. </returns>
		/// <exception cref="std::out_of_range"> Vyhodena, ak index nepatri do zoznamu. </exception>  
		T& operator[](const int index) override;

		/// <summary> Vrati hodnotou prvok na indexe. </summary>
		/// <param name = "index"> Index prvku. </param>
		/// <returns> Hodnota prvku na danom indexe. </returns>
		/// <exception cref="std::out_of_range"> Vyhodena, ak index nepatri do zoznamu. </exception>  
		const T operator[](const int index) const override;

		/// <summary> Prida prvok do zoznamu. </summary>
		/// <param name = "data"> Pridavany prvok. </param>
		void add(const T& data) override;

		/// <summary> Vlozi prvok do zoznamu na dany index. </summary>
		/// <param name = "data"> Pridavany prvok. </param>
		/// <param name = "index"> Index prvku. </param>
		/// <exception cref="std::out_of_range"> Vyhodena, ak index nepatri do zoznamu. </exception>  
		/// <remarks> Ak je ako index zadana hodnota poctu prvkov (teda prvy neplatny index), metoda insert sa sprava ako metoda add. </remarks>
		void insert(const T& data, const int index) override;

		/// <summary> Odstrani prvy vyskyt prvku zo zoznamu. </summary>
		/// <param name = "data"> Odstranovany prvok. </param>
		/// <returns> true, ak sa podarilo prvok zo zoznamu odobrat, false inak. </returns>
		bool tryRemove(const T& data) override;

		/// <summary> Odstrani zo zoznamu prvok na danom indexe. </summary>
		/// <param name = "index"> Index prvku. </param>
		/// <returns> Odstraneny prvok. </returns>
		/// <exception cref="std::out_of_range"> Vyhodena, ak index nepatri do zoznamu. </exception>  
		T removeAt(const int index) override;

		/// <summary> Vrati index prveho vyskytu prvku v zozname. </summary>
		/// <param name = "data"> Prvok, ktoreho index sa hlada. </param>
		/// <returns> Index prveho vyskytu prvku v zozname, ak sa prvok v zozname nenachadza, vrati -1. </returns>
		int getIndexOf(const T& data) override;

		/// <summary> Vymaze zoznam. </summary>
		void clear() override;

		void set(const T& data, const int index);
		/// <summary> Vrati skutocny iterator na zaciatok struktury </summary>
		/// <returns> Iterator na zaciatok struktury. </returns>
		/// <remarks> Zabezpecuje polymorfizmus. </remarks>
		Iterator<T>* getBeginIterator() const override;

		/// <summary> Vrati skutocny iterator na koniec struktury </summary>
		/// <returns> Iterator na koniec struktury. </returns>
		/// <remarks> Zabezpecuje polymorfizmus. </remarks>
		Iterator<T>* getEndIterator() const override;
	private:
		/// <summary> Pocet prvkov v zozname. </summary>
		size_t size_;
		/// <summary> Prvy prvok zoznamu. </summary>
		DCLinkedListItem<T>* first_;
		/// <summary> Posledny prvok zoznamu. </summary>
		DCLinkedListItem<T>* last_;
	private:
		/// <summary> Vrati prvok zoznamu na danom indexe. </summary>
		/// <param name = "index"> Pozadovany index. </summary>
		/// <returns> Prvok zoznamu na danom indexe. </param>
		/// <exception cref="std::out_of_range"> Vyhodena, ak index nepatri do zoznamu. </exception>  
		DCLinkedListItem<T>* getItemAtIndex(int index) const;

	};

	template<typename T>
	inline DCLinkedListItem<T>::DCLinkedListItem(T data) :
		DataItem<T>(data),
		next_(nullptr),
		prev_(nullptr)
	{
	}

	template<typename T>
	inline DCLinkedListItem<T>::DCLinkedListItem(const DCLinkedListItem<T>& other) :
		DataItem<T>(other),
		next_(other.next_),
		prev_(other.prev_)
	{
	}

	template<typename T>
	inline DCLinkedListItem<T>::~DCLinkedListItem()
	{
		next_ = nullptr;
		prev_ = nullptr;
	}

	template<typename T>
	inline DCLinkedListItem<T>* DCLinkedListItem<T>::getNext()
	{
		return next_;
	}

	template<typename T>
	inline DCLinkedListItem<T>* DCLinkedListItem<T>::getPrevious()
	{
		return prev_;
	}

	template<typename T>
	inline void DCLinkedListItem<T>::setNext(DCLinkedListItem<T>* next)
	{
		next_ = next;
	}

	template<typename T>
	inline void DCLinkedListItem<T>::setPrevious(DCLinkedListItem<T>* previous)
	{
		prev_ = previous;
	}

	template<typename T>
	inline DoublyCircularLinkedList<T>::DoublyCircularLinkedList() :
		List<T>::List(),
		size_(0),
		first_(nullptr),
		last_(nullptr)
	{
	}

	template<typename T>
	inline DoublyCircularLinkedList<T>::DoublyCircularLinkedList(const DoublyCircularLinkedList<T>& other) :
		DoublyCircularLinkedList()
	{
		*this = other;
	}

	template<typename T>
	inline DoublyCircularLinkedList<T>::~DoublyCircularLinkedList()
	{
		clear();
	}

	template<typename T>
	inline Structure* DoublyCircularLinkedList<T>::clone() const
	{
		return new DoublyCircularLinkedList<T>(*this);
	}

	template<typename T>
	inline size_t DoublyCircularLinkedList<T>::size() const
	{
		return size_;
	}

	//structures:: ?
	template<typename T>
	inline List<T>& DoublyCircularLinkedList<T>::operator=(const List<T>& other)
	{
		if (this != &other)
		{
			*this = dynamic_cast<const DoublyCircularLinkedList<T>&>(other);
		}
		return *this;
	}

	template<typename T>
	inline DoublyCircularLinkedList<T>& DoublyCircularLinkedList<T>::operator=(const DoublyCircularLinkedList<T>& other)
	{
		if (this != &other)
		{
			clear();
			DCLinkedListItem<T>* current = other.first_;
			for (int i = 0; i < size_; i++)
			{
				add(current->accessData());
				current = current->getNext();
			}
		}
		return *this;
	}

	template<typename T>
	inline T& DoublyCircularLinkedList<T>::operator[](const int index)
	{
		return getItemAtIndex(index)->accessData();
	}

	template<typename T>
	inline const T DoublyCircularLinkedList<T>::operator[](const int index) const
	{
		return getItemAtIndex(index)->accessData();
	}

	template<typename T>
	inline void DoublyCircularLinkedList<T>::add(const T& data)
	{
		DCLinkedListItem<T>* newItem = new DCLinkedListItem<T>(data);
		if (size_ == 0)
		{
			first_ = newItem;
			last_ = newItem;
			newItem->setPrevious(last_);
			newItem->setNext(first_);
		}
		else
		{
			last_->setNext(newItem);
			newItem->setPrevious(last_);
			newItem->setNext(first_);
			last_ = newItem;

		}
		first_->setPrevious(last_);
		size_++;
	}

	template<typename T>
	inline void DoublyCircularLinkedList<T>::insert(const T& data, const int index)
	{
		if (index == size_)
		{
			add(data);
		}
		else
		{
			if (index == 0)
			{
				DCLinkedListItem<T>* newItem = new DCLinkedListItem<T>(data);
				newItem->setNext(first_);
				first_->setPrevious(newItem);
				first_ = newItem;
				first_->setPrevious(last_);
				last_->setNext(first_);

			}
			else
			{
				DCLinkedListItem<T>* prevItem = getItemAtIndex(index - 1);
				DCLinkedListItem<T>* newItem = new DCLinkedListItem<T>(data);
				DCLinkedListItem<T>* next = prevItem->getNext();
				newItem->setNext(next);
				newItem->setPrevious(prevItem);
				prevItem->setNext(newItem);
				next->setPrevious(newItem);
			}
			size_++;
		}
	}

	template<typename T>
	inline bool DoublyCircularLinkedList<T>::tryRemove(const T& data)
	{
		int index = getIndexOf(data);
		if (index != -1)
		{
			removeAt(index);
			return true;
		}
		else
		{
			return false;
		}
	}

	template<typename T>
	inline T DoublyCircularLinkedList<T>::removeAt(const int index)
	{
		DCLinkedListItem<T>* deleted;
		if (index == 0 && size_ > 0) {
			deleted = first_;
			first_ = first_->getNext();
			first_->setPrevious(last_);
			last_->setNext(first_);

			if (size_ == 1)
			{
				last_ = nullptr;
			}

		}
		else {
			DCLinkedListItem<T>* prev = getItemAtIndex(index - 1);
			deleted = prev->getNext();
			prev->setNext(deleted->getNext());
			deleted->getNext()->setPrevious(prev);

			if (index == (size_ - 1)) {
				last_ = prev;
				last_->setNext(first_);
			}
		}

		T result = deleted->accessData();
		delete deleted;
		size_--;
		return result;
	}

	template<typename T>
	inline int DoublyCircularLinkedList<T>::getIndexOf(const T& data)
	{
		DCLinkedListItem<T>* current = first_;

		for (int i = 0; i < size_; i++)
		{
			if (current->accessData() == data)
			{
				return i;
			}
			current = current->getNext();
		}

		return -1;
	}

	template<typename T>
	inline void DoublyCircularLinkedList<T>::clear()
	{
		DCLinkedListItem<T>* current = first_;

		for (int i = 0; i < size_; i++)
		{
			DCLinkedListItem<T>* deleted = current;
			current = current->getNext();
			delete deleted;
		}

		first_ = nullptr;
		last_ = nullptr;
		size_ = 0;
	}

	template<typename T>
	inline void DoublyCircularLinkedList<T>::set(const T& data, const int index)
	{
		if (DSRoutines::rangeCheck(index, size_))
		{
			DCLinkedListItem<T>* hladanyPrvok = first_;
			for (int i = 0; i < index; i++)
			{
				hladanyPrvok = hladanyPrvok->getNext();
			}
			hladanyPrvok->accessData() = data;
		}
		else
		{
			throw std::logic_error("Invalid index!");
		}
	}

	template<typename T>
	inline Iterator<T>* DoublyCircularLinkedList<T>::getBeginIterator() const
	{
		return nullptr;
	}

	template<typename T>
	inline Iterator<T>* DoublyCircularLinkedList<T>::getEndIterator() const
	{
		return nullptr;
	}

	template<typename T>
	inline DCLinkedListItem<T>* DoublyCircularLinkedList<T>::getItemAtIndex(int index) const
	{

		DSRoutines::rangeCheckExcept(index, size_, "Invalid index!");
		if (index == (size_ - 1))
		{
			return last_;
		}
		else
		{
			DCLinkedListItem<T>* current;
			if (index <= (size_ - 1) / 2)
			{
				current = first_;
				for (int i = 0; i < index; i++)
				{
					current = current->getNext();
				}
			}
			else
			{
				current = last_;
				for (int i = 0; i < (size_ - index - 1); i++)
				{
					current = current->getPrevious();
				}
			}

			return current;
		}
	}
}