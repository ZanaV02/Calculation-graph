#pragma once
#include "Node.h"

template<typename T,int... N>
class Graph
{
	std::vector<Node<T, N...>> nodes;
	std::vector<std::vector<int>> matrix;
public:
	Graph() {}
	Graph(std::vector<Node<T, N...>> n, std::vector<std::vector<int>> m)
	{
		for (int i = 0;i < n.size();i++)
		{
			nodes.push_back(n.at(i));
		}
		matrix = m;

	}
	std::vector<Node<T, N...>> getNodes()
	{
		return this->nodes;
	}
	std::vector<std::vector<int>> getMatrix()
	{
		return this->matrix;
	}
	void addNode(Node<T, N...> n, int a = -1, int b = -1)
	{
		//std::cout << this->nodes.size() << " ";
		int pom = this->nodes.size();
		if (a >= pom || b >= pom || a < -1 || b < -1)
		{
			throw std::exception("Cvor sa kojim se pokusava povezati ne postoji!\n");
		}
		if (a != -1 && b != -1 && a == b)
		{
			throw std::exception("Cvor ne moze imati obe veze ka istom cvoru!\n");
		}
		//ako dodajem isti cvor sa unarnom operacijom, ne smije imati vise od 1 veze
		if (a != -1)
		{
			if (n.isTensor() && this->nodes.at(a).isTensor())
			{
				throw std::exception("Cvorovi koji sadrze tenzore ne mogu biti medjusobni susjedi!");
			}
		}
		if (b != -1)
		{
			if (n.isTensor() && this->nodes.at(b).isTensor())
			{
				throw std::exception("Cvorovi koji sadrze tenzore ne mogu biti medjusobni susjedi!");
			}
		}
		this->nodes.push_back(n);
		//formiranje matrice
		std::vector<T> tmp;
		tmp.resize(this->nodes.size());
		for (int i = 0;i < tmp.size();i++)
		{
			tmp.at(i) = 0;
		}
		if (a != -1)
			tmp.at(a) = 1;
		if (b != -1)
			tmp.at(b) = 1;
		this->matrix.push_back(tmp);
		for (int i = 0;i < this->nodes.size();i++)
		{
			this->matrix.at(i).resize(nodes.size());
		}
	}
	Tensor<T, N...> getResult(int index)
	{
		int tmp = this->nodes.size();
		if (index > tmp)
			throw std::exception("Cvor sa proslijedjenim indeksom ne postoji!");
		if (this->nodes.at(index).isTensor())
			return *this->nodes.at(index).getTensor();
		else
		{
			std::vector<int> pom;
			for (int i = 0;i < this->nodes.size();i++)
			{
				if (this->matrix[index][i] == 1)
				{
					pom.push_back(i);
				}
			}
			if (pom.size() == 2) //ako je binarna operacija
			{
				int a = pom.at(0);
				int b = pom.at(1);
				
				//std::cout << a << " " << b << std::endl;
				return this->nodes.at(index).getOperationn()->getOperation(getResult(a), getResult(b));
			}
			if (pom.size() == 1) //ako je unarna
			{
				int a = pom.at(0);
				//std::cout << a << std::endl;
				return this->nodes.at(index).getOperationn()->getOperation(getResult(a), this->nodes.at(index).getScalar());
			}
		}
	}
	friend std::ostream& operator<<(std::ostream& os, Graph<T, N...>& graph)
	{
		os << "Cvorovi:" << std::endl;
		for (int i = 0;i < graph.nodes.size();i++)
		{
			if (graph.getNodes().at(i).isTensor())
			{
				std::cout << "Cvor " << i << std::endl;
				std::cout << *graph.getNodes().at(i).getTensor();
			}
			else if (graph.getNodes().at(i).isOperation())
			{
				std::cout << "Cvor " << i << std::endl;
				os << 'O' << " " << whichOperation<T, N...>(graph.getNodes().at(i).getOperationn());
				if (graph.getNodes().at(i).isOperationUnare())
					os << graph.getNodes().at(i).getScalar() << std::endl;
				else
					os << std::endl;

			}
		}

		os << "\nMatrica susjednosti: " << std::endl;
		for (const auto& row : graph.matrix)
		{
			for (const auto& elem : row)
			{
				os << elem << " ";
			}
			os << std::endl;
		}

		return os;
	}
	void serializeGraph(std::ofstream& file)
	{
		if (file.is_open())
		{
			file << this->nodes.size() << std::endl;
			for (int i = 0;i < this->nodes.size();i++)
			{
				for (int j = 0;j < this->nodes.size();j++)
					file << this->matrix[i][j] << " ";
				file << std::endl;
			}
			for (int i=0;i<this->nodes.size();i++)
			{
				if (this->nodes.at(i).isTensor())
				{
					file << 'T' << " ";
					serialize<T, N...>(file, this->nodes.at(i).getTensor()->getValues());
				}
				else if (this->nodes.at(i).isOperation())
				{
					file << 'O' << " " << whichOperation<T, N...>(this->nodes.at(i).getOperationn());
					if (this->nodes.at(i).isOperationUnare())
						file << this->nodes.at(i).getScalar() << std::endl;
					else
						file << std::endl;

				}
			}
		}
	}
	Graph<T, N...> deserializeGraph(std::ifstream& file)
	{
		if (file.is_open())
		{
			std::vector<std::vector<int>> matrix;
			int size;
			file >> size;
			for (int i = 0;i < size;i++)
			{
				std::vector<int> tmp;
				for (int j = 0;j < size;j++)
				{
					int pom;
					file >> pom;
					tmp.push_back(pom);
				}
				matrix.push_back(tmp);
			}
			char c;
			int i = 0;
			std::vector<Node<T, N...>> nodes;
			for(int i = 0; i < size; i++)
			{
				file >> c;
				if (c == 'T')
				{
					Tensor<T, N...> pom = deserialize<T, N...>(file);
					Node<T, N...> tensor;
					tensor.setTensor(std::make_shared<Tensor<T, N...>>(pom));
					nodes.push_back(tensor);
				}
				else if (c == 'O')
				{
					char p;
					file >> p;
					Node<T, N...> operation;
					operation.setOperation(returnOperation<T,N...>(p));
					if (operation.isOperationUnare())
					{
						int scalar;
						file >> scalar;
						operation.setScalar(scalar);
					}
					nodes.push_back(operation);
				}
			}
			return Graph<T, N...>(nodes, matrix);
		}
	}
};
