#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct PassNode
{
  char pass[25];
} PassNode;

typedef struct Entry
{
  char name[25], email[25], password[25], description[140], url[100];
} Entry;

int authenticate()
{
  FILE *ifp;
  char pass[25];
  PassNode *passNode;
  passNode = (PassNode *)malloc(sizeof(PassNode));
  ifp = fopen("pass.txt", "r");
  if (ifp == NULL)
  {
    printf("Error opening file\n");
    return -2;
  }
  fread(passNode, sizeof(passNode), 1, ifp);
  fclose(ifp);
  if (passNode->pass[0] == '\0')
  {
    printf("No master password found, please enter one (max 25 characters)\n");
    FILE *ofp;
    ofp = fopen("pass.txt", "wb");
    scanf("%s", pass);
    strcpy(passNode->pass, pass);
    fwrite(passNode, sizeof(passNode), 1, ofp);
    printf("Master password set\n");
    fclose(ofp);
    return authenticate();
  }
  else
  {
    printf("Enter master password\n");
    scanf("%s", pass);
    if (strcmp(pass, passNode->pass) == 0)
    {
      printf("Master password accepted\n");
      return 0;
    }
    else
    {
      printf("Master password incorrect\n");
      return -1;
    }
  }
  return 0;
}

void createEntry()
{
  Entry *e;
  FILE *fp;
  char p[140];

  e = (Entry *)malloc(sizeof(Entry));
  fp = fopen("entries.txt", "a+");

  //Obligatory field

  printf("Enter name\n");
  scanf("%s", p);
  strcpy(e->name, p);
  fflush(stdin);

  //Obligatory field

  printf("Enter username/email\n");
  scanf("%s", p);
  strcpy(e->email, p);
  fflush(stdin);

  //Obligatory field

  printf("Enter your password\n");
  scanf("%s", p);
  fflush(stdin);
  strcpy(e->password, p);

  //Must fix optinal sections
  printf("Enter a description (Press Enter to skip)\n");
  fgets(p, 20, stdin);
  //printf("Description: %s\n", p);
  strcpy(e->description, p);

  printf("Enter a url (Press Enter to skip)\n");
  fgets(p, 20, stdin);
  strcpy(e->url, p);

  fwrite(e, sizeof(Entry), 1, fp);

  fclose(fp);
}

void listEntries()
{
  Entry *e;
  e = (Entry *)malloc(sizeof(Entry));

  FILE *fp;
  fp = fopen("entries.txt", "rb");

  int i = 1;
  if (fp != NULL)
  {
    while (1)
    {

      fread(e, sizeof(Entry), 1, fp);
      if (feof(fp))
      {
        break;
      }
      printf("Entry %i:", i++);
      printf("\n\tUsername: %s \n\tUsername/email: %s \n\tPassword: %s \n\tDescription: %s \tUrl: %s \n", e->name, e->email, e->password, e->description, e->url);
    }
  }
  fclose(fp);
}

void deleteEntry()
{
  int del;

  listEntries();
  printf("Select an entry: ");
  scanf("%d", &del);

  Entry *e;
  e = (Entry *)malloc(sizeof(Entry));

  FILE *fp;
  fp = fopen("entries.txt", "rb");

  Entry entries[10];


  int index = 0;

  if (fp != NULL)
  {
    while (1)
    {

      fread(e, sizeof(Entry), 1, fp);
      if (feof(fp))
      {
        break;
      }
      if (index != del -1){
        entries[index] = *e;
      }
      index++;
    }
  }
  fclose(fp);
  
  fp = fopen("entries.txt", "wb");
  for (int ii = 0; ii < index-1; ii++) {
    fwrite(&entries[ii], sizeof(Entry), 1, fp);
    printf("\n\tUsername: %s \n\tUsername/email: %s \n\tPassword: %s \n\tDescription: %s \tUrl: %s \n", entries[ii].name, entries[ii].email, entries[ii].password, entries[ii].description, entries[ii].url);
  }
  fclose(fp);
}


int main()
{
  int authRes = authenticate();
  int option;

  do
  {
    printf("1. Create entry\n");
    printf("2. Delete entry\n");
    printf("3. View all entries\n");
    printf("4. Select entry\n");
    printf("0. Exit Program\n");

    printf("Select an option: ");
    scanf("%d", &option);

    switch (option)
    {
    case 1:
      createEntry();
      break;
    case 2:
      deleteEntry();
      break;
    case 3:
      listEntries();
    }

  } while (option != 0);
  return 0;
}