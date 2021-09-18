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
    ofp = fopen("pass.txt", "w");
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

int main()
{
  int authRes = authenticate();
  return 0;
}