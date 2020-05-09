#ifndef ARRAYEMPLOYEES_H_INCLUDED
#define ARRAYEMPLOYEES_H_INCLUDED

typedef struct
{
    int id;
    char name[51];
    char lastName[51];
    float salary;
    int sector;
    int isEmpty;
}eEmployee;

#endif // ARRAYEMPLOYEES_H_INCLUDED

int initEmployees(eEmployee* list, int len);

void printAEmployee(eEmployee list);
int printEmployees(eEmployee* list, int len);

int findFree(eEmployee* list, int len);
int findEmployeeById(eEmployee* list, int len, int id);

int addEmployee(eEmployee* list, int len, int id, char name[], char lastName[], float salary, int sector);
int modifyEmployee(eEmployee* list, int len, int id);
int removeEmployee(eEmployee* list, int len, int id);

int sortEmployees(eEmployee* list, int len, int order);

float totalSalarios(eEmployee* list,int len);
float promedioSalarios(eEmployee* list, int len);
int superanPromedio(eEmployee* list, int len);

int hardcodearEmpleados(eEmployee vec[], int cant);

