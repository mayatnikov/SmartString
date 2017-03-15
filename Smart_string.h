/*
 
Требуется реализовать класс Smart_string Класс предоставляет интерфейс по работе со строками. 
Строки можно: 
	конкатенировать, 
	конструировать из чисел,  
	считывать из объекта FILE *,  
 * (отдельно описанная функция, ни в коем случае не конструктор!)
	сравнивать между собой. 
Выделять подстроку по координатам.  
Строка должна содержать память только для одной копии объекта.

Также реализовать класс Smart_string_exception для обработки ошибочных ситуаций, возникающих при работе со строками.

Приватная часть класса Smart_string должна включать три поля: 
	unsigned long int — для подсчёта числа копий строки 
		(для избегания проблем с константными объектами, рекомендуется это поле объявить с ключевым словом mutable), 
	size_t — для хранения длины строки, 
	а так же char *, для хранения самой строки.

Для класса Smart_string должны быть переопределены операции: +,+=,<,>,<, <=, >=, ==, !=.
Сравнение строк должно быть лексикографическим.

Дополнительно должны быть реализованы: 
	1.	Умножение str*n  -> Означает создать строку, состоящую из n повторений str.
	2.	Доступ к элементам []. 
			В аргументах могут быть: 
				число типа size_t, которое задаёт позицию в строке, 
				объект Smart_string — ищется как подстрока и возвращается Smart_string,
 *                               содержащая кусок от находки до конца строки;
	3.	Оператор передачи параметров, переопределённые (). 
			Пара чисел указанных через запятую, означающие возвращение подстроки из данного диапазона 
				(str(«1234567890») и затем str(3,7) вернёт Smart_string «45678»).
	4.	Метод c_str(), который возвращает нормальную  строку языка Cи, как копию данной.
	5.	Метод print(FILE *) который позволяет напечатать данную строку.

Далее приведены несколько выражений, которые должны быть верны:

Smart_string str1, str2(«lalala»);
const Smart_string str(«Const»);

str1=str+500*str2+str(0,2)+str[3];
str1+='\n';
str1+=»Ну и с новой строчки»;
str1+=»2+(»+str2+»)+3»
str1.print(stdout);

Требуется реализовать программу в файле test.cpp.  Реализации классов должны быть в отдельном файле. 
Программа будет содержать все возможные действия со строками, в том числе считывание из файла. 
Имя файла задаётся в аргументах main.

*/

/*
 * " Считывать из объекта FILE * "  ->
 *   ->    отдельно описанная функция, ни в коем случае не конструктор!
 *      Почему? Из файла можно считывать не одну строку, а много по запросу.
 */

/*
	ВОПРОСЫ: 
		1. Что значит "Строка должна содержать память только для одной копии объекта"? ->
 * Для этого и нужно число копий строки - чтобы отслеживать выход за границы массива
		2. Как конструировать строку из чисел? ->
 * Число превращается в строку
		3. Как определить размер массива-строки? -> 
 * Динамически выделяется память под массив типа size.
*/

#include <iostream>
#include <cstdio>
#include <cstring>
#include <fstream>
using namespace std;

#define MAXLEN 2000   // используем ВЕЗДЕ ! 
#define SS Smart_string // в какой то момент мне надоело писать  Smart_string
#define SSE Smart_string_exception  // просто что бы короче писать
#define N_MEMBERS 50  // максимальное число экземпляров класса, при превышении - exception

class Smart_string // Объект класса - строка
/* В числе контроля за ошибками должен быть контроль выхода за границы массива */
{
private:
   static int n_members; // Подсчет числа экземпляров класса, у класса введены ограничения N_MEMEBERS=10
   char* buffer; //  Указатель на массив символов, содержащий строку;
   size_t line_len; // Длина строки	
   //  подсчет числа экземпляров класса
   void inc();
   void dec();    
   
public:
    static int nget();
    Smart_string();
    Smart_string(const char *s);
    Smart_string(const Smart_string &);
    ~Smart_string();
    static void check_members();

    // Для класса Smart_string должны быть переопределены операции: +,+=,<,>,<, <=, >=, ==, !=.
        Smart_string operator+(char *str); // Есть
	Smart_string operator+(Smart_string str);
	Smart_string operator=(char *str);
	Smart_string operator=(Smart_string str);

	// операторы сравнения
        bool operator == (Smart_string str);
	bool operator > (Smart_string str);
	bool operator < (Smart_string str);
	bool operator <= (Smart_string str);
	bool operator >=(Smart_string str);
	bool operator != (Smart_string str);

	SS substring(size_t pos1, size_t pos2);
        Smart_string operator[](size_t pos);
        Smart_string operator()(size_t pos1, size_t pos2);
	Smart_string operator*(int );
	int compare(const char *str); // Сравнение со строкой
	int compare(Smart_string str); // Сравнение со строкой
	void show_str(); // печать строки
	char *getValue(); // return buffer value ref
	void print();
	size_t getLen();  // длина строки
//	Smart_string ReadFile();  // чтение из файла строк
//        Smart_string Increm(SS str, int n);
	Smart_string multiply(int n); // размножить строку	
};
void ss_from_file(const char *file_name);
void print_label();