#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct decode
{
  char meaning;
  char *morse;
};

typedef enum
{EXIT,TEXT_TO_MORSE,MORSE_TO_TEXT}menu_Item;

int morse_operation(int *check,struct decode* morse_array);
void end(void);

int main(void)
{
  int check=0;
  atexit(end);
  int num;

  FILE*f=NULL;
  f=fopen("morse.txt","r");
  struct decode *morse_array=malloc(sizeof(struct decode)*49);

  char meaning;
  char morse[80];

  int i=0;
  while(i<49)
  {
    char riga[80];
    fgets(riga,80,f);

    sscanf(riga,"%c %s",&meaning,morse);
    morse_array[i].meaning=meaning;

    morse_array[i].morse=malloc(strlen(morse)+1);
    strcpy(morse_array[i].morse,morse);

    i++;
  }
  fclose(f);

  while(!check)
  {
    morse_operation(&check,morse_array);
  }

  int j=0;
  while(j<49)
  {
    free(morse_array[j].morse);
    j++;
  }
  free(morse_array);

}

void end(void)
{
  printf("Thanks for the use of the app\n");
}
int morse_operation(int *check,struct decode* morse_array)
{
  char riga[80];
  printf("Write the text you want to translate into morse \n");
  fgets(riga,40,stdin);
  int length=strlen(riga);
  int n;

  for(n=0;n<length;n++)
  {
    if(riga[n]==' ')
      printf("%c",riga[n]);
    else
    {
      int flag=0;
      int i=0;
      while(i<49 && !flag)
      {
        if(morse_array[i].meaning==riga[n])
        {
          printf("%s",morse_array[i].morse);
          flag=1;
        }
        i++;
      }
    }
  }
  printf("\n");
}
