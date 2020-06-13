#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Employee.h"
#include "utn.h"

static int isValidName(char* cadena,int longitud);

Employee* employee_new()
{
    Employee* auxiliarP;
    auxiliarP = (Employee*) malloc(sizeof(Employee));
    return auxiliarP;
}

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

void employee_delete(Employee* this)
{
    if(this != NULL)
    {
        free(this);
        this = NULL;
    }
}

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

