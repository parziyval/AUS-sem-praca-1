#pragma once
#include "../structures/heap_monitor.h"
#include "matrix.h"
#include "implicit_matrix.h"
#include "explicit_matrix.h"
template<typename T>
class VytvaracMatic
{
public:
	virtual structures::Matrix<T>* vytvorMaticu(int riadky, int stlpce, T initHodnota) = 0;
};

