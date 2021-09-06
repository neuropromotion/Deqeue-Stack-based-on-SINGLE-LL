#include "list.h"
#include "func.h"

int main (void)
{  
      List people;
      Item temp;
      char file_name [MAX];
      bool file_down = false;
      InitializeList(&people);
      if(GetFileName(file_name, MAX))
            file_down = DownloadData(&people, file_name);
      short ch;
      while ((ch = menu()) != 10)
      { 
            switchcase(ch, &people, &temp);
      }
      if (file_down)
            UnloadData(&people, file_name);
      DeleteList(&people);
      printf("Programm is over!\n");
} 