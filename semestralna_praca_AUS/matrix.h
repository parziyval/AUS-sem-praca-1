#pragma once
#include "../structures/heap_monitor.h"
#include "../structures/structure.h"
namespace structures 
{
	template<typename T>
	class Matrix : public Structure
	{
	public:
		//virtual Matrix(const Matrix<T>& other) = 0; 
		virtual ~Matrix() {};
		virtual Matrix<T>& operator=(const Matrix<T>& other) = 0;
		//virtual Matrix<T>* clone() const = 0; Structure
		virtual T getItemAt(int row, int column) const = 0;
		virtual void setItemAt(int row, int column, T data) = 0;
		virtual int getRowCount() = 0;
		virtual int getColCount() = 0;

		Structure& operator=(const Structure& other) override;
		/*virtual Structure* clone() const = 0; 
		virtual size_t size() const = 0;*/
		virtual void print() = 0;
	};

	template<typename T>
	inline Structure& Matrix<T>::operator=(const Structure& other)
	{
		if (this != &other)
		{
			*this = dynamic_cast<const Matrix<T>&>(other);
		}
		return *this;
	}
}