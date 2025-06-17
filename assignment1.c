#include "assignment1.h"
void print_menu(){
    //system("clear"); // for macos, linux
//system("cls"); // for windows
printf("STUDENT MANAGEMENT SYSTEM\n");
printf("-------------------------\n");
printf("1. Add new student\n");
printf("2. Edit a student\n");
printf("3. Delete a student\n");
printf("4. Search for a student by ID\n");
printf("5. Search for a student by last name\n");
printf("6. Display all students sorted by last name\n");
printf("0. Exit\n");
}
int make_choice(int min, int max){
    int not_valid = 1, num, scanf_ret;
     char c;

     print_menu();
     fflush(stdin);
     do
    {
     printf("\nEnter your choice: ");
     scanf_ret = scanf("%d%c", &num, &c);
     if (scanf_ret < 2 || c != '\n')
     {
        print_menu();
        printf("\nYour choice is not valid. Please try again!\n");
        fflush(stdin);
     }
     else if (num < min || num > max)
     {
        print_menu();
        printf("\nYour choice is not valid. Please try again!\n");
     }
     else
        not_valid = 0;
     } while (not_valid);

        //system("clear");

     return num;
}
void add(){}
void edit(){}
void delete(){}
void search_by_id(){}
void search_by_name(){}
void display(){}