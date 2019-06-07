#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  FILE *fp1,*fp2;
  char * prog=argv[0];
  if (argc <3){ //no argomenti, copia lo stdin
    fprintf(stderr,"%s: no file da confrontare\n", prog);
    return 0;
  }
    //argv[1] e argv[2] sono 2 file da confrontare
  if ((fp1=fopen(argv[1],"r"))== NULL){
    fprintf(stderr,"%s: non riesco ad aprire %s\n", prog, argv[1]);
    return 1;
   }
  if ((fp2=fopen(argv[2],"r"))== NULL){
    fprintf(stderr,"%s: non riesco ad aprire %s\n", prog, argv[2]);
    return 1;
  }
  char * l1=malloc(sizeof(char)*100);
  char *l2=malloc(sizeof(char)*100);;
  while ( fgets(l1,80,fp1)!=NULL && fgets(l2,80,fp2)!=NULL ){
      if (strcmp(l1,l2)!=0){
	fputs(l1,stdout);
	fputs(l2,stdout);
	return 0;
      }
  }
  printf("No diff found\n");
  return 0;

}
