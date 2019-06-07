#include <stdio.h>
#include <stdlib.h>

int main(void)
{
  FILE *f=fopen("red_with_secret.bmp","rb");

  int n= fseek(f,54,SEEK_SET);
  int l=4;
  char *s;
  int nBytes=l*sizeof(char)*8;
  s=malloc(nBytes*sizeof(char));

  fread(s,nBytes,8,f);
  int i=0;
  int c='a';

  while((i%8)<8 && i<nBytes)
  {
     n=s[i]&1;
     c=(c<<1)|n;
     i++;

     if(i%8==0 && i!=0)
	     printf("%c",c);
  }

  printf("\n");
}
