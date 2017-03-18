#include <iostream>
#include <cstdio>
#include <stdexcept>
#include <cstring>
#include <fstream>
#include "Smart_string.h"

using namespace std;

int Smart_string::n_members;

struct Smart_string_exception:runtime_error
{
    Smart_string_exception(const char * message) : std::runtime_error(message)
    {
		 /*  что то тут надо делать ? */
		cerr << "ERR-->Smart_string runtime exception! \n";
	}
};

void SS::inc() {
    SS::n_members++;
}

void SS::dec() {
    Smart_string::n_members--;
}

int SS::nget() {
    return n_members;
}

void SS::check_members() {
    if(n_members > N_MEMBERS) 
        throw Smart_string_exception("Too many members!");
}

SS::Smart_string() 
{
    used=1;
    check_members();
    buffer = (char *)malloc(1);
    strcpy(buffer,"");
    line_len=strlen("");
    inc();
}

SS::SS(const Smart_string &ss) {
    used=1;
    check_members();
    buffer = (char *) malloc(ss.line_len + 1);
    strcpy(buffer, ss.buffer);
    line_len = ss.line_len;
    inc();
}

SS::SS(const char *s1) {
    used=1;
    check_members();
    size_t len = strlen(s1);
    if (len > MAXLEN) {
        fprintf(stderr, "Строка ( %lu  ) длинней допустимых %d  симвлов - не обрабатываем! \n", len, MAXLEN);
        // @TODO - здесь породить exception 
    } else {
        buffer = (char *) malloc(len + 1);
        line_len = len;
        strcpy(buffer, s1);
        inc();
    }
}


SS::~Smart_string() 
{
    if(used>1) used--;
    else {
        if(buffer!=NULL) free(buffer);
        dec();
    }
}

bool SS::fread(const char *fnm) {
    ifstream ifs(fnm);
    if(!ifs.is_open()) 
    {
	cout << "Такого файла нет:" << fnm << endl;
	return false;
    }
    else {
        string str;
        getline(ifs,str);
        this->setBuffer(str.c_str());
        ifs.close();
        return true;
    }
}

bool SS::fwrite(const char *fnm) {
    ofstream myfile (fnm);
  if (myfile.is_open())
  {
    myfile << buffer;
    myfile.close();
    return true;
  }
  else {
      cout << "Ошибка записи в файл";
      return false;
  }
}

char *SS::getValue() 
{
	return buffer;
} 

size_t SS::getLen() {
	return line_len;
}

int SS::compare(const char *str) // Сравнение 2 строк - объектов класса - между собой
{
	int rc=-1;
 // Если можно use srtcmp
	if (strcmp(buffer,str)==0) {  rc=0; }
	else if (strcmp(buffer,str)<0) { rc=1; }
	else {  rc=-1; } 

 return rc;
}

// TODO написать перегрузку оператора равно с учетом того, что должна сохраняться 
// ссылка на существующий экземпляр класса 

bool SS::operator==(SS ss) // Сравнение 2 строк - объектов класса - между собой
{
	bool rc=false;
	if (strcmp(buffer,ss.getValue())==0) {  rc=true; }
  	return rc;
}

bool SS::operator!=(SS ss) // Сравнение 2 строк - объектов класса - между собой
{
	bool rc=false;
	if (strcmp(buffer,ss.getValue())!=0) {  rc=true; }
  	return rc;
}

bool SS::operator>=(SS ss) // Сравнение 2 строк - объектов класса - между собой
{
	bool rc=false;
	if (strcmp(buffer,ss.getValue())>=0) {  rc=true; }
  	return rc;
}

bool SS::operator<=(SS ss) // Сравнение 2 строк - объектов класса - между собой
{
	bool rc=false;
	if (strcmp(buffer,ss.getValue())<=0) {  rc=true; }
  	return rc;
}

bool SS::operator<(SS ss) // Сравнение 2 строк - объектов класса - между собой
{
	bool rc=false;
	if (strcmp(buffer,ss.getValue())<0) {  rc=true; }
  	return rc;
}

bool SS::operator>(SS ss) // Сравнение 2 строк - объектов класса - между собой
{
	bool rc=false;
	if (strcmp(buffer,ss.getValue())>0) {  rc=true; }
  	return rc;
}

// Конкатенация строки с завершающим нулем
SS SS::operator+(char *str)
{
	char buf[MAXLEN];
	strcpy(buf,getValue());
	strcat(buf,str);
 Smart_string temp(buf);
 return temp;
}

// клонирует строку
SS SS::multiply(int mult)
{
  char *ptr = (char *)malloc (line_len*mult+1);
  strcpy(ptr,"");
  cout << "Цикл умножения строки длина:";
  for(int tik=0;tik<mult;tik++) {
	strcat(ptr,buffer);
	cout << "|"<< strlen(ptr);
  }
  cout << endl;
 SS temp(ptr);
 free (ptr);
 return temp;
  /*  SS tmp("");
      return tmp; */
}

// Умножение строк
SS SS::operator*(int mult) {
    return multiply(mult);
}

// Конкатенация объектов класса
SS SS::operator+(Smart_string str)
{
	char buf[MAXLEN];
	size_t len=line_len+str.line_len; 
	if (len > MAXLEN) {
		fprintf( stderr, "Сумма длин строк ( %lu  ) длинней допустимых %d  симвлов - не обрабатываем! \n", len, MAXLEN);
		throw SSE("Превышение максимально допустимой длины строки");
	}
	strcpy(buf,getValue());
	strcat(buf,str.getValue());
 	SS temp(buf);
 	return temp;
}


// Замена содержимого buffer Smart_строки
void SS::setBuffer(const char *str)
{
	size_t len = strlen(str);
	if(strlen(str) > MAXLEN) {
		fprintf( stderr, "оператор присваивания: строка дл=( %lu  ) длинней допустимых %d  символов - не обрабатываем! \n", len, MAXLEN);
		throw SSE("Operator = has very long input string");
	}
	else {
		if(buffer != NULL) free( buffer);
		buffer = (char *)malloc(len+1);
                strcpy(buffer,str);
                line_len = len;
    	}
}


SS* SS::refObj() {
    used++;
    return  this;
}


// Присваивание строки с завершающим нулем
SS SS::operator=(char *str)
{
	size_t len = strlen(str);
	if(strlen(str) > MAXLEN) {
		fprintf( stderr, "оператор присваивания: строка дл=( %lu  ) длинней допустимых %d  символов - не обрабатываем! \n", len, MAXLEN);
		throw SSE("Operator = has very long input string");
	}
	else {
		free( buffer)	;
		Smart_string temp(str);
		return(temp);
	}
	SS err;
	return err;
}

void SS::print() 
{
	cout << "SS: val=["<< buffer << "] len=" << line_len << " used:"<< used <<  " n_members:" << n_members <<endl;
}

void SS::show_str() {
    cout << buffer;
}

// исползуется внутри класса ( но можно и во вне )
SS SS::substring(size_t pos1, size_t pos2)
{
    char tmp[MAXLEN];
	char msg[MAXLEN];
    size_t pos;
    /*
      * char * strncpy( char * destptr, const char * srcptr, size_t num ); 
      * Функция копирует первые num символов из строки srcptr в строку destptr 
     */
		if( pos1>pos2 || pos1>line_len-1 || pos2>line_len-1) {  // если проверка не прошла - exception
			sprintf(msg,"Smart_sting operator() -> (%zu,%zu) incorrect parameters ",pos1,pos2);
			throw Smart_string_exception(msg);  
			}
        pos = pos2 - pos1 +1; //  ЗАБЫЛА +1 !!!!
	strncpy(tmp,&buffer[pos1], pos);
	tmp[pos] ='\0';   // ВАЖНО:  строка в С всегда оканчивается двоичным 0 
	SS temp(tmp);
	return temp;
}


/**
 Доступ к элементам []. 
    В аргументах могут быть: 
	число типа size_t, которое задаёт позицию в строке, 
	объект Smart_string — ищется как подстрока и возвращается Smart_string,
         содержащая кусок от находки до конца строки;
 */ 
SS SS::operator[](size_t pos)
{
	return substring(pos,line_len-1);
}

/*
 * Оператор передачи параметров, переопределённые (). 
    Пара чисел указанных через запятую, означающие возвращение подстроки из данного диапазона 
     (str(«1234567890») и затем str(3,7) вернёт Smart_string «45678»).
 */

SS SS::operator()(size_t pos1, size_t pos2) {
    return substring(pos1,pos2);
}
