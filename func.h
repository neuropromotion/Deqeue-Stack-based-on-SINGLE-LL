#ifndef _FUNC_H_
#define _FUNC_H_
#include "list.h"
#include <inttypes.h>
#include <ctype.h>
#define DELIMITER "*********************"
//Операция: отображение меню
//Предусловие: 
//Постусловие: функция возвращает выбранной пользователем пункт меню
short menu ();
//Операция: запись текста со стандартного входа в массив
//Предусловие: st указывает на начало массива символов для записи, sz - длина массива
//Постусловие: функция записывает текст в массив st и возвращает указатель на его начало
char * s_gets (char * st, int sz);
//Операция: очищение буфера
//Предусловие: 
//Постусловие: функция очищает буфер входных данных от мусора после отработки функций scanf и пр.
void buff ();
//Операция: запись данных от пользователя 
//Предусловие: pi указывает на структуру куда будет происходить запись данных
//Постусловие: функция записала в структуру на которую указывает pi данные от пользователя
void getitem (Item * pi);
//Операция: отображение элементов структуры
//Предусловие: item - структура, данные которой будут отображены в консоли
//Постусловие: функция вывела данные структуры item в консоль
void showlist (Item item);
//Операция: реализация выбора пользователя после функции menu()
//Предусловие: ch - является выбранным пользователем пункт меню, people указывает на начало списка, temp указывает на структуру для записи в список
//Постусловие: реализация одного из возможных пунков меню
void switchcase (short ch, List * people, Item * temp);
//Операция: загрузка данных из файла в программу
//Предусловие: plist указывает на начало списка, st указывает на название файла для открытия 
//Постусловие: функция загружает данные из файла в программу и возвращает true, false в противном случае
bool DownloadData (List * plist, char * st);
//Операция: выгрузка данных из программы в файл
//Предусловие: plist указывает на начало списка, st указывает на название файла для открытия 
//Постусловие: функция выгружает данные из программы в файл и возвращает true, false в противном случае
bool UnloadData (List * plist, char * st);
//Операция: получение названия файла для загрузки/выгрузки
//Предусловие: st указывает на массив для записи, sz на размер массива для записи названия файла
//Постусловие: функция записывает в st название файла и возвращает true, false в противном случае
bool GetFileName (char * st, int sz);
#endif