#include "assignment1.h"
int count_student(){
   int size=100,count,id;
   char lname[31],fname[16];
   float gpa;
   FILE *open=fopen("student.txt","r");
   if(open==NULL){
      return 0;
   }
   for(count=0;fscanf(open,"%d |%15[^|]|%30[^|]| %f",&id,fname,lname,&gpa)==4;count++);
   fclose(open);
   return count;
}
int existed_ID(int ID){
   int size=count_student();
   int *existed_id=malloc(sizeof(int)*size);
   char lname[31],fname[16];
   float gpa;
   FILE *open=fopen("student.txt","r");
   if(open==NULL){
      return 0;
   }

   for(int i=0;i<size;i++){
      fscanf(open,"%d |%15[^|]|%30[^|]| %f",&existed_id[i],fname,lname,&gpa)==4;
   }
   fclose(open);
    for(int i=0;i<size;i++){
      if(ID==existed_id[i]){
        free(existed_id);
        return 1;
      }
   }
   free(existed_id);
   return 0;
}

int delete_buffer(){/// ham nay xoa buffer neu nhu con buffer va tra ve 1 neu co xoa, tra ve 0 neu khong xoa
   int delete;
   int has_deleted=0;
   while(delete=getchar()!='\n' && delete!=EOF){
    has_deleted=1;
   }
   return has_deleted;
}

int cmp(const void *a, const void *b) { /// const void la do ham qsort yeu cau , (student *) ep kieu ve student
   return stricmp(((student *)a)->LastName, ((student *)b)->LastName);//stricmp la strcmp nhung khong phan biet viet hoa hay viet thuong
}

int valid_name(char str[]){
   for(int i=0;i<strlen(str);i++){
      if((str[i]>'z' || str[i]<'a') && (str[i]>'Z' || str[i]<'A') && str[i]!=' '){
         return 0;
      }
   }
   return 1;
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
   int ID,ret=-1,has_char,size=count_student(),existed_id,lenOfStr;//tao id va ret va has_char(bien kiem tra xem nhap co thanh cong hay khong)
   char first_name[16],last_name[31]; ///tao first name voi last name
   float GPA;//tao GPA
   char type_of_err_number[4][30]={"string ","negative number","number bigger than 10","existed ID"};
   char type_of_err_str[4][30]={"is empty","contain invalid character","is more than one word","is too long"};
   int id;
   char lname[31],fname[16];
   float gpa;
   FILE * add_text=fopen("student.txt","a");///tao file de them du lieu vao neu nhu file khong ton tai neu file ton tai thi them du lieu vao
   if(add_text==NULL){
      printf("can't open this file");
      return;
   }

   do {
      if(ret!=-1) {
         if(existed_id==1) ret=3;
         if(has_char==1) ret=0;
         printf("invalid ID,input contain a %s, please enter positive number\n",type_of_err_number[ret]);
      }
      printf("please enter a student's ID: ");
      ret=scanf("%d",&ID);
      has_char=delete_buffer();
      existed_id=existed_ID(ID);
   }while(ret==0 || ID <0 || has_char==1 || existed_id==1);// nhap ID

   ret=-1;
   do{
       if(ret!=-1) {
         if(has_char==1 && strlen(first_name)<15) ret=2;
         else if(has_char==1 && strlen(first_name)==15) ret=3;
         printf("Invalid first name, input %s\n",type_of_err_str[ret]);
         if(ret>0)
         printf("first name can only contain a word of length 15 from a to z(uppercase or lowercase)\n");
       }
       printf("please enter a student's first name: ");
       ret=scanf("%15s",first_name);
       has_char=delete_buffer();
   }while(ret==0 || valid_name(first_name)==0 || has_char==1);// nhap first name

   ret=-1;
   do{
       if(ret!=-1) {
         if(has_char==1) ret=3;
         printf("Invalid last name, input %s\n",type_of_err_str[ret]);
         if(ret==1 || ret==3)
         printf("last name can only contain a string of length 30 from a to z(uppercase or lowercase)\n");
       }
       printf("please enter a student's last name: ");
       ret=scanf("%30[^\n]",last_name);
       has_char=delete_buffer();//nhap last name
    }while(ret==0 || valid_name(last_name)==0 || has_char==1);

    ret=-1;///dieu kien check xem co phai lan dau chay khong
   do {
     if(ret!=-1) {
         if(GPA>10) ret=2;
         if(has_char==1 && GPA <=10) ret=0;
         printf("invalid GPA,input contain a %s, please enter positive number from 1 to 10\n",type_of_err_number[ret]);
      }
      printf("please enter a student's GPA: ");
      ret=scanf("%f",&GPA);
      has_char=delete_buffer();
   }while(ret==0 || GPA>10 || GPA <0 || has_char==1);//nhap GPA

   fprintf(add_text,"%d |%s|%s| %f\n",ID,first_name,last_name,GPA);/// dien thong tin vao file, format dien vao la "id,|first name|last name| GPA"; để dễ  kiểm soát
   fclose(add_text);///dong file
   printf("add successfully\n");

}

   void edit(){
   int MustFindID;
   int StudentIndex=0,found=-1,size=count_student()+5;
   FILE *fi = fopen("student.txt","r");
   student* students;
   students=malloc(sizeof(student)*size);///tao mang hoc sinh voi kich thuoc phu hop
   printf("Enter Student's ID that you want to edit: ");
   scanf("%d", &MustFindID);

   while (fscanf(fi,"%d |%99[^|]|%99[^|]| %f",&students[StudentIndex].ID, students[StudentIndex].FirstName, students[StudentIndex].LastName, &students[StudentIndex].GPA) == 4)
   {
      if (students[StudentIndex].ID==MustFindID) // tim vi tri cua id can tim trong luc nap du lieu
      {
         found=StudentIndex; // danh dau found la vi tri cua hoc sinh voi id can tim
      }
      StudentIndex++;
   }

   fclose(fi);

   if (found==-1) // neu khong thay hoc sinh voi id can tim thi mac dinh found = -1 va in ra khong ton tai va return
   {
      printf("Student with ID %d does not exist\n",MustFindID);
      return;
   }

   int type=-1;
   do
   {
      type=-1; // cho type = -1 de tranh truong hop nhap vao ki tu khong phai so 
      printf("=========================================\n");
      printf("WORKING ON STUDENT'S ID %d\n", MustFindID);
      printf("1: New First Name\n");
      printf("2: New Last Name\n");
      printf("3: New GPA\n");
      printf("0: Exit (Edit Completed)\n");
      printf("Choose an option: ");
      scanf("%d",&type);
      delete_buffer();
      switch (type)
      {
         case 1:
         {
            int ret=-1; // dieu kien lan dau nhap
            char NewFirstName[100];
            do {
            if (ret!=-1) printf("INVALID NAME, PLEASE TYPE AGAIN\n"); // neu khong phai lan dau nhap thi mac dinh la nhap sai
            printf("Type New First Name: ");
            ret=scanf("%99[^\n]", NewFirstName); // ret = 1 neu nhap duoc du lieu va = 0 neu khong nhap duoc du lieu
            delete_buffer();
            }
            while(ret==0 || valid_name(NewFirstName)==0);
            strcpy(students[found].FirstName,NewFirstName);
            break;
         }

         case 2:
         {
            int ret=-1;
            char NewLastName[100];
            do {
            if (ret!=-1) printf("INVALID LAST NAME, PLEASE TYPE AGAIN");
            printf("Type New Last Name: ");
            scanf("%99[^\n]",NewLastName);
            delete_buffer();
            }
            while (ret==0 || valid_name(NewLastName)==0);
            strcpy(students[found].LastName,NewLastName);
            break;
         }

         case 3:
         {
         float NewGPA;
         int ret=-1;///dieu kien check xem co phai lan dau chay khong
         do {
         if(ret!=-1) printf("invalid GPA (GPA must be a positive number in RANGE [0,10])\n");
         printf("Type New GPA: ");
         ret=scanf("%f",&NewGPA);
         students[found].GPA = NewGPA;
         delete_buffer();
         }while(ret==0 || NewGPA>10 || NewGPA <0);//nhap GPA
            break;
         }
         default:
         if (type!=0) // nhung truong hop con lai khong bao gom 0, neu la so <0 va >3 thi se nhap lai
            printf("Please type a NUMBER in range [0,3]\n");
         }
      }
      while (type!=0); // dieu kien lap lai vong lap neu nguoi dung van muon tiep tuc chinh sua hoc sinh voi id nay
         remove("student.txt"); 
         FILE *fo=fopen("student.txt","w");
         for (int i = 0; i < StudentIndex; i++) {
         fprintf(fo,"%d |%s|%s| %.2f\n", students[i].ID, students[i].FirstName, students[i].LastName, students[i].GPA);
         }
         fclose(fo);
         free(students); // do khong can truy cap nua nen giai phong mang
         printf("Edit successfully\n");
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
 int ID,ret=-1;
    FILE *f = fopen("student.txt", "r"); //open file to read
    if (f == NULL) {    //if file not open => error
        printf("Cannot open student.txt\n");
        return;
    }

   do {
      if(ret!=-1) printf("invalid ID\n");
      printf("please enter a student's ID: ");
      ret=scanf("%d",&ID);
      delete_buffer();
   }while(ret==0 || ID <0);// nhap ID

   student s;
   bool found = false;  //Ban đầu chưa có sinh viên nào cần tìm
    //Bắt đầu đọc trong file
    //Đọc theo format: ID|FirstName|LastName|GPA
   while (fscanf(f, "%d |%99[^|]|%99[^|]| %f", &s.ID, s.FirstName, s.LastName, &s.GPA) == 4) {
      if (s.ID == ID) {   //Kiểm tra xem ID có khớp không
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
      printf("No student found with ID: %d\n",ID);
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


void display(){/// ham
   int size=count_student();
   student *Std;
   FILE * open=fopen("student.txt","r");
    if(open==NULL || size==0){
      printf("no information to display");
      return;
   }
   Std=malloc(sizeof(student)*size);///tao mang hoc sinh voi kich thuoc phu hop

   for(int i=0;i<size;i++){
      fscanf(open,"%d |%15[^|]|%30[^|]| %f",&Std[i].ID,Std[i].FirstName,Std[i].LastName,&Std[i].GPA);//doc file /// do
   }

   qsort(Std,size,sizeof(student),cmp);/// sap xep (qsort la ham co san) ///npduy
   printf("%10s %-15s %-30s %8s\n", "ID", "Name", "Last Name" ,"Grade");
   printf("===================================================================\n");
    for(int i=0;i<size;i++)
    printf("%10d %-15s %-30s %8.2f\n",Std[i].ID,Std[i].FirstName,Std[i].LastName,Std[i].GPA);
    free(Std);///free mang///viet
    fclose(open);//dong file
}////khong sua ham nay


