#ifndef ASSIGNMENT1_H_INCLUDED
#define ASSIGNMENT1_H_INCLUDED
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<ctype.h>

typedef struct student{
int ID;
char FirstName[100], LastName[100];
float GPA;
}student;

int count_student();
int ID_exsited(int ID);
int delete_buffer();
int cmp(const void *a, const void *b);
int valid_name(char str[]);
void print_menu();
int make_choice(int min, int max);
void add();
void edit();
void delete();
void search_by_id();
void search_by_name();
void display();
#endif // ASSIGNMENT1_H_INCLUDED
