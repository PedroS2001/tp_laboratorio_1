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
    int rtafilter;
    LinkedList* listaEmpleados = ll_newLinkedList();
    LinkedList* subLista = NULL;
    LinkedList* listaFiltrada = NULL;
    LinkedList* listaClonada = NULL;

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
            if( !ll_isEmpty(listaEmpleados) && !controller_addEmployee(listaEmpleados))
            {
                printf("Se dio de alta al empleado\n");
            }
            else
            {
                printf("No se pudo dar de alta al empleado. Primero debes cargar el archivo\n");
            }

            break;

        case 4:
            if(!ll_isEmpty(listaEmpleados))
            {
                controller_editEmployee(listaEmpleados);
            }
            else
            {
                printf("Primero debe cargar el archivo\n");
            }

            break;

        case 5:
            if(!ll_isEmpty(listaEmpleados))
            {
                controller_removeEmployee(listaEmpleados);
            }
            else
            {
                printf("Error al intentar eliminar el empleado. Cargue el archivo\n");
            }

            break;

        case 6:
            if( !ll_isEmpty(listaEmpleados) && !controller_ListEmployee(listaEmpleados))
            {
                printf(".\n");
            }
            else
            {
                printf("No se cargaron los datos\n");
            }
            break;

        case 7:
            if( !ll_isEmpty(listaEmpleados) && !controller_sortEmployee(listaEmpleados))
            {
                printf("Empleados ordenados\n");
            }
            else
            {
                printf("No se pudieron ordenar los empleados\n");
            }

            break;

        case 8:
            if(!ll_isEmpty(listaEmpleados) && !controller_saveAsText("data.csv",listaEmpleados))
            {
                printf("Datos guardados en \"data.csv\" en modo texto\n");
            }
            else
            {
                printf("No se pudo guardar los datos en \"data.csv\" en modo texto\n");
            }
            break;

        case 9:
            if(!ll_isEmpty(listaEmpleados) && !controller_saveAsBinary("data.bin",listaEmpleados))
            {
                printf("Datos guardados en \"data.bin\" en modo binario\n");
            }
            else
            {
                printf("No se pudo guardar los datos en \"data.bin\" en modo binario\n");
            }
            break;

        case 10:
            if(!ll_isEmpty(listaEmpleados))
            {
                subLista = ll_createSublist(listaEmpleados);
                if(subLista!=NULL)
                {
                    printf("Sublista creada correctamente\n");
                }
            }
            else
            {
                printf("No se cargo la lista\n");
            }
            break;

        case 11:
            if( ll_isEmpty(subLista) || controller_ListEmployee(subLista))
            {
                printf("Fallo al imprimir sublista\n");
            }
            break;

        case 12:
            if(!ll_isEmpty(listaEmpleados))
            {
                listaClonada = ll_clone(listaEmpleados);
                if(listaClonada != NULL)
                {
                    printf("Se clono la listaEmpleados con exito\n");
                }
            }
            else
            {
                printf("No se cargo la lista\n");
            }
            break;

        case 13:
            if(!ll_isEmpty(listaClonada))
            {
                controller_ListEmployee(listaClonada);
            }
            break;

        case 14:
            if(!ll_isEmpty(listaEmpleados))
            {
                utn_getNumero(&rtafilter,"Desea filtrar por Sueldo(1) o por horas trabajadas(0)? ", "Error\n",0,1,2 );
                if(rtafilter)
                {
                    listaFiltrada = ll_filter(listaEmpleados,filtrarxRangoSueldo);
                    printf("Se filtro a los empleados que tienen sueldos entre 30.000 y 40.000");
                }
                else if(!rtafilter)
                {
                    listaFiltrada = ll_filter(listaEmpleados,filtrarxRangoHoras);
                    printf("Se filtro a los empleados que tienen entre 100 y 200 horas trabajadas\n");
                }
                else
                {
                    printf("NO SE PUDO FILTRAR\n");
                }
            }
            else
            {
                printf("No se cargo la lista\n");
            }
            break;

        case 15:
            if(!ll_isEmpty(listaFiltrada))
            {
                controller_ListEmployee(listaFiltrada);
            }
            break;

        case 16:
            if(!ll_isEmpty(subLista))
            {
                moverUnEmpleado(subLista);
            }
            else
            {
                printf("No se cargo la subLista\n");
            }
            break;

        case 17:
            if(!ll_isEmpty(subLista) && !ll_isEmpty(listaFiltrada))
            {
                if(ll_containsAll(subLista,listaFiltrada))
                {
                    printf("La SubLista contiene a todos los elementos de ListaFiltrada\n");
                }
                else
                {
                    printf("La SubLista NO CONTIENE a todos los elementos de la ListaFiltrada\n");
                }
            }
            else
            {
                printf("Alguna de las 2 listas no esta cargada\n");
            }
            break;

        case 18:
            if(!ll_isEmpty(subLista) && !controller_saveAsText("subLista.csv",subLista))
            {
                printf("Datos guardados en \"subLista.csv\" en modo texto\n");
            }
            else
            {
                printf("No se pudo guardar la subLista\n");
            }
            if(!ll_isEmpty(listaFiltrada) && !controller_saveAsText("listaFiltrada.csv",listaFiltrada))
            {
                printf("Datos guardados en \"listaFiltrada.csv\" en modo texto\n");
            }
            else
            {
                printf("No se pudo guardar la listaFlitrada\n");
            }
            if(!ll_isEmpty(listaClonada) && !controller_saveAsText("listaClonada.csv",listaClonada))
            {
                printf("Datos guardados en \"listaClonada.csv\" en modo texto\n");
            }
            else
            {
                printf("No se pudo guardar la listaClonada\n");
            }

            break;



        case 0:
            printf("\nEsta saliendo\n");
            break;

        }
        system("pause");
        system("cls");
    }
    while(option != 0);




    ll_deleteLinkedList(listaEmpleados);
    ll_deleteLinkedList(listaClonada);
    ll_deleteLinkedList(listaFiltrada);
    ll_deleteLinkedList(subLista);
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
    printf("10. Crear sublista de empleados\n");
    printf("11. Imprimir sublista\n");
    printf("12. Clonar lista de empleados\n");
    printf("13. Imprimir listaClonada\n");
    printf("14. Filtrar empleados por sueldo o horas trabajadas\n");
    printf("15. Imprimir lista de empleados filtrados\n");
    printf("16. Mover un empleado en la subLista a una posicion determinada\n");
    printf("17. Verificar si la SubLista contiene a todos los elementos de la ListaFiltrada\n");
    printf("18. Guardar la SubLista, listaFiltrada y listaClonada en sus respectivos archivos\n");
    printf("0. Salir\n");
    utn_getNumero(&opcion,"Que desea hacer? ","Error, respuesta invalida\n",0,18,2);
    return opcion;
}



