#pragma once
#include "Operations.h"
#include "Map.h"
#include <memory>

template <typename T, int ...N>
class Node
{
	std::shared_ptr<Tensor<T, N...>> tensor;
	std::shared_ptr<IOperation<T, N...>> operation;
	int scalar = -1;
public:
	Node()
	{
		tensor = nullptr;
		operation = nullptr;
	}
	void setScalar(int s)
	{
		scalar = s;
	}
	int getScalar()
	{
		return this->scalar;
	}
	Node(std::shared_ptr<Tensor<T, N...>> t)
	{
		tensor = t;
		operation = nullptr;
	}
	Node(std::shared_ptr<IOperation<T, N...>> o)
	{
		tensor = nullptr;
		operation = o;
	}
	bool isTensor()
	{
		if (this->tensor != nullptr)
			return true;
		else
			return false;
	}
	bool isOperation()
	{
		if (this->operation != nullptr)
			return true;
		else
			return false;
	}
	void setTensor(std::shared_ptr<Tensor<T, N...>> t)
	{
		this->tensor = t;
	}
	void setOperation(std::shared_ptr<IOperation<T, N...>> o)
	{
		this->operation = o;
	}
	std::shared_ptr<Tensor<T, N...>> getTensor()
	{
		return this->tensor;
	}
	std::shared_ptr<IOperation<T, N...>> getOperationn()
	{
		return this->operation;
	}
	bool isOperationUnare()
	{
		if (dynamic_cast<NegationSkalarOperation<T, N...>*>(this->operation.get()))
			return true;
		else if (dynamic_cast<PlusSkalarOperation<T, N...>*>(this->operation.get()))
			return true;
		else if (dynamic_cast<MinusSkalarOperation<T, N...>*>(this->operation.get()))
			return true;
		else if (dynamic_cast<MultiplySkalarOperation<T, N...>*>(this->operation.get()))
			return true;
		else
			return false;
	}
};

template<typename T, int ...N>
char whichOperation(std::shared_ptr<IOperation<T, N...>> (a))
{
	return globalMap<T, N...>[typeid(*a).name()];
};

template<typename T, int ...N>
std::shared_ptr <IOperation<T, N...>> returnOperation(char c)
{
	return globalMap2<T, N...>[c];
};
