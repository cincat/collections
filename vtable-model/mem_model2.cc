#include <iostream>

using namespace std;

class B
{
    public:
        int ib;
        char cb;
    public:
        B():ib(0),cb('B') {}
 
        virtual void f() { cout << "B::f()" << endl;}
        virtual void Bf() { cout << "B::Bf()" << endl;}
};
class B1 :  public B
{
    public:
        int ib1;
        char cb1;
    public:
        B1():ib1(11),cb1('1') {}
 
        virtual void f() { cout << "B1::f()" << endl;}
        virtual void f1() { cout << "B1::f1()" << endl;}
        virtual void Bf1() { cout << "B1::Bf1()" << endl;}
 
};
class B2:  public B
{
    public:
        int ib2;
        char cb2;
    public:
        B2():ib2(12),cb2('2') {}
 
        virtual void f() { cout << "B2::f()" << endl;}
        virtual void f2() { cout << "B2::f2()" << endl;}
        virtual void Bf2() { cout << "B2::Bf2()" << endl;}
 
};
 
class D : public B1, public B2
{
    public:
        int id;
        char cd;
    public:
        D():id(100),cd('D') {}
 
        virtual void f() { cout << "D::f()" << endl;}
        virtual void f1() { cout << "D::f1()" << endl;}
        virtual void f2() { cout << "D::f2()" << endl;}
        virtual void Df() { cout << "D::Df()" << endl;}
 
};

int main() {
	typedef void(*Fun)(void*);
	long** pVtab = NULL;
	Fun pFun = NULL;
	 
	D d;
	pVtab = (long**)&d;

	cout << sizeof d << endl;
	cout << "[0] D::B1::_vptr->" << endl;
	pFun = (Fun)pVtab[0][0];
	cout << "     [0] ";    pFun(&pVtab[0]);
	pFun = (Fun)pVtab[0][1];
	cout << "     [1] ";    pFun(&pVtab[0]);
	pFun = (Fun)pVtab[0][2];
	cout << "     [2] ";    pFun(&pVtab[0]);
	pFun = (Fun)pVtab[0][3];
	cout << "     [3] ";    pFun(&pVtab[0]);
	pFun = (Fun)pVtab[0][4];
	cout << "     [4] ";    pFun(&pVtab[0]);
	pFun = (Fun)pVtab[0][5];
	cout << "     [5] ";    pFun(&pVtab[0]);
	pFun = (Fun)pVtab[0][6];
	cout << "     [6] " << *(int*)&pFun << endl;
	 
	cout << "[1] B::ib = " << *((int*)&pVtab[1] + 0) << endl;
	cout << "[2] B::cb = " << *(char*)((int*)&pVtab[1] + 1) << endl;
	cout << "[3] B1::ib1 = " << *((int*)&pVtab[1] + 2) << endl;
	cout << "[4] B1::cb1 = " << *(char*)((int*)&pVtab[1] + 3) << endl;
	 
	cout << "[3] D::B2::_vptr->" << endl;
	pFun = (Fun)pVtab[3][0];
	cout << "     [0] ";    pFun(&pVtab[3]);
	pFun = (Fun)pVtab[3][1];
	cout << "     [1] ";    pFun(&pVtab[3]);
	pFun = (Fun)pVtab[3][2];
	cout << "     [2] ";    pFun(&pVtab[3]);
	pFun = (Fun)pVtab[3][3];
	cout << "     [3] ";    pFun(&pVtab[3]);
	pFun = (Fun)pVtab[3][4];
	cout << "     [4] " << *(int*)&pFun << endl;
	 
	cout << "[6] B::ib = " << *((int*)&pVtab[4] + 0) << endl;
	cout << "[7] B::cb = " << *(char*)((int*)&pVtab[4] + 1) << endl;
	cout << "[8] B2::ib2 = " << *((int*)&pVtab[4] + 2) << endl;
	cout << "[9] B2::cb2 = " << *(char*)((int*)&pVtab[4] + 3) << endl;
	 
	cout << "[10] D::id = " << *((int*)&pVtab[6] + 0) << endl;
	cout << "[11] D::cd = " << *(char *)((int*)&pVtab[6] + 1) << endl;	
	return 0;
}
