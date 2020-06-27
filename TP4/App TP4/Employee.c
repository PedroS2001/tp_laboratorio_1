#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Employee.h"
#include "utn.h"



int obtenerId(int* id)
{
    int retorno = -1;
    *id=1001 ;
    FILE* f = fopen("proximoId.bin", "rb");
    if(f!=NULL)
    {
        fread(id,sizeof(int),1,f);
        fclose(f);
        retorno = 0;
    }
}

int actualizarId(int id)
{
    int retorno = -1;
    id++;
    FILE* f = fopen("proximoId.bin", "wb");

    if(f!= NULL)
    {
        fwrite(&id, sizeof(int),1,f);
        fclose(f);
        retorno = 0;
    }

    return retorno;
}


static int isValidName(char* cadena,int longitud);

/** \brief Asigna lugar en memoria para un empleado
 *
 * \return puntero al lugar de memoria
 */

Employee* employee_new()
{
    Employee* auxiliarP;
    auxiliarP = (Employee*) malloc(sizeof(Employee));
    return auxiliarP;
}

/** \brief Asigna lugar en memoria para un empleado al que se le pasan los parametros
 *  \param Id del empleado
 *  \param nombre del empleado
 *  \param horas trabajadas por el empleado
 *  \param sueldo del empleado
 * \return puntero al lugar de memoria
 */

Employee* employee_newParametros(char* idStr,char* nombreStr,char* horasTrabajadasStr, char* sueldoStr)
{
    Employee* this;
    this = employee_new();
    if(this != NULL && idStr != NULL && nombreStr != NULL && horasTrabajadasStr != NULL && sueldoStr != NULL)
    {
        if(employee_setId(this,atoi(idStr)) == -1 ||
                employee_setNombre(this,nombreStr)  == -1 ||
                employee_setHorasTrabajadas(this,atoi(horasTrabajadasStr))  == -1 ||
                employee_setSueldo(this,atoi(sueldoStr)) == -1)
        {
            this = NULL;
        }
    }
    return this;
}

/** \brief elimina un empleado
 *
 * \param el empleado a eliminar
 *
 */

void employee_delete(Employee* this)
{
    if(this != NULL)
    {
        free(this);
        this = NULL;
    }
}

/** \brief Comprueba que el id sea valido y lo asigna al empleado
 *
 * \param   empleado al que se le asigna el id
 * \param el id a asignarle
 * \return 0 si salio bien y -1 si no
 *
 */
int employee_setId(Employee* this,int id)
{
    int retorno = -1;
    if(this != NULL && id >= 0)
    {
        retorno = 0;
        this->id = id;
    }
    return retorno;
}

/** \brief Obtiene el id de un empleado
 *
 * \param   empleado al que se le busca el id
 * \param   el lugar donde asignar el id leido
 * \return 0 si salio bien y -1 si no
 *
 */
int employee_getId(Employee* this,int* id)
{
    int retorno = -1;
    if(this != NULL && id != NULL)
    {
        retorno = 0;
        *id = this->id;
    }
    return retorno;
}

/** \brief Comprueba que el nombre sea valido y lo asigna al empleado
 *
 * \param   empleado al que se le asigna el nobmre
 * \param el nombre a asignarle
 * \return 0 si salio bien y -1 si no
 *
 */
int employee_setNombre(Employee* this,char* nombre)
{
    int retorno = -1;
    if(this != NULL && nombre != NULL)
    {
        if(isValidName(nombre,128))
        {
            retorno = 0;
            strncpy(this->nombre, nombre,128);
        }
    }
    return retorno;
}

/** \brief Obtiene el nombre de un empleado
 *
 * \param   empleado al que se le busca el nombre
 * \param   el lugar donde poner el nombre leido
 * \return 0 si salio bien y -1 si no
 *
 */
int employee_getNombre(Employee* this,char* nombre)
{
    int retorno = -1;
    if(this != NULL && nombre != NULL)
    {
        retorno = 0;
        strcpy(nombre, this->nombre);
    }
    return retorno;
}

/** \brief Comprueba que las horas trabajadas sean validas y lo asigna al empleado
 *
 * \param   empleado al que se le asigna las horas trabajadas
 * \param  las horas trabajadas a asignarle
 * \return 0 si salio bien y -1 si no
 *
 */
int employee_setHorasTrabajadas(Employee* this,int horasTrabajadas)
{
    int retorno = -1;
    if(this != NULL && horasTrabajadas > 0)
    {
        retorno = 0;
        this->horasTrabajadas = horasTrabajadas;
    }
    return retorno;
}

/** \brief Obtiene las horas trabajadas de un empleado
 *
 * \param   empleado al que se le busca las horas trabajadas
 * \param   el lugar donde poner el las horas leidas
 * \return 0 si salio bien y -1 si no
 *
 */
int employee_getHorasTrabajadas(Employee* this,int* horasTrabajadas)
{
    int retorno = -1;
    if(this != NULL && horasTrabajadas != NULL)
    {
        retorno = 0;
        *horasTrabajadas = this->horasTrabajadas ;
    }
    return retorno;

}

/** \brief Comprueba que el sueldo sea valido y lo asigna al empleado
 *
 * \param   empleado al que se le asigna el sueldo
 * \param el sueldo a asignarle
 * \return 0 si salio bien y -1 si no
 *
 */
int employee_setSueldo(Employee* this,int sueldo)
{
    int retorno = -1;
    if(this != NULL && sueldo > 0)
    {
        retorno = 0;
        this->sueldo = sueldo;
    }
    return retorno;
}

/** \brief Obtiene el sueldo de un empleado
 *
 * \param   empleado al que se le busca el sueldo
 * \param   el lugar donde poner el sueldo leido
 * \return 0 si salio bien y -1 si no
 *
 */
int employee_getSueldo(Employee* this,int* sueldo)
{
    int retorno = -1;
    if(this != NULL && sueldo != NULL)
    {
        retorno = 0;
        *sueldo = this->sueldo;
    }
    return retorno;
}

/**
 * \brief Verifica si la cadena ingresada es un nombre valido
 * \param cadena Cadena de caracteres a ser analizada
 * \return Retorna 1 (verdadero) si la cadena es valida y 0 (falso) si no lo es
 *
 */
static int isValidName(char* cadena,int longitud)
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

/** \brief ordena los empleados por id
 *
 * \param primer elemento a ordenar
 * \param segundo elemento a ordenar
 * \return 1 si el primer elemento es mayor, -1 si el segundo elemento es mayor o 0 si son iguales
 *
 */
int employee_ordenarPorId(void* item1, void* item2)
{
    int retorno;
    int id1;
    int id2;

    if(employee_getId(item1,&id1) == 0 && employee_getId(item2,&id2) == 0)
    {
        if(id1 > id2 )
        {
            retorno = 1;
        }
        else if(id1 < id2)
        {
            retorno = -1;
        }
        else
        {
            retorno = 0;
        }
    }

    return retorno;
}

/** \brief ordena los empleados por nombre
 *
 * \param primer elemento a ordenar
 * \param segundo elemento a ordenar
 * \return 1 si el primer elemento es mayor, -1 si el segundo elemento es mayor o 0 si son iguales
 *
 */
int employee_ordenarPorNombre(void* item1, void* item2)
{
    int retorno;
    char nombre1[128];
    char nombre2[128];

    if(employee_getNombre(item1,nombre1) == 0 && employee_getNombre(item2,nombre2) == 0)
    {
        retorno = stricmp(nombre1, nombre2);
    }

    return retorno;
}

/** \brief ordena los empleados por sueldo
 *
 * \param primer elemento a ordenar
 * \param segundo elemento a ordenar
 * \return 1 si el primer elemento es mayor, -1 si el segundo elemento es mayor o 0 si son iguales
 *
 */
int employee_ordenarPorSueldo(void* item1, void* item2)
{
    int retorno;
    int sueldo1;
    int sueldo2;

    if(!employee_getSueldo(item1,&sueldo1) && !employee_getSueldo(item2,&sueldo2) )
    {
        if(sueldo1 > sueldo2)
        {
            retorno = 1;
        }
        else if(sueldo1 < sueldo2)
        {
            retorno = -1;
        }
        else
        {
            retorno = 0;
        }
    }

    return retorno;
}

/** \brief ordena los empleados por horas trabajadas
 *
 * \param primer elemento a ordenar
 * \param segundo elemento a ordenar
 * \return 1 si el primer elemento es mayor, -1 si el segundo elemento es mayor o 0 si son iguales
 *
 */
int employee_ordenarPorHorasTrabajadas(void* item1, void* item2)
{
    int retorno;
    int horas1;
    int horas2;

    if(employee_getHorasTrabajadas(item1,&horas1)== 0 && employee_getHorasTrabajadas(item2,&horas2)==0)
    {
        if(horas1 > horas2)
        {
            retorno = 1;
        }
        else if(horas1 < horas2)
        {
            retorno = -1;
        }
        else
        {
            retorno = 0;
        }
    }
    return retorno;
}

int moverUnEmpleado(LinkedList* lista)
{
    int retorno= -1;
    int queIndice;
    int ultimoIndice = ll_len(lista)-1;
    int aMover;
    void* elementoMover;
    if( lista != NULL)
    {
        retorno = 0;

        printf("Ultimo indice: %d\n",ultimoIndice);

        utn_getNumero(&aMover,"Que indice quiere mover? ", "Error. No es un inidce valido\n",0,ultimoIndice,2);
        utn_getNumero(&queIndice,"En que indice quiere que este? ", "Error. No es un inidce valido\n",0,ultimoIndice,2);

        elementoMover = ll_pop(lista,aMover);
        ll_push(lista,queIndice,elementoMover);
    }

    return retorno;
}

int filtrarxRangoSueldo(void* empleado)
{
    int retorno = -1;
   // int maximo;
   // int minimo;
    Employee* auxEmpleado;
    if(empleado != NULL)
    {
        auxEmpleado = empleado;
            if(auxEmpleado->sueldo >= 30000 && auxEmpleado->sueldo <= 40000)
            {
                retorno = 0;
            }
    }
    return retorno;
}

int filtrarxRangoHoras(void* empleado)
{
    int retorno = -1;
    Employee* auxEmpleado;
    if(empleado != NULL)
    {
        auxEmpleado = empleado;
            if(auxEmpleado->horasTrabajadas >= 100 && auxEmpleado->horasTrabajadas <= 200)
            {
                retorno = 0;
            }
    }
    return retorno;
}
