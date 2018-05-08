#include <iostream>
#include <functional>

using namespace std; 

class Base1 {
public:
    int ibase1;
    Base1():ibase1(10) {}
    virtual void f() { cout << "Base1::f()" << endl; }
    virtual void g() { cout << "Base1::g()" << endl; }
    virtual void h() { cout << "Base1::h()" << endl; }
 
};
 
class Base2 {
public:
    int ibase2;
    Base2():ibase2(20) {}
    virtual void f() { cout << "Base2::f()" << endl; }
    virtual void g() { cout << "Base2::g()" << endl; }
    virtual void h() { cout << "Base2::h()" << endl; }
};
 
class Base3 {
public:
    int ibase3;
    Base3():ibase3(30) {}
    virtual void f() { cout << "Base3::f()" << endl; }
    virtual void g() { cout << "Base3::g()" << endl; }
    virtual void h() { cout << "Base3::h()" << endl; }
};
 
class Derive : public Base1, public Base2, public Base3 {
public:
    int iderive;
	//long iderive1 = 200;
    Derive():iderive(100) {}
    virtual void f() { cout << "Derive::f()" << endl; }
    virtual void g1() { cout << "Derive::g1()" << endl; }
};


int main() {
	typedef void(*Fun)(void*);
	Fun pFun = nullptr;
	 
	Derive d;
	 
	long** pVtab = (long**)&d;
	 
	cout << "[0] Base1::_vptr->" << endl;
	pFun = (Fun)pVtab[0][0];
	cout << "     [0] ";pFun(&pVtab[0]);
	 
	pFun = (Fun)pVtab[0][1];
	cout << "     [1] ";pFun(&pVtab[0]);
	 
	pFun = (Fun)pVtab[0][2];
	cout << "     [2] ";pFun(&pVtab[0]);
	 
	pFun = (Fun)pVtab[0][3];
	cout << "     [3] "; pFun(&pVtab[0]);
	 
	pFun = (Fun)pVtab[0][4];
	cout << "     [4] "; cout<<*(int*)&pFun<<endl;
	 
	cout << "[1] Base1.ibase1 = " << *(int*)&pVtab[1] << endl;
	 
	int s = sizeof(Base1)/(sizeof(int *));
	 
	cout << "[" << s << "] Base2::_vptr->"<<endl;
	pFun = (Fun)pVtab[s][0];
	cout << "     [0] "; pFun(&pVtab[s]);
	 
	pFun = (Fun)pVtab[s][1];
	cout << "     [1] "; pFun(&pVtab[s]);
	 
	pFun = (Fun)pVtab[s][2];
	cout << "     [2] "; pFun(&pVtab[s]);
	 
	pFun = (Fun)pVtab[s][3];
	cout << "     [3] "; cout<<*(int*)&pFun<<endl;
	 
	cout << "["<< s+1 <<"] Base2.ibase2 = " << *(int*)&pVtab[s+1] << endl;
	 
	s = s + sizeof(Base2)/sizeof(long *);
	 
	cout << "[" << s << "] Base3::_vptr->"<<endl;
	pFun = (Fun)pVtab[s][0];
	cout << "     [0] "; pFun(&pVtab[s]);
	 
	pFun = (Fun)pVtab[s][1];
	cout << "     [1] "; pFun(&pVtab[s]);
	 
	pFun = (Fun)pVtab[s][2];
	cout << "     [2] "; pFun(&pVtab[s]);
	 
	pFun = (Fun)pVtab[s][3];
	cout << "     [3] "; cout<<*(int*)&pFun<<endl;
	 
	s++;
	cout << "["<< s <<"] Base3.ibase3 = " << *(int*)&pVtab[s] << endl;
	//s++;
	cout << "["<< s <<"] Derive.iderive = " << *((int*)&pVtab[s] + 1) << endl;
	//cout << "Derive Class occupy " << sizeof d << " bytes" << endl;
	//<< *((int *)&d + 10) << endl;
	//auto p = &Derive::iderive;
	//cout << *(int*)&p << endl;
	//cout << &d.iderive << endl;;	
	//cout << &d.iderive  - &d.ibase3 << endl;
	//for (int i = 0; i < 12; i++) {
	//	cout << *((int*)&d + i) << endl;
	//}
	//Derive *pd = new Derive();
	//Base1 *pb1 = pd;	
	//Base2 *pb2 = pd;
	//cout << pd << endl;
	//cout << pb1 << endl;
	//cout << pb2 << endl;
	return 0;
}
