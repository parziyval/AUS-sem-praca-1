#pragma once
#include "../structures/heap_monitor.h"
#include <iostream>
#include "../structures/array/array.h"
#include "matrix.h"
namespace structures {
	template <typename T>
	class ImplicitMatrix:public Matrix<T>
	{
	public:
		ImplicitMatrix(int rows, int columns, T initValue);
		ImplicitMatrix(const ImplicitMatrix<T>& other);
		~ImplicitMatrix();

		Matrix<T>& operator=(const Matrix<T>& other);
		ImplicitMatrix<T>& operator=(const ImplicitMatrix<T>& other);
		ImplicitMatrix<T> operator+(const ImplicitMatrix<T>& other);
		ImplicitMatrix<T> operator*(const ImplicitMatrix<T>& other);
		Structure* clone() const override;
		size_t size() const;

		int getRowCount();
		int getColCount();
		T getItemAt(int row, int column) const;
		void setItemAt(int row, int column, T data);
		void print();
	private:
		Array<T>* matrix;
		size_t rowCount; //m
		size_t colCount; //n
	};

	template<typename T>
	inline ImplicitMatrix<T>::ImplicitMatrix(int rows, int columns, T initValue)
		: Matrix<T>::Matrix()
	{
		matrix = new Array<T>(rows * columns);
		rowCount = rows;
		colCount = columns;
		for (int i = 0; i < (rows * columns); i++)
		{
			(*matrix)[i] = initValue;
		}
	}

	template<typename T>
	inline ImplicitMatrix<T>::ImplicitMatrix(const ImplicitMatrix<T>& other)
		: Matrix<T>::Matrix()
	{
		matrix = new Array<T>(*other.matrix);
		rowCount = other.rowCount;
		colCount = other.colCount;
	}
		
	template<typename T>
	inline ImplicitMatrix<T>::~ImplicitMatrix()
	{
		delete matrix;
		matrix = nullptr;
		rowCount = 0;
		colCount = 0;
	}

	template<typename T>
	inline Matrix<T>& ImplicitMatrix<T>::operator=(const Matrix<T>& other)
	{
		if (this != &other)
		{
			*this = dynamic_cast<const ImplicitMatrix<T>&>(other);
		}
		return *this;
	}

	template<typename T>
	inline ImplicitMatrix<T>& ImplicitMatrix<T>::operator=(const ImplicitMatrix<T>& other)
	{
		if (this != &other)
		{
			delete matrix;
			matrix = new Array<T>(*other.matrix);
			colCount = other.colCount;
			rowCount = other.rowCount;
		}
		return *this;
	}

	template<typename T>
	inline ImplicitMatrix<T> ImplicitMatrix<T>::operator+(const ImplicitMatrix<T>& other)
	{
		if (rowCount != other.rowCount || colCount != other.colCount) {
			throw std::logic_error("Pocty riadkov alebo pocty stlpcov matic sa nerovnaju!");
		}

		ImplicitMatrix<T> returned(rowCount, colCount, 0);
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
	inline ImplicitMatrix<T> ImplicitMatrix<T>::operator*(const ImplicitMatrix<T>& other)
	{
		if (rowCount != other.colCount || colCount != other.rowCount)
		{
			throw std::logic_error("Rozmery matic nie su m x n a n x m!");
		}

		ImplicitMatrix<T> multiplied(rowCount, other.colCount, 0);

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
	inline Structure* ImplicitMatrix<T>::clone() const
	{
		return new ImplicitMatrix<T>(*this);
	}

	template<typename T>
	inline size_t ImplicitMatrix<T>::size() const
	{
		return rowCount*colCount;
	}

	template<typename T>
	inline int ImplicitMatrix<T>::getRowCount()
	{
		return rowCount;
	}

	template<typename T>
	inline int ImplicitMatrix<T>::getColCount()
	{
		return colCount;
	}

	template<typename T>
	inline T ImplicitMatrix<T>::getItemAt(int row, int column) const
	{
		/*DSRoutines::rangeCheckExcept(row, rowCount, "Invalid row index!");
		DSRoutines::rangeCheckExcept(column, colCount, "Invalid column index!");*/
		if (row < 0 || row >= rowCount || column < 0 || column >= colCount)
		{
			throw std::logic_error("Invalid row or column index!");
		}
		return (*matrix)[row * colCount + column];
	}

	template<typename T>
	inline void ImplicitMatrix<T>::setItemAt(int row, int column, T data)
	{
		/*DSRoutines::rangeCheckExcept(row, rowCount, "Invalid row index!");
		DSRoutines::rangeCheckExcept(column, colCount, "Invalid column index!");*/
		if (row < 0 || row >= rowCount || column < 0 || column >= colCount)
		{
			throw std::logic_error("Invalid row or column index!");
		}
		(*matrix)[row * colCount + column] = data;
	}

	template<typename T>
	inline void ImplicitMatrix<T>::print()
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