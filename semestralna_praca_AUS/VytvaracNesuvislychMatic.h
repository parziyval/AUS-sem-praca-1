#pragma once
#include "../structures/heap_monitor.h"
#include "VytvaracMatic.h"
template<typename T>
class VytvaracNesuvislychMatic :
    public VytvaracMatic<T>
{
public:
    structures::Matrix<T>* vytvorMaticu(int riadky, int stlpce, T initHodnota) override;
};

template<typename T>
inline structures::Matrix<T>* VytvaracNesuvislychMatic<T>::vytvorMaticu(int riadky, int stlpce, T initHodnota)
{
    return new structures::ExplicitMatrix<T>(riadky, stlpce, initHodnota);
}
