#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "LinkedList.h"
#include "Controller.h"
#include "Employee.h"
#include "utn.h"

int menuPrincipal();

int main()
{
    int option = 0;
    int flagCarga = 0;
    LinkedList* listaEmpleados = ll_newLinkedList();
    do
    {
        option = menuPrincipal();
        switch(option)
        {
        case 1:
            if(!flagCarga && !controller_loadFromText("data.csv",listaEmpleados))
            {
                printf("\nSe cargaron %d empleados del archivo \"data.csv\" en modo texto\n",ll_len(listaEmpleados));
                flagCarga = 1;
            }
            else
            {
                printf("\nError al cargar el archivo \"data.csv\" en modo texto\n");
            }

            break;

        case 2:
            if(!flagCarga && !controller_loadFromBinary("data.bin",listaEmpleados))
            {
                printf("\nSe cargaron %d empleados del archivo \"data.bin\" en modo binario\n",ll_len(listaEmpleados));
                flagCarga = 1;
            }
            else
            {
                printf("Error al cargar el archivo \"data.bin\" en modo binario\n");
            }

            break;

        case 3:
            if( flagCarga && !controller_addEmployee(listaEmpleados))
            {
                printf("Se dio de alta al empleado\n");
            }
            else
            {
                printf("No se pudo dar de alta al empleado. Primero debes cargar el archivo\n");
            }

            break;

        case 4:
            if(flagCarga)
            {
                controller_editEmployee(listaEmpleados);
            }
            else
            {
                printf("Primero debe cargar el archivo\n");
            }

            break;

        case 5:
            if(flagCarga)
            {
                controller_removeEmployee(listaEmpleados);
            }
            else
            {
                printf("Error al intentar eliminar el empleado. Cargue el archivo\n");
            }

            break;

        case 6:
            if( flagCarga && !controller_ListEmployee(listaEmpleados))
            {
                printf(".\n");
            }
            else
            {
                printf("No se cargaron los datos\n");
            }
            break;

        case 7:
            if( flagCarga && !controller_sortEmployee(listaEmpleados))
            {
                printf("Empleados ordenados\n");
            }
            else
            {
                printf("No se pudieron ordenar los empleados\n");
            }

            break;

        case 8:
            if(flagCarga && !controller_saveAsText("data.csv",listaEmpleados))
            {
                printf("Datos guardados en \"data.csv\" en modo texto\n");
            }
            else
            {
                printf("No se pudo guardar los datos en \"data.csv\" en modo texto\n");
            }
            break;

        case 9:
            if(flagCarga && !controller_saveAsBinary("data.bin",listaEmpleados))
            {
                printf("Datos guardados en \"data.bin\" en modo binario\n");
            }
            else
            {
                printf("No se pudo guardar los datos en \"data.bin\" en modo binario\n");
            }
            break;

        case 10:
            printf("\nEsta saliendo\n");
            break;

        }
        system("pause");
        system("cls");
    }
    while(option != 10);
    return 0;
}

int menuPrincipal()
{
    int opcion;
    printf("1. Cargar los datos de los empleados desde el archivo data.csv (modo texto)\n");
    printf("2. Cargar los datos de los empleados desde el archivo data.csv (modo binario)\n");
    printf("3. Alta de empleado\n");
    printf("4. Modificar datos de empleado\n");
    printf("5. Baja de empleado\n");
    printf("6. Listar empleados\n");
    printf("7. Ordenar empleados\n");
    printf("8. Guardar los datos de los empleados en el archivo data.csv (modo texto)\n");
    printf("9. Guardar los datos de los empleados en el archivo data.csv (modo binario)\n");
    printf("10. Salir\n");
    utn_getNumero(&opcion,"Que desea hacer? ","Error, respuesta invalida\n",1,10,2);
    return opcion;
}
