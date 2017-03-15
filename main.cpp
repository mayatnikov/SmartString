#include <iostream>
#include "Smart_string.h"
using namespace std;

// данные для тестирования
const char *str1 = "1234567890";
size_t len1= strlen(str1);
const char *str2 = "abcdefgh";
size_t len2 = strlen(str2);

void tst(const char *test_name, const char *description) {
    cout    <<"\n ---\n"
            << "Старт теста\n\tимя: "<<test_name
            << "\n\tназначение: "<< description
            <<endl;
}

void test0() {
    tst("test0", "Проверка пустого конструктора");
	// тестируем пустой конструктор
		SS s0;
                s0.print();
		cout << "s0 создан, проверка... ";
		if(strcmp("", s0.getValue()) == 0 ) cout << "--> Value is OK. ";
			else cout << "--! Value is diff. ";
			if(s0.getLen() == 0 ) cout << "--> String length OK. ";
			else cout << "--! String length diff. get:" << s0.getLen();
		cout << endl;	
}


void test1() {
    tst("test1","проверка конструктора из (const char *)");
	// создаем instance of class и проверяем его содержимое
		SS s1(str1);
                s1.print();
		cout << "s1 создан, проверка... ";
		if(strcmp(str1, s1.getValue()) == 0 ) cout << "--> Value is OK. ";
			else cout << "--! Value is diff. ";
			if(len1 == s1.getLen() ) cout << "--> String length OK. ";
			else cout << "ERROR: Строка не совпадает с эталоном! ";
		cout << endl;	
	
}


// TODO: по аналогии сделать проверку всех операций сравнения
void test2() {
    tst("test2", "Проверка операций сравнения");
	// проверка Smart_string::compare(char *str) - механизм от strcmp
	const char *str    = "3abcd";
	const char *str_lt = "1abcd";
	const char *str_gt = "5abcd";
	 
		SS s1(str);
                s1.print();
		cout << "s1 создан, проверка... ";
		int rc_00 = s1.compare(str);
		int rc_lt = s1.compare(str_lt);
		int rc_gt = s1.compare(str_gt);
		
		cout << "| oдинаковые значения ";
		if(rc_00 == 0 ) cout << "--> Value is OK. ";
			else cout << "--! Value is diff. ";

		cout << "| ср-е с большим ";
		if(rc_gt > 0 ) cout << "--> Value is OK. ";
			else cout << "--! Value is diff. ";

		cout << "| ср-е с меньшим ";
		if(rc_lt < 0 ) cout << "--> Value is OK. ";
			else cout << "--! Value is diff. ";
		cout << endl;	
	
}

void test3() {
    tst("test3()", "проверка операций \"+\"(СЛОЖЕНИЕ) " );
	// проверка операции "+"

// эталон для проверки
	char buf[200];
	strcpy(buf,str1); 
	strcat(buf,str2);
	size_t len = strlen(buf);


	SS s1(str1);
        s1.print();
	SS s2(str2);
        s2.print();
	
	SS ss = s1+s2;  // так работатет
	// SS ss; ss=s1+s2; // А вот так не работает?! 
        ss.print();
	 
		cout << "ss создан, проверка... ";
		if(strcmp(buf, ss.getValue()) == 0 ) cout << "--> Value is OK. ";
			else cout << "--! Value is diff. ";
			if(len == ss.getLen() ) cout << "--> String length OK. ";
			else cout << "--! String length diff. ";
		cout << endl;	
		cout << "Эталон:"<< buf << endl;
		cout << "res:"<< ss.getValue() << endl;
}

void test4() {
	tst("test4()",  "проверка перезагрузки операций [] и  == ");
// данные для проверки
	size_t pos=3;
	SS src("qwertyuiop");
        src.print();
	SS should_be ("rtyuiop");
        should_be.print();
// давай проверим
		SS s1(src);
                s1.print();
		cout << "s1 создан, проверка... ";
		SS result = s1[pos];
		result.print();
		if(result==should_be ) cout << "--> Value is OK. ";
			else cout << "--! Value is diff. ";
		cout << endl;	
}

void test5(const char *filename) {
    tst("test5()","чтение из файла (выполнено на основе стандартных классов");
	ss_from_file(filename);
}

void test6() {
    tst("test6()","Проверка operator \"()\" ");
	const char *p1 ="1234567890abcdef";
        cout << " Smart_string(3,5)  IN:"<<p1 
            << "\n OUT:";
	SS s0 = SS(p1);
	SS s1 = s0(3,5);
        s1.show_str();
	if(s1 == "456") cout << " --> Value is OK. ";
		else cout << " --! Value is diff. ";
}



void test6wex() {  // test 6 with exception
    tst("tst6wex()","Поверка exception при неправильных параметрах Smart_string(13,15) - выход параметров за границы вызывает исключение");
    const char *p1 ="1234567890";
	cout <<  "TEST-6wex Test operator \"()\" Smart_string(13,15) with exception  IN:"<<p1<< " call (13,15); ";
	SS s0 = SS(p1);
        s0.print();
	try {
		SS s1 = s0(13,15);
		s1.print();
	} catch (runtime_error ex) {  // перехват ошибки
		cout << "get Exception:"<<ex.what() << endl;
	}
}

void test7() {
    tst("test7()","Проверка перезагрузки оператора * (УМНОЖИТЬ)");
	const char *p1 ="_abc";
	cout <<  "TEST-7 Test operator \"*\" Smart_string(\"abc\")  IN:"<<p1;
	SS s0 = SS(p1);
        s0.print();
	SS s1 = s0*5;
	s1.print();
}


void test8() { // проверка допустимого числа экземпляра класса
    tst("test8()",  "Проверка превышения допустимого числа экземпляров класса"); 
// -----------------
    char tmp[20];
    int tik = 0;
    int tik_max=200;
    SS * ptr[tik_max];
    SS atStart("Это тестовая строка вначале test8()");
    atStart.print();
    try {
        for (; tik < tik_max; tik++) {
	  sprintf(tmp,"tst[%d]",tik);
	  ptr[tik] = new SS(tmp); // ВНИМАНИЕ ЭТО ПАМЯТЬ НЕ ОСВОБОЖДАЕТСЯ если закоментировать delete
	  ptr[tik]->print();
	    
            // delete(ptr[tik]); // ВОТ ПОЭТОМУ И НЕ ОСВОБОЖДАЕТСЯ, что закоментировал эту строку
        }
    } catch (runtime_error ex) {
        cerr << ex.what();
    }
        // освободим память 
    cout << "\n ---> Free memory after test8:\n";
    tik--;
        for (; tik >= 0; tik--) {
            cout << "Free N:"<<tik<<" | ";
            ptr[tik]->print();
            delete(ptr[tik]);
        }
    atStart.print();
}


int main(int argc, char* argv[]) { 
	char fileName[200] = "./data.txt";  // default file name
      
        print_label();
        cout << "Старт программы ..."
             << "Входные параметры:\n\targc = " << argc 
                << endl; 
   for(int i = 0; i < argc; i++) 
      cout << "\targv[" << i << "] = " << argv[i] << endl;
	if(argc<2) { 
            cout << "WARNING:нет параметра с именем файла! используем имя по умолчанию "<< fileName <<endl; 
        }
	else {
		strcpy(fileName,argv[1]);
	}
cout << "Имя файла для чтения строк:"<< fileName << endl;

 // это тесты того что сделано
 test0();
 test1();
 test2();
 test3();
 test6();
 test6wex();
 test7();

// ------------------------------------
  try {
      test8(); // тут исключение и мы его перехватываем программа не слетает
      } catch (runtime_error ex) {
          cerr << ex.what()<< endl;
      }
 test5(fileName);
 test4();
 cout << "Конец работы программы\n";
 return 0; 
}
