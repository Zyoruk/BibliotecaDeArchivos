#include<iostream>
#include <stdlib.h> 
#include <fstream>
#include <iostream>


using namespace std;
int main()
{


	fstream fs("ce2103.bin", std::ios::out | std::ios::in | std::ios::binary );
	int sizeofregister = 80;
	int sizeoffile = 0;
	// obtener tam del archivo
	if(fs){
		cout << "Tamanio " << ios::end << endl;
		fs.seekp (0, ios::end);
		sizeoffile = fs.tellp();
		cout << "END " << fs.tellp()<<endl;
	}



        //void * puntero_buffer = malloc(40);
        void * puntero_buffer = calloc(20,4);
        // Vamos a tener un registro con edad, promedio, nombre de maximo 71 caracteres (1 para espape de string)
        int * puntero_edad = (int *) puntero_buffer;
        int * puntero_promedio = (int *) (puntero_buffer + 4);
        char * puntero_nombre  = (char *) (puntero_buffer + 8) ;
        *puntero_edad  = 45;
        *puntero_promedio = 34;
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
	fs.write(reinterpret_cast<const char*>(puntero_buffer),sizeofregister);
	sizeoffile = sizeoffile + sizeofregister;
	// Vamos a leer todos los registros que hay e imprimir el nombre
	if(fs){
		fs.seekg(0,ios::beg);
		cout << ios::end << " " << ios::beg << " " <<  sizeofregister << endl;
		//int sizeoffile = ios::end - ios::beg;
		char * puntero_buffer_lectura = (char *) calloc(20,4);
                for(int i = 0; i< (sizeoffile/sizeofregister); i++)
		{
			fs.read(puntero_buffer_lectura, sizeofregister);
			cout<< "Nombre en el registro " << i << " " << (puntero_buffer_lectura+8) << endl;
			fs.seekg(i*sizeofregister,ios::beg);
		}
	}
	fs.close();
        return(0);
}

