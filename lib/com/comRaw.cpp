// * Autheur: Zakary Romdhane
// * Date: 2025/03/16
// * Description: Programme Arduino pour la communcation avec un ordinateur via serial
// *              Cree pour la S2.
// *              L'envoie de donnee de la mannette est fait par matrcie de 9 bytes
#include <ComRaw.h>

Frame errorFrame = {MSG_ID_ERROR, 0, 0};

void sendMsg(Frame frame); 
Frame readMsg();
Frame readMsg(byte id);
void serialEvent();
byte convertBoolsToByte(bool p_sw[8]);
void byteToBoolArray(byte b, bool arr[8]);


void sendMsg(Frame frame) {
  // * Si le code bug et que le buffer reste rempli, decommenter les 3 lignes suivantes
  // while (Serial.available()) {
  //   Serial.read();
  // }
  
  //Creation de message
  byte msg[MSG_SIZE] = {frame.id, frame.data, frame.checksum};
  // Checksum via XOR de tous les bytes
  byte checksum = 0;
  for (int i = 0; i < MSG_SIZE-1; i++) {
    checksum ^= msg[i];
  }
  msg[MSG_SIZE-1] = checksum;

  // Envoie
  Serial.write(msg, MSG_SIZE);
  Serial.flush();

}


Frame readMsg(){
  byte msg[MSG_SIZE];
  if (Serial.available() < MSG_SIZE) { 
    //Serial.println("WARING-AR: Not enough bytes available! Message ignored");
    return errorFrame;  
  }
  int a = Serial.readBytes(msg, MSG_SIZE);
  if (a != MSG_SIZE) { 
    //Serial.println("WARING-AR: Not enough bytes read! Message ignored");
    return errorFrame; 
  }
  // if (msg[0] != MSG_ID_FROM_PC) { 
  //   Serial.println("WARING-AR: Invalid message! Message ignored");
  //   return errorFrame; 
  // }
 
  // Checksum via XOR de tous les bytes
  byte checksum = 0;
  for (int i = 0; i < MSG_SIZE - 1; i++) {
    checksum ^= msg[i];
  }
  if (checksum != msg[MSG_SIZE - 1]) { 
    //Serial.println("WARING-AR: Checksum error! Message ignored");
    return errorFrame;  
    }

  Frame frame = {msg[0], msg[1], msg[2]};
  return frame;
}

Frame readMsg(byte id){
  byte msg[MSG_SIZE];
  if (Serial.available() < MSG_SIZE) { 
    //Serial.println("WARING-AR: Not enough bytes available! Message ignored");
    return errorFrame;  
  }
  int a = Serial.readBytes(msg, MSG_SIZE);
  if (a != MSG_SIZE) { 
    //Serial.println("WARING-AR: Not enough bytes read! Message ignored");
    return errorFrame; 
  }
  if (msg[0] != id) { 
    //Serial.println("WARING-AR: Invalid message! Message ignored");
    return errorFrame; 
  }
 
  // Checksum via XOR de tous les bytes
  byte checksum = 0;
  for (int i = 0; i < MSG_SIZE - 1; i++) {
    checksum ^= msg[i];
  }
  if (checksum != msg[MSG_SIZE - 1]) { 
    //Serial.println("WARING-AR: Checksum error! Message ignored");
    return errorFrame;  
    }

  Frame frame = {msg[0], msg[1], msg[2]};
  return frame;
}

byte convertBoolsToByte(bool p_sw[]) {
  byte b = 0;
  for (int i = 0; i < (sizeof(p_sw)); i++) {
    b |= (p_sw[i] << i); // Met le bit i à 1 si p_sw[i] est vrai
  }
  return b;
}

void byteToBoolArray(byte b, bool arr[8]) {
  for (int i = 0; i < 8; i++) {
    arr[i] = (b >> i) & 1; // Met arr[i] à vrai si le bit i de b est à 1
  }
}
