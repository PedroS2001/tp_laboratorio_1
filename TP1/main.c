#include <stdio.h>
#include <stdlib.h>

#include "biblioteca.h"

int main()
{
    int opcion;
    int corrector = -1;
    int A = 0;
    int B = 0;
    int rsuma;
    int rresta;
    float rdivision;
    int rmultiplicacion;
    int rfactorial1;
    int rfactorial2;

    do
    {
        printf("**MENU**\n1)Ingresar 1er operando (A=%d)\n2)Ingresar 2do operando (B=%d)\n3)Calcular todas las operaciones(Suma,resta,multiplicacion,division,factorial)\n4)Informar resultados\n5)Salir\nSu Opcion: ",A,B);
        scanf("%d",&opcion);
        switch(opcion)
        {
        case 1:
            printf("Ingrese primer operando: ");
            scanf("%d",&A);
            corrector = 0;
            break;
        case 2:
            printf("Ingrese segundo operando: ");
            scanf("%d",&B);
            corrector = 0;
            break;
        case 3:
            if(corrector == 0)
            {
                rsuma = sumarNumeros(A,B);
                rresta = restarNumeros(A,B);
                rdivision = dividirNumeros(A,B);
                rmultiplicacion = multiplicarNumeros(A,B);
                rfactorial1 = factorial(A);
                rfactorial2 = factorial(B);

                printf("\nTodas las operaciones calculadas\n\n");
                corrector = 1;
            }
            else
            {
                printf("\nNo se pueden realizar las operaciones\n\n");
            }
            break;
        case 4:
            if(corrector == 1)
            {
                printf("El resultado de %d + %d es %d\n",A,B,rsuma);
                printf("El resultado de %d - %d es %d\n",A,B,rresta);
                if(rdivision==-1)
                {
                    printf("No es posible dividir por 0\n");
                }
                else
                {
                    printf("El resultado de %d / %d es %.3f\n",A,B,rdivision);
                }
                printf("El resultado de %d * %d es %d\n",A,B,rmultiplicacion);
                if(rfactorial1==-1)
                {
                    printf("El factorial de %d no existe.",A);
                }
                else
                {
                    printf("El factorial de %d es %d",A,rfactorial1);
                }
                if(rfactorial2 == -1)
                {
                    printf(" Y El factorial de %d no existe.\n\n",B);
                }
                else
                {
                    printf(" Y el factorial de %d es %d\n\n",B,rfactorial2);
                }
                break;
            case 5:
                printf("\n\nESTA SALIENDO\n\n");
                break;
            }
            else
            {
                printf("\nPrimero debe realizar las operaciones.\n\n");
            }
            break;
        }
        system("pause");
        system("cls");
    }while(opcion != 5);

    return 0;
}
