#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ArrayEmployees.h"
#include "utn.h"

#define TAM 1000
#define HC 15


int menu();
int menuInformes();

int main()
{
    eEmployee empleados[TAM];

    int auxSector;
    float auxSalary;
    char auxName[51];
    char auxLastName[51];
    int respuesta ;
    int rtainformes;
    int proximoId = 1;
    int idAux;
    int orden;
    int flagCarga=0;

    initEmployees(empleados,TAM);

    if(hardcodearEmpleados(empleados,HC)==0) //Esto se descomenta si quiero hardcodear. La cantidad se asigna en el define.
    {                                       // Aumenta el proximo ID y desbloquea las opciones de modificar,baja y informes
        proximoId += HC;
        flagCarga = 1;
    }

    do
    {
        respuesta = menu();

        switch(respuesta)
        {
        case 1:
            printf("****ALTA****\n\n");
            if(findFree(empleados,TAM) == -1)   //si no encuentra lugar libre avisa
            {
                printf("No hay lugar disponible\n");
            }
            else        //si encuentra le asigna el id y permite cargar los datos
            {
                system("cls");
                printf("***ALTA***\n");
                printf("ID: %d\n",proximoId);
                if(utn_getNombre(auxName,20,"Ingrese nombre: ", "El nombre no puede tener mas de 20 letras ni contener numeros\n",2)==-1)  //cada funcion tiene su aviso en caso de que algo haya salido mal
                {
                    printf("\nERROR AL CARGAR EL NOMBRE\n\n");
                    break;
                }
                if(utn_getNombre(auxLastName,20,"Ingrese apellido: ", "El apellido no puede tener mas de 20 letras ni contener numeros\n",2)==-1)
                {
                    printf("\nERROR AL CARGAR EL APELLIDO\n\n");
                    break;
                }
                if(utn_getNumeroFlotante(&auxSalary,"Ingrese salario: ","El salario debe ser entre 1 y 9999.99\n",1,9999.99,2)==-1)
                {
                    printf("\nERROR AL CARGAR EL SALARIO\n\n");
                    break;
                }
                if(utn_getNumero(&auxSector,"Ingrese sector: ","Los sectores son del 1 al 10\n",1,10,2 )==-1)
                {
                    printf("\nERROR AL CARGAR EL SECTOR\n\n");
                    break;
                }
                if(addEmployee(empleados,TAM,proximoId,auxName,auxLastName,auxSalary,auxSector)==0)
                {
                    printf("\nEMPLEDO CARGADO PERFECTAMENTE\n");
                    proximoId++;
                    flagCarga=1;
                }
                else
                {
                    printf("No se pudo cargar\n");
                }
            }
            break;
        case 2:
            system("cls");
            printf("****MODIFICAR****\n");
            if(flagCarga==1)    //Si ya se cargo un empleado como minimo
            {
                printEmployees(empleados,TAM);      //los imprimo para que conozca los que tiene y elija el id correspondiente
                if(utn_getNumero(&idAux,"Ingrese el id del empleado que quiere modificar: ", "Id invalido\n",1,proximoId-1,2)==-1)
                {
                    printf("\nERROR. NO SE PUDO MODIFICAR\n");  //Si puso mal el id
                }
                else
                {
                    if(modifyEmployee(empleados,TAM,idAux)==-1)
                    {
                        printf("\nFALLO AL MODIFICAR\n");       //si no elije opcion correcta
                    }
                }
            }
            else    //en caso de no tener ningun empleado cargado
            {
                printf("Primero debe dar de alta a un empleado\n");
            }
            break;
        case 3:
            system("cls");
            printf("****BAJA****\n");
            if(flagCarga==1)
            {
                printEmployees(empleados,TAM);
                if(utn_getNumero(&idAux,"Ingrese el id del empleado a dar de baja: ", "Id invalido\n",1,proximoId-1,2)!=-1)
                {
                    removeEmployee(empleados,TAM,idAux);
                }
            }
            else
            {
                printf("Primero debe dar de alta algun empleado\n");
            }
            break;
        case 4:
            system("cls");
            printf("****INFORMES****\n\n");
            if(flagCarga==1)
            {
                rtainformes = menuInformes();
                if(rtainformes == 1)
                {   //
                    utn_getNumero(&orden,"Ascendente(1) o Descendente(0): ", "Error.\n", 0,1,2);
                    sortEmployees(empleados,TAM,orden);
                    printEmployees(empleados,TAM);
                }
                else if(rtainformes == 2)
                {
                    printf("\nEl total de los salarios es %.2f\n",totalSalarios(empleados,TAM));
                    printf("El promedio de los salarios es %.2f\n",promedioSalarios(empleados,TAM));
                    printf("Los empleados que superan el promedio son %d\n\n", superanPromedio(empleados,TAM));
                }
                else
                {
                    printf("\nERROR. No se pudo informar\n");
                }
            }
            else
            {
                printf("Primero debe dar de alta algun empleado\n");
            }
            break;
        case 5:
            printf("****SALIENDO****\n\n");
            break;
        }
        system("pause");
        system("cls");
    }
    while(respuesta!=5);


    return 0;
}

int menu()
{
    int respuesta;

    printf("****MENU****\n\n");
    printf("1)ALTAS\n");
    printf("2)MODIFICAR\n");
    printf("3)BAJA\n");
    printf("4)INFORMAR\n");
    printf("5)SALIR\n");
    utn_getNumero(&respuesta,"Que desea hacer? ", "Opcion incorrecta\n",1,5,2 );

    return respuesta;
}

int menuInformes()
{
    int rta;
    printf("1) Listado de los empleados ordenados alfabeticamente por Apellido y Sector\n");
    printf("2) Total y promedio de los salarios, y cuantos empleados superan el salario promedio\n");
    utn_getNumero(&rta,"Que desea hacer? ", "Opcion incorrecta\n",1,2,2 );

    return rta;
}

