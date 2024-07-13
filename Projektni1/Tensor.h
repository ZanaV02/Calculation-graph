#pragma once
#include <vector>
#include <iostream>
#include <fstream>
#include <exception>
#include "Concepts.h"


template <typename T, int ...N>
	requires Tensorable<T>
class Tensor
{
	std::vector<int> dimension;
	std::vector<T> values;

public:
	Tensor()
	{
		for (int i = 0;i < this->dimension.size();i++)
		{
			this->dimension.at(i) = 0;
		}
		for (int i = 0;i < this->values.size();i++)
		{
			this->values.at(i) = 0;
		}
	}

	Tensor(std::vector<T> values) : dimension({ N... }), values(values) {}

	std::vector<int> getDimension()
	{
		return this->dimension;
	}
	std::vector<T> getValues()
	{
		return this->values;
	}
	Tensor<T, N...>& operator=(const Tensor<T, N...>& other) 
	{
		if (this != &other)
		{
			dimension = other.dimension;
			values = other.values;
		}
		return *this;
	}
	bool operator==(const Tensor<T, N...>& other) const //provjera jednakosti
	{
		for (int i = 0;i < this->dimension.size();i++)
		{
			if (this->dimension.at(i) != other.dimension.at(i))
				return false;
		}
		for (int i = 0;i < this->values.size();i++)
		{
			if (this->values.at(i) != other.dimension.at(i))
				return false;
		}
		return true;
	}
	bool operator!=(const Tensor<T, N...>& other) const //provjera razlièitosti
	{
		return !(*this == other);
	}
	Tensor<T, N...> operator+(const Tensor<T, N...>& other) const //sabiranje 2 tenzora
	{
		for (int i = 0;i < this->dimension.size();i++)
		{
			if (this->dimension.at(i) != other.dimension.at(i))
				throw std::exception("Tensor dimensions are not equal!");
		}

		std::vector<T> rezultanteVrijednosti;
		for (int i = 0; i < this->values.size(); i++)
		{
			rezultanteVrijednosti.push_back(this->values.at(i) + other.values.at(i));
		}
		return Tensor<T,N...>(rezultanteVrijednosti);
	}

	Tensor<T, N...> operator-(const Tensor<T, N...>& other) const //oduzimanje 2 tenzora
	{
		for (int i = 0;i < this->dimension.size();i++)
		{
			if (this->dimension.at(i) != other.dimension.at(i))
				throw std::exception("Tensor dimensions are not equal!"); 
		}

		std::vector<T> rezultanteVrijednosti;
		for (int i = 0; i < this->values.size(); i++)
		{
			rezultanteVrijednosti.push_back(this->values.at(i) - other.values.at(i));
		}
		return Tensor<T, N...>(rezultanteVrijednosti);
	}

	Tensor<T, N...> operator*(const Tensor<T, N...>& other) const //Hadamardov proizvod
	{
		for (int i = 0;i < this->dimension.size();i++)
		{
			if (this->dimension.at(i) != other.dimension.at(i))
				throw std::exception("Tensor dimensions are not equal!");
		}

		std::vector<T> rezultanteVrijednosti;
		for (int i = 0; i < this->values.size(); i++)
		{
			rezultanteVrijednosti.push_back(this->values.at(i) * other.values.at(i));
		}
		return Tensor<T, N...>(rezultanteVrijednosti);
	}

	Tensor<T, N...> operator*(const T& scalar) const //množenje tenzora sa skalarom
	{
		std::vector<T> rezultanteVrijednosti;
		for (int i = 0;i < this->values.size();i++)
		{
			rezultanteVrijednosti.push_back(this->values.at(i) * scalar);
		}
		return Tensor<T, N...> (rezultanteVrijednosti);
	}

	Tensor<T, N...> operator+(const T& scalar) const //sabiranje tenzora sa skalarom
	{
		std::vector<T> rezultanteVrijednosti;
		for (int i = 0;i < this->values.size();i++)
		{
			rezultanteVrijednosti.push_back(this->values.at(i) + scalar);
		}
		return Tensor<T, N...> (rezultanteVrijednosti);
	}

	Tensor<T, N...> operator-(const T& scalar) const //oduzimanje skalara od tenzora
	{
		std::vector<T> rezultanteVrijednosti;
		for (int i = 0;i < this->values.size();i++)
		{
			rezultanteVrijednosti.push_back(this->values.at(i) - scalar);
		}
		return Tensor<T, N...>(rezultanteVrijednosti);
	}

	Tensor<T, N...> operator-() const //negacija tenzora
	{
		std::vector<T> rezultanteVrijednosti;
		for (int i = 0;i < this->values.size();i++)
		{
			rezultanteVrijednosti.push_back(this->values.at(i) * (-1));
		}
		return Tensor<T, N...> (rezultanteVrijednosti);
	}

	friend std::ostream& operator<<(std::ostream& os, const Tensor<T, N...>& tensor) //ispis na konzoli
	{
		if (tensor.dimension.size() == 0)
			os << "Tenzor ne postoji!";
		os << "Dimenzija: [ ";
		for (const auto& dim : tensor.dimension)
		{
			os << dim << " ";
		}
		os << "]\n";
		os << "Tenzor: [ ";
		for (const auto& value : tensor.values)
		{
			os << value << " ";
		}
		os << "]\n" << std::endl;
		return os;
	}

	void serialize(std::ofstream& file) //serijalizacija
	{
		if (file.is_open())
		{
			file << this->getDimension().size() << " ";
			for (int i = 0;i < this->getDimension().size();i++)
			{
				file << this->getDimension().at(i) << " ";
			}
			file << "\n";
			for (int i = 0;i < this->getValues().size();i++)
			{
				file << this->getValues().at(i) << " ";
			}
			file << "\n";
		}
		else
		{
			throw std::exception("Datoteka nije otvorena!");
		}
	}

	Tensor<T, N...> deserialize(std::ifstream& file) //deserijalization
	{
		if (file.is_open())
		{
			std::vector<int> dimension;
			std::vector<T> values;
			int size;
			file >> size;
			int dim;
			for (int i = 0;i < size;i++)
			{
				int dim;
				file >> dim;
				dimension.push_back(dim);
			}

			int pom = 1;
			for (int i = 0;i < dimension.size();i++)
			{
				pom *= dimension.at(i);
			}

			T val;
			while (file >> val)
			{
				values.push_back(val);
			}
			if (values.size() != pom)
			{
				throw std::runtime_error("Tensor dimensions are not equal!5");
			}
			return Tensor<T, N...>(values);
		}
		else
		{
			throw std::exception("File is not opened!");
		}
	}
};


template <typename T>
class Tensor<T>
{
	std::vector<int> dimension;
	std::vector<T> values;

public:
	Tensor()
	{
		for (int i = 0;i < this->dimension.size();i++)
		{
			this->dimension.at(i) = 0;
		}
		for (int i = 0;i < this->values.size();i++)
		{
			this->values.at(i) = 0;
		}
	}
	Tensor(std::vector<T> v1, std::vector<T> v2) : dimension(v1), values(v2)
	{
		int pom = 1;
		for (int i = 0;i < v1.size();i++)
		{
			pom *= v1.at(i);
		}
		if (v2.size() != pom)
		{
			throw std::exception("Tensor dimensions are not equal!\n");
		}
	}
	std::vector<int> getDimension()
	{
		return this->dimension;
	}
	std::vector<T> getValues()
	{
		return this->values;
	}
	Tensor<T>& operator=(const Tensor<T>& other) //dodjela tenzora
	{
		if (this != &other)
		{
			dimension = other.dimension;
			values = other.values;
		}
		return *this;
	}
	bool operator==(const Tensor<T>& other) const //provjera jednakosti
	{
		for (int i = 0;i < this->dimension.size();i++)
		{
			if (this->dimension.at(i) != other.dimension.at(i))
				return false;
		}
		for (int i = 0;i < this->values.size();i++)
		{
			if (this->values.at(i) != other.dimension.at(i))
				return false;
		}
		return true;
	}
	bool operator!=(const Tensor<T>& other) const 
	{
		return !(*this == other);
	}
	Tensor<T> operator+(const Tensor<T>& other) const //sabiranje 2 tenzora
	{
		for (int i = 0;i < this->dimension.size();i++)
		{
			if (this->dimension.at(i) != other.dimension.at(i))
				throw std::exception("Tensor dimensions are not equal!");
		}

		std::vector<T> rezultanteVrijednosti;
		for (int i = 0; i < this->values.size(); i++)
		{
			rezultanteVrijednosti.push_back(this->values.at(i) + other.values.at(i));
		}
		return Tensor(this->dimension, rezultanteVrijednosti);
	}

	Tensor<T> operator-(const Tensor<T>& other) const //oduzimanje 2 tenzora
	{
		for (int i = 0;i < this->dimension.size();i++)
		{
			if (this->dimension.at(i) != other.dimension.at(i))
				throw std::exception("Tensor dimensions are not equal!");
		}

		std::vector<T> rezultanteVrijednosti;
		for (int i = 0; i < this->values.size(); i++)
		{
			rezultanteVrijednosti.push_back(this->values.at(i) - other.values.at(i));
		}
		return Tensor(this->dimension, rezultanteVrijednosti);
	}

	Tensor<T> operator*(const Tensor<T>& other) const //Hadamardov proizvod
	{
		for (int i = 0;i < this->dimension.size();i++)
		{
			if (this->dimension.at(i) != other.dimension.at(i))
				throw std::exception("Tensor dimensions are not equal!");
		}

		std::vector<T> rezultanteVrijednosti;
		for (int i = 0; i < this->values.size(); i++)
		{
			rezultanteVrijednosti.push_back(this->values.at(i) * other.values.at(i));
		}
		return Tensor(this->dimension, rezultanteVrijednosti);
	}

	Tensor<T> operator*(const T& scalar) const //množenje tenzora sa skalarom
	{
		std::vector<T> rezultanteVrijednosti;
		for (int i = 0;i < this->values.size();i++)
		{
			rezultanteVrijednosti.push_back(this->values.at(i) * scalar);
		}
		return Tensor(this->dimension, rezultanteVrijednosti);
	}

	Tensor<T> operator+(const T& scalar) const //sabiranje tenzora sa skalarom
	{
		std::vector<T> rezultanteVrijednosti;
		for (int i = 0;i < this->values.size();i++)
		{
			rezultanteVrijednosti.push_back(this->values.at(i) + scalar);
		}
		return Tensor(this->dimension, rezultanteVrijednosti);
	}

	Tensor<T> operator-(const T& scalar) const //oduzimanje skalara od tenzora
	{
		std::vector<T> rezultanteVrijednosti;
		for (int i = 0;i < this->values.size();i++)
		{
			rezultanteVrijednosti.push_back(this->values.at(i) - scalar);
		}
		return Tensor(this->dimension, rezultanteVrijednosti);
	}

	Tensor<T> operator-() const //negacija tenzora
	{
		std::vector<T> rezultanteVrijednosti;
		for (int i = 0;i < this->values.size();i++)
		{
			rezultanteVrijednosti.push_back(this->values.at(i) * (-1));
		}
		return Tensor(this->dimension, rezultanteVrijednosti);
	}

	friend std::ostream& operator<<(std::ostream& os, const Tensor<T>& tensor) //ispis na konzoli
	{
		if (tensor.dimension.size() == 0)
			os << "Tensor doesn't exist!";
		os << "Dimension: [ ";
		for (const auto& dim : tensor.dimension)
		{
			os << dim << " ";
		}
		os << "]\n";
		os << "Tensor: [ ";
		for (const auto& value : tensor.values)
		{
			os << value << " ";
		}
		os << "]\n" << std::endl;
		return os;
	}

	void serialize(std::ofstream& file) //serialization
	{
		if (file.is_open())
		{
			file << this->getDimension().size() << " ";
			for (int i = 0;i < this->getDimension().size();i++)
			{
				file << this->getDimension().at(i) << " ";
			}
			file << "\n";
			for (int i = 0;i < this->getValues().size();i++)
			{
				file << this->getValues().at(i) << " ";
			}
			file << "\n";
		}
		else
		{
			throw std::exception("File is not opened!");
		}
	}

	Tensor<T> deserialize(std::ifstream& file) //deserialization
	{
		if (file.is_open())
		{
			std::vector<int> dimension;
			std::vector<T> values;
			int size;
			file >> size;
			for (int i = 0;i < size;i++)
			{
				int dim;
				file >> dim;
				dimension.push_back(dim);
			}

			int pom = 1;
			for (int i = 0;i < dimension.size();i++)
			{
				pom *= dimension.at(i);
			}

			T val;
			while (file >> val)
			{
				values.push_back(val);
			}
			if (values.size() != pom)
			{
				throw std::runtime_error("Tensor dimensions are not equal!5");
			}
			return Tensor<T>(dimension, values);
		}
		else
		{
			throw std::exception("File is not opened!");
		}
	}
};

template <typename T, int ...N>
void serialize(std::ofstream& file, Tensor<T, N...> t) //serialization
{
	if (file.is_open())
	{
		file << t.getDimension().size() << " ";
		for (int i = 0;i < t.getDimension().size();i++)
		{
			file << t.getDimension().at(i) << " ";
		}
		file << "\n";
		for (int i = 0;i < t.getValues().size();i++)
		{
			file << t.getValues().at(i) << " ";
		}
		file << "\n";
	}
	else
	{
		throw std::exception("Datoteka nije otvorena!");
	}
}

template <typename T, int ...N>
Tensor<T, N...> deserialize(std::ifstream& file) //deserialization
{
	if (file.is_open())
	{
		std::vector<int> dimension;
		std::vector<T> values;
		int size;
		file >> size;
		for (int i = 0;i < size;i++)
		{
			int dim;
			file >> dim;
			dimension.push_back(dim);
		}

		int pom = 1;
		for (int i = 0;i < dimension.size();i++)
		{
			pom *= dimension.at(i);
		}

		T val;
		for(int  i = 0; i < pom; i++)
		{
			file >> val;
			values.push_back(val);
		}
		if (values.size() != pom)
		{
			throw std::runtime_error("Tensor dimensions are not equal!5");
		}
		return Tensor<T, N...>(values);
	}
	else
	{
		throw std::exception("Datoteka nije otvorena!");
	}
}