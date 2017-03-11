#include <SoftwareSerial.h>
 
#define RXPIN 3
#define TXPIN 4
 
char command_inventory_rssi[] = { 0x43 , 0x03 , 0x01 };

int incomingByte;
SoftwareSerial myserial(RXPIN,TXPIN) ;
 
void setup()
{
    Serial.begin(9600);
    myserial.begin(115200);
    Serial.println( "Welcome to Cottonwood RSSI Command Center" );
    Serial.println( "Before you begin, make sure that pin 3 on the Arduino is connected to TX on Cottonwood" );
    Serial.println( "And that pin 4 on the Arduino is connected to RX on Cottonwood" );
    Serial.println( "Input r in the Arduino Serial to send an inventory command with rssi value" );
}
void loop()
{
    // turn on antenna
    while(Serial.available())
    {
        incomingByte = Serial.read();

        if(incomingByte=='r')
        {
          send_command_loop( command_inventory_rssi );
        }

    }
    //delay (1000);
    //^optinal delay
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
