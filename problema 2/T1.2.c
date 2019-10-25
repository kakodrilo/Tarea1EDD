/*****
*
FILE coincidencia
******
*
la función entrega un archivo en formato ASCII con las paginas en donde se
encuentran dos palabras al mismo tiempo, en base a dos archivos en formato
ASCII, uno indicando en que paginas se encuentra cada palabra, y el otro
indicando que par de palabras se estan consultando.
******
*
Input:
*
FILE 'palabras.dat' : archivo en formato ASCII que contiene N lineas,
                      donde cada linea representa una palabra, la primera linea
                      es la palabra 0. la linea esta compuesta por un entero C
                      seguido de C enteros que representan las paginas en donde
                      aparece la palabra.

FILE 'consulta.dat' : archivo en formato ASCII que contiene N lineas, donde
                      cada linea es una consulta, la consulta consiste en dos
                      enteros que representan las palabras a consultar.
*
.......
******
*
Returns:
*
FILE, archivo en formato ASCII que contiene tantas lineas como cantidad de
      consultas hechas, cada linea esta compuesta por un entero X indicando la
      cantidad de coincidencias, seguido de X enteros, en orden ascendente,
      indicando las paginas de coincidencia.

*****/

#include <stdio.h>
#include <stdlib.h>

typedef struct {  // struct destinado para ordenar lo datos de 'palabras.dat'
  int cantidad;   // tendrá un entero que indica la cantidad de paginas en donde
  int *p_arr;     // aparece la palabra, y un  puntero que eventualmente apuntará
}palabras;        // a un arreglo dinamico con las paginas en donde esta la palabra.

typedef struct { // struc destinado a ordenar los datos de 'consultas.dat',
  int p1;        // contiene dos enteros, correspondientes a las palabras
  int p2;        // consultadas.
}consulta;

/* metodo de comparación pra aplicar la función qsort(), que ordenara,
   ascendentemente las paginas de coincidencia */
int comparacion(const void *A, const void *B) {
   return ( *(int*)A - *(int*)B );
}

int main() {

  FILE *fp;       //puntero de tipo FILE para manejar los archivos
  palabras *p_pl; //puntero de tipo palabras, el cual es un struct
  consulta *p_cs; //puntero de tipo consulta, el cual es un struct
  int *pags;      //puntero de tipo entero, para manejar un arreglo
  int i,k,l,cl=0,cp,cc=0,cont;
  /* i,k y j para iteraciones, cl guardará la cantidad de palabras existentes
  en el archivo 'palabras.dat', cp guardará la cantidad de paginas coincidentes
  en las diferentes consultas, cc guardará la cantidad de consultas realizadas
  y cont se utilizará para ir cambiando de índice en un arreglo dinamico. */

  /* EXTRACCIÓN DE DATOS */
    /* -- Archivo 'palabras.dat' -- */

  fp = fopen("palabras.dat","r");
  if (fp == NULL){
    printf ("Error al abrir el archivo de palabras\n");
    exit(1);
  }
  while (!feof(fp)) {           // procedemos a contar la cantidad de lineas
    if (getc(fp)=='\n') cl++;   // que corresponde a la cantidad de palabras,
  }                             // para eventualmente crear un arreglo dinámico
  fseek(fp,0,SEEK_SET);         // del mismo largo.

  /* el arreglo dinamico tendrá un largo cl, donde cada indice corresponde a una palabra,
  y el tamaño de los elementos será equivalente a un struct palabras */
  p_pl=(palabras *)malloc(sizeof(palabras)*cl);
  if (p_pl==NULL) {
    printf("Error de asignacion de memoria\n");
    exit(1);
  }
  /* una vez creado el arreglo dinamico, procedemos a guardar los datos del
  archivo en él*/
  for (i = 0; i < cl; i++) {
    fscanf(fp,"%d",&p_pl[i].cantidad);
    p_pl[i].p_arr=(int *)malloc(sizeof(int)*p_pl[i].cantidad);
    if (p_pl[i].p_arr==NULL) {
      printf("Error de asignacion de memoria\n");
      exit(1);
    }
    for (k = 0; k < p_pl[i].cantidad; k++) fscanf(fp,"%d",&p_pl[i].p_arr[k]);
  }
  fclose(fp);

    /* -- Archivo 'consultas.dat' --*/

  fp=fopen("consultas.dat","r");
  if (fp == NULL){
    printf ("Error al abrir el archivo de consultas\n");
    exit(1);
  }
  while (!feof(fp)) {         // extraemos la cantidad de lineas que corresponderán
    if (getc(fp)=='\n') cc++; // a la cantidad de consultas realizadas, para luego
  }                           // crear un arreglo dinámico del mismo largo.
  fseek(fp,0,SEEK_SET);

  /* el arreglo dinámico tendrá un largo cc, cada elemento tendra un tamaño
  equivalente a un struct consulta */
  p_cs=(consulta *)malloc(sizeof(consulta)*cc);
  if (p_cs==NULL) {
    printf("Error de asignacion de memoria\n");
    exit(1);
  }
  /* procedemos a extraer y guardar los datos en el arreglo  */
  for (i = 0; i < cc; i++) fscanf(fp,"%d %d",&p_cs[i].p1,&p_cs[i].p2);
  fclose(fp);

  /* TRABAJO DE LOS DATOS */

  fp=fopen("salida.dat","w");  // apertura del archivo de salida
  if (fp == NULL){
    printf ("Error al abrir el archivo de salida\n");
    exit(1);
  }
  for (i = 0; i < cc; i++) {
    cp=0;
    /* contamos la cantidad de coincidencias que tienen las palabras
    para despues generar un arreglo que contenga las coincidencias */
    for (k = 0; k < p_pl[p_cs[i].p1].cantidad; k++) {
      for (l = 0; l < p_pl[p_cs[i].p2].cantidad; l++) {
        if (p_pl[p_cs[i].p1].p_arr[k]==p_pl[p_cs[i].p2].p_arr[l]) {
          cp++;
          break;
        }
      }
    }
    /* creamos el arreglo dinámico de largo equivalente a la cantidad de
    coincidencias, y procedemos a rellenarlo con las paginas coincidentes */
    cont=0;
    pags=(int*)malloc(sizeof(int)*cp);
    if (pags==NULL) {
      printf("Error de asignacion de memoria\n");
      exit(1);
    }
    for (k = 0; k < p_pl[p_cs[i].p1].cantidad; k++) {
      for (l = 0; l < p_pl[p_cs[i].p2].cantidad; l++) {
        if (p_pl[p_cs[i].p1].p_arr[k]==p_pl[p_cs[i].p2].p_arr[l]) {
          pags[cont]=p_pl[p_cs[i].p1].p_arr[k];
          cont++;
          break;
        }
      }
    }
    /* ordenamos el arreglo de que contiene las paginas coincidentes
    y luego escribimos en el archivo de salida la cantidad de coincidencias
    seguido de las paginas de coincidencia */
    qsort(pags,cp,sizeof(int),&comparacion);
    fprintf(fp, "%d", cp);
    for(l=0;l<cp;l++) fprintf(fp, " %d",pags[l]);
    fprintf(fp, "\n");
    free ((void *)pags);
  }
  /* Cierre de archivo de salida y liberación de memoria dinamica utilizada */
  fclose(fp);
  for (i = 0; i < cl; i++) free((void *)p_pl[i].p_arr);
  free((void *)p_pl);
  free((void *)p_cs);

  return 0;
}
