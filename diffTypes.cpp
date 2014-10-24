#include<iostream>
#include <stdlib.h> 
using namespace std;
int main()
{

        //void * puntero_buffer = malloc(40);
        void * puntero_buffer = calloc(20,4);
	// Vamos a tener un registro con edad, promedio, nombre de maximo 71 caracteres (1 para espape de string)
        int * puntero_edad = (int *) puntero_buffer;
	int * puntero_promedio = (int *) (puntero_buffer + 4);
	char * puntero_nombre  = (char *) (puntero_buffer + 8) ;
        *puntero_edad  = 28;
	*puntero_promedio = 82;
	*puntero_nombre = 'N';
	*(puntero_nombre+1) = 'e'; 
	*(puntero_nombre+2) = 'r';
 	*(puntero_nombre+3) = 'e';
	*(puntero_nombre+4) = 'o';
	*(puntero_nombre+5) = '\0';
	*(puntero_nombre+6) = 'X';

        cout << "Puntero Edad  " << puntero_edad << endl;
	cout << "Edad " << * puntero_edad << endl;
        cout << "Puntero Promedio " << puntero_promedio << endl;
	cout << "Promedio " << * puntero_promedio << endl;
        cout << "Puntero Nombre " <<  puntero_nombre << endl;

        return(0);
}
