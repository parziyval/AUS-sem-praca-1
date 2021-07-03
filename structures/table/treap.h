#pragma once

#include "../structures/heap_monitor.h"
#include "binary_search_tree.h"
#include <random>

namespace structures
{
	/// <summary> Prvok treap-u. </summary>
	/// <typeparam name = "K"> Kluc prvku. </typepram>
	/// <typeparam name = "T"> Typ dat ukladanych v prvku. </typepram>
	template <typename K, typename T>
	class TreapItem : public TableItem<K, T>
	{
	public:
		/// <summary> Konstruktor. </summary>
		/// <param name = "key"> Kluc prvku. </param>
		/// <param name = "data"> Data, ktore uchovava. </param>
		/// <param name = "priority"> Priorita. </param>
		TreapItem(K key, T data, int priority);

		/// <summary> Getter atributu priorita. </summary>
		/// <returns> Priorita. </returns>
		int getPriority();

		/// <summary> Nastavi minimalnu prioritu. </summary>
		void minimizePriority();
	private:
		/// <summary> Kluc prvku. </summary>
		int priority_;
	};

	/// <summary> Treap. </summary>
	/// <typeparam name = "K"> Kluc prvkov v tabulke. </typepram>
	/// <typeparam name = "T"> Typ dat ukladanych v tabulke. </typepram>
	template <typename K, typename T>
	class Treap : public BinarySearchTree<K, T>
	{
	public:
		/// <summary> Konstruktor. </summary>
		Treap();

		/// <summary> Kopirovaci konstruktor. </summary>
		/// <param name = "other"> Treap, z ktoreho sa prevezmu vlastnosti. </param>
		Treap(const Treap<K, T>& other);

		/// <summary> Destruktor. </summary>
		~Treap();

		/// <summary> Operacia klonovania. Vytvori a vrati duplikat udajovej struktury. </summary>
		/// <returns> Ukazovatel na klon struktury. </returns>
		Structure* clone() const override;

		/// <summary> Operator priradenia. </summary>
		/// <param name = "other"> Binarny vyhladavaci strom, z ktoreho ma prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa tato tabulka nachadza po priradeni. </returns>
		BinarySearchTree<K, T>& operator=(const BinarySearchTree<K, T>& other) override;

		/// <summary> Operator priradenia. </summary>
		/// <param name = "other"> Treap, z ktoreho ma prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa tato tabulka nachadza po priradeni. </returns>
		virtual Treap<K, T>& operator=(const Treap<K, T>& other);

		/// <summary> Vlozi data s danym klucom do tabulky. </summary>
		/// <param name = "key"> Kluc vkladanych dat. </param>
		/// <param name = "data"> Vkladane data. </param>
		/// <exception cref="std::logic_error"> Vyhodena, ak tabulka uz obsahuje data s takymto klucom. </exception>  
		void insert(const K& key, const T& data) override;

		/// <summary> Odstrani z tabulky prvok s danym klucom. </summary>
		/// <param name = "key"> Kluc prvku. </param>
		/// <returns> Odstranene data. </returns>
		/// <exception cref="std::logic_error"> Vyhodena, ak tabulka neobsahuje data s takymto klucom. </exception>  
		T remove(const K& key) override;

	private:
		/// <summary> Generator nahodnej priority. </summary>
		std::default_random_engine* generator_;

		/// <summary> Skontroluje, ci je haldove usporiadanie prvkov okolo vrcholu OK. </summary>
		/// <param name = "node"> Vrchol, ktoreho susedstvo sa kontroluje. </param>
		/// <returns> true, ak je haldove usporiadanie prvkov okolo vrcholu OK, false inak. </returns>
		bool isHeapOK(typename BinarySearchTree<K, T>::BSTTreeNode* node);

		/// <summary> Vytiahne prioritu z vrcholu stromu. </summary>
		/// <param name = "node"> Vrchol, ktoreho priorita ma byt zistena. </param>
		/// <returns> Priorita vrcholu. Ak je vrchol nullptr, vrati -1. </returns>
		int extractPriority(typename BinarySearchTree<K, T>::BSTTreeNode* node);

		/// <summary> Spravi lavu rotaciu vrchola okolo otca. </summary>
		/// <param name = "node"> Vrchol, ktory sa bude rotovat. </param>
		/// <remarks> 
		/// Musi byt pravym synom otca!
		/// Zaujme miesto svojho otca.
		/// Otec sa stane lavym synom tohto vrchola.
		/// Potencialny lavy syn tohto vrchola sa stane pravym synom otca.
		/// </remarks>
		void rotateLeftOverParent(typename BinarySearchTree<K, T>::BSTTreeNode* node);

		/// <summary> Spravi pravu rotaciu vrchola okolo otca. </summary>
		/// <param name = "node"> Vrchol, ktory sa bude rotovat. </param>
		/// <remarks> 
		/// Musi byt lavym synom otca!
		/// Zaujme miesto svojho otca.
		/// Otec sa stane pravym synom tohto vrchola.
		/// Potencialny pravy syn tohto vrchola sa stane lavym synom otca.
		/// </remarks>
		void rotateRightOverParent(typename BinarySearchTree<K, T>::BSTTreeNode* node);
	};

	template<typename K, typename T>
	inline TreapItem<K, T>::TreapItem(K key, T data, int priority):
		TableItem<K, T>(key, data),
		priority_(priority)
	{
	}

	template<typename K, typename T>
	inline int TreapItem<K, T>::getPriority()
	{
		return priority_;
	}

	template<typename K, typename T>
	inline void TreapItem<K, T>::minimizePriority()
	{
		priority_ = INT_MAX;
	}

	template<typename K, typename T>
	inline Treap<K, T>::Treap() :
		BinarySearchTree<K, T>(),
		generator_(new std::default_random_engine())
	{
	}

	template<typename K, typename T>
	inline Treap<K, T>::Treap(const Treap<K, T>& other) :
		Treap()
	{
		*this = other;
	}

	template<typename K, typename T>
	inline Treap<K, T>::~Treap()
	{
		delete this->generator_;
		this->generator_ = nullptr;
	}

	template<typename K, typename T>
	inline Structure * Treap<K, T>::clone() const
	{
		return new Treap<K, T>(*this);
	}

	template<typename K, typename T>
	inline BinarySearchTree<K, T>& Treap<K, T>::operator=(const BinarySearchTree<K, T>& other)
	{
		return *this = dynamic_cast<const Treap<K, T>&>(other);
	}

	template<typename K, typename T>
	inline Treap<K, T>& Treap<K, T>::operator=(const Treap<K, T>& other)
	{
		if (this != & other)
		{
			BinarySearchTree<K, T>::operator=(other);
			*this->generator_ = *other.generator_;
		}
		return *this;
	}

	template<typename K, typename T>
	inline void Treap<K, T>::insert(const K & key, const T & data)
	{
		TreapItem<K, T>* treapItem = new TreapItem<K, T>(key, data,(*generator_)());
		BinaryTreeNode<TableItem<K, T>*>* binaryTreeNode = new BinaryTreeNode<TableItem<K, T>*>(treapItem);

		if (this->tryToInsertNode(binaryTreeNode)) //zaradime vrchol do binarneho stromu ako keby sa nechumelilo
		{
			while (!isHeapOK(binaryTreeNode)) //potom usporiadame podla priorit
			{
				if (binaryTreeNode->isLeftSon())
				{
					this->rotateRightOverParent(binaryTreeNode);
				}
				else if (binaryTreeNode->isRightSon())
				{
					this->rotateLeftOverParent(binaryTreeNode);
				}
			}
			if (binaryTreeNode->isRoot())
			{
				binaryTree_->replaceRoot(binaryTreeNode);
			}
			this->size_++;
		}
		else
		{
			delete treapItem;
			delete binaryTreeNode;
			throw std::logic_error("Key already present!");
		}
	}

	template<typename K, typename T>
	inline T Treap<K, T>::remove(const K & key) 
	{
		bool found = false;

		typename BinarySearchTree<K, T>::BSTTreeNode* mazanyNode = findBSTNode(key, found);

		if (found)
		{
			TreapItem<K, T>* treapItem = dynamic_cast<TreapItem<K, T>*>(mazanyNode->accessData());
			treapItem->minimizePriority();

			int prioritaLavy = extractPriority(mazanyNode->getLeftSon());
			int prioritaPravy = extractPriority(mazanyNode->getRightSon());

			while (prioritaLavy != -1 || prioritaPravy != -1)
			{
				BinarySearchTree<K, T>::BSTTreeNode* rotateSon = nullptr;

				if (prioritaLavy != -1 && prioritaPravy != -1)
				{
					if (prioritaLavy < prioritaPravy)
					{
						rotateSon = mazanyNode->getLeftSon();
					}
					else
					{
						rotateSon = mazanyNode->getRightSon();
					}
				}
				else
				{
					if (prioritaLavy != -1)
					{
						rotateSon = mazanyNode->getLeftSon();
					}
					else
					{
						rotateSon = mazanyNode->getRightSon();
					}
				}

				bool resetRoot = mazanyNode->isRoot();

				if (rotateSon->isLeftSon())
				{
					rotateRightOverParent(rotateSon);
				}
				else
				{
					rotateLeftOverParent(rotateSon);
				}

				if (resetRoot)
				{
					binaryTree_->replaceRoot(rotateSon);
				}

				prioritaLavy = extractPriority(mazanyNode->getLeftSon());
				prioritaPravy = extractPriority(mazanyNode->getRightSon());
			}

			extractNode(mazanyNode);

			T result = mazanyNode->accessData()->accessData();
			delete mazanyNode->accessData();
			delete mazanyNode;
			BinarySearchTree::size_--; // BinarySearchTree::
			return result;
		}
		else
		{
			throw std::logic_error("Key not found!");
		}
	}

	template<typename K, typename T>
	inline bool Treap<K, T>::isHeapOK(typename BinarySearchTree<K, T>::BSTTreeNode* node)
	{
		int nodePriority = this->extractPriority(node);
		int parentPriority = this->extractPriority(node->getParent());
		int lSonPriority = this->extractPriority(node->getLeftSon());
		int rSonPriority = this->extractPriority(node->getRightSon());

		return (nodePriority >= parentPriority || parentPriority == -1) &&
			(nodePriority <= lSonPriority || lSonPriority == -1) &&
			(nodePriority <= rSonPriority || rSonPriority == -1);
	}

	template<typename K, typename T>
	inline int Treap<K, T>::extractPriority(typename BinarySearchTree<K, T>::BSTTreeNode * node)
	{
		if (node != nullptr)
		{
			TableItem<K, T>* item = node->accessData();
			return dynamic_cast<TreapItem<K, T>*>(item)->getPriority();
		}
		else
		{
			return -1;
		}
	}

	template<typename K, typename T>
	inline void Treap<K, T>::rotateLeftOverParent(typename BinarySearchTree<K, T>::BSTTreeNode * node)
	{
		if (node->isRightSon())
		{
			BinarySearchTree<K, T>::BSTTreeNode* lSon = node->getLeftSon();
			node->setLeftSon(nullptr); 
			BinarySearchTree<K, T>::BSTTreeNode* parent =  node->getParent();
			BinarySearchTree<K, T>::BSTTreeNode* grandParent = parent->getParent();
			parent->setRightSon(nullptr); 
			if (grandParent != nullptr)
			{
				if (parent->isLeftSon())
				{
					grandParent->setLeftSon(node);
				}
				else
				{
					grandParent->setRightSon(node);
				}
			}

			parent->setRightSon(lSon);
			node->setLeftSon(parent);
		}
	}

	template<typename K, typename T>
	inline void Treap<K, T>::rotateRightOverParent(typename BinarySearchTree<K, T>::BSTTreeNode * node)
	{
		if (node->isLeftSon())
		{
			BinarySearchTree<K, T>::BSTTreeNode* rSon = node->getRightSon();
			node->setRightSon(nullptr); 
			BinarySearchTree<K, T>::BSTTreeNode* parent = node->getParent();
			BinarySearchTree<K, T>::BSTTreeNode* grandParent = parent->getParent();
			parent->setLeftSon(nullptr); 
			if (grandParent != nullptr)
			{
				if (parent->isLeftSon())
				{
					grandParent->setLeftSon(node);
				}
				else
				{
					grandParent->setRightSon(node);
				}
			}

			parent->setLeftSon(rSon);
			node->setRightSon(parent);

		}
	}
}