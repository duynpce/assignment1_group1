#include "assignment1.h"

void delete_buffer(){/// ham nay xoa buffer neu nhu con buffer
   int delete;
   while(delete=getchar()!='\n' && delete!=EOF);
}

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

void add(){
   int ID,ret;//tao id va ret(bien kiem tra xem nhap co thanh cong hay khong)
   char first_name[100],last_name[100]; ///tao first name voi last name
   float GPA;//tao GPA
   FILE * add_text=fopen("student.txt","a");///tao file de them du lieu vao neu nhu file khong ton tai neu file ton tai thi them du lieu vao
   if(add_text==NULL){
      printf("can't open this file");
      return;
   }

   do {
      printf("please enter a student's ID: ");
      ret=scanf("%d",&ID);
      delete_buffer();
   }while(ret==0);// nhap ID
      
   printf("please enter a student's first name: ");
   scanf("%[^\n]s",first_name);
   delete_buffer();// nhap first name
   
   printf("please enter a student's last name: ");
   scanf("%[^\n]s",last_name);
   delete_buffer();//nhap last name

   do {
      printf("please enter a student's GPA: ");
      ret=scanf("%f",&GPA);
      delete_buffer();
   }while(ret==0);//nhap GPA
   
   fprintf(add_text,"%d |%s|%s| %f",ID,first_name,last_name,GPA);/// dien thong tin vao file, format dien vao la "id,|first name|last name| GPA"; để dễ  kiểm soát
   fclose(add_text);///dong file 
   printf("add successfully\n");

}

void edit(){}

void delete(){}

void search_by_id(){}

void search_by_name(){}

void display(){}