#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "utn.h"

int menuPrincipal(){

	int opc;

	utn_getNumero(&opc,
					"\n*****************************MENU PRINCIPAL*****************************\n\n"
							" 1. Cargar los datos de los empleados desde el archivo data.csv (modo texto).\n"
							" 2. Cargar los datos de los empleados desde el archivo data.csv (modo binario).\n"
							" 3. Alta de empleado\n"
							" 4. Modificar datos de empleado\n"
							" 5. Baja de empleado\n"
							" 6. Listar empleados\n"
							" 7. Ordenar empleados\n"
							" 8. Guardar los datos de los empleados en el archivo data.csv (modo texto).\n"
							" 9. Guardar los datos de los empleados en el archivo data.csv (modo binario).\n"
							" 10. Salir\n"
							"\n***************************************************************************\n"
							"\nElija una opcion: ",
							"\nError, no es una opcion valida\n", 1, 10, 2);

	return opc;
}

int menuModificar(){

	int opc;

	utn_getNumero(&opc,
					"\n*****************************MENU MODIFICAR*****************************\n\n"
							"1. Nombre \n"
							"2. Apellido \n"
							"3. Precio\n"
							"4. Tipo de pasajero\n"
							"5. Codigo de vuelo\n"
							"6. Estado de vuelo\n"
							"7. Regresar al menu principal\n"
					"\n**************************************************************************\n"
							"\nElija una opcion: ",
							"\nError opcion invalida", 1, 7, 2);

	return opc;
}

int menuOrdenar(){

	int opc;

	utn_getNumero(&opc,
					"\n*****************************MENU ORDENAR*****************************\n\n"
							"1. Id\n"
							"2. Nombre\n"
							"3. Apellido\n"
							"4. Precio\n"
							"5. Tipo de pasajero\n"
							"6. Codigo de vuelo\n"
							"7. Estado de vuelo\n"
							"8. Regresar al menu principal\n"
					"\n**************************************************************************\n"
							"\nElija una opcion: ",
							"\nError opcion invalida", 1, 8, 2);

	return opc;
}
