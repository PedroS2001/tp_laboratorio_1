#ifndef UTN_H_INCLUDED
#define UTN_H_INCLUDED

/**OBTENER DATOS**/
int utn_getNumero(int* pResultado, char* mensaje, char* mensajeError, int minimo, int maximo, int reintentos);
int utn_getNumeroFlotante(float* pResultado, char* mensaje,char* mensajeError, float minimo,float maximo,int reintentos);
int utn_getCaracter(char* pResultado, char* mensaje,char* mensajeError, char minimo,char maximo,int reintentos);
int utn_getNombre(char* pResultado, int longitud, char* mensaje, char* mensajeError,int reintentos);

/** ARRAYS **/
int utn_buscarNumeroEnArray(int numero, int array[], int len);
int utn_obtenerMayorEnArray(int array[], int len);
float utn_calcularPromedioDeArray(int array[], int len);

int utn_initArrayInt(int pArray[], int longitud, int valorInicial);
int utn_initArrayFlotante(float pArray[], int longitud, float valorInicial);
void utn_printArrayInt(int pArray[],int len);
void utn_printArrayFlotante(float pArray[],int len);

int utn_ordenarArrayInt(int vec[], int len, int criterio);
int utn_ordenarArrayFlotante(float vec[], int len, int criterio);


#endif // UTN_H_INCLUDED
