#include<iostream>
#include <stdlib.h> 
using namespace std;
int main()
{

	//void * puntero_buffer = malloc(40);
	void * puntero_buffer = calloc(10,4);
	int * puntero_segundo_int = (int *) (puntero_buffer + 4);
	//*puntero_segundo_int  = 16843009;
	*puntero_segundo_int = 1;
	int * puntero_otro_int  = (int *) (puntero_buffer +2);
	cout << "Puntero Segundo Int " << puntero_segundo_int << endl;
	cout << "Puntero Buffer " << puntero_buffer << endl;
	cout << "Puntero a otro int " <<  puntero_otro_int << endl;
	cout << *puntero_segundo_int << endl;
	cout << *puntero_otro_int << endl;
	cout<<"\nHello World,\nWelcome to my first C ++ program on Ubuntu Linux\n\n"<<endl;
	return(0);
}
