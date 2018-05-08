#include <iostream>

using namespace std;

class B
{
public:
	int ib;
	char cb;
	B():ib(0),cb('b') {}

	virtual void f() { cout << "B::f()" << endl;}
	virtual void Bf() { cout << "B::Bf()" << endl;}
};
class B1 : virtual public B
{
public:
	int ib1;
	char cb1;
	B1():ib1(11),cb1('1') {}

	virtual void f() { cout << "B1::f()" << endl; }
	virtual void f1() {cout << "B1::f1()" << endl;}
	virtual void Bf1() { cout << "B1::Bf1()" << endl;}
 
};
class B2: virtual public B
{
public:
    int ib2;
    char cb2;
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
	 
	B1 bb1;
	pVtab = (long**)&bb1;
	
	cout << "[0] B1::_vptr->" << endl;
	pFun = (Fun)pVtab[0][0];
	cout << "     [0] ";
	pFun(&bb1); //B1::f1();
	cout << "     [1] ";
	pFun = (Fun)pVtab[0][1];
	pFun(&bb1); //B1::bf1();
	cout << "     [2] ";
	pFun = (Fun)pVtab[0][2];
	pFun(&bb1);
	
	cout << "[1] B1::ib1 = ";
	cout << *((int*)&pVtab[1]+0) <<endl; //B1::ib1
	cout << "[2] B1::cb1 = ";
	cout << *(char*)((int*)&pVtab[1]+1) << endl; //B1::cb1
	 
	cout << "[3] B::_vptr->" << endl;
	//just because virtual thunk can cause segment fault if use pVtab[2][0]
	pFun = (Fun)pVtab[2][0];
	cout << "     [0] ";
	pFun(&pVtab[2]); //B1::f();
	pFun = (Fun)pVtab[2][1];
	cout << "     [1] ";
	pFun(&pVtab[2]); //B::Bf();
	cout << "     [2] ";
	cout << "0x" << (Fun)pVtab[2][2] << endl;
	 
	cout << "[4] B::ib = ";
	cout << *((int*)&pVtab[3]+0) <<endl; //B::ib
	cout << "[7] B::cb = ";
	cout << *(char*)((int*)&pVtab[3] + 1);
	return 0;
}
