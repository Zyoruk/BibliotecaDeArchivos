#include<iostream>
#include <stdlib.h> 
using namespace std;
int main()
{

	unsigned int i = 1;
   	char *c = (char*)&i;
   	if (*c)
       		cout << "Little endian" << endl;
   	else
       		cout << "Big endian" << endl;
   return 0;

}






