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
   int ID,ret=-1;//tao id va ret(bien kiem tra xem nhap co thanh cong hay khong)
   char first_name[100],last_name[100]; ///tao first name voi last name
   float GPA;//tao GPA
   FILE * add_text=fopen("student.txt","a");///tao file de them du lieu vao neu nhu file khong ton tai neu file ton tai thi them du lieu vao
   if(add_text==NULL){
      printf("can't open this file");
      return;
   }

   do {
      if(ret!=-1) printf("invalid ID\n");
      printf("please enter a student's ID: ");
      ret=scanf("%d",&ID);
      delete_buffer();
   }while(ret==0 || ID <0);// nhap ID

   ret=-1;
   do{
       if(ret!=-1) printf("Invalid first name\n");
       printf("please enter a student's first name: ");
       ret=scanf("%99[^\n]",first_name);
       delete_buffer();// nhap first name
   }while(ret==0);

   ret=-1;
   do{
       if(ret!=-1) printf("Invalid last name\n");
       printf("please enter a student's last name: ");
       scanf("%99[^\n]",last_name);
       delete_buffer();//nhap last name
    }while(ret==0);

    ret=-1;///dieu kien check xem co phai lan dau chay khong
   do {
      if(ret!=-1) printf("invalid GPA\n");
      printf("please enter a student's GPA: ");
      ret=scanf("%f",&GPA);
      delete_buffer();
   }while(ret==0 || GPA>10 || GPA <0);//nhap GPA

   fprintf(add_text,"%d |%s|%s| %f\n",ID,first_name,last_name,GPA);/// dien thong tin vao file, format dien vao la "id,|first name|last name| GPA"; để dễ  kiểm soát
   fclose(add_text);///dong file
   printf("add successfully\n");

}

void edit(){
   int MustFindID;
   int StudentIndex=0,found=-1;
   student students[1000];
   printf("Enter Student's ID that you want to edit: ");
   scanf("%d", &MustFindID);
   FILE *fi = fopen("student.txt","r");
   while (fscanf(fi,"%d|%99[^|]|%99[^|]|%f",&students[StudentIndex].ID, students[StudentIndex].FirstName, students[StudentIndex].LastName, &students[StudentIndex].GPA) == 4)
   {
      if (students[StudentIndex].ID==MustFindID)
      {
         found=StudentIndex;
      }
      StudentIndex++;
   }
   fclose(fi);
   remove("student.txt");
   if (found==-1)
   {
      printf("Student with ID: %d does not exist\n",MustFindID);
      return;
   }

   int type=-1;
   do
   {
      printf("Choose an option: \n");
      printf("1: First Name\n");
      printf("2: Last Name\n");
      printf("3: GPA\n");
      printf("0: Exit");
      scanf("%d",&type);
      delete_buffer();
      switch (type)
      {
         case 1:
         {
            char NewFirstName[100];
            printf("Type New First Name: ");
            scanf("%s",NewFirstName);
            strcpy(students[found].FirstName,NewFirstName);
            break;
         }

         case 2:
         {
            char NewLastName[100];
            printf("Type New Last Name: ");
            scanf("%99[^\n]",NewLastName);
            strcpy(students[found].LastName,NewLastName);
            break;
         }

         case 3:
         {
            int NewGPA;
            printf("Type New GPA: ");
            scanf("%d", &NewGPA);
            students[found].GPA=NewGPA;
            break;
         }
         defaut:
            printf("Please type a NUMBER in range [1,3]\n");
         }
      }
      while (type);

         FILE *fo=fopen("student.txt","w");
         for (int i = 0; i < StudentIndex; i++) {
         fprintf(fo,"%d|%s|%s|%.2f\n", students[i].ID, students[i].FirstName, students[i].LastName, students[i].GPA);
         fclose(fo);
         printf("Edit successfully\n");
   }

}

void delete()
{
    int id, found = 0, ret, targetID;///tao id, ID can xoa, co danh dau hop le va co danh dau neu xoa thanh cong
    char first_name[100], last_name[100], input[100], word; ///tao first name voi last name, input va word de check xem co ki tu khi nhap hay khong
    float gpa; ///tao gpa
    int isValid; ///kiem tra ID neu dung hoac sai

   do {
        printf("Enter the student's ID you desire to remove: ");
        fgets(input, sizeof(input), stdin); /// doc ca dong

        input[strcspn(input, "\n")] = '\0';/// Xoa enter neu co

        if (sscanf(input, "%d %c", &targetID, &word) != 1 || targetID < 0) {
            printf("Invalid ID format, please try again!\n");
            isValid = 0; ///sai
        } else {
            isValid = 1; /// dung, thoat vong lap
        }
    } while (!isValid);

    FILE * delete_student = fopen("student.txt","r");///mo file student.txt o che do doc
    FILE * temp = fopen("temp.txt","w");///tao mot file tam o che do ghi

    if(!delete_student||!temp)
    {
        printf("Error opening file. May be it is not created!\n");
        getchar();
        return;
    }

   while (fscanf(delete_student, "%d |%99[^|]|%99[^|]| %f", &id, first_name, last_name, &gpa) == 4)///doc tung dong trong student.txt
   {
       if(id == targetID)
       {
           found = 1;///gan co tim thay
       }
       else{
            fprintf(temp, "%d |%s|%s| %f\n" ,id,first_name,last_name,gpa);///ghi thong tin ra file tam temp
       }
   }

   fclose(delete_student);///dong file student.txt
   fclose(temp);///dong file temp


   if(found == 0){
        printf("The student with the ID %d can not be removed as they are not in the list\n",targetID);
        remove("temp.txt");///xoa file temp.txt
   }
   else{
        remove("student.txt");///xoa file student.txt
        rename("temp.txt","student.txt");///doi ten file temp thanh student.txt
        printf("Remove successfully!\n"); /// xoa thanh cong
   }
}

void search_by_id(){
   FILE *f = fopen("student.txt", "r"); //open file to read
   if (f == NULL) {    //if file not open => error
        printf("Cannot open student.txt\n");
        return;
    }

   int search_ID;   //input ID find
    printf("Enter ID to search: ");
    scanf("%d", &search_ID);

   student s;
   bool found = false;  //Ban đầu chưa có sinh viên nào cần tìm 
    //Bắt đầu đọc trong file
    //Đọc theo format: ID|FirstName|LastName|GPA
   while (fscanf(f, "%d|%99[^|]|%99[^|]|%f", &s.ID, s.FirstName, s.LastName, &s.GPA) == 4) { 
      if (s.ID == search_ID) {   //Kiểm tra xem ID có khớp không
        //printf ra nếu tìm thấy:
         printf("\nStudent found:\n");
         printf("ID: %d\n", s.ID);
         printf("First Name: %s\n", s.FirstName);
         printf("Last Name: %s\n", s.LastName);
         printf("GPA: %.2f\n", s.GPA);
         found = true; //khi tìm thấy => True
         break; //khi tìm thấy thì dừng không tìm nữa 
      }
   }
    //when not found
   if (!found) { 
      printf("No student found with ID: %d\n", search_ID);
   }

   fclose(f); //close file
}

void search_by_name() {
    char targetLastName[100];
    printf("Enter last name to search: ");
    scanf(" %[^\n]", targetLastName);  // Đọc họ cần tìm

    FILE *f = fopen("student.txt", "r");
    if (f == NULL) {
        printf("Cannot open file student.txt.\n");
        return;
    }

    student s;
    int found = 0;

    printf("\n%-10s %-15s %-15s %-5s\n", "ID", "First Name", "Last Name", "GPA");
    printf("-----------------------------------------------------\n");

    // Đọc từng sinh viên trong file
    while (fscanf(f, "%d |%99[^|]|%99[^|]| %f", &s.ID, s.FirstName, s.LastName, &s.GPA) == 4) {
        if (strcmp(s.LastName, targetLastName) == 0) {
            printf("%-10d %-15s %-15s %.2f\n", s.ID, s.FirstName, s.LastName, s.GPA);
            found = 1;
        }
    }

    if (!found) {
        printf("No student found with last name \"%s\".\n", targetLastName);
    }

    fclose(f);
}


void display(){}
int main()
{
 void (*funs[7])(void) = {NULL, &add, &edit, &delete, &search_by_id, &search_by_name, &display};
 int choice;
 do
 {
 choice = make_choice(0, 6);
 if (choice)
 {
 funs[choice]();
 printf("\nPress any key to return to the menu.");
 getchar();
 }
 } while (choice);
return 0;
}

