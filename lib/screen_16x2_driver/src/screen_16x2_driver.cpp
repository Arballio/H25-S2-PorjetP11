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

#include "screen_16x2_driver.h"

// ================================================================================================
// ================================================================================================
//            PRIVATE DEFINE DECLARATION
// ================================================================================================
// ================================================================================================


// ================================================================================================
// ================================================================================================
//            PRIVATE MACRO DEFINITION
// ================================================================================================
// ================================================================================================

// ================================================================================================
// ================================================================================================
//            PRIVATE STRUCTURE DECLARATION
// ================================================================================================
// ================================================================================================

const int rs = 12, en = 11, d4 = 49, d5 = 47, d6 = 45, d7 = 43;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


// ================================================================================================
// ================================================================================================
//            PRIVATE VARIABLE DECLARATION
// ================================================================================================
// ================================================================================================

extern Keypad customKeypad;



// ================================================================================================
// ================================================================================================
//            PRIVATE FUNCTION DECLARATION
// ================================================================================================
// ================================================================================================

int GetNumber(int MaxNum);

// ================================================================================================
// ================================================================================================
//            PUBLIC FUNCTION SECTION
// ================================================================================================
// ================================================================================================

  menu_t Menus[5] = {0};


  Shape_t *Shape;



void InitLcd(Shape_t *p_shape)
{
    lcd.begin(16, 2);

    /* Init Shape*/

    *Shape = *p_shape;

    Shape->PosX = 0;
    Shape->PosY = 0;
    Shape->Rad = 0;
    Shape->Height = 0;
    Shape->Lenght = 0;
    Shape->NbOfSides = 0;


  
      /** Menu principal */
  Menus[0].NbLines = 4;

  strcpy(Menus[0].lines[0], "Menu Principal");Menus[0].type[0] = info;
  strcpy(Menus[0].lines[1], "Menu Shape");Menus[0].type[1] = NextPage; Menus[0].MenuPointer[1] = 1;
  strcpy(Menus[0].lines[2], "Settings");Menus[0].type[2] = NextPage; Menus[0].MenuPointer[2] = 2;
  strcpy(Menus[0].lines[3], "Restart");Menus[0].type[3] = fonction;
  /** Fin init menu**/

  /** Menu shape */
  Menus[1].NbLines = 3;

  strcpy(Menus[1].lines[0], "Cercle");Menus[1].type[0] = fonction;
  strcpy(Menus[1].lines[1], "Polygone");Menus[1].type[1] = fonction;
  strcpy(Menus[1].lines[2], "return");Menus[1].type[4] = NextPage; Menus[1].MenuPointer[4] = 0;

  /** Fin init menu**/

  /** Menu Settings */
  Menus[2].NbLines = 5;

  strcpy(Menus[2].lines[0], "Coords");Menus[2].type[0] = NextPage; Menus[2].MenuPointer[0] = 3;
  sprintf(Menus[2].lines[1], "Rad = %d",Shape->Rad);Menus[2].type[1] = fonction;
  sprintf(Menus[2].lines[2], "Height = %d",Shape->Height);Menus[2].type[2] = fonction;
  sprintf(Menus[2].lines[3], "Lenght = %d",Shape->Lenght);Menus[2].type[3] = fonction;
  sprintf(Menus[2].lines[4], "Sides: = %d",Shape->NbOfSides);Menus[2].type[4] = fonction;
  sprintf(Menus[2].lines[5], "return");Menus[2].type[4] = NextPage; Menus[2].MenuPointer[4] = 0;
  /** Fin init menu**/

  /** Menu Settings */
  Menus[3].NbLines = 3;

  sprintf(Menus[3].lines[0], "PosX = %d",Shape->PosX);Menus[2].type[1] = fonction;
  sprintf(Menus[3].lines[1], "PosY = %d",Shape->PosY);Menus[2].type[2] = fonction;
  strcpy(Menus[3].lines[2], "return");Menus[2].type[4] = NextPage; Menus[3].MenuPointer[3] = 0;
  /** Fin init menu**/

  
    
}


void printLine(char *str)
{
	//str[15] = 0;

	lcd.print(str);

}

void printLine(char c)
{
  //str[15] = 0;

  lcd.print(c);

}

//Fonction interrompante?
Function_e MenuManager(inputs_e input)
{
	static int i = 0,j = 0;
	Function_e retCode = no_func;

	switch (input){
	case MENU_DOWN:
		j++;
		j>=Menus[i].NbLines?j=0:0;
		break;
	case MENU_UP:
		j--;
		j<0?j=Menus[i].NbLines-1:0;
		break;
	case MENU_ENTER://function time baby
		if(Menus[i].type[j] == info)
		{
		//Nada
		}else if(Menus[i].type[j] == fonction)
		{
			retCode = Function_e((i<<4 | j));

		}else if(Menus[i].type[j] == NextPage)
		{
			i = Menus[i].MenuPointer[j];
			j = 0;
		}


		break;


	}
  lcd.noDisplay();
	CLEAR_SCREEN();
	printLine(Menus[i].lines[j]);
	SET_CURSOR(0,1);
	printLine(Menus[i].lines[(j+1)>=Menus[i].NbLines?0:j+1]);
  lcd.display();
  
	return retCode;
}

void ChangeSpecs(Function_e Specs){

  CLEAR_SCREEN();

  switch (Specs)
  {
    case SetRad:
      printLine("New Rad:");SET_CURSOR(0,1);
      Shape->Rad = GetNumber(3);
      sprintf(Menus[2].lines[1], "Rad = %d",Shape->Rad);
      break;
    default:
      printLine("Mistake Were made");SET_CURSOR(0,1);
      Serial.print("Specs =");Serial.println(Specs,HEX);
      break;
  }
  
  
}

// ================================================================================================
// ================================================================================================
//            PRIVATE FUNCTION SECTION
// ================================================================================================
// ================================================================================================

int GetNumber(int MaxNum)
{
  int number = 0;
  char customKey = 0;
  
  for(int i = 0; i<MaxNum;i++)
  {
    while(customKey == 0){
      customKey = customKeypad.getKey();
    }
    //delay(3);
    
    //Serial.print("Key =");Serial.println(customKey);
    
    if(customKey == '*' || customKey == '#')
    {
      break;
    } else{
      printLine(customKey);
      number = (number*10)+(customKey - '0');
      customKey = 0;
    }
    //Serial.print("Number =");Serial.println(number,DEC);
  }
  delay(300);
  MenuManager(NO_INPUT);
  return number;
}
