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

const int rs = 53, rw = 51, en = 49, d4 = 47, d5 = 45, d6 = 43, d7 = 41;
LiquidCrystal lcd(rs,rw, en, d4, d5, d6, d7);


// ================================================================================================
// ================================================================================================
//            PRIVATE VARIABLE DECLARATION
// ================================================================================================
// ================================================================================================



// ================================================================================================
// ================================================================================================
//            PRIVATE FUNCTION DECLARATION
// ================================================================================================
// ================================================================================================

//int GetNumber(int MaxNum);

// ================================================================================================
// ================================================================================================
//            PUBLIC FUNCTION SECTION
// ================================================================================================
// ================================================================================================

  menu_t Menus[5] = {0};


void initLcd()
{
    lcd.begin(16, 2);

  
      /** Menu principal */
  Menus[0].NbLines = 3;

  strcpy(Menus[0].lines[0], "Menu Principal");Menus[0].type[0] = info;
  strcpy(Menus[0].lines[1], "Secret level");Menus[0].type[1] = nextPage; Menus[0].MenuPointer[1] = 1;
  strcpy(Menus[0].lines[2], "Restart");Menus[0].type[3] = fonction;
  /** Fin init menu**/
  /** Menu shape */
  Menus[1].NbLines = 2;
  strcpy(Menus[1].lines[0], "Enter password");Menus[1].type[0] = fonction;
  strcpy(Menus[1].lines[1], "return");Menus[1].type[1] = nextPage; Menus[1].MenuPointer[1] = 0;
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


Function_e menuManager(inputs_e input)
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

		}else if(Menus[i].type[j] == nextPage)
		{
			i = Menus[i].MenuPointer[j];
			j = 0;
		}
		break;
  default:
      break;
	}
  CLEAR_SCREEN();
  lcd.setCursor(0, 0);
  printLine(Menus[i].lines[j]);
  lcd.setCursor(0, 1);
  printLine(Menus[i].lines[(j+1)>=Menus[i].NbLines?0:j+1]);
  
	return retCode;
}




/*void ChangeSpecs(Function_e Specs){

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
  
  
}*/

// ================================================================================================
// ================================================================================================
//            PRIVATE FUNCTION SECTION
// ================================================================================================
// ================================================================================================

/*int GetNumber(int MaxNum)
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
*/