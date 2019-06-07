#include <stdlib.h>
#include <stdio.h>
void filecopy(FILE *ifp, FILE *ofp);
int main(int argc, char *argv[]) {
  FILE *fp;
  char * prog=argv[0];
  if (argc == 1) //no argomenti, copia lo stdin
    filecopy(stdin,stdout);
  else
    while (--argc >0)
      if ((fp=fopen(*++argv,"r"))== NULL){
	fprintf(stderr,"%s: non riesco ad aprire %s\n", prog, *argv);
	return 1;
      }else{
	filecopy(fp,stdout);
	fclose(fp);
      }
  if(ferror(stdout)){
    fprintf(stderr, "%s: errore nello scrivere su stdout\n",prog);
    exit(EXIT_FAILURE);
  }
  return 0;
}
void filecopy(FILE *ifp, FILE *ofp){
  int c;
  while ((c=getc(ifp)) != EOF)
    putc(c, ofp);
}
