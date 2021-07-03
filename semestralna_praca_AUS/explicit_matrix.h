#pragma once
#include "../structures/heap_monitor.h"
#include <iostream>
#include "../structures/array/array.h"
#include "matrix.h"

namespace structures {
	template <typename T>
	class ExplicitMatrix :public Matrix<T>
	{
	public:
		ExplicitMatrix(int rows, int columns, T initValue);
		ExplicitMatrix(const ExplicitMatrix<T>& other);
		~ExplicitMatrix();

		Matrix<T>& operator=(const Matrix<T>& other);
		ExplicitMatrix<T>& operator=(const ExplicitMatrix<T>& other);
		ExplicitMatrix<T> operator+(const ExplicitMatrix<T>& other);
		ExplicitMatrix<T> operator*(const ExplicitMatrix<T>& other);
		Structure* clone() const override;
		size_t size() const;
		
		int getRowCount();
		int getColCount();
		T getItemAt(int row, int column) const;
		void setItemAt(int row, int column, T data);
		void print();
	private:
		Array<Array<T>*>* matrix;
		size_t rowCount; //m
		size_t colCount; //n
	};

	template<typename T>
	inline ExplicitMatrix<T>::ExplicitMatrix(int rows, int columns, T initValue) 
		: Matrix<T>::Matrix()
	{
		rowCount = rows;
		colCount = columns;
		matrix = new Array<Array<T>*>(rowCount);

		for (int i = 0; i < rowCount; i++)
		{
			(*matrix)[i] = new Array<T>(colCount);
			for (int j = 0; j < colCount; j++)
			{
				(*(*matrix)[i])[j] = initValue;
			}
		}
	}

	template<typename T>
	inline ExplicitMatrix<T>::ExplicitMatrix(const ExplicitMatrix<T>& other) 
		: Matrix<T>::Matrix()
	{
		rowCount = other.rowCount;
		colCount = other.colCount;

		matrix = new Array<Array<T>*>(rowCount);
		for (int i = 0; i < rowCount; i++)
		{
			(*matrix)[i] = new Array<T>(*(*other.matrix)[i]);
		}
	}

	template<typename T>
	inline ExplicitMatrix<T>::~ExplicitMatrix()
	{
		for (int i = 0; i < rowCount; i++)
		{
			delete (*matrix)[i];
			(*matrix)[i] = nullptr;
		}
		delete matrix;
		matrix = nullptr;
		rowCount = 0;
		colCount = 0;
	}

	template<typename T>
	inline Matrix<T>& ExplicitMatrix<T>::operator=(const Matrix<T>& other)
	{
		if (this != &other)
		{
			*this = dynamic_cast<const ExplicitMatrix<T>&>(other);
		}
		return *this;
	}

	template<typename T>
	inline ExplicitMatrix<T>& ExplicitMatrix<T>::operator=(const ExplicitMatrix<T>& other)
	{
		if (this != &other)
		{
			for (int i = 0; i < rowCount; i++)
			{
				delete (*matrix)[i];
			}
			delete matrix;

			rowCount = other.rowCount;
			colCount = other.colCount;

			matrix = new Array<Array<T>*>(rowCount);
			for (int i = 0; i < rowCount; i++)
			{
				(*matrix)[i] = new Array<T>(*(*other.matrix)[i]);
			}
		}
		return *this;
	}

	template<typename T>
	inline ExplicitMatrix<T> ExplicitMatrix<T>::operator+(const ExplicitMatrix<T>& other)
	{
		if (rowCount != other.rowCount || colCount != other.colCount) {
			throw std::logic_error("Pocty riadkov alebo pocty stlpcov matic sa nerovnaju!");
		}

		ExplicitMatrix<T> returned(rowCount, colCount, 0);
		for (int i = 0; i < rowCount; i++)
		{
			for (int j = 0; j < colCount; j++)
			{
				returned.setItemAt(i, j, this->getItemAt(i, j) + other.getItemAt(i, j));
			}
		}

		return returned;
	}

	template<typename T>
	inline ExplicitMatrix<T> ExplicitMatrix<T>::operator*(const ExplicitMatrix<T>& other)
	{
		if (rowCount != other.colCount || colCount != other.rowCount)
		{
			throw std::logic_error("Rozmery matic nie su m x n a n x m!");
		}

		ExplicitMatrix<T> multiplied(rowCount, other.colCount, 0);

		for (int i = 0; i < rowCount; i++)
		{
			for (int j = 0; j < other.colCount; j++)
			{
				for (int k = 0; k < other.rowCount; k++)
				{
					//T item = multiplied.getItemAt(i, j) + (this->getItemAt(i, k) * other.getItemAt(k, j));
					multiplied.setItemAt(i, j, multiplied.getItemAt(i, j) + (this->getItemAt(i, k) * other.getItemAt(k, j)));
				}
			}
		}

		return multiplied;
	}

	template<typename T>
	inline Structure* ExplicitMatrix<T>::clone() const
	{
		return new ExplicitMatrix<T>(*this);
	}

	template<typename T>
	inline size_t ExplicitMatrix<T>::size() const
	{
		return rowCount * colCount;
	}

	template<typename T>
	inline int ExplicitMatrix<T>::getRowCount()
	{
		return rowCount;
	}

	template<typename T>
	inline int ExplicitMatrix<T>::getColCount()
	{
		return colCount;
	}

	template<typename T>
	inline T ExplicitMatrix<T>::getItemAt(int row, int column) const
	{
		/*DSRoutines::rangeCheckExcept(row, rowCount, "Invalid row index!");
		DSRoutines::rangeCheckExcept(column, colCount, "Invalid column index!");*/
		if (row < 0 || row >= rowCount || column < 0 || column >= colCount)
		{
			throw std::logic_error("Invalid row or column index!");
		}
		return (*(*matrix)[row])[column];
	}

	template<typename T>
	inline void ExplicitMatrix<T>::setItemAt(int row, int column, T data)
	{
		/*DSRoutines::rangeCheckExcept(row, rowCount, "Invalid row index!");
		DSRoutines::rangeCheckExcept(column, colCount, "Invalid column index!");*/
		if (row < 0 || row >= rowCount || column < 0 || column >= colCount)
		{
			throw std::logic_error("Invalid row or column index!");
		}
		(*(*matrix)[row])[column] = data;
	}

	template<typename T>
	inline void ExplicitMatrix<T>::print()
	{
		for (int i = 0; i < rowCount; i++)
		{
			for (int j = 0; j < colCount; j++)
			{
				std::cout << getItemAt(i, j);
				std::cout << " ";
			}
			std::cout << "\n";
		}
	}
}