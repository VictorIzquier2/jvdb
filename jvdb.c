#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>

#ifdef _WIN32
#include <direct.h>
#define mkdir _mkdir
#else
#include <sys/stat.h>
#endif

int main(int argc, char *argv[]){
  FILE *archivo;
  char *operacion = argv[1];
  char *basededatos = argv[2];
  char *coleccion = argv[3];


  if(strcmp(operacion, "select") == 0){
    char ruta[100];
    char *documento = argv[4];

    // Ruta para el archivo
    strcpy(ruta, basededatos);
    strcat(ruta, "/");
    strcat(ruta, coleccion);
    strcat(ruta, "/");
    strcat(ruta, documento);
    strcat(ruta, ".json");

    archivo = fopen(ruta, "r");
    printf("te doy datos: \n");
    char linea[1024];
    while(fgets(linea, sizeof(linea), archivo) != NULL){
      printf("Linea: %s", linea);
    }
  }else if(strcmp(operacion, "insert") == 0){
    char *documento = argv[4];
    char carpeta_base[100];
    char ruta[100];

    // Ruta para el archivo
    strcpy(ruta, basededatos);
    strcat(ruta, "/");
    strcat(ruta, coleccion);
    strcat(ruta, "/");
    strcat(ruta, documento);
    strcat(ruta, ".json");

    // Ruta para la carpeta
    strcpy(carpeta_base, basededatos);
    strcat(carpeta_base, "/");
    strcat(carpeta_base, coleccion);

    struct stat info;
    if(stat(carpeta_base, &info) != 0){
      if(mkdir(carpeta_base) != 0){
        perror("Error al crear la carpeta base");
        return 1;
      }
    }

    //printf("%s \n", ruta);
    archivo = fopen(ruta, "a");
    char *texto = argv[5];
    fputs(strcat(texto, "\n"), archivo);
    fclose(archivo);
  }else if(strcmp(operacion, "create_collection") == 0){  
    char ruta[100];
    char rutacoleccion[100];
    struct stat st;

    strcpy(rutacoleccion, basededatos);
    strcat(rutacoleccion, "/");
    strcat(rutacoleccion, coleccion);
    
    if(stat(rutacoleccion, &st) == 0){
       printf("El directorio de la coleccion ya existe: %s\n", rutacoleccion);
    }else{
      if(mkdir(rutacoleccion) == 0){
        printf("Directorio creado con exito: %s \n", rutacoleccion);
      }else{
        perror("Error al crear el directorio de la colección");
      }
    }

  }else{
    printf("operación no valida: %s", operacion);
  }  

  return 0;
}