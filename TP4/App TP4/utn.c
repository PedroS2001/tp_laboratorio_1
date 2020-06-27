#include <stdio.h>
#include <stdlib.h>
#include <string.h>


static int getString(char* cadena, int longitud);
static int getInt(int* pResultado);
static int esNumerica(char* cadena);
static int getFloat(float* pResultado);
static int esFlotante(char cadena[]);
static int getNombre(char* pResultado, int longitud);
static int esNombre(char* cadena, int longitud);

/** ex mygets(Ahora se llama getString) lee hasta un /0 o hasta el limite-1 para guardar el caracter terminador del array
* \brief Lee de stdin hasta que encuentra un '\n' o hasta que haya copiado en cadena un máximo de 'longitud -1' caracteres.
* \param cadena Puntero al espacio de memoria donde se copiara la cadena obtenida
* \param longitud Define el tamaño de cadena
* \return Retorna 0 (EXITO) si se obtiene una cadena y -1 (ERROR) si no
*/

static int getString(char* cadena, int longitud)      //Seria el fgets pero borrando el \n final
{
    int retorno=-1;
    char bufferString[4096]; //la unica linea que es dudosa

    if(cadena != NULL && longitud >0)
    {
        fflush(stdin);
        if(fgets(bufferString,sizeof(bufferString),stdin) != NULL)  //el fgets lee el \n tmb. Si lo lee no funciona el atoi entonces lo tenemos que sacar
        {
            //lo sacamos de la siguiente manera
            if(bufferString[strlen(bufferString)-1] == '\n')
            {
                bufferString[strlen(bufferString)-1] = '\0';
            }
            if(strlen(bufferString)<= longitud)     //una vez que ya tengo lo que necesito sin el \n la longitud de la cadena es menor a la longitud maxima que puedo obtener
            {
                // y recien ahi lo copio en la cadena
                strncpy(cadena,bufferString,longitud);
                retorno = 0;
            }
        }
    }
    return retorno;
}

/**
 * \brief Verifica si la cadena ingresada es un nombre valido
 * \param cadena Cadena de caracteres a ser analizada
 * \return Retorna 1 (verdadero) si la cadena es valida y 0 (falso) si no lo es
 *
 */
static int esNombre(char* cadena,int longitud)
{
    int i=0;
    int retorno = 1;

    if(cadena != NULL && longitud > 0)
    {
        for(i=0 ; cadena[i] != '\0' && i < longitud; i++)
        {
            if((cadena[i] < 'A' || cadena[i] > 'Z' ) && (cadena[i] < 'a' || cadena[i] > 'z' ))
            {
                retorno = 0;
                break;
            }
        }
    }
    return retorno;
}

/**
 * \brief Obtiene un string valido como nombre
 * \param pResultado Puntero al espacio de memoria donde se dejara el resultado de la funcion
 * \return Retorna 0 (EXITO) si se obtiene un numero flotante y -1 (ERROR) si no
 *
 */

static int getNombre(char* pResultado, int longitud)
{
    int retorno=-1;
    char buffer[4096];

    if(pResultado != NULL)
    {
        if( getString(buffer,sizeof(buffer))==0 && esNombre(buffer,sizeof(buffer)) && strlen(buffer) < longitud)
        {
            strncpy(pResultado,buffer,longitud);
            retorno = 0;
        }
    }
    return retorno;
}

/**
 * \brief Solicita un nombre al usuario, luego de verificarlo devuelve el resultado
 * \param pResultado Puntero al espacio de memoria donde se dejara el resultado de la funcion
 * \param longitud Es la longitud del array resultado
 * \param mensaje Es el mensaje a ser mostrado
 * \param mensajeError Es el mensaje de Error a ser mostrado
 * \param reintentos Cantidad de reintentos
 * \return Retorna 0 si se obtuvo el numero flotante y -1 si no
 *
 */

int utn_getNombre(char* pResultado, int longitud, char* mensaje, char* mensajeError,int reintentos)
{
    char bufferString[4096];
    int retorno = -1;
    while(reintentos>=0)
    {
        reintentos--;
        printf("%s",mensaje);
        if(getNombre(bufferString,sizeof(bufferString)) == 0 && strlen(bufferString) < longitud)
        {
            strncpy(pResultado,bufferString,longitud);
            retorno = 0;
            break;
        }
        printf("%s",mensajeError);
    }
    return retorno;
}

/**
* \brief Verifica si la cadena ingresada es numerica
* \param cadena Cadena de caracteres a ser analizada
* \return Retorna 1 (verdadero) si la cadena es numerica y 0 (falso) si no lo es
*/

static int esNumerica(char* cadena)
{
    int retorno = 1;
    int i=0;

    if(cadena[0] == '-')    //Si lo que hay en primer posicion(indice 0) es un signo '-', arrancaria del indice 1, sino del indice 0
    {
        i=1;
    }
    for( ; cadena[i] != '\0' ; i++) //Mientras no encuentre el caracter terminador
    {
        if(cadena[i] > '9' || cadena[i] < '0')  //Si encuentra algo que este fuera del rando de los numeros(algo que no sea un numero), devuelve 0 FALSO
        {
            retorno = 0;
            break;
        }
    }

    return retorno;
}

/**
* \brief Obtiene un numero entero
* \param pResultado Puntero al espacio de memoria donde se dejara el resultado de la funcion
* \return Retorna 0 (EXITO) si se obtiene un numero entero y -1 (ERROR) si no
*/

static int getInt(int* pResultado)
{
    int retorno=-1;
    char bufferString[64];

    if(pResultado != NULL)
    {
        if(getString(bufferString,sizeof(bufferString))==0 && esNumerica(bufferString) == 1) //valida que sea una cadena de caracteres y que sea solo numeros
        {
            *pResultado = atoi(bufferString);     //en el caso de que lo sea, convierte la cadena de caracteres a cadena de enteros
            //y el resultado lo asigna en el espacio de memoria del puntero
            retorno = 0;        //Avisa que la funcion se ejecuto con exito
        }
    }

    return retorno;
}

/**
* \brief Verifica si la cadena ingresada es flotante
* \param cadena Cadena de caracteres a ser analizada
* \return Retorna 1 (verdadero) si la cadena es flotante y 0 (falso) si no lo es
*/

static int esFlotante(char cadena[])
{
    int retorno = 1;
    int i;
    int flag = 0;
    if(cadena != NULL && strlen(cadena)>0)      //Valida que el puntero no sea nulo ni este vacio
    {
        for(i=0; cadena[i] != '\0' ; i++)   //mientras no encuentre el caracter terminador
        {
            if(i==0) //valido que si es la primer posicion, puede ser '-' o '+'
            {
                if(cadena[i] == '-' || cadena[i] == '+')
                {
                    continue;   //rompe esta iteracion pero continua dentro de la estructura iterativa
                }
            }
            if(cadena[i]< '0' || cadena[i]>'9')   //si esta fuera del rango de los numeros tiro error
            {
                if(cadena[i] == '.' && flag == 0) //a menos de que sea un punto '.' y sea el primero
                {
                    flag = 1;       //marco que encontre un punto, para que si encuentra otro arroje error
                    continue;
                }
                retorno = 0;
                break;
            }
        }
    }
    return retorno;
}

/**
* \brief Verifica si la cadena ingresada es solo numerica Flotante
* \param pResultado Puntero al espacio de memoria donde se dejara el resultado de la funcion
* \return Retorna 0 (EXITO) si se obtiene un numero entero y -1 (ERROR) si no
*/

static int getFloat(float* pResultado)
{
    int retorno=-1;
    char buffer[64];

    if(pResultado != NULL)
    {
        if(getString(buffer,sizeof(buffer))==0 && esFlotante(buffer)) //valida la cadena de caracteres y valida que sea solo numeros
        {
            *pResultado = atof(buffer);     //en el caso de que lo sea, convierte la cadena de caracteres a cadena de flotantes
            //y el resultado lo asigna en el espacio de memoria del puntero
            retorno = 0;        //Avisa que la funcion se ejecuto con exito
        }
    }

    return retorno;
}

/** \brief Solicita un numero entero al usuario, luego de verificarlo devuelve el resultado
 *
 * \param pResultado puntero a la variable en la que se asignara el numero ingresado
 * \param mensaje Mensaje a mostrar
 * \param mensajeError Mensaje que se muestra en caso de error
 * \param minimo Numero minimo permitido
 * \param maximo Numero maximo permitido
 * \param reintentos Cantidad de reintentos
 *
 * \return 0 si la funcion se ejecuto perfectamente y -1 en caso de que haya habido un error
 */

int utn_getNumero(int* pResultado, char* mensaje, char* mensajeError, int minimo, int maximo, int reintentos)
{
    int retorno = -1;    //Arranco poniendole el valor de error y se cambia a resuelto solamente si esta bien hecho
    int bufferInt;      //creo una variable para almacenar parcialmente el resultado. Solo la pasare al puntero resultado en caso de que lo que pusieron sea correcto

    if(pResultado != NULL && mensaje != NULL && mensajeError != NULL && minimo < maximo && reintentos >=0)  //Me aseguro que los punteros que me pasan no estan vacios
    {
        while(reintentos>=0)    //si le quedan reintentos entro
        {
            reintentos--;       //Quito un reintento
            printf("%s",mensaje);
            if(getInt(&bufferInt) == 0) //Me aseguro que sea un numero valido, que no tenga letras ni nada raro
            {
                if(bufferInt >= minimo && bufferInt <= maximo)  //si esta dentro del rango permitido le asigno el valor de la variable buffer al resultado y termino la iteracion
                {
                    *pResultado = bufferInt;
                    retorno = 0;
                    break;
                }
            }
            printf("%s",mensajeError);
        }
    }
    return retorno;
}

/**
* \brief Solicita un numero flotante al usuario, luego de verificarlo devuelve el resultado
*
* \param pResultado Puntero al espacio de memoria donde se dejara el resultado de la funcion
* \param mensaje Es el mensaje a ser mostrado
* \param mensajeError Es el mensaje de Error a ser mostrado
* \param minimo Es el numero minimo a ser aceptado
* \param maximo Es el minimo maximo a ser aceptado
*
* \return Retorna 0 si se obtuvo el numero flotante y -1 si no se encontro
*/

int utn_getNumeroFlotante(float* pResultado, char* mensaje, char* mensajeError, float minimo, float maximo, int reintentos)
{
    float bufferFloat;
    int retorno = -1;

    while(reintentos>=0)        //mientras tenga reintentos
    {
        reintentos--;
        printf("%s",mensaje);
        if(getFloat(&bufferFloat) == 0)     //Valida que sea un numero dentro de los flotantes
        {
            if(bufferFloat >= minimo && bufferFloat <= maximo)  //Si el numero esta dentro del rango definido
            {
                *pResultado = bufferFloat;  //asigno lo que hay dentro del buffer a el puntero pResultado y aviso que la funcion se ejecuto correctamente
                retorno = 0;
                break;
            }
        }
        printf("%s",mensajeError);
    }
    return retorno;
}

/** \brief Obtiene un caracter entre un rango determinado, con reintentos limitados
 *
 * \param puntero a la variable en la que se asignara el caracter ingresado
 * \param Mensaje a mostrar
 * \param Mensaje que se muestra en caso de error
 * \param Caracter minimo permitido
 * \param Caracter maximo permitido
 * \param Cantidad de reintentos
 *
 * \return 0 si la funcion se ejecuto perfectamente y -1 en caso de que haya habido un error
 */

int utn_getCaracter(char* pResultado, char* mensaje,char* mensajeError, char minimo,char maximo,int reintentos)
{
    int retorno = -1;
    char buffer;

    if(pResultado != NULL && mensaje != NULL && mensajeError != NULL && minimo < maximo && reintentos >=0)
    {
        do
        {
            printf("%s",mensaje);
            fflush(stdin);
            scanf("%c",&buffer);
            if(buffer>=minimo && buffer<=maximo)
            {
                *pResultado = buffer;
                retorno = 0;
                break;
            }
            else
            {
                printf("%s",mensajeError);
                reintentos--;
            }
        }
        while(reintentos>=0);
    }

    return retorno;
}


/** \brief Busca un numero dentro de un array de numeros
 *
 * \param  Numero a buscar dentro del array
 * \param  El array en el que voy a buscar el numero
 * \param  El tamaño del array
 *
 * \return Si lo encontro: devuelve el indice donde se encuentra el numero. Si no lo encontro devuelve -1
 */

int utn_buscarNumeroEnArray(int numero, int array[], int len)
{
    int indice = -1;    //arranco poniendo el indice en -1 para que en caso de no encontrar el numero devuelva eso y sea tomado como error
    int i;

    for(i=0; i<len; i++)    //recorre todo el array buscando el numero
    {
        if(array[i]==numero)    //si encuentra el numero lo pone en indice(que es lo que retorna) y hace un break
        {
            indice=i;
            break;
        }
    }
    return indice;
}

/** \brief Busca el numero mas grande dentro de un array de numeros
 *
 * \param  El array en el que voy a buscar el numero
 * \param  El tamaño del array
 *
 * \return El numero mas grande dentro del array
 */

int utn_obtenerMayorEnArray(int array[], int len)
{
    int mayor;
    int i;

    for(i=0; i<len; i++)
    {
        if(i==0 || array[i]>mayor)  //en la primer iteracion, coloca el primer numero del array como maximo. Despues a medida que vaya recorriendo el array
        {
            //solo entrara a cambiar el maximo si el numero que encontro es mayor que el que estaba en maximo
            mayor = array[i];
        }
    }
    return mayor;       //devuelve el numero mas alto encontrado
}

/** \brief Calcula el promedio de todos los numeros dentro de un array de numeros
 *
 * \param  El array del que voy a sacar el promedio
 * \param  El tamaño del array
 *
 * \return el promedio de todos los numeros dentro de el array
 */

float utn_calcularPromedioDeArray(int array[], int len)
{
    float promedio;
    int acumulador=0;
    int i;

    for(i=0; i<len; i++)
    {
        acumulador = acumulador + array[i]; //Acumula la suma de todos los numeros
    }

    promedio =(float) acumulador/len;   //la divide entre la cantidad de numeros ingresados y la devuelve

    return promedio;
}

/** \brief Imprime los indices y sus valores dentro de un array de enteros
 *
 * \param El array que quieras imprimir
 * \param El tamaño del array
 *
 * \return
 */

void utn_printArrayInt(int pArray[],int len)
{
    int i;
    for(i=0; i<len; i++)    //recorre todo el array imprimiendo los indices y su valor
    {
        printf("Indice: %d --- Valor: %d\n",i,pArray[i]);
    }
}

/** \brief Imprime los indices y sus valores dentro de un array de flotantes
 *
 * \param El array que quieras imprimir
 * \param El tamaño del array
 *
 * \return
 */

void utn_printArrayFlotante(float pArray[],int len)
{
    int i;
    for(i=0; i<len; i++)    //recorre todo el array imprimiendo los indices y su valor
    {
        printf("Indice: %d --- Valor: %.2f\n",i,pArray[i]);
    }
}

/** \brief Inicializa un array de enteros con un valor inicial
 *
 * \param El array que voy a inicializar
 * \param El tamaño del array
 * \param El valor con el que voy a inicializar todos los elementos del array
 *
 * \return Devuelve 0 Si pudo inicializar el array y -1 Si no pudo inicializar el array(xq es nulo o con tamaño invalido)
 */

int utn_initArrayInt(int pArray[], int longitud, int valorInicial)
{
    int respuesta = -1;
    int i;
    if(pArray!= NULL && longitud > 0)   //verifico que el array no este vacio y tenga un tamaño mayor a 0
    {
        respuesta = 0;
        for(i=0; i<longitud; i++) //recorro todo el array asignandole a todos los elementos un valor inicial
        {
            pArray[i] = valorInicial;
        }
    }
    return respuesta;
}

/** \brief Inicializa un array de flotantes con un valor inicial
 *
 * \param El array que voy a inicializar
 * \param El tamaño del array
 * \param El valor con el que voy a inicializar todos los elementos del array
 *
 * \return Devuelve 0 Si pudo inicializar el array y -1 Si no pudo inicializar el array(xq es nulo o con tamaño invalido)
 */

int utn_initArrayFlotante(float pArray[], int longitud, float valorInicial)
{
    int respuesta = -1;
    int i;
    if(pArray!= NULL && longitud > 0)   //verifico que el array no este vacio y tenga un tamaño mayor a 0
    {
        respuesta = 0;
        for(i=0; i<longitud; i++) //recorro todo el array asignandole a todos los elementos un valor inicial
        {
            pArray[i] = valorInicial;
        }
    }
    return respuesta;
}

/** \brief Ordena un array de enteros ascendentemente o descendentemente(0 Ascendente[de menor a mayor] y 1 descendente[de mayor a menor])
 *
 * \param El array que va a ser ordenado
 * \param El tamaño del array
 *
 * \return Devuelve 0 si se pudo ordenar con criterio o 1 si no pudo,xq le paso mal el criterio
 */

int utn_ordenarArrayInt(int vec[], int len, int criterio)
{
    int retorno=-1;
    int i;
    int j;
    int aux;

    for(i=0; i<len; i++)
    {
        for(j=i+1; j<len; j++)
        {
            if(!criterio)
            {
                if(vec[i] > vec[j])
                {
                    aux = vec[j];
                    vec[j] = vec[i];
                    vec[i] = aux;
                }
                retorno=0;
            }
            else if(criterio)
            {
                if(vec[i] < vec[j])
                {
                    aux = vec[j];
                    vec[j] = vec[i];
                    vec[i] = aux;
                }
                retorno=0;
            }
        }
    }
    return retorno;
}

/** \brief Ordena un array de flotantes ascendentemente o descendentemente(0 Ascendente[de menor a mayor] y 1 descendente[de mayor a menor])
 *
 * \param El array que va a ser ordenado
 * \param El tamaño del array
 *
 * \return Devuelve 0 si se pudo ordenar con criterio o 1 si no pudo,xq le paso mal el criterio
 */

int utn_ordenarArrayFlotante(float vec[], int len, int criterio)
{
    int retorno = -1;
    int i;
    int j;
    float aux;

    for(i=0; i<len; i++)
    {
        for(j=i+1; j<len; j++)
        {
            if(!criterio)
            {
                if(vec[i] > vec[j])
                {
                    aux = vec[j];
                    vec[j] = vec[i];
                    vec[i] = aux;
                }
                retorno = 0;
            }
            else if(criterio)
            {
                if(vec[i] < vec[j])
                {
                    aux = vec[j];
                    vec[j] = vec[i];
                    vec[i] = aux;
                }
                retorno = 0;
            }
        }
    }
    return retorno;
}
