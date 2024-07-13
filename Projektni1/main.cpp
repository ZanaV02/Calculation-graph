#include "Graph.h"
#include "Tensor.h"

int main()
{
    try
    {
        Tensor<int, 1, 2, 3> t1({ 1,0,0,0,0,1 });
        Tensor<int, 1, 2, 3> t2({ 1,2,3,4,5,6 });
        Tensor<int, 1, 2, 3> t3({ 2,2,2,2,2,2 });
        Tensor<int, 1, 2, 3> t4({ 1,1,1,1,1,1 });
        std::cout << "Tensor t1: \n" << t1;

        Tensor<int> to1({ 1,2,3 }, { 3,3,3,3,3,3 });
        Tensor<int> to2({ 1,2,3 }, { 4,4,4,4,4,4 });
        Tensor<int> to3({ 1,2,3 }, { 5,5,5,5,5,5 });
        Tensor<int> to4{ {1,2},{2,2} };
        std::cout << "Tensor to4: \n" << to4;


        /*if (t1 == t2)
            std::cout << "Tensors are equal!" << std::endl;
        else
            std::cout << "Tensors are not equal!" << std::endl;*/

        std::cout << "=================================================" << std::endl;
        std::cout << "\nTensor serialization..." << std::endl;

        std::ofstream file1;
        file1.open("Tenzor.txt");
        serialize(file1, t4);
        file1.close();


        std::ifstream file2;
        file2.open("Tenzor.txt");
        std::cout << "Tensor t4 after deserialization:\n" << deserialize<int, 1, 2, 3>(file2);
        file2.close();

        AddOperation<int, 1, 2, 3> o1;
        SubOperation<int, 1, 2, 3> o2;
        HadamardOperation<int, 1, 2, 3> o3;

        PlusSkalarOperation<int, 1, 2, 3> o4;
        MinusSkalarOperation<int, 1, 2, 3> o5;
        MultiplySkalarOperation<int, 1, 2, 3> o6;
        NegationSkalarOperation<int, 1, 2, 3> o7;


        std::cout << "=================================================" << std::endl;
        //std::cout << "t1+t2=\n" << o1.getOperation(t1, t2); //2, 2, 3, 4, 5, 7
        //std::cout << "t1-t2=\n" << o2.getOperation(t1, t2); //0, -2, -3, -4, -5, -5
        //std::cout << "t1*t2=\n" << o3.getOperation(t1, t2); //1, 0, 0, 0, 0, 6
        //std::cout << "t1+5=\n" << o4.getOperation(t1, 5); //6, 5, 5, 5, 5, 6
        //std::cout << "t1-5=\n" << o5.getOperation(t1, 5); //-4, -5, -5, -5, -5, -4
        //std::cout << "t1*5=\n" << o6.getOperation(t1, 5); //5, 0, 0, 0, 0, 0, 5
        //std::cout << "-t1=\n" << o7.getOperation(t1, 5); //-1, 0, 0, 0, 0, -1
        //std::cout << "=================================================" << std::endl;

        Node<int, 1, 2, 3> n1(std::make_shared<Tensor<int, 1, 2, 3>>(t1));
        Node<int, 1, 2, 3> n2(std::make_shared<Tensor<int, 1, 2, 3>>(t2));
        Node<int, 1, 2, 3> n3(std::make_shared<Tensor<int, 1, 2, 3>>(t3));
        Node<int, 1, 2, 3> n4(std::make_shared<Tensor<int, 1, 2, 3>>(t4));

        Node<int, 1, 2, 3> no1(std::make_shared<AddOperation<int, 1, 2, 3>>(o1));
        Node<int, 1, 2, 3> no2(std::make_shared<SubOperation<int, 1, 2, 3>>(o2));
        Node<int, 1, 2, 3> no3(std::make_shared<HadamardOperation<int, 1, 2, 3>>(o3));
        Node<int, 1, 2, 3> no4(std::make_shared<PlusSkalarOperation<int, 1, 2, 3>>(o4));
        no4.setScalar(2);
        Node<int, 1, 2, 3> no5(std::make_shared<MinusSkalarOperation<int, 1, 2, 3>>(o5));
        no5.setScalar(2);
        Node<int, 1, 2, 3> no6(std::make_shared<MultiplySkalarOperation<int, 1, 2, 3>>(o6));
        no6.setScalar(2);
        Node<int, 1, 2, 3> no7(std::make_shared<NegationSkalarOperation<int, 1, 2, 3>>(o7));

        /*if (no5.isOperationUnare())
            std::cout << "Operacija je unarna\n";
        else
            std::cout << "Operacija nije unarna\n";*/


        Graph<int, 1, 2, 3> a;
        a.addNode(n1);
        a.addNode(n2);
        a.addNode(n3);
        a.addNode(n4);
        a.addNode(no1, 0, 1);
        a.addNode(no2, 1, 2);
        a.addNode(no3, 4, 5);
        a.addNode(no4, 3); //unarni
        a.addNode(no1, 6, 7);
        a.addNode(no7, 8);
        std::cout << "Graf a: \n" << a << std::endl;
        std::cout << "-------------------------------------------------\n" << std::endl;
        std::cout << "Result tensor for node 9: \n" << a.getResult(9);

        std::cout << "=================================================" << std::endl;

        std::cout << "\nGraph serialization" << std::endl;
        std::ofstream file3;
        file3.open("graf.txt");
        a.serializeGraph(file3);
        file1.close();

        std::cout << "Deserijalizovan graf: " << std::endl;
        std::ifstream file4;
        file4.open("Graf.txt");
        Graph<int, 1, 2, 3> deserialized = a.deserializeGraph(file4);
        std::cout << "Rezultujuci tenzor za cvor 9: \n" << deserialized.getResult(9);
        file4.close();

        std::cout << "=================================================" << std::endl;

        /*Graph<int, 1, 2, 3> b;
        b.addNode(n1);
        b.addNode(n2);
        b.addNode(no4, 1);
        b.addNode(no6, 0);
        b.addNode(n3);
        b.addNode(no3, 2, 3);
        b.addNode(no2, 5, 4);
        std::cout << "Graf b:\n" << b << std::endl;
        std::cout << b.getResult(6) << std::endl;

        Graph<int, 1, 2, 3> c;
        c.addNode(n1);
        c.addNode(n2);
        c.addNode(n3);
        c.addNode(no2, 0, 1);
        c.addNode(no2, 3, 2);
        std::cout << c.getResult(3) << std::endl;
        std::cout << c.getResult(4);*/


        std::cout << whichOperation(no1.getOperationn())<< std::endl;

        std::shared_ptr<IOperation<int, 1, 2, 3>> a1 = returnOperation<int, 1, 2, 3>('+');
        std::cout << typeid(*a1).name() <<std::endl;

        std::shared_ptr<IOperation<int, 1, 2, 3>> a2 = returnOperation<int, 1, 2, 3>('N');
        std::cout << typeid(*a2).name();
    }
    catch (std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }
}