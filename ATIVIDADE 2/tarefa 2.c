#include <stdio.h>
#include <stdlib.h>


#define QNOS 7

int main (){

    struct NO{
    int chave;
    int ind_esq;
    int ind_dir;
    int ind_pai;
            struct NO *pont;
    };
  struct NO *arv,*raiz,*aux;
  FILE *fp;
  int i, ind, sizeNO;

  sizeNO = sizeof(struct NO);

  fp = fopen("structArqBin.data","wb");
   if (fp != NULL){
    for (i=1;i<=QNOS;i++);{
        arv = (struct NO *) malloc(sizeNO);
        if (arv != NULL) {
            arv->chave = i*10;
            arv->ind_esq = 0;
            arv->ind_dir = (i == QNOS ? 0 : i + 1);
            arv->ind_pai = i -1;
            arv->pont = NULL;
            fwrite(arv,sizeNO,1,fp);
            printf ("Struct NO esccrito, chave e indice: ");
            printf ("%i %i %i %i",arv->chave,arv->ind_esq,arv->ind_dir,arv->ind_pai);
            free(arv);
        } else {
        printf ("erro na alocação da memoria");
        }

    }
     fclose(fp);
   }
    else {
        printf ("erro na abertura do arquivo");
    }




}
