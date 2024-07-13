#pragma once
#include "Tensor.h"

template <typename T, int ...N>
class IOperation
{
public:
	virtual Tensor<T, N...> getOperation(Tensor <T, N...> a, Tensor<T, N...> b) const = 0;
	virtual Tensor<T, N...> getOperation(Tensor <T, N...> a, int scalar) const = 0;
};

template <typename T, int ...N>
class AddOperation :public IOperation <T, N...>
{
public:
	Tensor<T, N...> getOperation(Tensor <T, N...> a, Tensor <T, N...> b) const override
	{
		return a + b;
	}
	Tensor<T, N...> getOperation(Tensor <T, N...> a, int scalar) const override
	{
		throw std::exception("Greska");
	}
};
template <typename T, int ...N>
class SubOperation :public IOperation <T, N...>
{
public:
	Tensor<T, N...> getOperation(Tensor <T, N...> a, Tensor <T, N...> b) const override
	{
		return a - b;
	}
	Tensor<T, N...> getOperation(Tensor <T, N...> a, int scalar) const override
	{
		throw std::exception("Greska");
	}
};
template <typename T, int ...N>
class HadamardOperation :public IOperation <T, N...>
{
public:
	Tensor<T, N...> getOperation(Tensor <T, N...> a, Tensor <T, N...> b) const override
	{
		return a * b;
	}
	Tensor<T, N...> getOperation(Tensor <T, N...> a, int scalar) const override
	{
		throw std::exception("Greska");
	}

};

template <typename T, int ...N>
class PlusSkalarOperation :public IOperation <T, N...>
{
public:

	Tensor<T, N...> getOperation(Tensor <T, N...> a, Tensor <T, N...> b) const override
	{
		throw std::exception("Greska");
	}
	Tensor<T, N...> getOperation(Tensor <T, N...> a, int scalar) const override
	{
		return a + scalar;
	}
};
template <typename T, int ...N>
class MinusSkalarOperation :public IOperation <T, N...>
{
public:

	Tensor<T, N...> getOperation(Tensor <T, N...> a, Tensor <T, N...> b) const override
	{
		throw std::exception("Greska");
	}
	Tensor<T, N...> getOperation(Tensor <T, N...> a, int scalar) const override
	{
		return a - scalar;
	}
};
template <typename T, int ...N>
class MultiplySkalarOperation :public IOperation <T, N...>
{
public:

	Tensor<T, N...> getOperation(Tensor <T, N...> a, Tensor <T, N...> b) const override
	{
		throw std::exception("Greska");
	}
	Tensor<T, N...> getOperation(Tensor <T, N...> a, int scalar) const override
	{
		return a * scalar;
	}
};
template <typename T, int ...N>
class NegationSkalarOperation :public IOperation <T, N...>
{
public:

	Tensor<T, N...> getOperation(Tensor <T, N...> a, Tensor <T, N...> b) const override
	{
		throw std::exception("Greska");
	}
	Tensor<T, N...> getOperation(Tensor <T, N...> a, int scalar) const override
	{
		return a * (-1);
	}
};
 


