// ------------------------------------------------------------------------------------------------
/* BcGE Universite de Sherbrooke- usherbrooke.ca
   COPYRIGHT (c) 2017-2024 BY P16-A24-UdeSherbrooke ALL RIGHTS RESERVED. NO PART OF
   THIS PROGRAM OR PUBLICATION MAY BE REPRODUCED, TRANSMITTED, TRANSCRIBED, STORED IN A RETRIEVAL
   SYSTEM, OR TRANSLATED INTO ANY LANGUAGE OR COMPUTER LANGUAGE IN ANY FORM OR BY ANY MEANS,
   ELECTRONIC, MECHANICAL, MAGNETIC, OPTICAL, CHEMICAL, MANUAL, OR OTHERWISE, WITHOUT THE PRIOR
   WRITTEN PERMISSION OF GEGI DEPARTMENT.
*/
// ------------------------------------------------------------------------------------------------
/*!@file
   @brief

   @author Arthur Blanchard
   @version 1.0
*/
// ------------------------------------------------------------------------------------------------

#ifndef SCREEN_16X2_DRIVER_H_INCLUDED
#define SCREEN_16X2_DRIVER_H_INCLUDED

#include "stdio.h"
#include "stdint.h"
#include "string.h"
#include <LiquidCrystal.h>

// ================================================================================================
// ================================================================================================
//            DEFINE DECLARATION
// ================================================================================================
// ================================================================================================

#define SET_CURSOR(x,y) lcd.setCursor(x, y)
#define NB_MAX_LIGNE_MENU 6
#define CLEAR_SCREEN() lcd.clear()

// ================================================================================================
// ================================================================================================
//            ENUM DECLARATION
// ================================================================================================
// ================================================================================================

typedef enum{
	info,
	fonction,
	NextPage,
}LineType_e;

typedef enum Functions{
//	FUNC_NAME 	= 0x{MENU}{LIGNE},
	no_func		= 0,
}Function_e;


typedef enum Inputs{
	NO_INPUT = 0,
	MENU_UP,
	MENU_DOWN,
	MENU_LEFT,
	MENU_RIGHT,
	MENU_ENTER,
}inputs_e;



// ================================================================================================
// ================================================================================================
//            STRUCTURE DECLARATION
// ================================================================================================
// ================================================================================================

typedef struct Menu{
	int NbLines;//Nombre de ligne dans ce menu la
	char lines[NB_MAX_LIGNE_MENU][17];//Max de 5 lignes de 17 caractere incluant le \0.
	LineType_e type[NB_MAX_LIGNE_MENU];//Lets choose what the line does, next menu
	int MenuPointer[NB_MAX_LIGNE_MENU];
}menu_t;


// ================================================================================================
// ================================================================================================
//            EXTERNAL FUNCTION DECLARATION
// ================================================================================================
// ================================================================================================

void printLine(char *str);
Function_e menuManager(inputs_e input);
void initLcd();
void changeSpecs(Function_e Specs);

#endif // SCREEN_16X2_DRIVER_H_INCLUDED
