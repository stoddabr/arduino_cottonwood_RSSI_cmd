#include <SoftwareSerial.h>
 
#define RXPIN 3
#define TXPIN 4
 
char command_power[]={0x18,0x03,0xFF};//const
char command_inventory_rssi[] = { 0x43 , 0x03 , 0x01 };
char command_inventory[] = { 0x31 , 0x03 , 0x01 };
char command_select_tag[] = { 0x33 , 0x0F , 0x0E , 0xFF , 0xFF , 0xFF , 0xFF , 0x0FF , 0xFF, 0xFF , 0xFF , 0xFF , 0xFF , 0x0FF , 0xFF }; 
int incomingByte;
SoftwareSerial myserial(RXPIN,TXPIN) ;
 
void setup()
{
    Serial.begin(9600);
    myserial.begin(115200);
    Serial.println( "Welcome to Cottonwood Command Document" );
    Serial.println( "Before you begin, make sure that pin 3 on the Arduino is connected to TX on Cottonwood" );
    Serial.println( "And that pin 4 on the Arduino is connected to RX on Cottonwood" );
    Serial.println( "Press p to turn on power" );
    Serial.println( "Press i to send an inventory command" );
    Serial.println( "Press r to send an inventory command with rssi value" );
}
void loop()
{
    // turn on antenna
    while(Serial.available())
    {
        incomingByte = Serial.read();
        if(incomingByte=='p')
        {
          send_command(command_power);
        }
        if(incomingByte=='i')
        {
          send_command(command_inventory_rssi);
        }
        if(incomingByte=='q')
        {
          send_command_loop( command_inventory_rssi );
        }
        if(incomingByte=='r')
        {
          send_command( command_inventory );
        }
        if(incomingByte=='s')
        {
          send_command( command_select_tag );
        }
    }
    //delay (1000);
    //
    while (myserial.available())
    {
        incomingByte = myserial.read();
        Serial.print(incomingByte,HEX);
        Serial.print( " " );
    }
}

void send_command( char com[] ){ //command array is passed
  Serial.println("");
  for( int i = 0; i<sizeof(com); i++ ){
      Serial.print( com[i] , HEX );
      Serial.print( " " );
  }
  Serial.println(" ");
  myserial.print( com );
}
void send_command_loop( char com[] ){ //command array is passed
  Serial.println("");
  char found = 0;
  while( found == 0 ){
      myserial.print( com );
      int count = 0;
      int found = 0;
      while(myserial.available()){
          incomingByte = myserial.read();
          if ( count==3 && incomingByte != 0 ){
              found = 1;    //found at least one tag tag
              Serial.print( incomingByte , HEX);
              Serial.println( " tags found");
          }
          if ( found != 0){
              Serial.print( incomingByte , HEX );
              Serial.print(" ");
          }
          count++;
      }
  } 
}
