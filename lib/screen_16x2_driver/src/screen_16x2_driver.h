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
#include <Keypad.h>

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
	circle 		= 0x10,
	polynome 	= 0x11,
	SetCoords	= 0x20,
	SetRad		= 0x21,
	SetHeight	= 0x22,
	SetLenght	= 0x23,
}Function_e;


typedef enum Inputs{
	NO_INPUT = 0,
	MENU_UP = '2',
	MENU_DOWN = '8',
	MENU_LEFT = '4',
	MENU_RIGHT = '6',
	MENU_ENTER = '5',
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


typedef struct shape{
    int PosX;
    int PosY;
    int Rad;
    int Height;
    int Lenght;
    int NbOfSides;
}Shape_t;


// ================================================================================================
// ================================================================================================
//            EXTERNAL FUNCTION DECLARATION
// ================================================================================================
// ================================================================================================

void printLine(char *str);
Function_e MenuManager(inputs_e input);
void InitLcd(Shape_t *p_shape);
void ChangeSpecs(Function_e Specs);

#endif // SCREEN_16X2_DRIVER_H_INCLUDED
