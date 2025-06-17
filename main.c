#include "assignment1.h"
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
