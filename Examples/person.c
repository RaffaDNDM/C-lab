#include<stdio.h>
#include<stdlib.h>

#define SIZE 300
#define NUM 3

struct persona{
  char nome[20];
  char cognome[20];
  int eta;
} ;

void print_persona(struct persona p);

int main()
{
  FILE *fp;
  
  fp=fopen("archivio.dat","wb");

  struct persona p;
  char tmp_buf[SIZE];
  
  int i=0;
  //lettura da tastiera e scrittura su file
  do {
    printf("Inserisci i dati della persona num. %d\n",i);
    fgets(tmp_buf,SIZE,stdin);
    int r=sscanf(tmp_buf,"%s%s%d\n",p.nome, p.cognome,&p.eta);
    if (r!=3){
      printf("Error in the data format\n");
    }
    else{
      i++;
      fwrite(&p,sizeof(p),1,fp);
    }
  }  while(i<NUM);

  fclose(fp);
  //lettura da file e scrittura su schermo
  if ( (fp=fopen("archivio.dat","rb")) == NULL ){
    fprintf(stderr,"Can't open archivio file\n");
    exit(EXIT_FAILURE);
  }

  // you got the data from the file!
  struct persona p1;
  
  fread(&p1,sizeof(p1),1,fp);
  print_persona(p1);
    
  rewind(fp);

  //stampiamo tutte le informazioni sulle persone:
  for (i=0;i<NUM; i++){
    fread(&p1,sizeof(p1),1,fp);
    print_persona(p1);
  }
   return 0;
}

void print_persona(struct persona p)
{
  printf("%s %s - %d\n",p.nome, p.cognome, p.eta);
} 
