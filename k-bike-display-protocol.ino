/* Copyright (c) 2014, Nordic Semiconductor ASA
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */


/** @defgroup ble_uart_project_template ble_uart_project_template
@{
@ingroup projects
@brief Empty project that can be used as a template for new projects.

@details
This project is a firmware template for new projects.
The project will run correctly in its current state.
It can send data on the UART TX characteristic
It can receive data on the UART RX characterisitc.
With this project you have a starting point for adding your own application functionality.

The following instructions describe the steps to be made on the Windows PC:

 -# Install the Master Control Panel on your computer. Connect the Master Emulator
    (nRF2739) and make sure the hardware drivers are installed.

-# You can use the nRF UART app in the Apple iOS app store and Google Play for Android 4.3 for Samsung Galaxy S4
   with this UART template app

-# You can send data from the Arduino serial monitor, maximum length of a string is 19 bytes
   Set the line ending to "Newline" in the Serial monitor (The newline is also sent over the air

 *
 * Click on the "Serial Monitor" button on the Arduino IDE to reset the Arduino and start the application.
 * The setup() function is called first and is called only once for each reset of the Arduino.
 * The loop() function as the name implies is called in a loop.
 *
 * The setup() and loop() function are called in this way.
 * main()
 *  {
 *   setup();
 *   while(1)
 *   {
 *     loop();
 *   }
 * }
 *
 */
#include <SPI.h>
#include <RTCZero.h>
//#include <EEPROM.h>
//#include <lib_aci.h>
//#include <aci_setup.h>

#include "Adafruit_BLE.h"
#include "Adafruit_BluefruitLE_SPI.h"
#include "Adafruit_BluefruitLE_UART.h"

#include "uart_over_ble.h"
#include "cp.h"
#include "cp_if.h"

#include "iconsf.h"
//#include "icons_navigation.h"
//#include "iconsmap.h"
#include "onboardscreen.h"


#include <Arduino.h>
#include <U8g2lib.h>
//#include <SD.h>
/**
Put the nRF8001 setup in the RAM of the nRF8001.
*/
#include "services.h"


#define VERBOSE_MODE                   true

#define BUTTON_KEY                   2

#define BLUEFRUIT_HWSERIAL_NAME      Serial1
#define BLUEFRUIT_UART_MODE_PIN        6    // Set to -1 if unused
#define BUFSIZE                        128 

#define IMTU_OVERBLEUART             20  // input one unit transfer size over BLE packet
#define OMTU_OVERBLEUART             20  // output one unit transfer size over BLE packet 

#ifndef MAX
# define MAX(x, y) ((x) > (y) ? (x) : (y))
#endif


    #define FACTORYRESET_ENABLE      1

    #define MANUFACTURER_APPLE         "0x004C"
    #define MANUFACTURER_NORDIC        "0x0059"

    #define BEACON_MANUFACTURER_ID     MANUFACTURER_APPLE
    #define BEACON_UUID                "01-12-23-34-45-56-67-78-89-9A-AB-BC-CD-DE-EF-F0"
    #define BEACON_MAJOR               "0x0000"
    #define BEACON_MINOR               "0x0000"
    #define BEACON_RSSI_1M             "-54"


    #define FACTORYRESET_ENABLE         1
    #define MINIMUM_FIRMWARE_VERSION    "0.6.6"
    #define MODE_LED_BEHAVIOUR          "MODE"    
/*=========================================================================*/


//SCREEN NAVIGATION MACROS

#define   MAINMENUSCREEN1             13
#define   MAINMENUSCREEN2             14
#define   MAINMENUSCREEN3             15
#define   MAINMENUSCREEN4             16
#define   MAINMENUSCREENNAVIGATE      17

//SCREEN DM SYSTEM ALERT MACROS
#define   DMALERTSCREENLOWBAT         6
#define   DMALERTSCREENBLEDISCONN     7
#define   DMALERTSCREENBLEPAIRREQ     8
   
/**
Include the services_lock.h to put the setup in the OTP memory of the nRF8001.
This would mean that the setup cannot be changed once put in.
However this removes the need to do the setup of the nRF8001 on every reset.
*/

//U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE|U8G_I2C_OPT_DEV_0);  // I2C / TWI

//U8G2_LS027B7DH01_400x240_F_4W_SW_SPI u8g2(U8G2_R0, /* clock=*/ 9, /* data=*/ 8, /* cs=*/ 7, /* dc=*/ U8X8_PIN_NONE, /* reset=*/ U8X8_PIN_NONE);
U8G2_LS027B7DH01_400x240_F_4W_HW_SPI u8g2(U8G2_R0, /* cs=*/ 7, /* dc=*/ U8X8_PIN_NONE, /* reset=*/ U8X8_PIN_NONE);

Adafruit_BluefruitLE_UART ble(BLUEFRUIT_HWSERIAL_NAME, BLUEFRUIT_UART_MODE_PIN);


/* Create an rtc object */
RTCZero rtc;

/* Change these values to set the current initial time */
const byte seconds = 0;
const byte minutes = 19;
const byte hours = 22;

/* Change these values to set the current initial date */
const byte day = 10;
const byte month = 5;
const byte year = 17;

char timeBuffer[9];
char dateBuffer[11];



char CurrNavDistanceStr[10];

char BatteryVoltageStr[10];

byte oldgetSeconds=0;

bool toggleSecond=0;

bool newBleString=false;

byte DM_batterySOC=100;

//uint8_t bleRcvS = NULL0];
uint8_t *bleRcvStr;
int nav_icon_id=0,oldnav_icon_id=1;



bool NotfirstChar=0;
bool connectEvent=0;
bool disconnectEvent=0;
bool bleconnect=false;


int sensorValue=0;
float voltage=0;

unsigned char ScreenMenu=0,ScreenMenuOld=1;

unsigned long oldcharrxtime=0,lastBLErxtime=0;

    //screen blinking control
    unsigned long blinkPrevMillis=0;
    unsigned char blinkcontrol=0;
    


/*
Timing change state variable
*/
static bool timing_change_done          = false;

/*
Used to test the UART TX characteristic notification
*/
static uart_over_ble_t uart_over_ble;
static uint8_t         uart_buffer[MAX(IMTU_OVERBLEUART, OMTU_OVERBLEUART)];
static uint8_t         uart_buffer_len = 0;
static uint8_t         dummychar = 0;
uint8_t                passkey [6];



/* nitant - added for display protocol */
struct kbike_communication_protocol *session;
/*
Initialize the radio_ack. This is the ack received for every transmitted packet.
*/


char device_name[8];


//****************** screen  animation
//
//#define ROW_COUNT          240
//#define COLUMN_COUNT         50
//#define SCREEN_BUFF_SIZE  12000
//
//typedef enum {
//  
//  RIGHT_TRANSITION = 0x00,
//  LEFT_TRANSITION,
//  UP_TRANSITION,
//  DOWN_TRANSITION,
//  ROTATE,
//  
//}u8g2_AnimationTypeDef;
//
//typedef enum {
//
//  SPEED_1x = 0x00,
//  SPEED_2x,
//  SPEED_5x,
//  SPEED_10x,
//  SPEED_MAX
//
//}u8g2_TransitionSpeedTypeDef;
//
//void u8g2_ShowScreen(u8g2_t *u8gOutBuffer, u8g2_AnimationTypeDef screenTransition, u8g2_TransitionSpeedTypeDef speed);
//void u8g2_UpdateScreen(u8g2_t *u8gOutBuffer);
//void u8g2_ToggleScreen(u8g2_t *u8gOutBuffer, uint8_t *screen);


//######################################



////unsigned char ProcessedImage[120/8][120/8];
//typedef struct bitmapimageBig194x194
//{ 
//    bool bits[194][194];
//};
//
//typedef struct bitmapimageSmall71x71
//{ 
//    bool bits[71][71];
//};
//
//typedef union abtractimage194x194data
//{     struct bitmapimageBig bitdata;
//      unsigned char bytedata[128/8][128/8];
//};
//
//union abtractimagedata ProcessedImage;
//
//
//
////example
//
//ProcessedImage.bitdata.bits[l][k]=true;
//
//
//ProcessedImage.bytedata[0][0]
//
//
//void flipma



// A small helper
void error(const __FlashStringHelper*err) {
  Serial.println("Major Issue detected :--");
  Serial.println(err);
  while (1);
}

//Global variable use by checkbuttonPressPattern functions
unsigned long buttonPrevMillis=0;
unsigned int buttonONtime=0;
bool ButtonTapPressDetect=false;
bool ButtonShortPressDetect=false;
bool ButtonLongPressDetect=false;
bool ButtonUltraLongPressDetect=false;
bool bleModeAdafuitApps=false;




uint8_t stringComplete = 0;  // whether the string is complete
uint8_t stringIndex = 0,stringIndexOld=0;      //Initialize the index to store incoming chars

static struct communication_protocol_ind ind_callback = { .callback_ind = cp_ind_callback_ind, };

static struct communication_protocol_cfm cfm_callback = { .callback_cfm = cp_cfm_callback_cfm, };

static struct transport_cb transport_callback = { .try_send = try_send_data,}; //try_send, };



//*****************DATA FROM ANDROID PHONE ****************************
    struct current_date_time* timedat;
    struct current_maneuver_icon* CurrNavIconId;
    struct current_maneuver_distance_unit* CurrNavDistance;
    struct vehicle_battery_voltage* VehBatteryVoltage;
    struct source_name*   Trip_source_name;
    struct destination_name*   Trip_destination_name; 
    struct eta* Trip_eta;       

//dmPayloadInfo PayloadData;

  
    

void checkbuttonPressPattern(void)//detect Tapping, short and long press condition, Not acblocking call using millis HW timer, can be call on while loop
{
  //Serial.println(millis());
  if((millis()- buttonPrevMillis) > 100)//check button Every 100msec
  {
      //Serial.println(digitalRead(BUTTON_KEY));
      if(digitalRead(BUTTON_KEY)==LOW )//LOW means press button
      {
          buttonONtime++; 
          
          if(buttonONtime >= 25)//button press for 2500msec or more time is taken as Ultra Long press button
          {
            ButtonUltraLongPressDetect =true; //it should be manually reset
            buttonONtime=0;
          }
      }
      else
      {
          if(buttonONtime > 1 && buttonONtime < 2) //button press for 20msec to 150 msec is taken as Tap button 
          {
            ButtonTapPressDetect = true; //it should be manually reset
          }
          else if(buttonONtime >= 2 && buttonONtime < 10) //button press for 150msec to 1000msec is taken as short press button
          {
            ButtonShortPressDetect = true; //it should be manually reset
          }
          else if(buttonONtime >= 10 && buttonONtime < 25)//button press for 1000msec to 2.5 sec is taken as Long press button
          {
            ButtonLongPressDetect =true; //it should be manually reset
          }
          else if(buttonONtime >= 25)//button press for 2500msec or more time is taken as Ultra Long press button
          {
            ButtonUltraLongPressDetect =true; //it should be manually reset
          }

       
          buttonONtime=0;
      }
      buttonPrevMillis=millis();
  }  
 
}


void drawString(int x, int y, char *str) {

  u8g2.drawStr(x, y, str);          
  //u8g2.sendBuffer();
}





/*
 COMMENT ONLY FOR ARDUINO
 SerialEvent occurs whenever a new data comes in the
 hardware serial RX.  This routine is run between each
 time loop() runs, so using delay inside loop can delay
 response.  Multiple bytes of data may be available.
 Serial Event is NOT compatible with Leonardo, Micro, Esplora
 */

void serialBleRxControl() {
 // ble.setMode(BLUEFRUIT_MODE_DATA);
  while(ble.available() > 0 )
  {
    // get the new byte:
    dummychar = (uint8_t)ble.read();
//        Serial.print("[0x");
//          if (dummychar <= 0xF) Serial.print(F("0"));
//          Serial.print(dummychar,HEX);
//          Serial.print("]");
    if(stringComplete != 2)
    {
        uart_buffer[stringIndex++] = dummychar;


        if(stringIndex > (IMTU_OVERBLEUART-1) )//On buffer full passed data to process protocol
        {
          stringComplete = 2;
          uart_buffer_len = stringIndex;
           
           oldcharrxtime=0;
//          Serial.println("Receive succesfully 20 chunk of bytes.......");
//          Serial.println("Length : ");
//          Serial.println(stringIndex,DEC);
          return;
        }
        
    }
    stringComplete=1;    
    oldcharrxtime=millis();
  }
  if(((millis()-oldcharrxtime)> 70) && stringComplete == 1)
  {
    stringComplete = 2;
    uart_buffer_len = stringIndex;
     
     oldcharrxtime=0;
//    Serial.println("Receive succesfully timeout char rx...");
//    Serial.println("Length : ");
//    Serial.println(stringIndex,DEC);
      return;
  } 

 // ble.setMode(BLUEFRUIT_MODE_COMMAND);


}
//void serialBleRxcapture() {
//
//  while(ble.available() > 0){
//    // get the new byte:
//    dummychar = (uint8_t)ble.read();
//    if(!stringComplete)
//    {
//      if (dummychar == '\n' || dummychar == '\r')
//      {
//        // if the incoming character is a newline, set a flag
//        // so the main loop can do something about it
//        stringIndex--;
//        stringComplete = true;
//      }
//      else
//      {
//        if(stringIndex > 19)
//        {
//          Serial.println("Serial input truncated");
//          stringIndex--;
//          stringComplete = true;
//        }
//        else
//        {
//          // add it to the uart_buffer
//          uart_buffer[stringIndex] = dummychar;
//          stringIndex++;
//        }
//      }
//    }
//  }
//}
 
void serialEvent() {

  while(Serial.available() > 0){
    // get the new byte:
    dummychar = (uint8_t)Serial.read();
    if(!stringComplete)
    {
      if (dummychar == '\n')
      {
        // if the incoming character is a newline, set a flag
        // so the main loop can do something about it
        stringIndex--;
        stringComplete = true;
      }
      else
      {
        if(stringIndex > 19)
        {
          Serial.println("Serial input truncated");
          stringIndex--;
          stringComplete = true;
        }
        else
        {
          // add it to the uart_buffer
          uart_buffer[stringIndex] = dummychar;
          stringIndex++;
        }
      }
    }
  }
}

void setDeviceName(const char * deviceName)
{
  if (strlen(deviceName) > 7)
  {
    /* String too long! */
    return;
  }
  else
  {
    memcpy(device_name, deviceName, strlen(deviceName));
  }
}

int freeRam () {
  extern int __heap_start, *__brkval; 
  int v; 
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval); 
}


void processMessage(unsigned int len) {

  communication_protocol_receive_payload(session, len);  

 // Clear the old message to be ready for the new one
  for (int i=0; i<MAX(session->imtu, session->omtu); i++) 
  {
    //bleMessage[i] = ' ';
    uart_buffer[i] = ' ';
    *((session->inbuf)+i) = ' ';
  }  

  Serial.println("Message Process end");
}


//BLE Callbacks
void connectedd(void)
{
  Serial.println( F("Connected") );
    if(ScreenMenu==1)
        ScreenMenu=MAINMENUSCREEN1;
    bleconnect=true;
    lastBLErxtime=millis();
}

void disconnected(void)
{ 
  if(millis() - lastBLErxtime >2000)
  {
    Serial.println( F("Disconnected") );
      bleconnect=false;
      if(ScreenMenu!=1)
        ScreenMenu=0;
  }
}


void BleUartRX(char * data, uint16_t len)
{
    int j;
//  Serial.print( F("[BLE UART RX]" ) );
//  Serial.write(data, len);
//  Serial.println();
      uart_buffer_len=len;
      Serial.print(uart_buffer_len,DEC);
      for (j = 0; j < uart_buffer_len; j++)
      {
          Serial.print("[0x");
          if (data[j] <= 0xF) Serial.print(F("0"));
          Serial.print(data[j],HEX);
          Serial.print("]");
          *((session->inbuf)+j)=data[j];//store copy to session structure
          data[j] = 0x00;
      }
      Serial.println("}");

      if(uart_buffer_len>20)
      {
      
          Serial.println("Handle more than 20 byte of payload receive");
          processMessage(20); // call process message 
          if((uart_buffer_len-20) <= 20)
          {
              for (j = 20; j < uart_buffer_len; j++)
              {
                  Serial.print("[0x");
                  if (data[j] <= 0xF) Serial.print(F("0"));
                  Serial.print(data[j],HEX);
                  Serial.print("]");
                  *((session->inbuf)+(j-20))=data[j];//store copy to session structure
                  stringComplete=2;
              }            
          }
          else
          {
             Serial.println("*******###########ERROR_BLE !!!!!!!!!!!!!!");
          }
      }
      else
          stringComplete=2;

     lastBLErxtime=millis();
}




void setup(void)
{
  delay(1000);
  Serial.begin(115200);
  //Wait until the serial port is available (useful only for the Leonardo)
  //As the Leonardo board is not reseted every time you open the Serial Monitor
//  #if defined (__AVR_ATmega32U4__)
//    while(!Serial)
//    {}
//    delay(5000);  //5 seconds delay for enabling to see the start up comments on the serial board
//  #elif defined(__PIC32MX__)
//    delay(1000);
//  #endif


  //while (!Serial);
  delay(500);

  rtc.begin(); // initialize RTC

  // Set the time
  rtc.setHours(hours);
  rtc.setMinutes(minutes);
  rtc.setSeconds(seconds);

  // Set the date
  rtc.setDay(day);
  rtc.setMonth(month);
  rtc.setYear(year);

  
  pinMode(BUTTON_KEY, INPUT_PULLUP);
  Serial.println("Starting the CPU...............");

  // setup SD-card
//  Serial.print("Initializing SD card...");
//  if (!SD.begin(4)) {
//    Serial.println(" SD card init failed!");
//    while(true);
//  }
//  Serial.println(" SD card init done.");
  




  //Serial.println(F("Arduino setup"));
  //Serial.println(F("Set line ending to newline to send data from the serial monitor"));

  
  u8g2.begin();
  u8g2.clearBuffer();          // clear the internal memory
//  u8g2.drawBox(0,0,400,240);
//  u8g2.sendBuffer();
//  u8g2.clearBuffer();
//  u8g2.sendBuffer();
//
////  u8g2.setFont(u8g2_font_karla_22_tf); // choose a suitable font
////  u8g2.setDrawColor(2);  
//  u8g2.setFont(u8g2_font_karla_22_tf);
//  u8g2.setColorIndex(1);
//  
//  u8g2.drawStr(110,120,"WELCOME LETS RIDE !!");  // write something to the internal memory
//  u8g2.sendBuffer();
//  u8g2.clearBuffer();
//  u8g2.sendBuffer();

 
//KPIT serial protocol

//  session = communication_protocol_new(IMTU_OVERBLEUART, OMTU_OVERBLEUART, NULL, NULL, NULL);
  session = communication_protocol_new(IMTU_OVERBLEUART, OMTU_OVERBLEUART, &ind_callback, &cfm_callback, &transport_callback);
      
//  //Set the Device Name
//  memset(device_name, 0x00, 8);
//  setDeviceName("KBIKE");
//
////  u8g2.setFont(u8g2_font_karla_22_tf);
////  u8g2.setColorIndex(1);
////  u8g2.setFontRefHeightExtendedText();
////  //u8g2.setDefaultForegroundColor();
////  u8g2.setFontPosTop();


  stringComplete = 0;


  u8g2.setFontPosTop();
    u8g2.setDrawColor(0);
    
  delay(200);  

 
  ScreenMenu=0,ScreenMenuOld=1;
  nav_icon_id=0,oldnav_icon_id=1;
  newBleString=false;



  bleInitialize();



  
}

void bleInitialize(void)
{
//Enable BLE advistise mode
  if ( !ble.begin(VERBOSE_MODE) )
  {
    error(F("Couldn't find Bluefruit, make sure it's in CoMmanD mode & check wiring?"));
  }
  if ( FACTORYRESET_ENABLE )
  {
    /* Perform a factory reset to make sure everything is in a known state */
    Serial.println(F("Performing a factory reset: "));
    if ( ! ble.factoryReset() ){
      error(F("Couldn't factory reset"));
    }
  }

  if (! ble.sendCommandCheckOK(F("AT+GAPDEVNAME=KBikeBLE_DMRed")) ) {
    error(F("Could not set device name?"));
  }
  
  /* Disable command echo from Bluefruit */
  ble.echo(false);
  // check response status
    /* Print Bluefruit information */
  ble.info();

  // LED Activity command is only supported from 0.6.6
  if ( ble.isVersionAtLeast(MINIMUM_FIRMWARE_VERSION) )
  {
    // Change Mode LED Activity
    Serial.println(F("Change LED activity to " MODE_LED_BEHAVIOUR));
    ble.sendCommandCheckOK("AT+HWModeLED=" MODE_LED_BEHAVIOUR);
  }
    /* Wait for connection */
  
  Serial.println(F("******************************"));
  /* Set callbacks */
  ble.setConnectCallback(connectedd);
  ble.setDisconnectCallback(disconnected);
  ble.setBleUartRxCallback(BleUartRX);

  

  Serial.println(F("******************************"));

    ble.verbose(false);  // debug info is a little annoying after this point!
  // Set module to DATA mode
//  Serial.println( F("Switching to DATA mode!") );
 // ble.setMode(BLUEFRUIT_MODE_DATA);
}

//
//unsigned char DMState=0;
//
//#define DM_


void loop() {
 // ble.setMode(BLUEFRUIT_MODE_COMMAND);
  ble.update(150);//get status of BLE connection status, it call disconnect and connected callback inside.
  //ble.setMode(BLUEFRUIT_MODE_DATA);
  
  checkbuttonPressPattern(); //USER Switch checks...... every 10 msec

  if(ButtonTapPressDetect)
  {  
     Serial.println("******TAP detected**********");
//     bleModeAdafuitApps^=true;//toggle
     ButtonTapPressDetect=false;
     ScreenMenu++;

  }
  else if(ButtonShortPressDetect)
  { 
    Serial.println("******Short Press detected**********");
    ButtonShortPressDetect=false;
    ScreenMenu++;

  }
  else if(ButtonLongPressDetect)
  { Serial.println("******Long Press detected**********");
    ButtonLongPressDetect=false;
    //ScreenMenu++;

  }
  else if(ButtonUltraLongPressDetect)
  { Serial.println("****** Ultra Long Press detected**********");
    ButtonUltraLongPressDetect=false;
    
    u8g2.clearBuffer();
    u8g2.setDrawColor(1);
    u8g2.setFont(u8g2_font_karla_45_tf);
    u8g2.drawStr( 70,120,"bye bye ...");//u8g2_font_osb41_tn
    u8g2.setDrawColor(0);
    u8g2.sendBuffer();
    delay(2000);
    Serial.println("****** Going to sleep *********");

    
    u8g2.clearBuffer();
    u8g2.sendBuffer();
    while(digitalRead(BUTTON_KEY)==LOW );//LOW means press button, wait till release
    buttonONtime=0;
    ButtonTapPressDetect=false;
    ButtonShortPressDetect=false;
    ButtonLongPressDetect=false;
    ButtonUltraLongPressDetect=false;
    buttonONtime=0;
    while(1)
    {
       checkbuttonPressPattern(); //USER Switch checks...... every 10 msec
//       ButtonTapPressDetect=false;
//       ButtonShortPressDetect=false;
       ButtonLongPressDetect=false;
       ButtonUltraLongPressDetect=false;
       if(ButtonTapPressDetect ||ButtonShortPressDetect )
       {
          ButtonTapPressDetect=false;
          ButtonShortPressDetect=false;
          ScreenMenu=0;
          ScreenMenuOld=1;
          Serial.println("****** Wakeup from sleep *********");
          u8g2.clearBuffer(); //WelcomeScreen_bits
          u8g2.drawXBM(0, 0, 399, 239, screen1_bits);//testpenguin_bits apple_bits directionLogo1_bits
          u8g2.sendBuffer();          
          while(digitalRead(BUTTON_KEY)==LOW );//LOW means press button, wait till release
          buttonONtime=0;
          ble.flush();
          
          
          break;
       }
    }

  }



//  if(bleModeAdafuitApps)
//  {  
//    serialBleRxStrDisplay();//display directly what comes on display
//  }
//  else
//  {
//    serialBleRxControl();//buffer ble data
//  }

   // serialBleRxcapture();


    if (stringComplete==2)//byte stream of data has been recieve from phone
    {
      //Serial.println(F("Rx on BLE Uart : "));
      //Serial.print("RX data: ");
  
      

      //if(uart_buffer_len>20)
      
//      // copy clear the uart_buffer:
//      for (int j = 0; j < uart_buffer_len; j++)
//      {
//          Serial.print("[0x");
//          if (uart_buffer[j] <= 0xF) Serial.print(F("0"));
//          Serial.print(uart_buffer[j],HEX);
//          Serial.print("]");
//          *((session->inbuf)+j)=uart_buffer[j];//store copy to session structure
//          uart_buffer[j] = ' ';
//          
//      }
//      Serial.println(" ");
      stringIndex    = 0;
      stringComplete = 0;//reset rx and rearm for packet to receive    
  
      processMessage(uart_buffer_len);
    }  


    if(ScreenMenuOld!=ScreenMenu)
    { 
          
          ScreenMenuOld=ScreenMenu;
          switch(ScreenMenu)
          {
            
            case 0:               u8g2.clearBuffer(); //WelcomeScreen_bits
                                  u8g2.setDrawColor(0);
                                  u8g2.drawXBM(0, 0, 399, 239, screen1_bits);//testpenguin_bits apple_bits directionLogo1_bits
                                   
//                                  sensorValue = analogRead(ADC_BATTERY);
//                                  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 4.3V):
//                                  voltage = sensorValue * (4.3 / 1023.0);
//                                  // print out the value you read:
//                                  Serial.print("DM Battery Voltage = ");
//                                  Serial.print(voltage);
//                                  Serial.println("V");
//                                
//                                  u8g2.setFontPosTop();
//                                  //u8g2.setDrawColor(0);
//                                
//                                  u8g2.clearBuffer(); //main menu start
//                                  sprintf (dateBuffer, "DM Battery : %.2f V", voltage);
//                                  u8g2.setFont(u8g2_font_karla_35_tf);
//                                  //sprintf (timeBuffer, ":%.2d",rtc.getSeconds());
//                                  u8g2.drawStr( 30,50,dateBuffer);   
//
//                                  if(voltage >= 3.8)    
//                                    DM_batterySOC=100;
//                                  else if(voltage < 3.45)
//                                    DM_batterySOC=0;
//                                  else
//                                    DM_batterySOC=((voltage-3.45)/(3.8-3.45))*100;
//                                  
//                                  sprintf (dateBuffer, "DM SOC : %d ", DM_batterySOC);
//                                  u8g2.drawStr( 30,180,dateBuffer);  
                                                                   
                                  u8g2.sendBuffer();
                                  delay(3000);
                                  
                                  ScreenMenu++;
                                  break;

            case 1:      
//                                  u8g2.clearBuffer(); 
//                                  u8g2.setDrawColor(0);
//                                  u8g2.drawXBM(0, 0,  399, 239, screen2_bits);//testpenguin_bits apple_bits directionLogo1_bits
//                                  u8g2.setDrawColor(1);
//                                  u8g2.sendBuffer();
                                  showLetRideScreen();
                                  //delay(1000);
                                  
                                  //ScreenMenu++;
                                  break;                
//            case 2:             //Clock screen Menu
//                                  showClockScreen();
//                                  delay(1000);
//                                  
//                                  ScreenMenu++;
//                                  break;
//            case 3:             //Show welcome
//                                  showWelcomeScreen();
//                                  delay(1000);
//                                  
//                                  ScreenMenu++;
//                                  ScreenMenu++;
//                                  break;
//
//            
//            case 4:               u8g2.clearBuffer(); //main menu start
//                                  u8g2.setDrawColor(1);
//                                  //u8g2.drawXBM(200-48, 120-40, 80, 80, callrec80x80_bits);
//                                  u8g2.drawXBM(200-(70/2), 120-(70/2), 70, 70, calling70x70_bits);
//                                  //calling70x70_bits
//                                  u8g2.setDrawColor(0);
//                                  u8g2.sendBuffer();
//                                  delay(1000);
//                                  
//                                  ScreenMenu=MAINMENUSCREEN1;
//                                  break;
            case MAINMENUSCREEN1:             //Show welcome
                                  showMenu1Screen();
                                  break;                                                                  
            case MAINMENUSCREEN2:             //Show welcome
                                  showMenu2Screen();
                                  break; 
            case MAINMENUSCREEN3:             //Show welcome
                                  showMenu3Screen();
                                  break;  
            case MAINMENUSCREEN4:             //Show welcome
                                  showMenu4Screen();
                                  break;    
            case MAINMENUSCREENNAVIGATE:      //Show welcome

                                  navigationScreen();
                                  newBleString=false;
                                  oldnav_icon_id=nav_icon_id;// reset                                 
                                  break;                                      
                                                                                                     
            default:              break;                       
          }
    }
    



    if(ScreenMenu==(MAINMENUSCREENNAVIGATE+1))
    {
      ScreenMenu=MAINMENUSCREEN1;  
    }
    //screen blinking control
//    if(ScreenMenu==MAINMENUSCREEN1)
//    {
//
//          if(((millis()- blinkPrevMillis) > 1000) && blinkcontrol==0)//check button Every 25msec
//          {
//              u8g2.clearBuffer();
//              u8g2.sendBuffer();
//              blinkcontrol=1;
//          }
//          else if(((millis()- blinkPrevMillis) > 500) && blinkcontrol==1)//check button Every 25msec
//          {
//        
//            ScreenMenuOld^=0x01; //flip so that screen update with current menu screen
//             blinkcontrol=0;
//            blinkPrevMillis=millis();
//          }   
//                 
//    }

    if( (rtc.getSeconds()!= oldgetSeconds))//update second display
    {
        if(ScreenMenu==MAINMENUSCREEN1 || ScreenMenu==MAINMENUSCREEN2)
        {   
//            u8g2.setDrawColor(0);
//            
//            u8g2.setFontPosTop();
//            u8g2.drawBox(110,10,290,100);
//            u8g2.setDrawColor(1);
//            if(toggleSecond){
//              sprintf (timeBuffer, "%.2d:%.2d", rtc.getHours(), rtc.getMinutes());
//              //Serial.println("toggle 1");
//            }
//            else{
//              sprintf (timeBuffer, "%.2d.%.2d", rtc.getHours(), rtc.getMinutes());  
//              //Serial.println("toggle 0");
//            }
//            toggleSecond^=1;
//            sprintf (dateBuffer, "%.2d-%.2d-%.4d", rtc.getDay(), rtc.getMonth(), 2000 + rtc.getYear());
//
//            u8g2.setFont(u8g2_font_karla_90_tf);
//            //sprintf (timeBuffer, ":%.2d",rtc.getSeconds());
//            //u8g2.setCursor(110, 40);
//            u8g2.drawStr( 140,104-u8g2.getAscent(),timeBuffer);  
//            u8g2.setFont(u8g2_font_karla_22_tf);
//  
//            u8g2.drawStr( 150,130,dateBuffer);
//            u8g2.setDrawColor(0);   
//            u8g2.sendBuffer();
           ScreenMenuOld=0; 
        }
//        if(ScreenMenu==2)//update second display
//        {
//            // Print date...
//            sprintf (dateBuffer, "%.2d.%.2d.%.4d", rtc.getDay(), rtc.getMonth(), 2000 + rtc.getYear());
//            // ...and time
//            sprintf (timeBuffer, "%.2d:%.2d", rtc.getHours(), rtc.getMinutes());
//            u8g2.clearBuffer();
//            u8g2.setDrawColor(1);
//            u8g2.setFontPosTop();
//            u8g2.setFont(u8g2_font_karla_90_tf);  // choose a suitable font
//            u8g2_uint_t width = u8g2.getStrWidth(timeBuffer);
//            u8g2.drawStr(180 - width/2, 60, timeBuffer);  // write something to the internal memory
//            //u8g2.setFont(u8g2_font_karla_22_tf);
//            u8g2.setFont(u8g2_font_karla_90_tf);//u8g2_font_inb21_mf
//            sprintf (timeBuffer, ":%.2d",rtc.getSeconds());
//            u8g2.drawStr( (350 - (u8g2.getStrWidth(timeBuffer))/2),60,timeBuffer);
//            u8g2.setFont(u8g2_font_karla_45_tf);
//            width = u8g2.getStrWidth(dateBuffer);
//            u8g2.drawStr(200 - width/2, 160, dateBuffer);
//            u8g2.sendBuffer();  
//            u8g2.setDrawColor(0);     
//            
//        }
        
        oldgetSeconds=rtc.getSeconds();  
        
    }    

    //update navigation screen
    if((ScreenMenu==MAINMENUSCREENNAVIGATE)&&((nav_icon_id != oldnav_icon_id) ||(newBleString)))
    {
 
      navigationScreen();
      oldnav_icon_id=nav_icon_id;
      newBleString=false;
    }

//    if(bleconnect==false)
//    {
//      
//      u8g2.setDrawColor(1);
//      u8g2.drawXBM(400-35, 0, 35, 35, notlive_bits);
//      u8g2.setDrawColor(0);
//      u8g2.sendBuffer();      
//    }
//    else//drawBox(u8g2_uint_t x, u8g2_uint_t y, u8g2_uint_t w, u8g2_uint_t h)
//    {
//      u8g2.setDrawColor(0);
//      u8g2.drawBox(400-35, 0, 35, 35);
//      u8g2.setDrawColor(0);
//      u8g2.sendBuffer();      
//    }

//  ble.setMode(BLUEFRUIT_MODE_COMMAND);
  if(ble.isConnected())
  {
    if(bleconnect == false && (millis() - lastBLErxtime >2000) )
    {
        if(ScreenMenu==1)
            ScreenMenu=MAINMENUSCREEN1;
        bleconnect=true;
        Serial.println("BLE connected");
    }
  }
  else
  {
    if(bleconnect == true && (millis() - lastBLErxtime >2000))
    {
        bleconnect=false;
        Serial.println("BLE disconnected");
        if(ScreenMenu!=1)
          ScreenMenu=0;
    }
  }
//  ble.setMode(BLUEFRUIT_MODE_DATA);

//  ble.setMode(BLUEFRUIT_MODE_COMMAND);
//  if((!ble.isConnected()) && bleconnect=true)
//  {
//    bleconnect=false;
//    Serial.println("BLE disconnected");
//    if(ScreenMenu!=1)
//      ScreenMenu=0;
//  }
//  ble.setMode(BLUEFRUIT_MODE_DATA);

  
//  unsigned char DMState=DM_IDLE;
//
//#define  DM_IDLE          0
//      
//
//  Switch(DMState)
//  {
//    case 
//  }
  
    ButtonTapPressDetect=false;
    ButtonShortPressDetect=false;
    ButtonLongPressDetect=false;
    ButtonUltraLongPressDetect=false;
}




void printlnlog(const char *printdata)
{
  Serial.println(printdata);
}


void showLetRideScreen(void)
{
  int tileWidth;
  u8g2.clearBuffer();
  u8g2.setDrawColor(0);
  u8g2.drawXBM(30, 34, 70, 70, rocket70x70_bits);
  u8g2.drawXBM(30, 132, 70, 70, dmbatteryfull70xy70_bits);
  u8g2.setDrawColor(1);
//  u8g2.drawFrame(30, 34, 70, 70);
//  u8g2.drawFrame(30, 132, 70, 70);
//  u8g2.drawFrame(140,132, 218, 70);
//  u8g2.drawFrame(140, 44, 218, 60);
  u8g2.setDrawColor(1);
  u8g2.setFont(u8g2_font_karla_50_tf);
  u8g2.drawStr(140, 104-u8g2.getAscent(), "Let's ride");
  u8g2.drawBox(30,117,330,2);//draw divider line
  u8g2.setFont(u8g2_font_karla_22_tf);
  u8g2.drawStr(140, 132, "NEURON BATTERY:");
  u8g2.setFont(u8g2_font_karla_50_tf);
  sensorValue = analogRead(ADC_BATTERY);
  voltage = sensorValue * (4.3 / 1023.0);
  sprintf(dateBuffer, "0%.2f", voltage);
  u8g2.drawStr(140, 202-u8g2.getAscent(), dateBuffer);  
  tileWidth = u8g2.getStrWidth(dateBuffer);
  u8g2.setFont(u8g2_font_karla_45_tf);
  u8g2.drawStr(140+tileWidth, 202 - u8g2.getAscent(), "v"); 
  u8g2.sendBuffer();
}



void showClockScreen()
{
  u8g2.clearBuffer();
//  u8g2.setDrawColor(0);
//  u8g2.drawBox(0,0,400,240);
  u8g2.setDrawColor(1);
//  u8g2.setFontMode(0);

  // Print date...
  sprintf (dateBuffer, "%.2d.%.2d.%.4d", rtc.getDay(), rtc.getMonth(), 2000 + rtc.getYear());
  // ...and time
  sprintf (timeBuffer, "%.2d:%.2d", rtc.getHours(), rtc.getMinutes());
  u8g2.setDrawColor(1);
  u8g2.setFontPosTop();
  u8g2.setFont(u8g2_font_karla_90_tf);  // choose a suitable font
  u8g2_uint_t width = u8g2.getStrWidth(timeBuffer);
  u8g2.drawStr(180 - width/2, 60, timeBuffer);  // write something to the internal memory
  //u8g2.setFont(u8g2_font_karla_22_tf);
  u8g2.setFont(u8g2_font_karla_22_tf);//u8g2_font_inb21_mf
  sprintf (timeBuffer, ":%.2d",rtc.getSeconds());
  u8g2.drawStr( (350 - (u8g2.getStrWidth(timeBuffer))/2),60,timeBuffer);
  u8g2.setFont(u8g2_font_karla_45_tf);
  width = u8g2.getStrWidth(dateBuffer);
  u8g2.drawStr(200 - width/2, 160, dateBuffer);
  u8g2.sendBuffer();  
  u8g2.setDrawColor(0);
}

void showWelcomeScreen()
{
  char charbuffer[20];
  u8g2.clearBuffer();
  u8g2.setDrawColor(0);
  u8g2.drawXBM(20, 20, 70, 70, rocket70x70_bits);//draw upper left with ridelogo
  u8g2.drawXBM(20, 140, 70, 70, dmbatteryfull70xy70_bits);//draw lower left with batteryDM80x80_bits
  u8g2.setDrawColor(1);
  u8g2.setFontMode(0);
  
  u8g2.drawBox(20,120-2,360,4);//draw divider line
  u8g2.setFontPosTop();
  //u8g2.setFont(u8g2_font_karla_45_tf);
  

  //u8g2.drawStr(110,100,charbuffer);

  u8g2.setFont(u8g2_font_karla_35_tf);//u8g2_font_inb21_mf
 //sprintf (timeBuffer, ":%.2d",rtc.getSeconds());
  u8g2.drawStr( 110,60,"Let's ride");

  u8g2.setFont(u8g2_font_karla_22_tf);
  u8g2.drawStr( 130,60+70," DM BATTERY");
  
  u8g2.setFont(u8g2_font_karla_45_tf);
  u8g2.drawStr( 110,60+100," 100 %");//u8g2_font_osb41_tn
  u8g2.setDrawColor(0);

    
  u8g2.sendBuffer(); 

}

void showMenu1Screen()
{
  char charbuffer[20];
  u8g2.clearBuffer();
  u8g2.setDrawColor(0);
  u8g2.drawXBM(30, 34, 70, 70, estimatedclock70x70_bits);//draw upper left with ridelogo
  u8g2.drawXBM(30, 132, 70, 70, currentlocation70x70_bits);//draw lower left with batteryDM80x80_bits
  u8g2.setDrawColor(1);
  u8g2.setFontMode(0);
  
  u8g2.drawBox(30,117,328,4);//draw divider line
  u8g2.setFontPosTop();
  //u8g2.setFont(u8g2_font_karla_45_tf);
  sprintf (dateBuffer, "%.2d-%.2d-%.4d", rtc.getDay(), rtc.getMonth(), 2000 + rtc.getYear());
  
  sprintf (timeBuffer, "%.2d:%.2d", rtc.getHours(), rtc.getMinutes());

  u8g2.setFont(u8g2_font_karla_90_tf);
  
  u8g2.drawStr( 140,104-u8g2.getAscent(),timeBuffer);

  u8g2.setFont(u8g2_font_karla_22_tf);
  
  u8g2.drawStr( 150,130,dateBuffer);
  
  u8g2.drawStr( 110,160," KPIT Technologies Pune");
  
  u8g2.setDrawColor(0);

  u8g2.drawXBM(160, 240-20, 89, 8, oneoutoffivedots89x7_75_bits);
  
  u8g2.sendBuffer(); 

}

void showMenu2Screen()
{
  char charbuffer[20];
  u8g2.clearBuffer();
  u8g2.setDrawColor(0);
  u8g2.drawXBM(30, 34, 70, 70, estimatedtime70x70_bits);//draw upper left with ridelogo
  u8g2.drawXBM(30, 132, 70, 70, estimateddistance70x70_bits);//draw lower left with batteryDM80x80_bits
  u8g2.setDrawColor(1);
  u8g2.setFontMode(0);
  
  u8g2.drawBox(30,117,328,4);//draw divider line
  u8g2.setFontPosTop();

  sprintf (dateBuffer, "%.2d-%.2d-%.4d", rtc.getDay(), rtc.getMonth(), 2000 + rtc.getYear());
  
  sprintf (timeBuffer, "%.2d:%.2d", rtc.getHours(), rtc.getMinutes());

  u8g2.setFont(u8g2_font_karla_90_tf);
  u8g2.drawStr( 140,104-u8g2.getAscent(),timeBuffer);

  u8g2.setFont(u8g2_font_karla_22_tf);
  u8g2.drawStr( 150,130,dateBuffer);

  u8g2.setFont(u8g2_font_karla_35_tf);
  u8g2.drawStr( 110,60+100," 400 m");//u8g2_font_osb41_tn

  u8g2.setDrawColor(0);


  u8g2.drawXBM(160, 240-20, 89, 8, twooutoffivedots89x7_75_75_bits);
  

    
  u8g2.sendBuffer(); 

}

void showMenu3Screen()
{
  char charbuffer[20];
  u8g2.clearBuffer();
  u8g2.setDrawColor(0);
  u8g2.drawXBM(30, 34, 70, 70, fuel70x70_bits);//draw upper left with ridelogo
  u8g2.drawXBM(30, 132, 70, 70, batteryfull70x70_bits);//draw lower left with batteryDM80x80_bits
  u8g2.setDrawColor(1);
  u8g2.setFontMode(0);
  
  u8g2.drawBox(30,117,328,4);//draw divider line
  u8g2.setFontPosTop();

  
  u8g2.setFont(u8g2_font_karla_45_tf);

  u8g2.drawStr( 110,40,"12Liter");//u8g2_font_osb41_tn
  u8g2.drawStr( 110,60+100," 87 %");//u8g2_font_osb41_tn

  u8g2.setFont(u8g2_font_karla_22_tf);
  u8g2.drawStr( 120,130,"VEHICLE BATTERY");

  u8g2.setDrawColor(0);


  u8g2.drawXBM(160, 240-20, 89, 8, threeoutoffivedots89x7_75_bits);
  

    
  u8g2.sendBuffer(); 

}

void showMenu4Screen()
{
  char charbuffer[20];
  u8g2.clearBuffer();
  u8g2.setDrawColor(0);
  u8g2.drawXBM(165, 35, 70, 70, settingsclog70x70_80_bits); 
  u8g2.setDrawColor(1);
  u8g2.setFontMode(0);
  u8g2.setFontPosTop();

  u8g2.setFont(u8g2_font_karla_45_tf);

  u8g2.drawStr( 100,130,"Settings");
  
//  u8g2.setFont(u8g2_font_karla_45_tf);
//  u8g2.drawStr( 110,60+100," 100 %");//u8g2_font_osb41_tn

  u8g2.setDrawColor(0);


  u8g2.drawXBM(160, 240-20, 89, 8, fouroutoffivedots89x7_75_bits);
  

    
  u8g2.sendBuffer(); 

}

void navigationScreen()
{
  //if(newBleString!=true)
  u8g2.clearBuffer();

  switch(nav_icon_id)
  {
    case 1 :  //iconType.contains("head") || iconType.contains("straight") || iconType.isEmpty() || iconType.equals("") || iconType.equals(" ") || iconType == null
              u8g2.setDrawColor(0);
              //u8g2.drawXBM(280+24, 25, 71, 71, straight71x71_bits);
              u8g2.drawXBM(15, 18, 169, 194, arrowroundaboutstraight169x194px_bits);
              u8g2.setDrawColor(1);              
              break;
    case 2 :  //iconType.contains("turn-left")
              u8g2.setDrawColor(0);
              u8g2.setDisplayRotation(U8G2_MIRROR);//mirror the image
              //u8g2.drawXBM(400-((280+24)+71), 25, 71, 71, right71x71_bits); //render navigation small icons with 
              u8g2.drawXBM(400-(10 +194), 23, 169, 194, arrowright169x194px_bits); //render navigation large icons
              u8g2.setDisplayRotation(U8G2_R0);
              u8g2.setDrawColor(1);
              break;
    case 3 :  //iconType.contains("turn-right")
              u8g2.setDrawColor(0);
              //u8g2.drawXBM(280+24, 25, 71, 71, right71x71_bits);
              u8g2.drawXBM(15, 18, 169, 194, arrowright169x194px_bits);
              u8g2.setDrawColor(1);            

              break;              
    case 4 :  //iconType.contains("move-left")
              u8g2.setDrawColor(0);
              u8g2.setDisplayRotation(U8G2_MIRROR);//mirror the image
              //u8g2.drawXBM(280+24, 25, 71, 71, arrowexitinghighway71x71_bits);
              u8g2.drawXBM(15, 18, 169, 194, arrowexitinghighway169x194_bits);
              u8g2.setDisplayRotation(U8G2_R0);
              u8g2.setDrawColor(1);
              break;
    case 5 :  //iconType.contains("move-right")//arrowexitinghighway169x194_bits
              u8g2.setDrawColor(0);
              //u8g2.drawXBM(280+24, 25, 71, 71, arrowexitinghighway71x71_bits);
              u8g2.drawXBM(15, 18, 169, 194, arrowexitinghighway169x194_bits);
              u8g2.setDrawColor(1);    
              break;               
    case 6 :  // iconType.contains("turn-slight-left")
              u8g2.setDrawColor(0);
              u8g2.setDisplayRotation(U8G2_MIRROR);//mirror the image
              //u8g2.drawXBM(400-((280+24)+71), 25, 71, 71, slightright71x71_bits); //render navigation small icons with 
              u8g2.drawXBM(400-(15 +169), 18, 169, 194, arrowslightright169x194px_bits); //render navigation large icons
              u8g2.setDisplayRotation(U8G2_R0);
              u8g2.setDrawColor(1);

              break;
    case 7 :  // iconType.contains("turn-slight-right")
              u8g2.setDrawColor(0);
              //u8g2.drawXBM(280+24, 25, 71, 71, slightright71x71_bits);
              u8g2.drawXBM(15, 18, 169, 194, arrowslightright169x194px_bits);
              u8g2.setDrawColor(1);   
              break;
    case 8 :  //iconType.contains("fork-left")
              u8g2.setDrawColor(0);
              u8g2.setDisplayRotation(U8G2_MIRROR);//mirror the image
              //u8g2.drawXBM(400-((280+24)+71), 25, 71, 71, forkright71x71_bits); //render navigation small icons with 
              u8g2.drawXBM(400-(15 +169), 18, 169, 194, arrowforkright169x194px_bits); //render navigation large icons
              u8g2.setDisplayRotation(U8G2_R0);
              u8g2.setDrawColor(1);
              break;  
    case 9 :  //iconType.contains("fork-right")
              u8g2.setDrawColor(0);
              //u8g2.drawXBM(280+24, 25, 71, 71, forkright71x71_bits);
              u8g2.drawXBM(15, 18, 169, 194, arrowforkright169x194px_bits);
              u8g2.setDrawColor(1);   

              break;                                        
    case 10 :  // iconType.contains("keep-left")
              u8g2.setDrawColor(0);
              u8g2.setDisplayRotation(U8G2_MIRROR);//mirror the image
              //u8g2.drawXBM(400-((280+24)+71), 25, 71, 71, keepright71x71_bits); //render navigation small icons with 
              u8g2.drawXBM(400-(15 +169), 18, 169, 194, arrowkeepright169x194px_bits); //render navigation large icons
              u8g2.setDisplayRotation(U8G2_R0);
              u8g2.setDrawColor(1);
              break;
    case 11 :  // iconType.contains("keep-right")
              u8g2.setDrawColor(0);
              //u8g2.drawXBM(280+24, 25, 71, 71, keepright71x71_bits);
              u8g2.drawXBM(15, 18, 169, 194, arrowkeepright169x194px_bits);
              u8g2.setDrawColor(1);
              break;
    case 12 :  // iconType.contains("ramp-left")
              u8g2.setDrawColor(0);
              u8g2.setDisplayRotation(U8G2_MIRROR);//mirror the image
              //u8g2.drawXBM(400-((280+24)+71), 25, 71, 71, rampright71x71_bits); //render navigation small icons with 
              u8g2.drawXBM(400-(15 +169), 18, 169, 194, arrowrampright169x194px_bits); //render navigation large icons
              u8g2.setDisplayRotation(U8G2_R0);
              u8g2.setDrawColor(1);
              break;
    case 13 :  // iconType.contains("ramp-right")
              u8g2.setDrawColor(0);
              //u8g2.drawXBM(280+24, 25, 71, 71, rampright71x71_bits);
              u8g2.drawXBM(15, 18, 169, 194, arrowrampright169x194px_bits);  
              u8g2.setDrawColor(1); 
              break;
    case 14 :  // iconType.contains("turn-sharp-left")
              u8g2.setDrawColor(0);
              u8g2.setDisplayRotation(U8G2_MIRROR);//mirror the image
              //u8g2.drawXBM(400-((280+24)+71), 25, 71, 71, sharp_right71x71_bits); //render navigation small icons with 
              u8g2.drawXBM(400-(15 +169), 18, 169, 194, arrowsharpright169x194px_bits); //render navigation large icons
              u8g2.setDisplayRotation(U8G2_R0);
              u8g2.setDrawColor(1);
              break;
    case 15 :  // iconType.contains("turn-sharp-right")
              u8g2.setDrawColor(0);
              //u8g2.drawXBM(280+24, 25, 71, 71, sharp_right71x71_bits);
              u8g2.drawXBM(15, 18, 169, 194, arrowsharpright169x194px_bits);  
              u8g2.setDrawColor(1); 
              break;
    case 16 :  // iconType.contains("roundabout-left")
              u8g2.setDrawColor(0);
              u8g2.setDisplayRotation(U8G2_MIRROR);//mirror the image
             // u8g2.drawXBM(400-((280+24)+71), 25, 71, 71, roundaboutright_71x71_bits); //render navigation small icons with 
              u8g2.drawXBM(400-(15 +169), 18, 169, 194, arrowroundaboutright169x194px_bits); //render navigation large icons
              u8g2.setDisplayRotation(U8G2_R0);
              u8g2.setDrawColor(1);
              break;                                                                                       
    case 17 :  // iconType.contains("roundabout-right")
              u8g2.setDrawColor(0);
             // u8g2.drawXBM(280+24, 25, 71, 71, roundaboutright_71x71_bits);
              u8g2.drawXBM(15, 18, 169, 194, arrowroundaboutright169x194px_bits);  
              u8g2.setDrawColor(1); 
              break;   
    case 18 :  // iconType.contains("uturn-left")
              u8g2.setDrawColor(0);
              u8g2.setDisplayRotation(U8G2_MIRROR);//mirror the image
              u8g2.drawXBM(400-((280+24)+71), 25, 71, 71, roundaboutlastturn71x71_bits); //render navigation small icons with 
              u8g2.drawXBM(400-(15 +169), 18, 169, 194, arrowroundaboutlastturn169x194px_bits); //render navigation large icons
              u8g2.setDisplayRotation(U8G2_R0);
              u8g2.setDrawColor(1);
              break;   
    case 19 :  // iconType.contains("uturn-left")
              u8g2.setDrawColor(0);
              u8g2.drawXBM(280+24, 25, 71, 71, roundaboutlastturn71x71_bits);
              u8g2.drawXBM(15, 18, 169, 194, arrowroundaboutlastturn169x194px_bits);  
              u8g2.setDrawColor(1);
              break;   
    case 20 :  // iconType.contains("merge")
              u8g2.setDrawColor(0);
              //u8g2.drawXBM(280+24, 25, 71, 71, merge71x71_bits);
              u8g2.drawXBM(15, 18, 169, 194, arrowmerge169x194_bits);
              u8g2.setDrawColor(1); 
              break;
    default : Serial.println("*************** error : icons id out of range.........");
              break;                              
                            
  }
   
  u8g2.setDrawColor(1);  
  u8g2.drawFrame(280,1,120,120);
  u8g2.setFontMode(0);
  u8g2.setFontPosTop();
  u8g2.setFont(u8g2_font_karla_60_tf);
  u8g2.drawStr( 200,160,(char*)CurrNavDistanceStr);
  u8g2.setDrawColor(0);

  u8g2.drawXBM(160, 240-20, 89, 8, fiveoutoffivedots89x7_75_bits);    
  u8g2.sendBuffer(); 

}




/************* Transport Callback Implementation ****************/
bool try_send_data(void *data, size_t len) {
    int stringIndex = 0;
  char *str = (char*)data;
Serial.print(F("try_send Len:"));
Serial.println(len,DEC);
Serial.print("Send Data:");
    // clear the uart_buffer:
    for (stringIndex = 0; stringIndex < len; stringIndex++)
    {     
      uart_buffer[stringIndex] = (uint8_t)*(str + stringIndex);
      Serial.print(uart_buffer[stringIndex],HEX);
      Serial.print(",");
    }
    Serial.println(" ");
    uart_buffer_len = len + 2;

//    //if (!lib_aci_send_data(PIPE_UART_OVER_BTLE_UART_TX_TX, uart_buffer, len))
//    {
//      Serial.println(F("Serial input dropped"));
//    }
//    else
//      Serial.println(F("dara sent"));
    ble.writeBLEUart(uart_buffer,len);
    Serial.println("Data sent Done");

    // clear the uart_buffer:
    for (stringIndex = 0; stringIndex < OMTU_OVERBLEUART; stringIndex++)
    {
      uart_buffer[stringIndex] = ' ';
    }

  return TRUE;
}

//void show_error(uint8_t status) {
//
//}


//****************** screen  animation

//void u8g2_ShowScreen(u8g2_t *u8gOutBuffer, u8g2_AnimationTypeDef screenTransition, u8g2_TransitionSpeedTypeDef speed)
//{
//  int outBufferIndex, preBufferIndex, newBuffIndex = 0;
//  uint16_t offsetCount, rowIndex, columnIndex, steps;
//  uint8_t *newScreenBuffPointer;
//  static bool ifScreenPresent = false;
//  static uint8_t preScreenBuffer[SCREEN_BUFF_SIZE];
//  outBufferIndex = offsetCount = preBufferIndex = 0;
//
//  if(!ifScreenPresent)
//  {
//     memset(preScreenBuffer, 0x00, SCREEN_BUFF_SIZE);
//     ifScreenPresent = true;
//     newScreenBuffPointer = (uint8_t*)malloc(SCREEN_BUFF_SIZE);
//     memcpy((uint8_t*)newScreenBuffPointer, (uint8_t*)u8gOutBuffer->tile_buf_ptr, SCREEN_BUFF_SIZE);
//     u8g2.clearBuffer(u8gOutBuffer);
//  }
//  else
//  {
//     newScreenBuffPointer = (uint8_t*)malloc(SCREEN_BUFF_SIZE);
//     memcpy((uint8_t*)newScreenBuffPointer, (uint8_t*)u8gOutBuffer->tile_buf_ptr, SCREEN_BUFF_SIZE);
//     u8g2.clearBuffer(u8gOutBuffer);
//     
//  }
//
//  if(screenTransition == LEFT_TRANSITION || screenTransition == RIGHT_TRANSITION)
//  {
//    switch(speed)
//    {
//      case SPEED_1x :
//        steps = 1;
//        break;
//      case SPEED_2x :
//        steps = 2;
//        break;
//      case SPEED_5x :
//        steps = 5;
//        break;
//      case SPEED_10x :
//        steps = 10;
//        break;
//      case SPEED_MAX :
//        steps = 25;
//        break;
//      default :
//        steps = 5;
//      break;
//    }
//  }
//  else if(screenTransition == UP_TRANSITION || screenTransition == DOWN_TRANSITION)
//  {
//    switch(speed)
//    {
//      case SPEED_1x :
//        steps = 1;
//        break;
//      case SPEED_2x :
//        steps = 4;
//        break;
//      case SPEED_5x :
//        steps = 16;
//        break;
//      case SPEED_10x :
//        steps = 24;
//        break;
//      case SPEED_MAX :
//        steps = 80;
//        break;
//      default :
//        steps = 5;
//      break;
//    }
//  }
//
//
//  switch(screenTransition)
//  {
//    case RIGHT_TRANSITION :
//        while(offsetCount <= COLUMN_COUNT)
//        {
//          for(rowIndex = 1; rowIndex <= ROW_COUNT; rowIndex++)
//          {
//            newBuffIndex = (COLUMN_COUNT * rowIndex) - offsetCount;
//
//            for(columnIndex = 1; columnIndex <= COLUMN_COUNT; columnIndex++)
//            {
//              if(columnIndex <= offsetCount)
//                u8gOutBuffer->tile_buf_ptr[outBufferIndex++] = (newScreenBuffPointer[newBuffIndex++]);
//              else
//                u8gOutBuffer->tile_buf_ptr[outBufferIndex++] = (preScreenBuffer[preBufferIndex++]);
//            }
//            preBufferIndex += offsetCount;
//          }
//          u8g2.sendBuffer(u8gOutBuffer);
//          offsetCount+=steps;
//          preBufferIndex = outBufferIndex = 0;
//        }
//      break;
//    case LEFT_TRANSITION :
//        while(offsetCount <= COLUMN_COUNT)
//        {
//          for(rowIndex = 1; rowIndex <= ROW_COUNT; rowIndex++)
//          {
//            preBufferIndex = preBufferIndex + offsetCount;
//
//            for(columnIndex = 1; columnIndex <= COLUMN_COUNT; columnIndex++)
//            {
//              if(columnIndex <= (COLUMN_COUNT - offsetCount))
//              {
//                u8gOutBuffer->tile_buf_ptr[outBufferIndex++] = preScreenBuffer[preBufferIndex++];
//              }
//              else
//              {
//                u8gOutBuffer->tile_buf_ptr[outBufferIndex++] = newScreenBuffPointer[newBuffIndex++];
//              }
//            }
//
//            newBuffIndex = newBuffIndex + (COLUMN_COUNT - offsetCount);
//          }
//          u8g2.sendBuffer(u8gOutBuffer);
//          outBufferIndex = preBufferIndex = newBuffIndex = 0;
//          offsetCount += steps;
//        }
//      break;
//    case UP_TRANSITION :
//        while(offsetCount <= ROW_COUNT)
//        {
//          preBufferIndex = COLUMN_COUNT * offsetCount;
//
//          for(outBufferIndex = 0; outBufferIndex < SCREEN_BUFF_SIZE; )
//          {
//            if(outBufferIndex < (SCREEN_BUFF_SIZE - COLUMN_COUNT * offsetCount))
//            {
//              u8gOutBuffer->tile_buf_ptr[outBufferIndex] = preScreenBuffer[preBufferIndex++];
//              outBufferIndex++;
//            }
//            else
//            {
//              u8gOutBuffer->tile_buf_ptr[outBufferIndex] = newScreenBuffPointer[newBuffIndex++];
//              outBufferIndex++;
//            }
//          }
//          newBuffIndex = preBufferIndex = outBufferIndex = 0;
//          u8g2.sendBuffer(u8gOutBuffer);
//          offsetCount += steps;
//        }
//      break;
//    case DOWN_TRANSITION :
//        while(offsetCount <= ROW_COUNT)
//        {
//          newBuffIndex = SCREEN_BUFF_SIZE - (COLUMN_COUNT * offsetCount) - 1;
//
//          for(outBufferIndex = 0; outBufferIndex < SCREEN_BUFF_SIZE; )
//          {
//            if(outBufferIndex < (offsetCount * 50))
//            {
//              u8gOutBuffer->tile_buf_ptr[outBufferIndex] = newScreenBuffPointer[newBuffIndex++];
//              outBufferIndex++;
//            }
//            else
//            {
//              u8gOutBuffer->tile_buf_ptr[outBufferIndex] = preScreenBuffer[preBufferIndex++];
//              outBufferIndex++;
//            }
//          }
//          u8g2.sendBuffer(u8gOutBuffer);
//          outBufferIndex = preBufferIndex = 0;
//          offsetCount += steps;
//        }
//      break;
//    default :
//      break;
//  }
//  memcpy((uint8_t*)preScreenBuffer, (uint8_t*)newScreenBuffPointer, 12000);
//  free(newScreenBuffPointer);
//}
//
//void u8g2_UpdateScreen(u8g2_t *u8gOutBuffer)
//{
//  u8g2_SendBuffer(u8gOutBuffer);
//}
//
//
//void u8g2_ToggleScreen(u8g2_t *u8gOutBuffer, uint8_t *screen)
//{
//  static bool color = true;
//  if (color == true)
//    color = false;
//  else
//    color = true;
//  u8g2_SetDrawColor(u8gOutBuffer, color);
//  u8g2_DrawXBMP(u8gOutBuffer, 0, 0, 399, 239, screen);
//  u8g2_UpdateScreen(u8gOutBuffer);
//}


//######################################


/**********************************************************************************************************************
 * Command Indication Callback implementation
 *  @brief   cp_ind_function_name :makes te command data available to application
 *  @parameters that can be accessed here are 1> payload data and 2>its size
 * *******************************************************************************************************************/


bool cp_ind_callback_ind(struct kbike_communication_protocol *session) {


 // osStatus status;
    bool res = FALSE;

  communication_protocol_header *hdr = (communication_protocol_header*) session->in.buf;

  //KLOG("Entry->cp_ind_callback_ind");
  Serial.println("Entry->cp_ind_callback_ind");

#ifdef __linux__
    void *data_payload = (void*) malloc(hdr->size_payload);
#elif __APPLE__
    void *data_payload = (void*) malloc(hdr->size_payload);
#else
    void *data_payload = pvPortMalloc(hdr->size_payload);
#endif

    if (data_payload == NULL)
    {
       //error in allocating memory
      //KLOGE("Error in allocating memory to data_payload in indication function");

      }
    else
    {
       memset(data_payload, 0, hdr->size_payload);
       memcpy(data_payload, session->in.buf + sizeof(*hdr), hdr->size_payload);

       if(hdr->cmd_group == COMMUNICATION_PROTOCOL_CMD_GRP_DM_NEW_PARAMETERS)
       {
          switch(hdr->cmd)
          { case COMMUNICATION_PROTOCOL_CMD_CURRENT_DATE_TIME:
          
                                timedat=(struct current_date_time *)data_payload;
                                  // Set the time
                                rtc.setHours(timedat->HH);
                                rtc.setMinutes(timedat->MIN);
                                rtc.setSeconds(timedat->SS);
                              
                                // Set the date
                                rtc.setDay(timedat->DD);
                                rtc.setMonth(timedat->MM);
                                rtc.setYear(timedat->YY);
                                Serial.println("Date Time updated");
                                ScreenMenu=MAINMENUSCREEN1;
                                break;
          case COMMUNICATION_PROTOCOL_CMD_VEHICLE_BATTERY_VOLTAGE :
                                VehBatteryVoltage=(struct vehicle_battery_voltage*)data_payload;
                                
                                 

                                Serial.print("Vehicle Battery recieved : ");
                                Serial.print(VehBatteryVoltage->voltage, DEC);
                                Serial.print(" V");
                                break;
          case COMMUNICATION_PROTOCOL_CMD_SOURCE_NAME :
                        
                                Trip_source_name = (struct source_name*)data_payload;
                
                                Serial.println("Travel Start Detail recieved");  
                                break;
          case COMMUNICATION_PROTOCOL_CMD_DESTINATION_NAME :

                            
                                Trip_destination_name = (struct destination_name*)data_payload;
                                Serial.println("Travel Destination Detail recieved"); 

                                break;
          case COMMUNICATION_PROTOCOL_CMD_ETA :
                                Trip_eta = (struct eta*)data_payload;
                                Serial.println("Expected Time of Travel recieved");   
                                break;
          case COMMUNICATION_PROTOCOL_CMD_CURRENT_MANUEVER_ICON :
                                CurrNavIconId =(struct current_maneuver_icon *)data_payload;
                                nav_icon_id=CurrNavIconId->IconID;
                                Serial.print("Navigation Icons ID recieved : "); 
                                Serial.println(nav_icon_id); 
                                break;                  
          case COMMUNICATION_PROTOCOL_CMD_CURRENT_MANUEVER_DISTANCE_UNIT :
                                CurrNavDistance = (struct current_maneuver_distance_unit *)data_payload;
                                Serial.println("Turn distance recieved"); 
                                if(ScreenMenu == MAINMENUSCREENNAVIGATE) //navigation screen or menu
                                {   Serial.print("In Navigation Mode:");
                                    if(CurrNavDistance->UnitFlag  == KILOMETER)    
                                            sprintf(CurrNavDistanceStr, "%d km" , CurrNavDistance->distance);
                                    else if(CurrNavDistance->UnitFlag  == METER)
                                            sprintf(CurrNavDistanceStr, "%d m" , CurrNavDistance->distance);
                                    if(CurrNavDistance->distance == 0)
                                    {
                                         sprintf(CurrNavDistanceStr, "Now !!");
                                    }
                                            
                                    Serial.println(CurrNavDistanceStr);        
//                                    u8g2.setDrawColor(0);  
//                                    u8g2.drawBox(200,160,200,60);
//                                    u8g2.setDrawColor(1); 
//                                    u8g2.setFontMode(0);
//                                    u8g2.setFontPosTop();
//                                    u8g2.setFont(u8g2_font_karla_45_tf);
//                                    u8g2.drawStr( 200,160,(char*)CurrNavDistanceStr);
//                                    u8g2.setDrawColor(0);
//                                  
//                                    //u8g2.drawXBM(160, 240-20, 89, 9, i5dots89x9_bits);    
//                                    u8g2.sendBuffer();
                                    newBleString=true; //set a flag for navigation engine to receive 
                                }
                                break;
          case COMMUNICATION_PROTOCOL_CMD_NEXT_MANUEVER_ICON :
                                Serial.println("NEXT_MANUEVER_ICON recieved");
                                break;  
          case COMMUNICATION_PROTOCOL_CMD_NEXT_MANUEVER_DISTANCE_UNIT :
                                Serial.println("NEXT_MANUEVER_DISTANCE recieved");
                                break;
          case COMMUNICATION_PROTOCOL_CMD_BIKE_FULE_LEVEL :
          struct bike_fuel_level* BikeFuelLevel;
                                BikeFuelLevel= (struct bike_fuel_level*)data_payload; 

                                Serial.println("Bike Fuel Level recieved");
                                break;
          case COMMUNICATION_PROTOCOL_CMD_BIKE_MILEAGE_DISTANCE_UNIT :
                                break;
          case COMMUNICATION_PROTOCOL_CMD_TRAVELLED_DISTANCE_UNIT :
                                break;
          case COMMUNICATION_PROTOCOL_CMD_CM_HEALTH_STATUS_PARAMETERS :
                                break;
          case COMMUNICATION_PROTOCOL_CMD_DM_INFO_PARAMETERS :
                                break;
          case COMMUNICATION_PROTOCOL_CMD_DM_USER_NAME :
                                break;
          case COMMUNICATION_PROTOCOL_CMD_DM_PASSKEY :
                                break;                                                                                               
          default:      break;
           
       }

    }

  }

#ifdef __linux__
      free(data_payload);
#elif __APPLE__
      free(data_payload);
#else
      vPortFree(data_payload);
#endif


 // KLOGI(INFO,"Exit->cp_ind_callback_ind");

  return 1;

}

/**********************************************************************************************************************
 * Command Confirmation Callback implementation
 *  @brief  cp_cfm_function_name : notifies status of sent command to application.
 *   @parameters  status
 * *******************************************************************************************************************/


void cp_cfm_callback_cfm(struct kbike_communication_protocol *session, uint8_t status) {
  //KLOG(METHOD,"ENTER--> cp_cfm_callback\n\r ");
  Serial.println("ENTER--> cp_cfm_callback\n\r ");
  if (status == COMMUNICATION_PROTOCOL_SUCCESS_ACK)
    ;
  else {
    ;
    show_error(status);
  }
  //KLOG(METHOD,"EXIT--> cp_cfm_callback\n\r ");
}



void show_error(uint8_t status) {
  //KLOG(METHOD,"ENTER--> show_error \n");
  Serial.println("ENTER--> show_error \n");
  switch (status) {
  case COMMUNICATION_PROTOCOL_BAD_HEADER_FORMAT:
    //printf("Bad Header format\n");
  // //KLOGL("Bad Header format\n");
    break;
  case COMMUNICATION_PROTOCOL_BAD_LENGTH:
    //printf("Bad packet length\n");
  //  //KLOGL("Bad packet length\n");
    break;
  case COMMUNICATION_PROTOCOL_INVALID_COMMAND:
    //printf("Invalid Command\n");
   // //KLOGL("Invalid Command\n");
    break;
  case COMMUNICATION_PROTOCOL_NO_BUFFER_SPACE:
    //printf("Insufficient IN Buffer Space\n");
   // //KLOGL("Insufficient IN Buffer Space\n");
    break;
  default:
    break;
  }
  //KLOG(METHOD,"EXIT--> show_error \n");
}


