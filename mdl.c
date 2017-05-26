/**
  *****************************************************************************************************************************
  * File Name          : mdl.c
  * Description        : This file provides trial implementation of linked list.
  *              
  *****************************************************************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include <string.h>
#include "mdlf.h"
#include "mdl.h"
//#define KLOG_CATEGORY MDL
//#include "klog.h"
//#include "nvmi_if.h"
#include "iconsf.h"

/* Variables ------------------------------------------------------------------*/
list_t * widgetList; 
list_t * elementList; 
list_t * screenList; 
//iconAttributes_TypeDef icontest = {1, "currentlocation", 70, 70};
  
  
/* USER CODE BEGIN 0 */

/***********************************************ELEMENT RELATED FUNCTIONS*********************************************/
  
list_t * elementListInit(void)
{
  //Nodal definition of 'Element' linked list
  MDL_Element_TypeDef * ptrElementDefintion;    //to assign value to the element node
  MDL_Element_TypeDef * elementDefinition;
  
  //creation of 'Element' linked list
//  list_t * elementList; 
  elementList = list_new();
  
  //adding nodes to the already formed Element list as per MAX_NUM_OF_ELEMENTS
  for(int i = 0; i < MAX_NUM_OF_ELEMENTS; i++)
  {
    //node creation of type MDL_Element_AttributesTypeDef 
    ptrElementDefintion = malloc(sizeof(MDL_Element_TypeDef));
    list_node_t * elementNode = list_node_new((void *) ptrElementDefintion);  
    
    //add component ID
    elementNode->componentID = elementInformationFlash[i].elementID;
    
    //node linking
    list_node_t * currentNode = list_rpush(elementList, elementNode); 
//    currentNode->val = (MDL_Element_TypeDef *) currentNode->val;
    elementDefinition = (MDL_Element_TypeDef *) currentNode->val;
    elementDefinition -> elementID = elementInformationFlash[i].elementID;
    elementDefinition -> elementHeight = elementInformationFlash[i].elementHeight;
    elementDefinition -> elementWidth = elementInformationFlash[i].elementWidth;
  }
  return elementList;

//  uint8_t fuelLevel = 50;   //read the fuel data from phone into this variable
//  //populating the parameters with their dummy data
//  parameterInformation[0].parameterID = FUEL_LEVEL;
//  parameterInformation[0].data = &fuelLevel;
//  
//  char * batteryLevel = "LOW BATTERY";    //represent the battery level in this variable in the string format
//  parameterInformation[1].parameterID = BATTERY_LEVEL;
//  parameterInformation[1].data = batteryLevel;
//  
//  //populating the elements with their dummy data
//  elementInformation[0].elementID = 1;
//  elementInformation[0].elementHeight = 10;
//  elementInformation[0].elementWidth = 10;
//  
//  elementInformation[1].elementID = 2;
//  elementInformation[1].elementHeight = 20;
//  elementInformation[1].elementWidth = 20;  
//  
//  //===== fuel level indicator - Text and its value ===== 
//  widgetInformation[0].widgetId = 1;                                      //forming WIDGET 1
//  widgetInformation[0].elementID = elementInformation[0].elementID;
//  widgetInformation[0].objectDef.objectType.textString = "Fuel level";    //should have been Text ID
//  widgetInformation[0].objectDef.data = "Fuel level";
//  
//  widgetInformation[1].widgetId = 2;                                      //forming WIDGET 2
//  widgetInformation[1].elementID = elementInformation[1].elementID; 
//  widgetInformation[1].objectDef.objectType.parameter = parameterInformation[0].parameterID;
//  widgetInformation[1].objectDef.data = parameterInformation[0].data;
//  

//  //===== Battery level indicator - Text and its value =====
//  widgetInformation[2].widgetId = 3;                                      //forming widget 3
//  widgetInformation[2].elementID = elementInformation[0].elementID;
//  widgetInformation[2].objectDef.objectType.textString = "Battery level";   //should have been Text ID
//  widgetInformation[2].objectDef.data = "Battery level";  
//  
//  widgetInformation[3].widgetId = 4;                                    //forming widget 4
//  widgetInformation[3].elementID = elementInformation[1].elementID;
//  widgetInformation[3].objectDef.objectType.parameter = parameterInformation[1].parameterID;
//  widgetInformation[3].objectDef.data = parameterInformation[1].data;
  
  
  //formation of screen1
//  widgetPlacementInformation[0].widgetId = widgetInformation[0].widgetId;
//  widgetPlacementInformation[0].widgetXPos = 390;
//  widgetPlacementInformation[0].widgetYPos = 140;
//  
//  widgetPlacementInformation[0].widgetId = widgetInformation[1].widgetId;
//  widgetPlacementInformation[0].widgetXPos = 380;
//  widgetPlacementInformation[0].widgetYPos = 110;
  
  
//  screenInformation[0].screenId = 1;
//  screenInformation[0].screenWidth = 400;       //Maximum value
//  screenInformation[0].screenHeight = 240;
//  screenInformation[0].numOfWidgets = 2;        //fuel level text and is value
//  
//  screenInformation[0].widgetPlacementInformation[0].widgetId = widgetInformation[0].widgetId;      //widget1
//  screenInformation[0].widgetPlacementInformation[0].widgetXPos = 390;
//  screenInformation[0].widgetPlacementInformation[0].widgetYPos = 140;
//  
//  screenInformation[0].widgetPlacementInformation[1].widgetId = widgetInformation[1].widgetId;      //widget2
//  screenInformation[0].widgetPlacementInformation[1].widgetXPos = 380;
//  screenInformation[0].widgetPlacementInformation[1].widgetYPos = 110;
//  
//  
//  //formation of screen2
//  screenInformation[1].screenId = 2;
//  screenInformation[1].screenWidth = 400;       //Maximum value
//  screenInformation[1].screenHeight = 240;
//  screenInformation[1].numOfWidgets = 2;        //fuel level text and is value
//  
//  screenInformation[1].widgetPlacementInformation[0].widgetId = widgetInformation[2].widgetId;
//  screenInformation[1].widgetPlacementInformation[0].widgetXPos = 390;
//  screenInformation[1].widgetPlacementInformation[0].widgetYPos = 140;
//  
//  screenInformation[1].widgetPlacementInformation[1].widgetId = widgetInformation[3].widgetId;
//  screenInformation[1].widgetPlacementInformation[1].widgetXPos = 380;
//  screenInformation[1].widgetPlacementInformation[1].widgetYPos = 110;
//  
//  //both the screens are in the same carousel
//  carouselInformation[0].carouselId = 1;
//  carouselInformation[0].numOfScreens = 2;    
}

//
//char * wholeString[3];
//char * str1 = "Suspicious";
//char * str2 = "bike";
//char * str3 = "activity";
/***********************************************WIDGET RELATED FUNCTIONS*********************************************/

list_t * widgetListInit(void)
{
  //Nodal definition of 'Widget' linked list
  MDL_Widget_TypeDef * ptrWidgetDefintion;    //to assign value to the widget node
  MDL_Widget_TypeDef * widgetDefinition;
  
  //creation of 'Widget' linked list
//  list_t * widgetList; 
  widgetList = list_new();
  
  //adding nodes to the already formed Widget list as per MAX_NUM_OF_WIDGETS
  for(int i = 0; i < MAX_NUM_OF_WIDGETS; i++)
  {
    //node creation of type MDL_Widget_TypeDef 
    ptrWidgetDefintion = malloc(sizeof(MDL_Widget_TypeDef));    //make the pointer to point to some real memory location
    list_node_t * widgetNode = list_node_new((void *) ptrWidgetDefintion);  

    //add component ID
    widgetNode->componentID = widgetInformationFlash[i].widgetId;
    
    //node linking
    list_node_t * currentNode = list_rpush(widgetList, widgetNode); 
//    currentNode->val = (MDL_Widget_TypeDef *) currentNode->val;
    widgetDefinition = (MDL_Widget_TypeDef *) currentNode->val;
    widgetDefinition->LiveFlag = widgetInformationFlash[i].LiveFlag;
    widgetDefinition->widgetId = widgetInformationFlash[i].widgetId;
    widgetDefinition->elementID = widgetInformationFlash[i].elementID;
    widgetDefinition->widgetObjectType = widgetInformationFlash[i].widgetObjectType;
    widgetDefinition->objectID = widgetInformationFlash[i].objectID;
    widgetDefinition->verticalAlignment = widgetInformationFlash[i].verticalAlignment;
    widgetDefinition->horizontalAlignment = widgetInformationFlash[i].horizontalAlignment;
    widgetDefinition->widgetInversion = widgetInformationFlash[i].widgetInversion;
    widgetDefinition->widgetAnimation = widgetInformationFlash[i].widgetAnimation;    
    
    switch(i)
    {
      case 0: widgetDefinition->objectDefinition.data = estimatedtime70x70_bits;
//              widgetDefinition->objectDefinition.updateCB = "Fuel Level Icon UpdateCB";
              break;
              
      case 1: widgetDefinition->objectDefinition.data = "88:88";
              break;
              
      case 2: widgetDefinition->objectDefinition.data = estimateddistance70x70_bits;
              break;
              
      case 3: widgetDefinition->objectDefinition.data = "1000m";
              break;

      case 4: widgetDefinition->objectDefinition.data = oneoutoffourdots69x7_bits;
              break;
              
      case 5: widgetDefinition->objectDefinition.data = rocket70x70_bits;
              break;

      case 6: widgetDefinition->objectDefinition.data = "Let's ride";
              break;

      case 7: widgetDefinition->objectDefinition.data = dmbatteryhalffull70x70_bits;
              break;

      case 8: widgetDefinition->objectDefinition.data = "NEURON BATTERY:";
              break;

      case 9: widgetDefinition->objectDefinition.data = "50%";
              break;

      case 10:  widgetDefinition->objectDefinition.data = settingsclog70x70_80_bits;
              break;

      case 11:  widgetDefinition->objectDefinition.data = "Settings";
              break;

      case 12:  widgetDefinition->objectDefinition.data = "Hold to access";
              break;

      case 13:  widgetDefinition->objectDefinition.data = fouroutoffourdots89x7_bits;
              break;

      case 14:  widgetDefinition->objectDefinition.data = severe70x70_bits;
              break;

      case 15:  widgetDefinition->objectDefinition.data = "Severe conditions";
              break;

      case 16:  widgetDefinition->objectDefinition.data = "Hold to send";
              break;

      case 17:  widgetDefinition->objectDefinition.data = fouroutoffivedots89x7_75_bits;
              break;

      case 18:  widgetDefinition->objectDefinition.data = sendalert70x70_bits;
              break;

      case 19:  widgetDefinition->objectDefinition.data = "Send alert";
              break;

      case 20:  widgetDefinition->objectDefinition.data = suspiciousbike70x70_bits;
              break;

      case 21:  widgetDefinition->objectDefinition.data = urgentalertbar400x11_bits;
              break;

      case 22:  widgetDefinition->objectDefinition.data = "Suspicious bike activity";
              break;

      case 23:  widgetDefinition->objectDefinition.data = fuelempty70x70_bits;
              break;

      case 24:  widgetDefinition->objectDefinition.data = "No fuel";
              break;

      case 25:  widgetDefinition->objectDefinition.data = oneoutoffivedots89x7_75_bits;
              break;

      case 26:  widgetDefinition->objectDefinition.data = puncture70x70_bits;
              break;

      case 27:  widgetDefinition->objectDefinition.data = "Puncture";
              break;

      case 28:  widgetDefinition->objectDefinition.data = "Hold to send";
              break;

      case 29:  widgetDefinition->objectDefinition.data = twooutoffivedots89x7_75_75_bits;
              break;

      case 30:  widgetDefinition->objectDefinition.data = accident70x70_bits;
              break;

      case 31:  widgetDefinition->objectDefinition.data = "Accident";
              break;

      case 32:  widgetDefinition->objectDefinition.data = "Hold to send";
              break;

      case 33:  widgetDefinition->objectDefinition.data = threeoutoffivedots89x7_75_bits;
              break;

      case 34:  widgetDefinition->objectDefinition.data = cancel70x70_bits;
              break;

      case 35:  widgetDefinition->objectDefinition.data = "Cancel";
              break;

      case 36:  widgetDefinition->objectDefinition.data = "Hold to confirm";
              break;

      case 37:  widgetDefinition->objectDefinition.data = fiveoutoffivedots89x7_75_bits;
              break;

      default:  //KLOGI("Nothing to display here"); 
                break;    
    }
    
    switch(i)
    {
      case 0: widgetDefinition->widgetAnimationDefinition.animationEnable = 0;      //FLAG ICON
              widgetDefinition->widgetAnimationDefinition.duration = 0;
              break;
              
      case 1: widgetDefinition->widgetAnimationDefinition.animationEnable = 0;      //ETA
              widgetDefinition->widgetAnimationDefinition.duration = 0;
              break;
              
      case 2: widgetDefinition->widgetAnimationDefinition.animationEnable = 1;      //LOCATE ICON
              widgetDefinition->widgetAnimationDefinition.duration = 5;
              break;
              
      case 3: widgetDefinition->widgetAnimationDefinition.animationEnable = 1;      //Distance to be covered
              widgetDefinition->widgetAnimationDefinition.duration = 5;
              break;

      case 4: widgetDefinition->widgetAnimationDefinition.animationEnable = 0;      //Menubar Icon 1 of 4
              widgetDefinition->widgetAnimationDefinition.duration = 0;
              break;
              
      case 5: widgetDefinition->widgetAnimationDefinition.animationEnable = 0;      //RIDE LOGO ICON
              widgetDefinition->widgetAnimationDefinition.duration = 0;
              break;

      case 6: widgetDefinition->widgetAnimationDefinition.animationEnable = 0;      //"Let's Ride" text
              widgetDefinition->widgetAnimationDefinition.duration = 0;
              break;

      case 7: widgetDefinition->widgetAnimationDefinition.animationEnable = 1;      //DM BATTERY LEVEL ICON
              widgetDefinition->widgetAnimationDefinition.duration = 5;
              break;

      case 8: widgetDefinition->widgetAnimationDefinition.animationEnable = 1;      //"Neuron Battery" text
              widgetDefinition->widgetAnimationDefinition.duration = 5;
              break;

      case 9: widgetDefinition->widgetAnimationDefinition.animationEnable = 0;      //"Textual data" - DM Battery level
              widgetDefinition->widgetAnimationDefinition.duration = 0;
              break;

      case 10:  widgetDefinition->widgetAnimationDefinition.animationEnable = 0;      //SETTINGS ICON
              widgetDefinition->widgetAnimationDefinition.duration = 0;
              break;

      case 11:  widgetDefinition->widgetAnimationDefinition.animationEnable = 1;      //"Settings" text
              widgetDefinition->widgetAnimationDefinition.duration = 5;
              break;

      case 12:  widgetDefinition->widgetAnimationDefinition.animationEnable = 1;      //"Hold to access"
              widgetDefinition->widgetAnimationDefinition.duration = 5;
              break;

      case 13:  widgetDefinition->widgetAnimationDefinition.animationEnable = 0;      //Menubar icon 4 of 4
              widgetDefinition->widgetAnimationDefinition.duration = 0;
              break;

      case 14:  widgetDefinition->widgetAnimationDefinition.animationEnable = 0;      //SEVERE CONDITIONS ICON
              widgetDefinition->widgetAnimationDefinition.duration = 0;
              break;

      case 15:  widgetDefinition->widgetAnimationDefinition.animationEnable = 1;      //"Severe Conditions" text
              widgetDefinition->widgetAnimationDefinition.duration = 5;
              break;

      case 16:  widgetDefinition->widgetAnimationDefinition.animationEnable = 1;      //"Hold to send"
              widgetDefinition->widgetAnimationDefinition.duration = 5;
              break;

      case 17:  widgetDefinition->widgetAnimationDefinition.animationEnable = 0;      //Menubar icon 4 of 5
              widgetDefinition->widgetAnimationDefinition.duration = 0;
              break;

      case 18:  widgetDefinition->widgetAnimationDefinition.animationEnable = 1;      //SEND ALERT ICON
              widgetDefinition->widgetAnimationDefinition.duration = 5;
              break;

      case 19:  widgetDefinition->widgetAnimationDefinition.animationEnable = 0;      //"Send alert"
              widgetDefinition->widgetAnimationDefinition.duration = 0;
              break;

      case 20:  widgetDefinition->widgetAnimationDefinition.animationEnable = 0;      //Menubar icon 3 of 4
              widgetDefinition->widgetAnimationDefinition.duration = 0;
              break;

      case 21:  widgetDefinition->widgetAnimationDefinition.animationEnable = 1;      //SEND ALERT ICON
              widgetDefinition->widgetAnimationDefinition.duration = 5;
              break;

      case 22:  widgetDefinition->widgetAnimationDefinition.animationEnable = 0;      //"Send alert"
              widgetDefinition->widgetAnimationDefinition.duration = 0;
              break;
      case 23:  widgetDefinition->widgetAnimationDefinition.animationEnable = 0;      //NO FUEL ICON
              widgetDefinition->widgetAnimationDefinition.duration = 0;
              break;

      case 24:  widgetDefinition->widgetAnimationDefinition.animationEnable = 1;      //"No fuel" text
              widgetDefinition->widgetAnimationDefinition.duration = 5;
              break;

      case 25:  widgetDefinition->widgetAnimationDefinition.animationEnable = 0;      //Menubar icon 1 of 5
              widgetDefinition->widgetAnimationDefinition.duration = 0;
              break;

      case 26:  widgetDefinition->widgetAnimationDefinition.animationEnable = 0;      //PUNCTURE ICON
              widgetDefinition->widgetAnimationDefinition.duration = 0;
              break;

      case 27:  widgetDefinition->widgetAnimationDefinition.animationEnable = 0;      //"Puncture" text
              widgetDefinition->widgetAnimationDefinition.duration = 0;
              break;

      case 28:  widgetDefinition->widgetAnimationDefinition.animationEnable = 1;      //"Hold to send"
              widgetDefinition->widgetAnimationDefinition.duration = 5;
              break;

      case 29:  widgetDefinition->widgetAnimationDefinition.animationEnable = 0;      //Menubar icon 2 of 5
              widgetDefinition->widgetAnimationDefinition.duration = 0;
              break;

      case 30:  widgetDefinition->widgetAnimationDefinition.animationEnable = 0;      //ACCIDENT ICON
              widgetDefinition->widgetAnimationDefinition.duration = 0;
              break;

      case 31:  widgetDefinition->widgetAnimationDefinition.animationEnable = 0;      //"Accident" text
              widgetDefinition->widgetAnimationDefinition.duration = 0;
              break;

      case 32:  widgetDefinition->widgetAnimationDefinition.animationEnable = 1;      //"Hold to send"
              widgetDefinition->widgetAnimationDefinition.duration = 5;
              break;

      case 33:  widgetDefinition->widgetAnimationDefinition.animationEnable = 0;      //Menubar icon 3 of 5
              widgetDefinition->widgetAnimationDefinition.duration = 0;
              break;

      case 34:  widgetDefinition->widgetAnimationDefinition.animationEnable = 0;      //CANCEL ICON
              widgetDefinition->widgetAnimationDefinition.duration = 0;
              break;

      case 35:  widgetDefinition->widgetAnimationDefinition.animationEnable = 0;      //"Cancel" text
              widgetDefinition->widgetAnimationDefinition.duration = 0;
              break;

      case 36:  widgetDefinition->widgetAnimationDefinition.animationEnable = 1;      //"Hold to confirm"
              widgetDefinition->widgetAnimationDefinition.duration = 5;
              break;

      case 37:  widgetDefinition->widgetAnimationDefinition.animationEnable = 0;      //Menubar icon 5 of 5
              widgetDefinition->widgetAnimationDefinition.duration = 0;
              break;

      default:  //KLOGI("Nothing to display here"); 
                break;    
    }
  }
  return widgetList;
}




/***********************************************SCREEN RELATED FUNCTIONS*********************************************/

//function to create screen list
list_t * screenListInit(void)
{
  //Nodal definition of 'Screen' linked list
  MDL_Screen_TypeDef * ptrScreenDefintion;    //for formation of screen node; used as 'value' argument
  MDL_Screen_TypeDef * screenDefinition;
  
  //creation of 'Screen' linked list
//  list_t * screenList; 
  screenList = list_new();
  
  //assignment of match function for the newly created screen list
  screenList->match = matchScreenID;
  
  //adding nodes to the already formed Screen list as per MAX_NUM_OF_SCREENS
  for(int i = 0; i < MAX_NUM_OF_SCREENS; i++)
  {
    //node creation of type MDL_Screen_TypeDef 
    ptrScreenDefintion = malloc(sizeof(MDL_Screen_TypeDef)); //make the pointer to point to some real memory location; value for node
    list_node_t * screenNode = list_node_new((void *) ptrScreenDefintion);  

    //add component ID
    screenNode->componentID = screenInformationFlash[i].screenId;
    
    //node linking
    list_node_t * currentNode = list_rpush(screenList, screenNode); 
//    currentNode->val = (MDL_Screen_TypeDef *) currentNode->val;
    screenDefinition = (MDL_Screen_TypeDef *) currentNode->val;
    
    //assignment of values in the node
    screenDefinition->screenId = screenInformationFlash[i].screenId;
    screenDefinition->screenHeight = screenInformationFlash[i].screenHeight;
    screenDefinition->screenWidth = screenInformationFlash[i].screenWidth;
    screenDefinition->numOfWidgets = screenInformationFlash[i].numOfWidgets;
    
    if(screenDefinition->numOfWidgets <= MAX_NUM_OF_WIDGETS_ON_A_SCREEN)
    {
      for(int j = 0; j < screenDefinition->numOfWidgets; j++)   //to be changed later, when widgets on a screen not equal to max number
      {
        screenDefinition->widgetPlacementInformation[j].widgetId = screenInformationFlash[i].widgetPlacementInformationFlash[j].f_widgetId;
        screenDefinition->widgetPlacementInformation[j].widgetXPos = screenInformationFlash[i].widgetPlacementInformationFlash[j].f_widgetXPos;
        screenDefinition->widgetPlacementInformation[j].widgetYPos = screenInformationFlash[i].widgetPlacementInformationFlash[j].f_widgetYPos;
      }

      switch(i)
      {
        case 0: screenDefinition->screenTransition.transitionEnable = 0;
                screenDefinition->screenTransition.transition = 0;
                screenDefinition->screenTransition.duration = 0;
                screenDefinition->screenInversion = 0;
                break;

        case 1: screenDefinition->screenTransition.transitionEnable = 1;
                screenDefinition->screenTransition.transition = 3;
                screenDefinition->screenTransition.duration = 2;
                screenDefinition->screenInversion = 1;
                break;

        case 2: screenDefinition->screenTransition.transitionEnable = 1;
                screenDefinition->screenTransition.transition = 3;
                screenDefinition->screenTransition.duration = 2;
                screenDefinition->screenInversion = 1;
                break;

        case 3: screenDefinition->screenTransition.transitionEnable = 0;
                screenDefinition->screenTransition.transition = 0;
                screenDefinition->screenTransition.duration = 0;
                screenDefinition->screenInversion = 0;
                break;

        default:  //KLOGI("Nothing to display here");
                  break;
      }
    }
    else
    {
      //KLOGE("Sorry! The number of widgets on a screen exceed the max limit");
    }   
  }
  return screenList;
}



//function to match up provided ID with IDs in each screen node in the desired screen LL
int matchScreenID(uint16_t idToMatch, uint16_t idToBeMatchedWith )
{
  if(idToBeMatchedWith == idToMatch)
  {
    //KLOGI("Found the desired screen :)");
    return VICTORY;
  }
  else
  {
    //KLOGE("No such screen exists :( ");
    return FAILURE;
  }
}



//add new screen nodes into the list,
list_node_t * addScreenNode(list_t * screenList, MDL_Screen_TypeDef * newData)
{
  //check whether that screen already exists or not; if it does, exit the function 
  list_node_t* nodeFound = list_find(screenList, newData->screenId);
//  assert_param(IS_VALID_NEW_SCREEN(nodeFound));
  
  if(!(nodeFound))      //node is not found in the existing list
  {
    MDL_Screen_TypeDef * ptrScreenNewDefintion;
    MDL_Screen_TypeDef * screenNewDefintion;
    
    //check if the widget ID exists
    for(int i = 0; i < newData->numOfWidgets; i++)
    {
      list_node_t* widgetFound = list_find(widgetList, newData->widgetPlacementInformation[i].widgetId);
      assert_param(IS_VALID_WIDGET(widgetFound));
      if(!(widgetFound))
      {
        //KLOGE("SORRY---widget ID doesn't exist in the list");
        return FAILURE;     //assert
      }
      else
      {
        //KLOGI("Widget exists with ID: %d", newData->widgetPlacementInformation[i].widgetId);
      }
    }   
    ptrScreenNewDefintion = malloc(sizeof(MDL_Screen_TypeDef)); //make the pointer to point to some real memory location; value for node
    list_node_t * screenNewNode = list_node_new((void *) ptrScreenNewDefintion);  

    //add component ID
    screenNewNode->componentID = newData->screenId;
    
    //node linking
    list_node_t * currentNewNode = list_rpush(screenList, screenNewNode); 
//    currentNewNode->val = (MDL_Screen_TypeDef *) currentNewNode->val;
    screenNewDefintion = (MDL_Screen_TypeDef *)currentNewNode->val;
    
    //assignment of values in the new node
    screenNewDefintion->screenId = newData->screenId;
    screenNewDefintion->screenHeight = newData->screenHeight;
    screenNewDefintion->screenWidth = newData->screenWidth;
    screenNewDefintion->numOfWidgets = newData->numOfWidgets;
    
  
    //now add information about widgets
    for(int j = 0; j < newData->numOfWidgets; j++)
    {
      screenNewDefintion->widgetPlacementInformation[j].widgetId = newData->widgetPlacementInformation[j].widgetId;
      screenNewDefintion->widgetPlacementInformation[j].widgetXPos = newData->widgetPlacementInformation[j].widgetXPos;
      screenNewDefintion->widgetPlacementInformation[j].widgetYPos = newData->widgetPlacementInformation[j].widgetYPos;
    }       
    screenNewDefintion->screenTransition.transitionEnable = newData->screenTransition.transitionEnable; 
    screenNewDefintion->screenTransition.transition = newData->screenTransition.transition; 
    screenNewDefintion->screenTransition.duration = newData->screenTransition.duration;
    screenNewDefintion->screenInversion = newData->screenInversion;
    return currentNewNode;
  }
  else
  {
    //KLOGE("SORRY----Screen Already exists");
    return FAILURE;
  }
}


//modify existing screen nodes in the list
list_node_t * modifyScreenNode(list_t * screenList, uint16_t screenIdToModify, MDL_Screen_TypeDef * modifiedData)
{
  MDL_Screen_TypeDef * screenModifiedDefintion;
  //check whether that screen already exists or not; if it does, exit the function 
  list_node_t* nodeFound = list_find(screenList, screenIdToModify); 
  
  //modify data only if node is found
  if(nodeFound)
  {
    //check if the widget being used in the screen; their ID exists
    for(int i = 0; i < modifiedData->numOfWidgets; i++)
    {
      list_node_t* widgetFound = list_find(widgetList, modifiedData->widgetPlacementInformation[i].widgetId);
      assert_param(IS_VALID_WIDGET(widgetFound));
      if(!(widgetFound))
      {
        //KLOGE("SORRY---widget ID doesn't exist in the list");
        return FAILURE;     //assert can't proceed with screen formation
      }
      else
      {
        //KLOGI("Widget exists with ID: %d", modifiedData->widgetPlacementInformation[i].widgetId);
      }
    }
    screenModifiedDefintion = (MDL_Screen_TypeDef *)nodeFound->val;
    
//    if(screenModifiedDefintion->screenId == screenIdToModify)
//    {
      //assignment of modified values in the existing node
  //    screenModifiedDefintion->screenId = modifiedData->screenId;     
      screenModifiedDefintion->screenHeight = modifiedData->screenHeight;
      screenModifiedDefintion->screenWidth = modifiedData->screenWidth;
      screenModifiedDefintion->numOfWidgets = modifiedData->numOfWidgets;
      
  
      
      //now add information about widgets
      for(int j = 0; j < modifiedData->numOfWidgets; j++)
      {
        screenModifiedDefintion->widgetPlacementInformation[j].widgetId = modifiedData->widgetPlacementInformation[j].widgetId;
        screenModifiedDefintion->widgetPlacementInformation[j].widgetXPos = modifiedData->widgetPlacementInformation[j].widgetXPos;
        screenModifiedDefintion->widgetPlacementInformation[j].widgetYPos = modifiedData->widgetPlacementInformation[j].widgetYPos;
      }       
      screenModifiedDefintion->screenTransition.transitionEnable = modifiedData->screenTransition.transitionEnable; 
      screenModifiedDefintion->screenTransition.transition = modifiedData->screenTransition.transition; 
      screenModifiedDefintion->screenTransition.duration = modifiedData->screenTransition.duration;
      screenModifiedDefintion->screenInversion = modifiedData->screenInversion;
//    }
//    else
//    {
//      KLOGE("SORRY---This is not the screen to be modified");
//    }
  }
  else
  {
    //KLOGE("SORRY----Screen to be modified doesn't exist");
  }   
}
  

//delete existing screen in the list
void deleteScreenNode(list_t * screenList, uint16_t screenIdToDelete)
{
  //find the node to be deleted; if it does not, exit the function
  list_node_t* nodeFound = list_find(screenList, screenIdToDelete); 

  if(nodeFound)
  {
    list_node_remove(screenList, nodeFound);
//    KLOGI("Node with Screen ID: %d successfully deleted", screenIdToDelete);
    //KLOGI("Node with Screen ID: %d successfully deleted", nodeFound->componentID);
  }
  else
  {
    //KLOGE("SORRY---Screen to be deleted does not exist");
  }
}




/***********************************************CAROUSEL RELATED FUNCTIONS*********************************************/

list_t * carouselListInit(void)
{
  //Nodal definition of 'Carousel' linked list
  MDL_Carousel_TypeDef * ptrCarouselDefintion;    //to assign value to the carousel node
  MDL_Carousel_TypeDef * carouselDefinition;
  
  //creation of 'Carousel' linked list
  list_t * carouselList; 
  carouselList = list_new();
  
  //adding nodes to the already formed Carousel list as per MAX_NUM_OF_CAROUSELS
  for(int i = 0; i < MAX_NUM_OF_CAROUSELS; i++)
  {
    //node creation of type MDL_Carousel_TypeDef 
    ptrCarouselDefintion = malloc(sizeof(MDL_Carousel_TypeDef));
    list_node_t * carouselNode = list_node_new((void *) ptrCarouselDefintion);  

    //add component ID
    carouselNode->componentID = carouselInformationFlash[i].carouselId;
    
    //node linking
    list_node_t * currentNode = list_rpush(carouselList, carouselNode); 
//    currentNode->val = (MDL_Carousel_TypeDef *) currentNode->val;
    carouselDefinition = (MDL_Carousel_TypeDef *) currentNode->val;
    
    //assignment of values in the node
    carouselDefinition->carouselId = carouselInformationFlash[i].carouselId;
    carouselDefinition->numOfScreens = carouselInformationFlash[i].numOfScreens;
    
    if(carouselDefinition->numOfScreens <= MAX_NUM_OF_SCREENS_IN_A_CAROUSEL)
    {
      for(int j = 0; j < carouselDefinition->numOfScreens; j++)
      {
        carouselDefinition->screenIdArray[j] = carouselInformationFlash[i].screenIdArrayFlash[j];
      }
    }
    else
    {
      //KLOGE("Sorry! The number of screens in a carousel exceed maximum limit allowed");
    }
  }
  return carouselList;
}



/* USER CODE END 0 */


/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

