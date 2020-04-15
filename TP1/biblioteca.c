#include <stdio.h>
#include <stdlib.h>


/** \brief Suma dos numeros
 *
 * \param primer operando a sumar
 * \param segundo operando a sumar
 * \return El resultado de la suma de los 2 operandos
 *
 */
int sumarNumeros(int a, int b)
{
    int resultado = a+b;
    return resultado;

}

/** \brief Le resta el segundo numero al primero
 *
 * \param Primer operando, a ser restado
 * \param Segundo operando a restar
 * \return la diferencia entre el primer operando y el segundo
 *
 */
int restarNumeros(int a, int b)
{
    int resultado = a-b;
    return resultado;
}

/** \brief Divide el primer numero por el segundo
 *
 * \param Primer operando, numero a dividir
 * \param Segundo operando, entre cuanto se va a dividir al primero
 * \return El resultado de la division si fue posible y si el segundo operando es 0 devuelve -1 notificando el error
 *
 */
float dividirNumeros(int a, int b)
{
    float resultado = -1;
    if(b!=0)
    {
        resultado = (float) a/b;
    }
    return resultado;
}

/** \brief Multiplica dos numeros
 *
 * \param Primer operando
 * \param Segundo operando
 * \return La multiplicacion del primer operando por el segundo
 *
 */
int multiplicarNumeros(int a, int b)
{
    int resultado = a*b;
    return resultado;
}

/** \brief Saca el factorial de un numero
 *
 * \param Numero al que le quiero calcular el factorial
 * \return El factorial del numero. En caso de ser un numero negativo notifico el errror devolviendo -1
 *
 */
int factorial (int a)
{
    int retorno = -1;
    int fact = 1;
    int i;
    if(a>=0)
    {
        for(i=1; i<=a; i++)
        {
            fact*=i;
        }
        retorno = fact;
    }
    return retorno;
}
