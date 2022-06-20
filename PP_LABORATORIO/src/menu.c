#include <stdio.h>
#include <stdlib.h>
#include "utn.h"
#include "menu.h"

int menuPrincipal(){

	int opcion;

	utn_getNumero(&opcion,

					"\n*****************************MENU PRINCIPAL*****************************\n\n"
							"1. Carga censista: \n"
							"2. Modificar censista: \n"
							"3. Dar de baja censista: \n"
							"4. Cargar zona: \n"
							"5. Asignar zona a censar: \n"
							"6. Carga de datos: \n"
							"7. Mostrar censistas: \n"
							"8. Mostrar zonas: \n"
							"9. Carga forzada Censistas: \n"
							"10. Carga Forzada Zonas: \n"
							"11. SALIR\n"
							"\nElija una opcion: ",

					"\nError opcion invalida", 1, 13, 2);

	return opcion;
}

int menuModificar(){

	int opcion;

	utn_getNumero(&opcion,
					"\n*****************************MENU MODIFICAR*****************************\n\n"
							"1. NOMBRE \n"
							"2. APELLIDO \n"
							"3. FECHA DE NACIMIENTO\n"
							"4. EDAD\n"
							"5. DOMICILIO\n"
							"6. REGRESAR AL MENU PRINCIPAL\n"
							"\nElija una opcion: ",

					"\nError opcion invalida", 1, 6, 2);

	return opcion;
}

int menuModificarFecha(){

	int opcion;

	utn_getNumero(&opcion,
					"\n*****************************MODIFICAR FECHA DE NACIMIENTO*****************************\n\n"
							"1. DIA: \n"
							"2. MES: \n"
							"3. ANIO: \n"
							"4. VOLVER ATRAS \n"
							"\nElija una opcion: ",

							"\nError opcion invalida", 1, 4, 2);

	return opcion;
}

int menuModificarDomicilio(){

	int opcion;

	utn_getNumero(&opcion,
					"\n*****************************MODIFICAR DOMICILIO*****************************\n\n"
							"1. CALLE: \n"
							"2. ALTURA: \n"
							"3. VOLVER ATRAS \n"
							"\nElija una opcion: ",

							"\nError opcion invalida", 1, 3, 2);

	return opcion;
}
