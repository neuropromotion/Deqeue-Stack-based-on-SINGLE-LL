#include "list.h"
#include "func.h"
static void AddFromFile (List * plist, List * add);
static List GetLast (List * plist);
short menu ()
{ 
      short num;
      char arr [MAX];
      puts(DELIMITER);
      puts("Enter appropriate number:");
      puts("1) Add name in front of list        2) Add name in back of list");
      puts("3) Delete name from front of list   4) Delete name form back of list");
      puts("5) Add name in n position of list   6) Delete name from n position of list");
      puts("7) Show list from front to back     8) Show list from back to front");
      puts("9) Show quantity of names in list   10) Exit");
      puts(DELIMITER);
      while (fgets(arr, MAX, stdin) != NULL)
      {
            if ((strlen(arr) > 2) && (atoi(arr) != 10))
            {
                  puts("Incorrect data, try again!");
                  continue;
            }
            if ((atoi(arr) < 11) && (atoi(arr) > 0))
                  break;
            puts("Incorrect data, try again!");
      }
      num = atoi(arr);
      return num;
}
char * s_gets (char * st, int sz)
{
      char * ret_val;
      char * find;
      ret_val = fgets(st, sz, stdin);
      if (ret_val)
      {
            find = strchr(st, '\n');
            if (find)
            {
                  *find = '\0';
            }
      }
      return ret_val;
}
void buff ()
{
      while (getchar() != '\n')
            continue;
}
void getitem (Item * pi)
{
      printf("Enter name:\n");
      s_gets(pi->name, MAX);
      puts("Enter age:");
      scanf("%d", &pi->age);
      buff();
}
void showlist (Item item)
{
      printf("Name: [%s], age: [%d]\n", item.name, item.age);
}

void switchcase (short ch, List * people, Item * temp)
{
      int position;
      switch (ch)
      {
            case 1: 
                  getitem(temp);
                  if (AddFront(*temp, people))
                        printf("[%s] was succesfully added in list\n", (*temp).name);
                  else
                        puts("Error!\n"); 
                  break;
            case 2:
                  getitem(temp);
                  if (EnQueue(temp, people))
                        printf("[%s] was succesfully added in list\n", (*temp).name);
                  else
                        puts("Error!\n");
                  break;
            case 3:
                  *temp = DeleteFront(people);
                  printf("[%s] was deleted from list\n", (*temp).name);
                  break;
            case 4: 
                  *temp = DeQueue(people);
                  printf("[%s] was deleted from list\n", (*temp).name);
                  break;
            case 5: 
                  getitem(temp);
                  printf("Enter number of position: \n");
                  scanf("%d", &position);
                  buff();
                  if (Insert(temp, people, position))
                        printf("[%s] was succesfully added in list\n", (*temp).name);
                  else
                        puts("Error!\n");
                  break;
            case 6:
                  printf("Enter number of position: \n");
                  scanf("%d", &position);
                  buff();
                  *temp = DeleteNth(people, position);
                  printf("[%s] was deleted from list!\n", (*temp).name);
                  break;
            case 7: 
                  Traverse (people, showlist);
                  break;
            case 8: 
                  Traverse_recurr(people, showlist);
                  break;
            case 9: 
                  printf("Names in list if [%d]\n", ListItemCount(people));
                  break;
            default: 
                  printf("Switch case error! Try again!\n");
                  break;
      }
}

bool DownloadData (List * plist, char * st)
{
      bool cond = true;
      FILE * ptr;
      uint32_t size;
      uint32_t ctr = 0;
      List temp;
      if ((ptr = fopen(st, "rb")) == NULL)
      {
            fprintf(stderr, "File did not open!\n");
            cond = false;
      }
      else
      {
            fread(&size, sizeof(uint32_t), 1, ptr);
            while (ctr < size)
            {
                  temp = (Node*)malloc(sizeof(Node));
                  if (temp == NULL)
                  {
                        fprintf(stderr, "Allocating memory ERROR!\n");
                        cond = false;
                        break;
                  }
                  fread(temp, sizeof(Node), 1, ptr);
                  AddFromFile(plist, &temp);
                  ctr++;
            }
      }
      fclose(ptr);
      return cond;
}
bool UnloadData (List * plist, char * st)
{ 
      List temp = *plist;
      bool cond = true;
      FILE * ptr;
      uint32_t size = ListItemCount(plist);
      uint32_t ctr = 0;
      uint32_t * int_ptr = &size;
      if ((ptr = fopen(st, "wb")) == NULL)
      {
            fprintf(stderr, "File did not open!\n");
            cond = false;
      }
      
      else 
      {
            //puts("File opened to write!");
            fwrite(int_ptr, sizeof(uint32_t), 1, ptr);
            while (ctr < size && temp)
            {
                  fwrite(temp, sizeof(Node), 1, ptr);
                  temp = temp->next;
                  ctr++;
            }
      }
      fclose(ptr);
      return cond;
}



static void AddFromFile (List * plist, List * add)
{
      List seek;
      if (ListIsEmpty(plist))
      {
            *plist = *add;
            (*add)->next = NULL;
      }
      else 
      {
            seek = GetLast(plist);
            seek->next = *add;
            (*add)->next = NULL;
      }
}

static List GetLast (List * plist)
{
    List seek = *plist;
    if (ListIsEmpty(plist))
        return seek;
    while (seek->next != NULL)
        seek = seek->next;
    return seek;
}


bool GetFileName (char * st, int sz)
{
      bool cond = true;
      puts("If you want to download data from file, enter file's name or empty string to continue without downloading:");
      s_gets(st, sz);
      if (st[0] == '\0')
            cond = false;
      return cond;
}