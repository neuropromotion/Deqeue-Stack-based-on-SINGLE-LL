#include "list.h"

static void PutItem (Item item, List * plist);
static List GetNth (List * plist, int n);
static List GetLast (List * plist);
static List GetPenult (List * plist);
void InitializeList (List * plist)
{
    *plist = NULL;
}
bool ListIsEmpty (const List * plist)
{
    return (*plist == NULL) ? true : false;
}

bool ListIsFull (void)
{
    bool temp = false;
    List pnew;
    pnew = (Node*)malloc(sizeof(Node));
    if (pnew == NULL)
    {
        fprintf(stderr, "ERROR: Not enough memory to allocate!\n");
        temp = true;
    }
    free(pnew);
    return temp;
}
bool AddFront (Item item, List * plist)
{
    bool temp = true;
    if (ListIsFull())
        temp = false;
    List pnew;
    pnew = (Node *) malloc(sizeof(Node));
    PutItem(item, &pnew);
    pnew->next = *plist;
    *plist = pnew;
    return temp; 
}
Item DeleteFront (List * plist)
{
    Item temp_item;
    List temp;
    if (ListIsEmpty(plist))
        exit(EXIT_FAILURE);
    temp = *plist;
    temp_item = (*plist)->item;
    (*plist) = (*plist)->next;
    free(temp);
    return temp_item;
}

bool EnQueue (Item * pi, List * plist)
{
    List temp;
    List seek;
    if (ListIsEmpty(plist))
        return false;
    temp = (Node*)malloc(sizeof(Node));
    temp->next = NULL;
    PutItem(*pi, &temp);
    seek = GetLast(plist);
    seek->next = temp;
    return true;
}


Item DeQueue (List * plist)
{
    List penult;
    List temp_list;
    Item temp;
    if (ListIsEmpty(plist))
        exit(EXIT_FAILURE);
    penult = GetPenult(plist);
    temp = penult->next->item; 
    temp_list = penult->next;
    penult->next = NULL;
    free (temp_list);
    return temp;
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

static List GetPenult (List * plist)
{  
    List seek = *plist;
    if (ListIsEmpty(plist))
        return NULL;
    while (seek->next->next != NULL)
        seek = seek->next;
    return seek;
}

static List GetNth (List * plist, int n)
{
    List seek = *plist;
    int ctr = 0;
    if (ListIsEmpty(plist))
        return seek;
    while ((seek->next) && (ctr < n))
    {
        seek = seek->next;
        ctr++;
    }
    return seek;
}

bool Insert (Item * pi, List * plist, int n)
{
    List temp;
    List seek;
    if (ListIsFull())
        return false;
    temp = (Node*)malloc(sizeof(Node));
    PutItem(*pi, &temp);
    seek = GetNth(plist, n);
    if (seek->next)
    {
        temp->next = seek->next;
    }
    else
    {
        temp->next = NULL;
    } 
    seek->next = temp;
    return true;
}
Item DeleteNth (List *plist, int n)
{
    List seek;
    List temp;
    Item temp_item;
    if (n == 0)
        return DeleteFront(plist);
    if (ListIsEmpty(plist))
        exit(EXIT_FAILURE);
    seek = GetNth(plist, n-1);
    temp = seek->next;
    temp_item = seek->next->item;
    seek->next = seek->next->next;
    free (temp);
    return temp_item;
}
void DeleteList (List * plist)
{
    if (ListIsEmpty(plist))
        return;
    List temp;
    while ((*plist)->next)
    {
        temp = *plist;
        *plist = (*plist)->next;
        free(temp);
    }
    free(*plist);
}

void Traverse (List * plist, void (*pfun)(Item item))
{
    if (ListIsEmpty(plist))
    {
        puts("List is empty!\n");
        return;
    }
    List temp;
    temp = *plist;
    while (temp)
    {
        pfun(temp->item);
        temp = temp->next;
    }
}

void Traverse_recurr (List * plist, void(*pfun)(Item item))
{
    if ((*plist)->next)
        Traverse_recurr(&(*plist)->next, pfun);
    pfun((*plist)->item);
}
static void PutItem (Item item, List * plist)
{
    (*plist)->item.age = item.age;
    strcpy((*plist)->item.name, item.name);
} 
int ListItemCount (const List *plist)
{
    List trav;
    int ctr = 0;
    if (ListIsEmpty(plist))
        return ctr;
    trav = *plist;
    while (trav != NULL)
    {
        ctr++;
        trav = trav->next;
    }
    return ctr;
}

