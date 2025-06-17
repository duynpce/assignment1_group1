#ifndef ASSIGNMENT1_H_INCLUDED
#define ASSIGNMENT1_H_INCLUDED
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

typedef struct student{
int ID;
char FirstName[100], LastName[100];
float GPA;
}student;

void delete_buffer();
void print_menu();
int make_choice(int min, int max);
void add();
void edit();
void delete();
void search_by_id();
void search_by_name();
void display();
#endif // ASSIGNMENT1_H_INCLUDED
