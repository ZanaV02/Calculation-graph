#pragma once
#include "Operations.h"
#include <map>

template<typename T, int ...N>
std::map < std::string, char> globalMap = {
	{typeid(AddOperation<T, N...>).name(), '+'},
	{typeid(SubOperation<T, N...>).name(), '-'},
	{typeid(HadamardOperation<T, N...>).name(), '*'},
	{typeid(PlusSkalarOperation<T, N...>).name(), 'P'},
	{typeid(MinusSkalarOperation<T, N...>).name(), 'M'},
	{typeid(MultiplySkalarOperation<T, N...>).name(), 'm'},
	{typeid(NegationSkalarOperation<T, N...>).name(), 'N'}
};

template<typename T, int ...N>
std::map <char, std::shared_ptr<IOperation<T, N...>>> globalMap2 = {
	{'+', std::make_shared<AddOperation<T, N...>>()},
	{'-', std::make_shared<SubOperation<T, N...>>()},
	{'*', std::make_shared<HadamardOperation<T, N...>>()},
	{'P', std::make_shared<PlusSkalarOperation<T, N...>>()},
	{'M', std::make_shared<MinusSkalarOperation<T, N...>>()},
	{'m', std::make_shared<MultiplySkalarOperation<T, N...>>()},
	{'N', std::make_shared<NegationSkalarOperation<T, N...>>()}
};
