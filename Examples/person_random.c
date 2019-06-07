#include<stdio.h>
#include<stdlib.h>

#define SIZE 300
#define NUM 3

struct persona{
  char nome[20];
  char cognome[20];
  int eta;
} ;

void print_persona(char * s, struct persona p);

int main()
{

  FILE *fp;
  
  fp=fopen("archivio.dat","wb");

  struct persona p;
  char tmp_buf[SIZE];
  //scrittura
  int i=0;
  
  do {
    printf("Inserisci i dati della persona num. %d\n",i);
    fgets(tmp_buf,SIZE,stdin);
    int r=sscanf(tmp_buf,"%s%s%d\n",p.nome, p.cognome,&p.eta);
    if (r!=3){
      printf("error in the data format\n");
    }
    else{
      i++;
      fwrite(&p,sizeof(p),1,fp);
    }
  }  while(i<NUM);

  fclose(fp);
  //lettura
  fp=fopen("archivio.dat","rb");

  // get first record  from the file!
  struct persona p1;
  
  rewind(fp);
  fread(&p1,sizeof(p1),1,fp);
  
  print_persona("Prima persona:", p1);

  //iterate on records:
  rewind(fp);
  int j;
  printf("\nIterate on records\n");
  for (j=0;j<NUM;j++){
    fread(&p1,sizeof(p1),1,fp);
    sprintf(tmp_buf,"Persona %d",j);
    print_persona(tmp_buf, p1);
  }

  //getLasttRecord
  fseek(fp,-sizeof(p1),2);
  
  fread(&p1,sizeof(p1),1,fp);

  //printf("Il nome dell'ultima persona inserita e'%s, il cognome %s\n", p1.nome,p1.cognome); 
  print_persona("Ultima persona inserita: ", p1);
  return 0;

  
}

void print_persona(char *s, struct persona p)
{
  printf("%s: %s %s - %d\n",s,p.nome, p.cognome, p.eta);
}
