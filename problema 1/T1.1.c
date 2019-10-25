/*****
*
FILE aprobados
******
*
la función recibe tres archivos, dos en formato binario y uno en foramto ASCII,
los archivos corresponden a 2 semestres de estudio, los cuales contienen datos
de los alumnos, cursos y notas. La funcion retorna dos archivos en formato ASCII,
el primero contiene a todos los alumnos que aprobaron todos los ramos del primer
semestre, y el segundo archivo contiene a los alumnos que aprobaron todos los
ramos del segundo semestre.
******
*
Input:
*
FILE 'notas.dat' : archivo, en formato binario, que contiene un entero M
                   seguido de M notas, correspondientes a ambos semestres,
                   ordenadas en forma de struct, el cual contiene un arreglo
                   con el rol del estudiante, un arreglo con la sigla del
                   curso y un entero con la nota.

FILE 'cursos.dat': archivo, en foramto binario, que contiene un entero C
                   seguido de C cursos, los cuales corresponden a los cursos
                   de ambos semestres, estos están ordenados en structs
                   que contienen un arreglo con la sigla del curso y un entero
                   que indica el semestre al que corresponde el curso,
                   este entero puede tomar el valor 1 o 2.

FILE 'alumnos.txt':  archivo, en formato ASCII, que en su primera linea
                     contiene un entero N, seguido de N lineas, cada linea
                     contiene el rol, Nombre, apellido y año de ingreso
                     correspondientes a un alumno.
*
.......
******
*
Returns:
*
FILE, archivo, en formato ASCII, que contiene a los alumnos que aprobaron
      todos los cursos del primer semestre, cada alumno debe estar en una
      linea del archivo, la cual debe contener el rol del alumno, su nombre
      y apellido, seguido de los ramos aprobados con su rescpectiva nota.

FILE, archivo, en formato ASCII, que contiene a los alumnos que aprobaron
      todos los cursos del segundo semestre, cada alumno debe estar en una
      linea del archivo, la cual debe contener el rol del alumno, su nombre
      y apellido, seguido de los ramos aprobados con su rescpectiva nota.

*****/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* struct para ordenar los datos de los ramos aprobados de cada alumno */
typedef struct{
  char sigla[7];
  int nota;
}aprobado;

/* struct para ordenar  los datos del archivo 'alumnos.txt' */
typedef struct {
  char rol[12];
  char nombre[20];
  char apellido[20];
  int ano;
}alumno;

/* struct que representa la forma en la que estan ordenados los datos del
   archivo 'cursos.dat' */
typedef struct {
  char sigla[7];
  int semestre;
}curso;

/* struct que representa la forma en la que estan odenados los datos del
   archivo 'notas.dat' */
typedef struct nota{
  char rolEstudiante[12];
  char siglaCurso[7];
  int nota;
}nota;

int main() {
  FILE *fp;        // puntero para manejar los archivos
  nota *p_nt;      // puntero para manejar un arreglo del tipo struct nota
  curso *p_cs;     // puntero para manejar un arreglo del tipo struct curso
  alumno *p_al;    // puntero para manejar un arreglo del tipo struct alumno
  aprobado *p_ap;  // puntero para manejar un arreglo del tipo struct aprobado
  int i,k,l,cn,cc,ca,r1,r2,ra1,ra2,in;
  /* i,k y l para iteraciones, cn guardara la cantidad de notas, cc la cantidad
     de cursos y ca la cantidad de alumnos, estos tres ultimos necesarios para
     crear arreglos dinámicos. r1 y r2 guardarán la cantidad de cursos del
     primer y segundo semestre correspondientemente. ra1 y ra2 guardarán la
     cantidad de cursos aprobados del primer y segundo semestre,
     correspondientemente, de cada alumno*/

  /* EXTRACCIÓN DE DATOS */
    /* --  --*/
  fp=fopen("notas.dat","r");       /* Abrimos el archivo y verificamos que se
                                    haya abierto de manera correcta */
  if (fp==NULL) {
    printf("error al abrir archivo 1\n");
    exit(1);
  }
  fread(&cn,sizeof(int),1,fp);     //Leemos la cantidad de notas
  p_nt=(nota *)malloc(sizeof(nota)*cn); /*Creamos el arreglo del tamaño encontrado
                                           y verificamos si hay memoria*/
  if (p_nt==NULL) {
    printf("Error de asignacion de memoria\n");
    exit(1);
  }
  fread(p_nt,sizeof(nota),cn,fp);//Leemos las notas y las guardamos en el arreglo
  fclose(fp);                           //Cerramos el archivo


  fp=fopen("cursos.dat","r");       /* Abrimos el archivo y verificamos que se
                                    haya abierto de manera correcta */
  if (fp==NULL) {
    printf("Error al abrir archivo 2");
    exit(1);
  }
  fread(&cc,sizeof(int),1,fp);      //Leemos la cantidad de cursos
  p_cs=(curso *)malloc(sizeof(curso)*cc);   /*Creamos el arreglo del tamaño
                                         encontrado y verificamos si hay memoria*/
  if (p_cs==NULL) {
    printf("Error de asignacion de memoria\n");
    exit(1);
  }
  fread(p_cs,sizeof(curso),cc,fp);  //Leemos los cursos y los guardamos en el arreglo
  fclose(fp);                       //Cerramos el archivo


  fp= fopen("alumnos.txt","r");      /* Abrimos el archivo y verificamos que se
                                    haya abierto de manera correcta */
  if (fp == NULL){
    printf ("Error al abrir el archivo de alumnos\n");
    exit(1);
  }
  fscanf(fp,"%d",&ca);              //Leemos la cantidad de alumnos
  p_al=(alumno *)malloc(sizeof(alumno)*ca); /*Creamos el arreglo del tamaño
                                         encontrado y verificamos si hay memoria*/
  if (p_al==NULL) {
    printf("Error de asignacion de memoria\n");
    exit(1);
  }
  for (i = 0; i < ca; i++) {    //Leemos los alumnos y los guardamos en el arreglo
    fscanf(fp,"%s %s %s %d",p_al[i].rol,p_al[i].nombre,p_al[i].apellido,&p_al[i].ano);
  }
  fclose(fp);     //Cerramos el archivo
        /* --  --*/
/* FIN DE EXTRACCIÓN DE DATOS*/

  r1=0; //Inicializamos variables contadores
  r2=0;
  /* Recorremos el arreglo de structs cursos para ver cuantos hay del primer semestre y
  cuantos del segundo */
  for (i = 0; i < cc; i++) {
    if (p_cs[i].semestre==1) {
      r1++;
    }
    else{
      r2++;
    }
  }
  /* Recorremos el arreglo de structs alumnos y por cada alumno comparamos su rol con
  los roles del arreglo de structs notas y además verificamos de que haya aprobado el ramo.
  Luego recorremos el arreglo de structs cursos y vemos si el ramo corresponde al
  semestre 1 o al semestre 2*/
  for (i = 0; i < ca; i++) {
    ra1=0;    //Inicializamos variables contadores
    ra2=0;
    for (k = 0; k < cn; k++) {
      if (strcmp(p_al[i].rol,p_nt[k].rolEstudiante)==0 && p_nt[k].nota>=55) {
        for (l = 0; l < cc; l++) {
          if(strcmp(p_nt[k].siglaCurso,p_cs[l].sigla)==0){
            if (p_cs[l].semestre==1) ra1++;
            else ra2++;
          }
        }
      }
    }
    /*Verificamos que el alumno haya aprobado todos los cursos del semestre 1, en caso de ser
    asi, se crea un arreglo que contendrá structs con el curso y la nota */
    if (ra1==r1) {
      p_ap=(aprobado *)malloc(sizeof(aprobado)*ra1);
      in=0;
   /*Se recorre el arreglo de struct notas y  se compara el rol del
   estudiante con los roles del struct nota y además de que el ramo esté aprobado
   Luego, recorremos el arreglo de structs cursos y verificamos que sea el mismo
   curso y del semestre 1, en caso de que se cumpla se guarda el curso y la
   nota en el struct correspondiente*/
      for (k = 0; k < cn; k++) {
        if (strcmp(p_al[i].rol,p_nt[k].rolEstudiante)==0 && p_nt[k].nota>=55) {
          for (l = 0; l < cc; l++) {
            if (strcmp(p_nt[k].siglaCurso,p_cs[l].sigla)==0 && p_cs[l].semestre==1) {
              strcpy(p_ap[in].sigla,p_nt[k].siglaCurso);
              p_ap[in].nota=p_nt[k].nota;
              in++;
            }
          }
        }
      }
      /* Abrimos/creamos el archivo aprobados-s1 en el modo append, verificamos de que se
      haya abierto/creado correctamente y escribimos los datos del struct del alumno */
      fp=fopen("aprobados-s1.txt","a");
      if (fp == NULL){
        printf ("Error al abrir el archivo de aprobados s1\n");
        exit(1);
      }
      fprintf(fp,"%s %s %s",p_al[i].nombre,p_al[i].apellido,p_al[i].rol);
      for (k = 0; k < r1; k++) {
        fprintf(fp," %s %d",p_ap[k].sigla,p_ap[k].nota);
      }
      fprintf(fp,"\n");
      fclose(fp);
      free((void *)p_ap); //Liberamos la memoria que pedimos
    }
    /*Verificamos que el alumno haya aprobado todos los cursos del semestre 2,
    en caso de ser asi, se crea un arreglo que contendrá structs con el curso y la nota */
    if (ra2==r2) {
      p_ap=(aprobado *)malloc(sizeof(aprobado)*ra2);
      in=0;
      /*Se recorre el arreglo de struct notas y  se compara el rol del
      estudiante con los roles del struct nota y además de que el ramo esté aprobado
      Luego, recorremos el arreglo de structs cursos y verificamos que sea el mismo
      curso y del semestre 2, en caso de que se cumpla se guarda el curso y la
      nota en el struct correspondiente*/
      for (k = 0; k < cn; k++) {
        if (strcmp(p_al[i].rol,p_nt[k].rolEstudiante)==0 && p_nt[k].nota>=55) {
          for (l = 0; l < cc; l++) {
            if (strcmp(p_nt[k].siglaCurso,p_cs[l].sigla)==0 && p_cs[l].semestre==2) {
              strcpy(p_ap[in].sigla,p_nt[k].siglaCurso);
              p_ap[in].nota=p_nt[k].nota;
              in++;
            }
          }
        }
      }
      /* Abrimos/creamos el archivo aprobados-s2 en el modo append, verificamos de que se
      haya abierto/creado correctamente y escribimos los datos del struct del alumno */
      fp=fopen("aprobados-s2.txt","a");
      if (fp == NULL){
        printf ("Error al abrir el archivo de aprobados s2\n");
        exit(1);
      }
      fprintf(fp,"%s %s %s",p_al[i].nombre,p_al[i].apellido,p_al[i].rol);
      for (k = 0; k < r2; k++) fprintf(fp," %s %d",p_ap[k].sigla,p_ap[k].nota);
      fprintf(fp,"\n");
      fclose(fp);
      free((void *)p_ap); //Liberamos la memoria que pedimos
    }
  }
  free((void *)p_nt);
  free((void *)p_cs);     //Liberamos la memoria que pedimos
  free((void *)p_al);
  return 0;
}             //Fin del programa
