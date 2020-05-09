#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ArrayEmployees.h"
#include "utn.h"
#include "datoshardcode.h"


/** \brief inicializa los empleados en "libre"
 * \param array de empleados
 * \param tamaño del array
 * \return -1 si tiene puntero o tamaño invalido y 0 si los pudo inicializar
 */

int initEmployees(eEmployee* list, int len)
{
    int retorno = -1;
    int i;
    if(list != NULL && len > 0) //valido que el puntero tenga algo y que tenga un tamaño valido
    {
        retorno = 0;
        for(i=0; i<len; i++)
        {
            list[i].isEmpty=1;      //inicializo todo en 1(libre)
        }
    }
    return retorno;
}

/** \brief Imprime un empleado
 * \param El empleado a imprimir los datos
 */

void printAEmployee(eEmployee list)
{
    printf("%4d  %15s   %15s    %07.2f      %d\n",list.id, list.name, list.lastName, list.salary, list.sector);
}

/** \brief Imprime el contenido del array de empleados
 * \param el array de empleados
 * \param tamaño del array
 * \return 0 si se pudo imprimir y -1 si hubo un error
 */

int printEmployees(eEmployee* list, int len)
{
    int retorno = -1;
    int i;
    if(list != NULL && len > 0)
    {
        retorno = 0;

        printf("\n*****Lista de empleados*****\n");
        printf("  ID           NOMBRE          APELLIDO    SALARIO   SECTOR\n");//Para que quede prolijito

        for(i=0; i<len; i++)
        {
            if(list[i].isEmpty == 0)
            {
                printAEmployee(list[i]);
            }
        }
    }
    return retorno;
}

/** \brief busca un lugar libre dentro del array de empleados
 *
 * \param el array de empleados
 * \param el tamaño del array
 * \return si encontro un lugar libre devuelve el indice. sino -1 para notificar que no hay
 *
 */

int findFree(eEmployee* list, int len)
{
    int retorno= -1;
    int i;
    if(list != NULL && len > 0)
    {
        for(i=0; i<len; i++)
        {
            if(list[i].isEmpty == 1)
            {
                retorno = i;        //en caso de encontrar un lugar libre devuelvo la posicion
                break;
            }
        }
    }
    return retorno;
}

/** \brief Agrega en un array de empleados existente los valores recibidos como parámetro en la primer posición libre.
 *
 * \param array de empleados
 * \param tamaño del array
 * \param id que va a recibir el empleado
 * \param nombre que va a recibir el empleado
 * \param apellido que va a recibir el empleado
 * \param salario que va a recibir el empleado
 * \param sector que va a recibir el empleado
 * \return 0 si se pudo añadir el empleado y -1 si no se pudo
 *
 */

int addEmployee(eEmployee* list, int len, int id, char name[], char lastName[], float salary, int sector)
{
    int retorno = -1;
    int indice;
    if(list != NULL && len > 0 && id > 0 && name != NULL && lastName != NULL && salary > 0 && sector >0 && sector <= 10)    //valido que todos los datos contengan algo y sea valido
    {
        retorno = 0;
        indice = findFree(list,len); //le asigno un lugar libre
                                    //copio los datos pasados por parametros al empleado en esa posicion
        list[indice].id = id;
        strcpy(list[indice].name, name);
        strcpy(list[indice].lastName, lastName);
        list[indice].salary = salary;
        list[indice].sector = sector;
        list[indice].isEmpty = 0;
    }
    return retorno;
}

/** \brief busca un empleado por el id
 *
 * \param array de empleados
 * \param tamaño del array
 * \param id que voy a buscar
 *
 * \return el id si lo encontre y sino -1
 */

int findEmployeeById(eEmployee* list, int len,int id)
{
    int retorno=-1;
    int i;
    if(list != NULL && len > 0)
    {
        for(i=0; i<len; i++)
        {
            if(list[i].id == id && list[i].isEmpty == 0)        //si encuentra el id del empleado en una posicion en la que hay un empleado devuelve su id
            {
                retorno = i;
                break;
            }
        }
    }
    return retorno;
}

/** \brief Elimina un empleado de la lista de empleados activos
 *
 * \param array de empleados
 * \param tamaño del array
 * \param id del empleado que quiero eliminar
 * \return -1 si tuvo algun error y 0 si lo pudo eliminar correctamente
 *
 */

int removeEmployee(eEmployee* list, int len, int id)
{
    int retorno=-1;
    int indice;
    char rta;
    if(list != NULL && len > 0)
    {
        indice = findEmployeeById(list,len,id);
        if(indice!= -1) //esto quiere decir que lo encontro
        {
            retorno = 0;
            system("cls");
            printf("ID      NOMBRE    APELLIDO    SALARIO   SECTOR\n");     //para que quede lindo
            printf("---------------------------------------------\n");
            printAEmployee(list[indice]);
            printf("---------------------------------------------\n");

            do
            {
                printf("\nEsta seguro que quiere eliminar este empleado(s/n)? ");   //le pregunto si esta seguro de eliminarlo
                fflush(stdin);                                                      //valido que elija si o no
                scanf("%c",&rta);
                if(rta=='s')
                {
                    list[indice].isEmpty = -1;
                    printf("Empleado eliminado\n");
                }
                else if(rta=='n')
                {
                    printf("Se ha cancelado la baja\n");
                }
                else
                {
                    printf("Respuesta incorrecta\n");
                }
            }
            while(rta != 's' && rta != 'n');
        }
        else
        {
            printf("No se ha encontrado un empleado con ese id\n");
        }
    }
    return retorno;
}

/** \brief Ordena los empleados por apellido y sector segun el orden que elija el usuario
 *
 * \param Array de empleados
 * \param Tamaño del array
 * \param Orden en el que quiere ordenar el array
 * \return 0 si lo ordeno y -1 si no pudo
 */

int sortEmployees(eEmployee* list, int len, int order)
{
    int retorno=-1;
    int i,j;
    eEmployee aux;
    if(list != NULL && len > 0 && order>=0 && order <=1)
    {
        retorno = 0;
        for(i=0; i<len; i++)
        {
            for(j=i+1; j<len; j++)
            {
                if(order == 1)  //ORDENA POR NOMBRE ASCENDENTEMENTE
                {
                    if( stricmp(list[i].lastName,list[j].lastName) > 0 )
                    {
                        aux = list[i];
                        list[i] = list[j];
                        list[j] = aux;
                    }   //SI TIENEN EL MISMO NOMBRE ORDENA POR SECTOR ASCENDENTEMENTE
                    else if(stricmp(list[i].lastName,list[j].lastName)== 0 && list[i].sector > list[j].sector);
                    {
                        aux = list[i];
                        list[i] = list[j];
                        list[j] = aux;
                    }
                }
                else if(order == 0) //ORDENA POR NOMBRE DESCENDENTEMENTE
                {
                    if( stricmp(list[i].lastName,list[j].lastName) > 0 )
                    {
                        aux = list[i];
                        list[i] = list[j];
                        list[j] = aux;
                    }   //SI TIENEN EL MISMO NOMBRE ORDENA POR SECTOR DESCENDENTEMENTE
                    else if(stricmp(list[i].lastName,list[j].lastName) == 0 && list[i].sector < list[j].sector)
                    {
                        aux = list[i];
                        list[i] = list[j];
                        list[j] = aux;
                    }
                }
            }//cierre primer for
        }//cierre segundo for
    }
    return retorno;
}

/** \brief Hardcodea los empleados asignandole los datos de la biblioteca datoshardcode
 *
 * \param Array de empleados
 * \param Cantidad a hardcodear
 */

int hardcodearEmpleados(eEmployee vec[], int cant)
{
    int i;
    if(vec != NULL && cant > 0)
    {
        for(i=0; i<cant; i++)
        {
            vec[i].id = ids[i];
            strcpy(vec[i].name,nombres[i]);
            strcpy(vec[i].lastName,apellidos[i]);
            vec[i].salary = sueldos[i];
            vec[i].sector = sectores[i];
            vec[i].isEmpty = 0;
        }
    }
    return 0;
}

/** \brief Calcula el total de los salarios de los empleados
 *
 * \param Array de empleados
 * \param Tamaño del array
 * \return La sumatoria de los salarios de todos los empleados activos
 *
 */

float totalSalarios(eEmployee* list,int len)
{
    float total = 0;
    if(list != NULL && len > 0)
    {
        for(int i=0; i<len; i++)
        {
            if(list[i].isEmpty == 0)
            {
                total += list[i].salary;
            }
        }
    }
    return total;
}

/** \brief Calcula el promedio de los salarios de los empleados
 *
 * \param Array de empleados
 * \param Tamaño del array
 * \return el promedio de los salarios de todos los empleados activos
 *
 */

float promedioSalarios(eEmployee* list, int len)
{
    float total = totalSalarios(list,len);
    float promedio = 0;
    int empleados = 0;

    if(list != NULL && len > 0)
    {
        for(int i=0; i<len; i++)
        {
            if(list[i].isEmpty == 0)
            {
                empleados++;
            }
        }
        promedio = (float)total/empleados;
    }
    return promedio;
}

/** \brief Calcula la cantidad de empleados que superan el salario promedio
 *
 * \param Array de empleados
 * \param Tamaño del array
 * \return la cantidad de empleados que superan el salario promedio
 *
 */

int superanPromedio(eEmployee* list, int len)
{
    int superan = 0;
    if(list != NULL && len > 0)
    {

        for(int i=0; i<len; i++)
        {
            if(list[i].isEmpty == 0 && list[i].salary > promedioSalarios(list,len))
            {
                superan++;
            }
        }
    }
    return superan;
}

/** \brief Modifica un empleado del array
 *
 * \param Array de empleados
 * \param Tamaño del array
 * \param Id del empleado a modificar
 * \return -1 si no encontro el empleado y 0 si lo encontro para modificar
 *
 */

int modifyEmployee(eEmployee* list, int len, int id)
{
    int retorno = -1;
    int indice;
    int modifica;

    if(list != NULL && len > 0)
    {
        indice = findEmployeeById(list,len,id);

        if(indice != -1)
        {
            system("cls");
            printf("---------------------------------------------\n");
            printAEmployee(list[indice]);
            printf("---------------------------------------------\n");

            printf("\n1)Nombre\n");
            printf("2)Apellido\n");
            printf("3)Salario\n");
            printf("4)Sector\n");
            printf("5)Cancelar\n");
            if(utn_getNumero(&modifica, "Que desea modificar? ", "Opcion incorrecta\n",1,5,2)!=-1)
            {
                retorno = 0;
                switch(modifica)
                {
                case 1:
                    utn_getNombre(list[indice].name,20,"Ingrese nuevo nombre: ", "El nombre no puede tener mas de 20 letras ni contener numeros\n",2);
                    break;
                case 2:
                    utn_getNombre(list[indice].lastName,20,"Ingrese nuevo apellido: ", "El apellido no puede tener mas de 20 letras ni contener numeros\n",2);
                    break;
                case 3:
                    utn_getNumeroFlotante(&list[indice].salary,"Ingrese nuevo salario: ","El salario debe ser entre 1 y 9999.99\n",1, 9999.99,2);
                    break;
                case 4:
                    utn_getNumero(&list[indice].sector,"Ingrese nuevo sector: ","Los sectores son del 1 al 10\n",1,10,2 );
                    break;
                case 5:
                    printf("Se ha cancelado la modificacion\n");
                    break;
                }
            }
        }
    }
    return retorno;
}
