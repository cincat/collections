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
	D d;
	typedef void(*Fun)(void*); 
	Fun pFun = nullptr;
	long ** pVtab = nullptr;

	pVtab = (long**)&d;
	cout << "[0] D::B1::_vptr->" << endl;
	pFun = (Fun)pVtab[0][0];//D::f();
	cout << "     [0] ";    pFun(&pVtab[0]); 
	pFun = (Fun)pVtab[0][1];//D::f1();
	cout << "     [1] ";    pFun(&pVtab[0]); 
	pFun = (Fun)pVtab[0][2];//B1::Bf1();
	cout << "     [2] ";    pFun(&pVtab[0]); 
	pFun = (Fun)pVtab[0][3];//D::f2();
	cout << "     [3] "; pFun(&pVtab[0]);
	pFun = (Fun)pVtab[0][4];//D::Df();
	cout << "     [4] "; pFun(&pVtab[0]);
	pFun = (Fun)pVtab[0][5];
	cout << "     [5] ";
	cout << *(int*)&pFun << endl;
	 
	//cout << pVtab[4][2] << endl;
	//cout << "[1] = 0x";
	//cout <<  (int*)((int*)(&pVtab[1])+1) <<endl; //????
	 
	cout << "[1] B1::ib1 = ";
	cout << *((int*)(&d)+2) <<endl; //B1::ib1
	cout << "[2] B1::cb1 = ";
	cout << (char)*((int*)(&d)+3) << endl; //B1::cb1
	 
	//---------------------
	cout << "[3] D::B2::_vptr->" << endl;
	// pVtab[3][0] will cause segment fault because virtual thunk
	pFun = (Fun)pVtab[2][0];
	cout << "     [0] ";    pFun(&pVtab[2]); //D::f();
	// pVtab[3][1] will cause segment fault because virtual thunk
	pFun = (Fun)pVtab[2][1];
	cout << "     [1] ";    pFun(&pVtab[2]); //D::f2();
	pFun = (Fun)pVtab[2][2]; //B2::Bf2
	cout << "     [2] ";	pFun(&pVtab[2]);
	pFun = (Fun)pVtab[2][3];
	cout << "     [2] ";
	cout << *(int*)&pFun << endl;
	 
	//cout << "[5] = 0x";
	//cout << *((int*)(&dd)+5) << endl; // ???
	 
	cout << "[4] B2::ib2 = ";
	cout << (int)*((int*)(&d)+6) <<endl; //B2::ib2
	cout << "[5] B2::cb2 = ";
	cout << (char)*((int*)(&d)+7) << endl; //B2::cb2
	 
	cout << "[6] D::id = ";
	cout << *((int*)(&d)+8) << endl; //D::id
	cout << "[7] D::cd = ";
	cout << (char)*((int*)(&d)+9) << endl;//D::cd
	 
	//cout << "[10]  = 0x";
	//cout << (int*)*((int*)(&dd)+10) << endl;
	//---------------------
	cout << "[8] D::B::_vptr->" << endl;
	pFun = (Fun)pVtab[5][0];
	cout << "     [0] ";    pFun(&pVtab[5]); //D::f();
	pFun = (Fun)pVtab[5][1];
	cout << "     [1] ";    pFun(&pVtab[5]); //B::Bf();
	pFun = (Fun)pVtab[5][2];
	//cout << "     [2] ";	//pFun(&pVtab[5]); 
	//pFun = (Fun)pVtab[5][3];
	//cout << "     [3] ";
	//cout << *(long*)&pFun << endl;
	 
	cout << "[9] B::ib = ";
	cout << *((int*)(&d)+12) << endl; //B::ib
	cout << "[10] B::cb = ";
	cout << (char)*((int*)(&d)+13) <<endl;//B::cb	return 0;
	return 0;
}
