/**
  ************************************************************************************************************************************
  * File Name          : mdlf.h
  * Description        : This file provides structural definitions of various components and conventions that have been devised
  *                       to together form Menu Definition Language.
  *
  ************************************************************************************************************************************
  */

/**
 * \mainpage %Display Module
 */

 /**
 * \defgroup MDL MDL
 *
 * \author Sonal Shrivastava
 * \date 17.04.17
 */

 /**
 * \ingroup MDL
 * \defgroup Flash_Components MDL Flash components
 *
 * \author Sonal Shrivastava
 * \date 17.04.17
 *
 * \brief MDL Framework's Structural Implementation in flash
 *
 * MDL Structural Implementation file holds the implementation of all the elementary units that form the foundation of MDL
 * (Menu Definition Language). These units pertain to the components or pieces that finally constitute the whole puzzle,
 * which here is, MDL. MDL deals with these individual pieces to give the whole organisation a proper heirarchy, shape,
 * functionality (UI-wise visible) for the Display Module; yet being flexibile enough such that there is scope for
 * future development as well.
 *
 */

 /**
 * \addtogroup Framework
 * @{
 */


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MDLF_H
#define __MDLF_H
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stdint.h"



/*********************************************************MACRO DEFINITIONS***********************************************/
#define MAX_NUM_OF_PARAMETERS 2               /**< \brief Maximum number of parameters that are going to be displayed on DM. */

#define MAX_NUM_OF_ICONS 2                    /**< \brief Maximum number of icons that are going to be displayed on DM. */

#define MAX_NUM_OF_ELEMENTS 9                 /**< \brief Maximum number of elements that the DM supports. */

#define MAX_NUM_OF_WIDGETS 38                 /**< \brief Maximum number of widgets that the DM supports. */

#define MAX_NUM_OF_WIDGETS_ON_A_SCREEN 5      /**< \brief Maximum number of widgets on a screen (for now). */

#define MAX_NUM_OF_SCREENS 10                 /**< \brief Maximum number of screens that the DM supports. */

#define MAX_NUM_OF_SCREENS_IN_A_CAROUSEL 10   /**< \brief Maximum number of screens in a carousel (for now). */

#define MAX_NUM_OF_CAROUSELS 1                /**< \brief Maximum number of carousels that the DM supports. */

#define MAX_ICON_SIZE 5000                    /**< \brief SIze of Icon data in bytes. */



/*****************************************************PARAMETER IDS IN FLASH********************************************/

/**
 * @brief  Parameter IDs stored in Flash
 *
 * The Parameter IDs act as the (1 byte) IDs that shall be assigned to each one of the parameters, eventually displayed
 * on the DM. Only the parameter IDs mentioned below are supported by the DM.
 *
 */
 //TO BE UPDATED BY CP
 /**< \brief Parameter ID 1 = ETA. */
 /**< \brief Parameter ID 2 = Total distance to be travelled. */
 /**< \brief Parameter ID 3 = Current date. */
 /**< \brief Parameter ID 4 = Current Time. */
 /**< \brief Parameter ID 5 = Fuel level Indicator. */
 /**< \brief Parameter ID 6 = DM Battery Level. */
 /**< \brief Parameter ID 7 = Bike Battery Level. */
 /**< \brief Parameter ID 8 = Distance left to take a turn. */
 /**< \brief Parameter ID 9 = Distance to next turn. */
 /**< \brief Parameter ID 10 = BLE Connection status. */




/*****************************************************ICON IDS IN FLASH************************************************/

/**
 * @brief  Icon IDs stored in Flash
 *
 * The Icon IDs act as the (2 byte) IDs that shall be assigned to each one of the icons, eventually displayed
 * on the DM. Only the icon IDs mentioned below are supported by the DM.
 *
 */
 //TO BE UPDATED BY CP
 /**< \brief Icon ID 1 . */
 /**< \brief Icon ID 2 . */
 /**< \brief Icon ID 3 . */
 /**< \brief Icon ID 4 . */
 /**< \brief Icon ID 5 . */
 /**< \brief Icon ID 6 . */
 /**< \brief Icon ID 7 . */
 /**< \brief Icon ID 8 . */
 /**< \brief Icon ID 9 . */
 /**< \brief Icon ID 10 . */

//typedef struct {
//  uint16_t iconId;
//  uint8_t iconName[16];
//  uint16_t iconWidth;
//  uint16_t iconHeight;
//  uint8_t * iconData;
//  };
//}iconAttributes_TypeDef;



/**
 * @brief  Structural definition of an 'Icon' component that is to be shown on DM
 *
 * The following structure specifies the complete definition of a icon, which in turn includes its ID (refer #MDL_Widget_IconIDTypeDef) and
 * its data. Every icon shall be referenced with its uniquely defined number and the data is stored in the flash.
 *
 */
//typedef struct
//{
//  uint8_t iconID;                             /**< \brief Unique ID for the icon (refer #MDL_Widget_IconIDTypeDef). */
//  uint16_t iconHeight;
//  uint16_t iconWidth;
//  uint8_t data[MAX_ICON_SIZE];                              /**< \brief Pointer to where data has been stored.  */
//} MDLF_IconDefinitionTypeDef;



/**
 * @brief  Array definition of all 'Icon' components together
 *
 * The following array is a collection of all the icons that are going to be used on the display. Each element on the array is of type
 * MDL_Icon_DefinitionTypeDef. For any change to be done in the icon data, it must be accessed by its iconID.
 *
 */
// MDLF_IconDefinitionTypeDef iconInformationFlash[MAX_NUM_OF_ICONS] = {
// //iconID, iconHeight, iconWidth, icon data
// {1, 128, 64, {/*icon 1 data*/}},
// {2, 64, 32, {/*icon 2 data*/}}
// };

//MDLF_IconDefinitionTypeDef iconInformation[MAX_NUM_OF_ICONS] = {
//{ 1,
//  128,
//  64,
//  {
//     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//     0x3c, 0x80, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0x00, 0x00,
//     0x00, 0x00, 0x00, 0x00, 0x3c, 0x80, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00,
//     0x00, 0xfe, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x80, 0x07, 0x00,
//     0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00,
//     0x3c, 0x80, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xcf, 0x07, 0x00,
//     0x00, 0x00, 0x00, 0x00, 0x3c, 0x80, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00,
//     0x80, 0x83, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x80, 0x07, 0xf8,
//     0x00, 0x00, 0x00, 0x00, 0x00, 0x81, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00,
//     0x3c, 0x80, 0x07, 0xfc, 0x03, 0x1c, 0x00, 0x3e, 0x1c, 0xc0, 0x03, 0x00,
//     0x00, 0x00, 0x00, 0x00, 0x3c, 0x80, 0x07, 0xff, 0x07, 0x7f, 0x80, 0xff,
//     0x3f, 0xe0, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x80, 0x07, 0xff,
//     0x8f, 0xff, 0xc1, 0xff, 0x3f, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//     0x3c, 0x80, 0x87, 0xff, 0xdf, 0xff, 0xc1, 0xc3, 0x07, 0x7c, 0x00, 0x00,
//     0x00, 0x00, 0x00, 0x00, 0x3c, 0x80, 0x87, 0x0f, 0xfe, 0xff, 0xe3, 0x81,
//     0x03, 0x1e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x80, 0xc7, 0x07,
//     0xfc, 0xe3, 0xe3, 0x81, 0x07, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//     0x3c, 0x80, 0xc7, 0x07, 0xf8, 0xc1, 0xe7, 0x81, 0x87, 0xff, 0x07, 0x00,
//     0x00, 0x00, 0x00, 0x00, 0x3c, 0x80, 0xc7, 0x03, 0xf0, 0x80, 0xe7, 0xc3,
//     0x87, 0xff, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x80, 0xc7, 0x03,
//     0x70, 0x80, 0xc7, 0xe7, 0x83, 0xff, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00,
//     0x3c, 0x80, 0xc7, 0x03, 0x78, 0x80, 0xc7, 0xff, 0x03, 0x00, 0x00, 0x00,
//     0x00, 0x00, 0x00, 0x00, 0x3c, 0x80, 0xc7, 0x03, 0xf8, 0xc0, 0x87, 0xff,
//     0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x80, 0xc7, 0x07,
//     0xfc, 0xc1, 0xc7, 0x7f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//     0x3c, 0xc0, 0x87, 0x0f, 0xfe, 0xff, 0xe3, 0x01, 0x00, 0x00, 0x00, 0x00,
//     0x00, 0x00, 0x00, 0x00, 0x78, 0xc0, 0x83, 0xff, 0xdf, 0xff, 0xe3, 0x03,
//     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0xf1, 0x03, 0xff,
//     0x8f, 0xff, 0xe1, 0xff, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//     0xf0, 0xff, 0x01, 0xfe, 0x0f, 0xff, 0xc0, 0xff, 0x0f, 0x00, 0x00, 0x00,
//     0x00, 0x00, 0x00, 0x00, 0xe0, 0xff, 0x00, 0xfc, 0x03, 0x7c, 0xc0, 0xff,
//     0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x3f, 0x00, 0xf8,
//     0x01, 0x00, 0xe0, 0x01, 0x1e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x00, 0x1e, 0x00, 0x00, 0x00,
//     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x00,
//     0x1e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//     0x00, 0x20, 0xf0, 0xc7, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//     0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0xe0, 0xff, 0x0f, 0x00, 0x00, 0x00,
//     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0xc0, 0xff,
//     0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 0xff, 0xff, 0xff,
//     0xff, 0xff, 0x01, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//     0xf8, 0xff, 0xff, 0xff, 0xff, 0xff, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00,
//     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00,
//     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//     0x00, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//     0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00,
//     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//     0x00, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//     0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00,
//     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//     0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//     0x00, 0x00, 0x00, 0x00, 0x40, 0x24, 0x20, 0x00, 0x00, 0x08, 0x46, 0x02,
//     0x00, 0x80, 0xc0, 0x40, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x6e, 0x6a, 0xc0,
//     0xa4, 0x48, 0x04, 0xaa, 0xac, 0x8c, 0xaa, 0xac, 0x00, 0x00, 0x00, 0x00,
//     0x6a, 0xa4, 0xaa, 0x20, 0xea, 0xa4, 0x64, 0x66, 0xaa, 0x46, 0x4a, 0x8a,
//     0x00, 0x00, 0x00, 0x00, 0x4c, 0xa4, 0xaa, 0x20, 0xaa, 0xa2, 0x44, 0x2a,
//     0xaa, 0x28, 0xaa, 0x4c, 0x00, 0x00, 0x00, 0x00, 0xe8, 0xa8, 0x6c, 0xc4,
//     0xa4, 0x42, 0xee, 0x2a, 0xcc, 0x26, 0x6c, 0xe8, 0x00, 0x00, 0x00, 0x00,
//     0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06,
//     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//     0x00, 0x00, 0x00, 0x00 }
//},

//};



/*****************************************************ELEMENT DEFINITIONS********************************************/
/**
 * @brief  Structure defining an 'Element' component (space) on a screen in its crude/ raw form
 *
 * An element is nothing but a space reserved on a particular screen which is then dedicated to show either text, value or icon.
 * The following structure specifies the attributes that are characteristic to an element. It comprises of simply element's
 * UID (Unique ID), its width and height measures.
 *
 */
typedef struct
{
  uint16_t elementID;                       /**< \brief Unique ID for the element. */
  uint16_t elementWidth;                    /**< \brief Width of the element (max 400).  */
  uint16_t elementHeight;                   /**< \brief Height of the element (max 240).  */
} MDLF_ElementAttributesTypeDef;



/**
 * @brief  Array definition of all 'Element' components together
 *
 * The following array is a collection of all the 'Elements' that are going to be used on the display. Each element on the array is of type
 * MDL_Element_AttributesTypeDef. For any change to be done in the element's data, it must be accessed by its elementID.
 *
 */
MDLF_ElementAttributesTypeDef elementInformationFlash[MAX_NUM_OF_ELEMENTS] = { //elementID, elementWidth, elementHeight
      /*square box for icon*/                       {1, 70, 70},
      /*rectangular box for text (main menu)*/              {2, 218, 60},
      /*rectangular box for menubar icon - four dots*/          {3, 69, 8},
      /*'NEURON BATTERY' - ETA screen*/                 {4, 218, 22},
      /*'Battery percentage' - ETA screen*/               {5, 218, 48},
      /*big font 'strings' in screens with single icon*/          {6, 400, 42},
      /*strings like 'Hold to access'*/                 {7, 400, 16},
      /*alert zebra bar*/                         {8, 402, 10},
      /*rectangular box for menubar icon - five dots*/          {9, 89, 8},
                                      };


/*****************************************************WIDGET DEFINITIONS***********************************************/

/**
 * @brief  MDLF Widget Color Inversion characteristic description
 *
 * The following enum describes the color inversion that the widget is capable of displaying. It can either
 * be displayed as 'Black (parameter) over white (background)' type or 'White (parameter) over black (background)'
 * type. If it is zero, it means no inversion is there. That means, widget is dislpayed in its default skin (White
 * over black combination). If it is one, it means inversion is present for the widget and it is displayed in
 * inverted color form (Black over white).
 */
typedef enum
{
  W_NORMAL        = 0x00,             /**< \brief Widget displayed in white over black skin. */
  W_INVERTED       = 0x01,                /**< \brief Widget displayed in Black over white skin. */
} MDLF_WidgetColorInversionTypeDef;



/**
 * @brief  MDLF Widget Animation characteristic description
 *
 * The following enum describes the animation types that the widget supports. Only the below mentioned animation types
 * are supported. In order for the widget to show any sort of animation, ensure that the 'animationEnable' is set to 1
 * (refer #MDL_Widget_AnimationParamTypeDef).
 */
typedef enum
{
  W_NOANIMATION         = 0x00,             /**< \brief Widget supports no animation. */
  W_SLIDEUP           = 0x01,             /**< \brief Widget slides upward in the screen. */
  W_SLIDEDOWN             = 0x02,             /**< \brief Widget slides downward in the screen. */
  W_FADEIN              = 0x03,             /**< \brief Widget fades into the screen. */
  W_FADEOUT             = 0x04,             /**< \brief Widget fades out of the screen. */
} MDLF_WidgetAnimationTypeDef;



/**
 * @brief  Structure defining animation for a MDL Widget (Name to be changed)
 *
 * The following structure specifies the parameters that are to be given to enable and define animation of a widget on a
 * particular screen. In order to enable animation for a widget, first off set the 'animationEnable' parameter. If it is
 * set to zero all other settings are ignored (even if entered) and hence, no animation is set for that widget. Hence,
 * animation settings are applicable if and only if 'animationEnable' is set.
 *
 * It encompasses and defines values like 'animationEnable' bit, the 'type' of animation to be set for that widget, which is
 * defined as per only the animations that are supported for the widget (refer #MDL_Widget_AnimationTypeDef) and the last
 * parameter defines the time duration for which the animation will last for that widget.
 *
 */
//typedef struct
//{
//  uint8_t animationEnable;                /**< \brief Defines whether widget has any animation defined or not. */
//  MDL_Widget_AnimationTypeDef type;       /**< \brief Defines the type of animation that widget shall have. */
//  uint16_t duration;                      /**< \brief Defines the duration of animation for the widget. */
//} MDL_Widget_AnimationParamTypeDef;



/**
 * @brief  Structure defining a MDL 'Widget' component on a particular screen (Name to be changed)
 *
 * Basically, keeping explanation straightforward and lucid, an element comes alive when extra attributes are clubbed to it
 * which culminates into a @b widget on the screen. Hence, an element in itself is nothing but a reserved space on screen or,
 * in other words, rectangular boundary defined for the object to be shown. To create a widget, following characteristics are
 * mandatory to be provided to complete its existence by its definition.
 *
 * - Element ID (skeleton of the widget)
 * - Object ID (body of the widget) and other related information
 * - extra attributes (like animation, color inversion etc.)
 *
 * The first value signifies Widget ID, acting as a unique Identification number for the widget; basically its identity.
 *
 * The second value signifies Element ID, as mentioned above, upon which element it will rest upon (skeleton), referenced from
// * array elementInformation.
 *
// * The third value holds all the information about the object inside the widget (refer #MDL_Widget_ObjectDefsTypeDef).
 *
 *  The fourth value holds the color inverion information for the widget (refer #MDL_Widget_ColorInversionTypeDef).
 *
 * The fifth value holds the animation related information for the widget (refer #MDL_Widget_AnimationParamTypeDef).
 */
typedef struct
{
    uint8_t LiveFlag;                 /**< \brief Whether info is stale or fresh. */
  uint16_t widgetId;                    /**< \brief Identification number for widget. */
  uint8_t elementID;                  /**< \brief Identification number for the element. */
  uint8_t widgetObjectType;               /**< \brief Type of object to be put into the widget (icon = 0, text = 1). */
  uint8_t objectID;                 /**< \brief ID of object being stored (Text (Parameter) ID, Icon ID). */
  uint8_t verticalAlignment;              /**< \brief Vertical Alignment of the object being put into the widget (0-bottom, 1-Centre, 2-Top). */
  uint8_t horizontalAlignment;            /**< \brief Horizontal Alignment of the object being put into the widget (0-Left, 1-Centre, 2-Right). */
  MDLF_WidgetColorInversionTypeDef widgetInversion; /**< \brief No Inversion = 0, Inversion = 1. */
  MDLF_WidgetAnimationTypeDef widgetAnimation;    /**< \brief Animation type supported by the widget. */
} MDLF_WidgetAttributesTypeDef;



/**
 * @brief  Array definition of all 'Widget' components together
 *
 * The following array is a collection of all the 'Widgets' that are going to be used on the display. Each element on the array is of type
 * MDL_Widget_TypeDef. For any change to be done in the widget's data, it must be accessed by its widgetId.
 *
 */
MDLF_WidgetAttributesTypeDef widgetInformationFlash[MAX_NUM_OF_WIDGETS] = {
//widgetId, elementID, widgetObjectType, objectID, verticalAlignment, horizontalAlignment, widgetInversion, widgetAnimation
//screen ID 13 info -- ETA Screen
  {0, 1, 1, 0, 1, 1, 1, 0, 0},      //flag icon widget (ETA TIME)
  {0, 2, 2, 1, 1, 1, 1, 0, 0},      //Text for ETA
  {0, 3, 1, 0, 2, 1, 1, 0, 0},      //Locate icon
  {0, 4, 2, 1, 2, 1, 1, 0, 0},      //Text for distance to be travelled
  {0, 5, 3, 0, 3, 1, 1, 0, 0},      //menubar 1 of 4 icon

//screen ID 10 info -- Intro Screen
  {0, 6, 1, 0, 4, 1, 1, 0, 0},      //Ride Logo Icon Widget
  {0, 7, 2, 1, 3, 1, 1, 0, 0},      //Text "Let's Ride"
  {0, 8, 1, 0, 5, 1, 1, 0, 0},      //DM Battery Icon
  {0, 9, 4, 1, 4, 1, 1, 0, 0},      //Text "Neuron Battery"
  {0, 10, 5, 1, 5, 1, 1, 0, 0},     //Text /*battery percentage*/

//screen ID 15 info -- Settings Screen
  {0, 11, 1, 0, 6, 1, 1, 0, 0},     //Settings icon widget
  {0, 12, 6, 1, 6, 1, 1, 0, 0},     //Text "Settings"
  {0, 13, 7, 1, 7, 1, 1, 0, 0},     //Text "Hold to access"
  {0, 14, 3, 0, 7, 1, 1, 0, 0},     //menubar 4 of 4 icon

//screen ID 21 info -- Severe Condition Screen
  {0, 15, 1, 0, 8, 1, 1, 0, 0},     //Severe conditions icon widget
  {0, 16, 6, 1, 8, 1, 1, 0, 0},     //Text "Severe conditions"
  {0, 17, 7, 1, 9, 1, 1, 0, 0},     //Text "Hold to send"
  {0, 18, 9, 0, 9, 1, 1, 0, 0},     //menubar 4 of 5 icon

//screen ID 17 info -- Send Alert Screen
  {0, 19, 1, 0, 10, 1, 1, 0, 0},      //Send alert icon widget
  {0, 20, 6, 1, 10, 1, 1, 0, 0},      //Text "Send alert"

//screen ID 34 info -- Suspicious Bike activity Screen
  {0, 21, 1, 0, 11, 1, 1, 0, 0},      //Suspicious bike icon widget
  {0, 22, 8, 0, 12, 1, 1, 0, 0},      //Urgent Alert Zebra icon widget
  {0, 23, 6, 1, 11, 1, 1, 0, 0},      //Text "Suspicious bike activity"

//screen ID 18 info -- No Fuel (Alert Menu) Screen
  {0, 24, 1, 0, 13, 1, 1, 0, 0},      //No Fuel icon widget
  {0, 25, 6, 1, 12, 1, 1, 0, 0},      //Text "No Fuel"
  {0, 26, 9, 0, 14, 1, 1, 0, 0},      //menubar 1 of 5 icon

//screen ID 19 info -- Puncture Screen
  {0, 27, 1, 0, 15, 1, 1, 0, 0},      //Puncture icon widget
  {0, 28, 6, 1, 13, 1, 1, 0, 0},      //Text "Puncture"
  {0, 29, 7, 1, 14, 1, 1, 0, 0},      //Text "Hold to send"
  {0, 30, 9, 0, 16, 1, 1, 0, 0},      //menubar 2 of 5 icon

//screen ID 20 info -- Accident Screen
  {0, 31, 1, 0, 17, 1, 1, 0, 0},      //Accident icon widget
  {0, 32, 6, 1, 15, 1, 1, 0, 0},      //Text "Accident"
  {0, 33, 7, 1, 16, 1, 1, 0, 0},      //Text "Hold to send"
  {0, 34, 9, 0, 18, 1, 1, 0, 0},      //menubar 3 of 5 icon

//screen ID 22 info -- Cancel (alert menu) Screen
  {0, 35, 1, 0, 19, 1, 1, 0, 0},      //Cancel icon widget
  {0, 36, 6, 1, 17, 1, 1, 0, 0},      //Text "Cancel"
  {0, 37, 7, 1, 18, 1, 1, 0, 0},      //Text "Hold to confirm"
  {0, 38, 9, 0, 20, 1, 1, 0, 0},      //menubar 5 of 5 icon
};


/***********************************************SCREEN RELATED DEFINITIONS*********************************************/

/**
 * @brief  MDLF Screen Color Inversion characteristic description
 *
 * The following enum describes the color inversion that the widget is capable of displaying. It can either
 * be displayed as 'Black (parameter) over white (background)' type or 'White (parameter) over black (background)'
 * type. If it is zero, it means no inversion is there. That means, widget is dislpayed in its default skin (White
 * over black combination). If it is one, it means inversion is present for the widget and it is displayed in
 * inverted color form (Black over white).
 */
typedef enum
{
  SCREEN_NORMAL         = 0x00,             /**< \brief Widget displayed in white over black skin. */
  SCREEN_INVERTED       = 0x01,             /**< \brief Widget displayed in Black over white skin. */
} MDLF_ScreenInversionTypeDef;




/**
 * @brief  MDL 'Screen' component Transition Parameter description
 *
 * The following enum describes the transition types that the screen supports. Only the below mentioned transition types
 * are supported. In order for the screen to show any sort of transition, ensure that the 'transitionEnable' is set to 1
 * (refer #MDL_Screen_TransitionParamTypeDef) .
 */
typedef enum
{
  SCREEN_NOTRANSITION           = 0x00,             /**< \brief Screen supports no transition. */
  SCREEN_SLIDEUP              = 0x01,             /**< \brief Screen slides upward. */
  SCREEN_SLIDEDOWN            = 0x02,             /**< \brief Screen slides downward. */
  SCREEN_SLIDERIGHT           = 0x03,             /**< \brief Screen slides towards the right. */
  SCREEN_SLIDELEFT            = 0x04,             /**< \brief Screen slides towards the left. */
} MDLF_ScreenTransitionTypeDef;



/**
 * @brief  Structure defining Widget related information for a MDL 'Screen' component (Name to be changed)
 *
 * The following structure specifies the parameters that are to be given to define the placement of a widget on a screen with proper coordinates.
 * The structure consists of:
 *
 * - Widget ID; that is going to be placed on the screen (refer #MDL_Widget_TypeDef)
 * - Widgets X & Y coordinates on the screen (ensure it fits perfectly and does not overlap any other object on the screen and maintains clear
 *   visibility.
 *
 */
typedef struct
{
  uint16_t f_widgetId;                            /**< \brief Information about all widgets on the screen. */
  uint16_t f_widgetXPos;                              /**< \brief X-Coordinate for the widget (max = 240 - width).  */
  uint16_t f_widgetYPos;                              /**< \brief Y-Coordinate for the widget (max = 400 - height).  */
} MDLF_Screen_WidgetPlacementTypeDef;



/**
 * @brief  Array definition of all 'Widget' components present in a particular screen
 *
 * The following array is a collection of all the 'Widgets' that are going to be displayed on a particular screen. Each element on the array
 * is of the type MDL_Screen_WidgetPlacementTypeDef. The array will be of size defined by the number of widgets eventually to be put on the
 * screen, which is equal to 'numOfWidgets' member defined in MDL_Screen_TypeDef.
 *
 * Since the screen has to bother only about the widget's placement on a screen, rest of the information about each widget is found in the
 * array widgetInformation, referred to by its ID.
 *
 */
 MDLF_Screen_WidgetPlacementTypeDef widgetPlacementInformationFlash[MAX_NUM_OF_WIDGETS_ON_A_SCREEN];



/**
 * @brief  Structure defining a MDL 'Screen' component (Name to be changed)
 *
 * The following structure specifies the attributes of the 'screen' component of the MDL. It comprises its Identifcation
 * number, its resolution height and width, number of widgets that are to be shown on the screen and their complete
 * information and transition related definition for that particular screen. Following attributes are a mandate to define
 * a screen completely in compliance with its definition.
 *
 * - Screen ID (its UID)
 * - Resolution width and height (size of the screen)
 * - total number of widgets on the screen and their complete information
 * - placement information about each widget with its X & Y coordinates defined properly.
 * - extra attributes but not necessary (like transitions etc.)
 *
 * The first value signifies Screen ID, acting as a unique Identification number for the screen; basically its identity.
 *
 * The second and third values signify its width and height resolution.
 *
 * The fourth value specifies the total number of widgets on the screen.
 *
 * The fifth value holds complete info about the widgets' placements to be shown on the screen.
 *
 * The sixth value holds complete info about screen's transitions (if there is any defined).
 *
 */
typedef struct
{
  uint16_t screenId;                                      /**< \brief Identification number of a screen. */
  uint16_t screenWidth;                                   /**< \brief Width resolution of the screen (default = max value). */
  uint16_t screenHeight;                                  /**< \brief Height resolution of the screen (default = max value). */
  uint8_t numOfWidgets;                                   /**< \brief Number of widgets on the screen. */
  MDLF_Screen_WidgetPlacementTypeDef widgetPlacementInformationFlash[MAX_NUM_OF_WIDGETS_ON_A_SCREEN];                           /**< \brief Information about all widgets on the screen. */
  MDLF_ScreenTransitionTypeDef screenTransition;          /**< \brief Transition supported by the screen. */
  MDLF_ScreenInversionTypeDef screenInversion;            /**< \brief Inversion supported by the screen. */
} MDLF_ScreenAttributesTypeDef;



/**
 * @brief  Array definition of all 'Screen' components together
 *
 * The following array is a collection of all the 'Screens' that are going to be grouped into a particular carousel. Each element on
 * the array is of type MDL_Screen_TypeDef. For any change to be done in the screen's data, it must be accessed by its screenId.
 *
 */
MDLF_ScreenAttributesTypeDef screenInformationFlash[MAX_NUM_OF_SCREENS] = {
// screenId, screenWidth, screenHeight, numOfWidgets, numOfWidgets * {widgetId, widgetXPos, widgetYPos}, screenTransition, screenInversion}
//SCREEN_NORMAL-----SCREEN_INVERTED
{13, 400, 240, 5, {{1, 30, 34}, {2, 140, 44}, {3, 30, 132}, {4, 140, 142}, {5, 165, 216}}, 0, SCREEN_NORMAL},//ETA screen
{10, 400, 240, 5, {{6, 30, 34}, {7, 140, 44}, {8, 30, 132}, {9, 140, 132}, {10, 131, 154}}, 0, SCREEN_NORMAL},//Intro Screen
{15, 400, 240, 4, {{11, 165, 34}, {12, 0, 130}, {13, 0, 187}, {14, 165, 217}}, 0, SCREEN_NORMAL},//settings  screen
{21, 400, 240, 4, {{15, 165, 34}, {16, 0, 130}, {17, 0, 187}, {18, 165, 217}}, 0, SCREEN_NORMAL},//severe condn
{17, 400, 240, 2, {{19, 165, 34}, {20, 0, 130}}, 0, SCREEN_NORMAL},//send alert screen
{34, 400, 240, 3, {{21, 165, 24}, {22, 0, 107}, {23, 2, 130}}, 0, SCREEN_INVERTED},//bike theft screen
{18, 400, 240, 3, {{24, 165, 34}, {25, 0, 130}, {26, 155, 217}}, 0, SCREEN_NORMAL},//no fuel (alert  menu) screen
{19, 400, 240, 4, {{27, 165, 34}, {28, 0, 130}, {29, 0, 187}, {30, 165, 217}}, 0, SCREEN_NORMAL},//puncture (alert menu) screen
{20, 400, 240, 4, {{31, 165, 34}, {32, 0, 130}, {33, 0, 187}, {34, 165, 217}}, 0, SCREEN_NORMAL},//accident (alert menu) screen
{22, 400, 240, 4, {{35, 165, 34}, {36, 0, 130}, {37, 0, 187}, {38, 165, 217}}, 0, SCREEN_NORMAL},//cancel (alert menu) screen

//{10, 400, 240, 2, {{1, 390, 140}, {2, 380, 110}}, 0, 0},
//{20, 400, 240, 2, {{3, 400, 150}, {4, 410, 120}}, 1, 1},
};


/***********************************************CAROUSEL RELATED DEFINITIONS*********************************************/


/**
 * @brief  Structure defining Screen's transition related information inside a MDL 'Carousel' component (Name to be changed)
 *
 * The following structure specifies the parameters that are to be given to define the transition of a screen into another screen.
 * The structure consists of:
 *
 * - Screen ID; which identifies which screen the tansition is going to be applied to (refer #MDL_Screen_TypeDef).
 * - Transitional information of the screen in hand (refer #MDL_Screen_TransitionParamTypeDef).
 *
 */
//typedef struct
//{
//  uint16_t screenId;                                      /**< \brief Identification number of a screen. */
//  MDL_Screen_TransitionParamTypeDef transitionParam;      /**< \brief Information about transition of the screen. */
//} MDLF_Carousel_ScreenTransitionTypeDef;



/**
 * @brief  Array definition of transitions related to all 'Screen' components present in a particular carousel
 *
 * The following array is a collection of transitions defined for all the 'Screens' present in a particular carousel. Each element on the array
 * is of the type MDL_Carousel_ScreenTransitionTypeDef. The array will be of size defined by the number of widgets eventually to be put on the
 * screen, which is equal to 'numOfScreens' member defined in MDL_Carousel_TypeDef.
 *
 * Since the carousel has to bother only about the screens' transitions in a carousel, rest of the information about each screen is found in the
 * array screenInformation, referred to by its ID.
 *
 */
//MDL_Carousel_ScreenTransitionTypeDef screenTransitionInformation[MAX_NUM_OF_SCREENS_IN_A_CAROUSEL];




/**
 * @brief  Structure defining a MDL 'Carousel' component (Name to be changed)
 *
 * The following structure specifies the attributes of the 'Carousel' component of the MDL. It comprises its Identifcation
 * number, number of screens that are to be grouped into the carousel and their transitional information. Following attributes
 * are a mandate to define a carousel completely in compliance with its definition.
 *
 * - Carousel ID (its UID).
 * - total number of screens in the carousel and their complete information.
 * - transitions defined for all screens.
 *
 * The first value signifies Carousel ID, acting as a unique Identification number for the carousel; basically its identity.
 *
 * The second value specifies the total number of screens inside the carousel.
 *
 * The third value holds screen IDs of all the screens to be grouped inside the carousel.
 *
 */
typedef struct
{
  uint8_t carouselId;                                       /**< \brief Identification number for a carousel. */
  uint8_t numOfScreens;                                     /**< \brief Number of screens in the carousel. */
  uint8_t screenIdArrayFlash[MAX_NUM_OF_SCREENS_IN_A_CAROUSEL];       /**< \brief List of screen IDs grouped into the carousel. */
//  screenTransitionInformation[numOfScreens];              /**< \brief Information about transitions of all screens in the carousel. */
} MDLF_CarouselAttributesTypeDef;



/**
 * @brief  Array definition of all 'Carousel' components together
 *
 * The following array is a collection of all the 'Carousels' that exist in the DM. Each element on the array is of type MDL_Carousel_TypeDef.
 * For any change to be done in the carousel's data, it must be accessed by its carouselId.
 *
 */
MDLF_CarouselAttributesTypeDef carouselInformationFlash[MAX_NUM_OF_CAROUSELS] = {
// carouselId, numOfScreens, {numOfScreens * screenId}
{1, 6, {17, 18, 19, 20, 21, 22}}
};




#ifdef __cplusplus
}
#endif
#endif /*__ MDLF_H */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT KPIT TECHNOLOGIES LTD*****END OF FILE*******************************************/

