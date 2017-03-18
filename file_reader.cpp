#include <iostream>
#include <vector>
#include <string>

#include "Smart_string.h"

using namespace std;
/* 

чтение данных строк из файла	
метод в отличии от остальных использует готовые class c++
 1-читает строки
 2 - копит данные в vector<Smart_string>
 3 - по всему накопленному списку выполняет метод Smart_string.print();

*/

bool write_to_file(const char *file_name, char *str) {
      ofstream myfile (file_name);
  if (myfile.is_open())
  {
    myfile << "---------- This is a first line.\n";
    myfile << str;
    myfile << "---------- This is last line.\n";
    myfile.close();
    return true;
  }
  else {
      cout << "Ошибка записи в файл";
      return false;
  }
}

void ss_from_file(const char *file_name) 
{
	string str;
	ifstream In(file_name);
        vector<SS> ss_buffer;
    if(!In.is_open()) 
    {
	cout << "Такого файла нет:" << file_name << endl;
	exit(-1);
    }
    while ( ! In.eof() ) // если задано несуществующее имя файла тут мы зависаем НАВСЕГДА!
    {
    	getline (In, str);
    	ss_buffer.push_back(SS(str.c_str()));
    }

	for ( SS ss : ss_buffer ) 
    {
	ss.print();
    }
}
void print_label() {
    const char *label = "label";
    string str;
    ifstream In(label);
    cout << "------------------------------------------------------------" << endl;
    if(!In.is_open()) 
    {
	cout << ">>>>>>>>>>>>>>>>>>>>>> Smart_String <<<<<<<<<<<<<<<<<<<<<<<<<" << endl;
    }
    else while ( ! In.eof() ) 
    {
    	getline (In, str);
        cout << str << endl;
    }
}
