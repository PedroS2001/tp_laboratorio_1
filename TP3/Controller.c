#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Employee.h"
#include "parser.h"
#include "utn.h"

void listarUnEmpleado(LinkedList* lista,int indice)
{
    Employee* empleado = (Employee*) employee_new();
    int tam = ll_len(lista);

    int auxId ;
    int auxHoras ;
    int auxSueldo ;
    char auxNombre[128] ;

    for(int i=0; i<tam; i++)
    {
        empleado = ll_get(lista, i);
        employee_getId(empleado,&auxId);
        if(auxId == indice)
        {
            employee_getHorasTrabajadas(empleado,&auxHoras);
            employee_getSueldo(empleado,&auxSueldo);
            employee_getNombre(empleado,auxNombre);

            printf("%4d  %10s %10d  %15d\n", auxId, auxNombre, auxHoras, auxSueldo);
            break;
        }
    }
}


/** \brief Carga los datos de los empleados desde el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_loadFromText(char* path, LinkedList* pArrayListEmployee)
{
    int retorno = -1;
    FILE *pArchivo;

    if((pArchivo = fopen(path, "r"))!=NULL)
    {
        retorno = 0;
        parser_EmployeeFromText(pArchivo, pArrayListEmployee);
    }
    else
    {
        printf("No se pudo leer\n");
    }
    return retorno;
}

/** \brief Carga los datos de los empleados desde el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_loadFromBinary(char* path, LinkedList* pArrayListEmployee)
{
    int retorno = -1;
    FILE *pArchivo;

    if((pArchivo = fopen(path, "rb"))==NULL)
    {
        printf("No se pudo leer\n");
    }
    else
    {
        retorno = 0;
        parser_EmployeeFromBinary(pArchivo, pArrayListEmployee);
    }

    return retorno;
}

/** \brief Alta de empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_addEmployee(LinkedList* pArrayListEmployee)
{
    Employee* auxiliar = employee_new();
    int retorno = -1;
    int auxId ;
    int auxHoras ;
    int auxSueldo ;
    char auxNombre[128] ;

    int proximoId = ll_len(pArrayListEmployee) +1;

    auxId = proximoId;
    utn_getNombre(auxNombre,128,"Ingrese el nombre: ","Nombre invalido\n",2);
    utn_getNumero(&auxHoras,"Ingrese horas trabajadas(entre 10 y 350): ","Las horas estan entre 10 y 350\n",10,350,2);
    utn_getNumero(&auxSueldo,"Ingrese sueldo entre 10000 y 200000: ","Los sueldos van desde 10000 hasta 200000\n",10000,200000,2);

    employee_setId(auxiliar,auxId);
    employee_setHorasTrabajadas(auxiliar,auxHoras);
    employee_setSueldo(auxiliar,auxSueldo);
    employee_setNombre(auxiliar,auxNombre);

    if(!ll_add(pArrayListEmployee,auxiliar))
    {
        printf("Alta exitosa\n");
        retorno = 0;
    }
    else
    {
        employee_delete(auxiliar);
    }

    return retorno;
}

/** \brief Modificar datos de empleado
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_editEmployee(LinkedList* pArrayListEmployee)
{
    int retorno = -1;
    Employee* empleado;

    int idEmpleado;
    int auxId;
    char auxNombre[128];
    int auxHoras;
    int auxSueldo;
    int tam = ll_len(pArrayListEmployee);
    int i;
    int rta;

    if(pArrayListEmployee != NULL)
    {
        retorno = 0;
        utn_getNumero(&auxId,"Ingrese el id del empleado a modificar: ","No se encuentra un empleado con ese id\n",1,tam,2);
        listarUnEmpleado(pArrayListEmployee,auxId);

        for( i=0; i<tam; i++)
        {
            empleado = (Employee*) ll_get(pArrayListEmployee, i);
            employee_getId(empleado,&idEmpleado);
            if( auxId == idEmpleado )
            {
                printf("1)Nombre\n");
                printf("2)Horas trabajadas\n");
                printf("3)Sueldo\n");
                printf("4)Cancelar\n");
                utn_getNumero(&rta,"Que quiere modificar? ","Opcion invalida\n",1,4,2);
                switch(rta)
                {
                case 1:
                    utn_getNombre(auxNombre,128,"Ingrese nuevo nombre: ","Nombre invalido\n",2);
                    employee_setNombre(empleado, auxNombre);
                    break;
                case 2:
                    utn_getNumero(&auxHoras,"Ingrese nuevas horas trabajadas: ","Cantidad invalida. Van desde 10 hasta 350\n",10,350,2);
                    employee_setHorasTrabajadas(empleado, auxHoras);
                    break;
                case 3:
                    utn_getNumero(&auxSueldo,"Ingrese nuevo sueldo: ","Sueldo incorrecto.Los sueldos van desde 10000 hasta 200000",10000,200000,2);
                    employee_setSueldo(empleado, auxSueldo);
                    break;
                case 4:
                    printf("Se ha cancelado la modificacion\n");
                    break;
                }
            }
        }
    }
    return retorno;
}

/** \brief Baja de empleado
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_removeEmployee(LinkedList* pArrayListEmployee)
{
    int retorno = -1;
    Employee* empleado;
    int tam = ll_len(pArrayListEmployee);
    int i;
    int idAux;
    int idEmpleado;
    char seguro;

    if(pArrayListEmployee !=NULL)
    {
        utn_getNumero(&idAux,"ingrese ID  a remover: ","No se encuentra nadie con ese ID\n",1,tam,2);
        retorno = 0;
        for(i=0; i<tam; i++)
        {
            empleado = (Employee*) ll_get(pArrayListEmployee, i);
            employee_getId(empleado,&idEmpleado);
            if(idEmpleado == idAux)
            {
                listarUnEmpleado(pArrayListEmployee,idAux);
                do
                {
                    printf("Esta seguro(s o n)?  ");
                    fflush(stdin);
                    scanf("%c",&seguro);
                }
                while(seguro != 'n' && seguro != 's');
                if(seguro=='s')
                {
                    ll_remove(pArrayListEmployee, i);
                    printf("Empleado borrado con exito\n");
                    employee_delete(empleado);
                }
                else
                {
                    printf("Se ha cancelado la baja\n");
                }

                break;
            }
        }
    }
    return retorno;
}

/** \brief Listar empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_ListEmployee(LinkedList* pArrayListEmployee)
{
    Employee* auxiliar;
    int retorno = -1;
    int id;
    char nombre[128];
    int horasTrabajadas;
    int sueldo;
    int tamanio = ll_len(pArrayListEmployee);
    int i;
    if(pArrayListEmployee!=NULL)
    {
        if(tamanio > 0)
        {
            printf(" Id      Nombre   Horas trabajadas   Sueldo \n");

            for(i = 0; i < tamanio; i++)
            {
                auxiliar = (Employee*)ll_get(pArrayListEmployee, i);
                employee_getId(auxiliar, &id);
                employee_getNombre(auxiliar,nombre);
                employee_getHorasTrabajadas(auxiliar,&horasTrabajadas);
                employee_getSueldo(auxiliar,&sueldo);
                printf("%4d  %10s %10d  %15d\n",id, nombre, horasTrabajadas, sueldo);

            }
            retorno = 0;
        }
        else
        {
            printf("No se cargaron los datos\n");
        }
    }
    return retorno;
}

/** \brief Ordenar empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_sortEmployee(LinkedList* pArrayListEmployee)
{
    int respuesta;
    int rtaOrden;
    int retorno = -1;
    if(pArrayListEmployee!= NULL)
    {
        retorno = 0;

        printf("1)Ordenar por id\n");
        printf("2)Ordenar por nombre\n");
        printf("3)Ordenar por horas trabajadas\n");
        printf("4)Ordenar por sueldo\n");

        utn_getNumero(&respuesta,"Ingrese opcion: ","Error\n",1,5,2);
        switch(respuesta)
        {
        case 1:
            utn_getNumero(&rtaOrden,"ORDEN:\n1)Ascendente \n0)Descendente\n","ERROR\n",0,1,2);
            ll_sort(pArrayListEmployee,employee_ordenarPorId,rtaOrden);
            break;
        case 2:
            utn_getNumero(&rtaOrden,"ORDEN:\n1)Ascendente \n0)Descendente\n","ERROR\n",0,1,2);
            ll_sort(pArrayListEmployee,employee_ordenarPorNombre,rtaOrden);
            break;
        case 3:
            utn_getNumero(&rtaOrden,"ORDEN:\n1)Ascendente \n0)Descendente\n","ERROR\n",0,1,2);
            ll_sort(pArrayListEmployee,employee_ordenarPorHorasTrabajadas,rtaOrden);
            break;
        case 4:
            utn_getNumero(&rtaOrden,"ORDEN:\n1)Ascendente \n0)Descendente\n","ERROR\n",0,1,2);
            ll_sort(pArrayListEmployee,employee_ordenarPorSueldo,rtaOrden);
            break;
        }

    }

    return retorno;
}

/** \brief Guarda los datos de los empleados en el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_saveAsText(char* path, LinkedList* pArrayListEmployee)
{
    int retorno = -1;
    int i;
    FILE* fpArchivo;

    int len = ll_len(pArrayListEmployee);
    Employee* auxiliar;

    int id;
    char nombre[50];
    int horasTrabajadas;
    int sueldo;

    if(pArrayListEmployee != NULL && path != NULL)
    {
        fpArchivo = fopen(path,"w");
        if(fpArchivo != NULL)
        {
            fprintf(fpArchivo,"id,nombre,horasTrabajadas,sueldo\n"); //para volver a copiar la cabecera
            retorno = 0;
            for (i=0; i<len ; i++)
            {
                auxiliar = ll_get(pArrayListEmployee, i);
                if(!employee_getId(auxiliar,&id)&&
                        !employee_getNombre(auxiliar,nombre) &&
                        !employee_getHorasTrabajadas(auxiliar,&horasTrabajadas) &&
                        !employee_getSueldo(auxiliar,&sueldo)
                  )
                {
                    fprintf(fpArchivo,"%d,%s,%d,%d\n",id,nombre,horasTrabajadas,sueldo);
                }
            }
            fclose(fpArchivo);
        }
    }
    return retorno;
}

/** \brief Guarda los datos de los empleados en el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_saveAsBinary(char* path, LinkedList* pArrayListEmployee)
{
    int retorno = -1;
    int listLen = ll_len(pArrayListEmployee);
    int i;
    Employee* auxiliar;
    FILE* pArchivo = fopen(path,"wb");

    if(pArchivo != NULL)
    {
        if(pArrayListEmployee != NULL)
        {
            retorno = 0;
            for(i = 0; i < listLen; i++)
            {
                auxiliar = (Employee*)ll_get(pArrayListEmployee, i);
                fwrite(auxiliar,sizeof(Employee), 1, pArchivo);
            }
            printf("Archivo guardado\n");
        }
    }
    else
    {
        printf("Error al guardar\n");
    }
    fclose(pArchivo);

    return retorno;
}

