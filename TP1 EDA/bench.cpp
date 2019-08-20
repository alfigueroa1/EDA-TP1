/***************************************************************************//**
  @file     +main.cpp+
  @brief    +Descripcion del archivo+
  @author   +Nombre del autor (ej: Salvador Allende)+
 ******************************************************************************/

 /*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include <stdio.h>
#include "parseLib.h"
#include "parseCallback.h"
#include "calculadora.h"

/*******************************************************************************
* CONSTANT AND MACRO DEFINITIONS USING #DEFINE
******************************************************************************/
#define NCASES 5
#define NRO_DE_PRUEBAS 20
//#define NARGS 2

/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/
static void testCmdLine(int argc_, char* argv_[], int* correctos, int* incorrectos);

 /*******************************************************************************
  *******************************************************************************
							 MAIN DE PRUEBAS
  *******************************************************************************
  ******************************************************************************/
int main(int argc, char* argv[]) {

	/*
	const char* testCase1[] = { "parse.exe", "--" };			//, 2=NARGS
	const char* testCase2[] = { "parse.exe", "suma-"};
	const char* testCase3[] = { "parse.exe", "- " };
	const char* testCase4[] = { "parse.exe", "--" };
	const char* testCase5[] = { "parse.exe","-suma", "-suma"} };
	*/
	typedef const char* argvTest[];

	//CASOS INCORRECTOS
	argvTest argvT1w = {"prueba.exe" , "-"};	//no hay clave
	argvTest argvT2w = { "prueba.exe" , "--"};	//clave sin valor
	argvTest argvT3w = { "prueba.exe" , "-", "10"};	//no hay clave
	argvTest argvT4w = { "prueba.exe" , "-opcion" };	//clave sin valor
	argvTest argvT5w = { "prueba.exe" , "valor" };	//parametro q no existe en callback
	argvTest argvT6w = { "prueba.exe" , "-sen", "2","-sen","2"};	//no permitido en callback
	argvTest argvT7w = { "prueba.exe" , "-suma", "dos" };	//valor no permitido
	argvTest argvT8w = { "prueba.exe" , "-resta", "-" };		//valor no permitido
	argvTest argvT9w = { "prueba.exe" , "-producto", "1","-producto","1"};	//no permitido en callback
	argvTest argvT10w = { "prueba.exe" , "16", "-division", "4"};	//"

	//CASOS CORRECTOS
	argvTest argvT1r = { "prueba.exe" , "-suma", "-12.3456", "-y", "-14.534", "redondeo3" };
	argvTest argvT2r = { "prueba.exe" , "-cociente", "-345", "-y", "0.12" };
	argvTest argvT3r = { "prueba.exe" , "-sen","360","-angulo","grados"};
	argvTest argvT4r = { "prueba.exe" , "-ln" , "2.7182","-nota", "Esto debería ser 1"};
	argvTest argvT5r = { "prueba.exe" , "ayuda"};
	argvTest argvT6r = { "prueba.exe" , "-raiz", "121.11011","redondeo1"};
	argvTest argvT7r = { "prueba.exe" , "-base", "12.45", "-exp","5"};
	argvTest argvT8r = { "prueba.exe" , "-modulo", "-120.23455", "redondeo4"};
	argvTest argvT9r = { "prueba.exe" , "-fact", "9.0", "-nota", "Esto es el factorial de 9"};
	argvTest argvT10r = { "prueba.exe" };


	int correctos = 0, incorrectos = 0;
	
		testCmdLine(sizeof(argvT1w)/sizeof(char*), argvT1w, &correctos, &incorrectos);
		testCmdLine(sizeof(argvT2w) / sizeof(char*), argvT2w, &correctos, &incorrectos);
		testCmdLine(sizeof(argvT3w) / sizeof(char*), argvT3w, &correctos, &incorrectos);
		testCmdLine(sizeof(argvT4w) / sizeof(char*), argvT4w, &correctos, &incorrectos);
		testCmdLine(sizeof(argvT5w) / sizeof(char*), argvT5w, &correctos, &incorrectos);
		testCmdLine(sizeof(argvT6w) / sizeof(char*), argvT6w, &correctos, &incorrectos);
		testCmdLine(sizeof(argvT7w) / sizeof(char*), argvT7w, &correctos, &incorrectos);
		testCmdLine(sizeof(argvT8w) / sizeof(char*), argvT8w, &correctos, &incorrectos);
		testCmdLine(sizeof(argvT9w) / sizeof(char*), argvT9w, &correctos, &incorrectos);
		testCmdLine(sizeof(argvT10w) / sizeof(char*), argvT10w, &correctos, &incorrectos);


	printf("Resumen de las pruebas realizadas: \n Correctos:%d  Incorrectos:%d", correctos, incorrectos);
	return 0;
} 

static void testCmdLine(int argc_, char * argv_ [] ,  int* correctos, int* incorrectos)
{
	static int nroDePrueba;
	pCallback_t pToCallback = parseCallback;
	userData_t datosPrueba;
	int check;
	check = parseCmdLine(argc_, argv_, pToCallback, &datosPrueba);

	printf("INICIO DE PRUEBA _%d_\n\n", nroDePrueba);
	if (check == -1)
	{
		(*incorrectos)++;
		printf("PRUEBA INCORRECTA\n");
	}
	else
	{
		(*correctos)++;
		calculadora(datosPrueba);
		printf("PRUEBA CORRECTA\n");
	}
	printf("\nFIN DE PRUEBA _%d_\n", nroDePrueba++);
	return;
}