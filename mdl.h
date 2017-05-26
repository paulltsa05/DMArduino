/**
  ************************************************************************************************************************************
  * File Name          : mdl.h
  * Description        : This header file provides nodal definitions of linked lists formed for various MDL components.
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
 *
 *
 * The @b MDL stands for <b>Menu Definition Language</b>. This language signifies the heirarchical composition that makes up for 
 * the whole language definition. It comprises of numerous components that are core to its organization and definition. It lays 
 * down the structural definitions pertaining to each component and their affiliated parameters as well. It has been defined in 
 * such a way that the whole language togther with the state machine for the Display Module governs the working of DM. It will 
 * also eventually take into consideration the user's input that will be monitored by the state machine which drive the working 
 * of DM based on Menu Definition Language (acronym used across the document MDL).
 */

 /**
 * \ingroup MDL 
 * \defgroup Framework MDL Framework
 *
 * \author Sonal Shrivastava
 * \date 17.04.17
 *
 * \brief MDL Framework's Structural Implementation
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
#ifndef __MDL_H
#define __MDL_H
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stdint.h"
#include "linked_list.h"
//#include "cpcb_if.h"
 //#include "mdlf.h"



#define VICTORY 1

#define FAILURE 0

#define MAX_NUM_OF_ELEMENTS 9            /**< \brief Maximum number of elements that the DM supports. */

#define MAX_NUM_OF_WIDGETS 38           /**< \brief Maximum number of widgets that the DM supports. */

#define MAX_NUM_OF_WIDGETS_ON_A_SCREEN 5      /**< \brief Maximum number of widgets on a screen (for now). */

#define MAX_NUM_OF_SCREENS 10           /**< \brief Maximum number of screens that the DM supports. */

#define MAX_NUM_OF_SCREENS_IN_A_CAROUSEL 10     /**< \brief Maximum number of screens in a carousel (for now). */

#define MAX_NUM_OF_CAROUSELS 1            /**< \brief Maximum number of carousels that the DM supports. */

#define IS_VALID_WIDGET(VALUE) (((VALUE) > 0 ))

#define IS_VALID_NEW_SCREEN(VALUE) (((VALUE) = 0 ))


/*****************************************************PARAMETER ID DEFINITIONS********************************************/
///** 
// * @brief  MDL Element's (held) / MDL supported Parameter IDs  
// *
// * The following enum specifies the IDs assigned to each one of the parameters that can be displayed on the DM. Only the parameter
// * mentioned below are supported by the DM, and no other parameters can be supported (static or dynamic).
// *
// */  
typedef enum 
{
  ETA               = 1,                  /**< \brief Parameter ID 1 = ETA. */
  DISTANCE_TO_COVER     = 2,                  /**< \brief Parameter ID 2 = Total distance to be travelled . */

  PARAMID2          = 3,                  /**< \brief Parameter ID 3 = Time needed for coverage. */
  PARAMID3          = 4,                  /**< \brief Parameter ID 4 = Current date. */
  PARAMID4          = 5,                  /**< \brief Parameter ID 5 = Current Time. */
  PARAMID5          = 6,                  /**< \brief Parameter ID 6 = Fuel level Indicator. */
  PARAMID6          = 7,                  /**< \brief Parameter ID 7 = DM Battery Level. */
  PARAMID7          = 8,                  /**< \brief Parameter ID 8 = Bike Battery Level. */
  PARAMID8          = 9,                  /**< \brief Parameter ID 9 = Distance left to take a turn. */
  PARAMID9          = 10,                 /**< \brief Parameter ID 10 = Distance to next turn. */
  PARAMID10         = 11,               /**< \brief Parameter ID 11 = BLE Connection status. */
} MDL_Widget_ParamIDTypeDef;


///** 
// * @brief  Structural definition of a 'Parameter' component that is to be shown on DM
// *
// * The following structure specifies the complete definition of a parameter, which in turn includes its ID (refer #MDL_Widget_ParamIDTypeDef) and 
// * its data. Every parameter shall be referenced with its uniquely defined number and the data could be either be in value format or text format, 
// * depends on what kind of information it is meant to hold.
// *  
// */  
typedef struct 
{
  MDL_Widget_ParamIDTypeDef parameterID;                      /**< \brief Unique ID for the parameter (refer #MDL_Widget_ParamIDTypeDef). */
  void * data;                                                /**< \brief Pointer to where data has been stored.  */    
} MDL_Parameter_DefinitionTypeDef;



///** 
// * @brief  Array definition of all 'Parameter' components together 
// *
// * The following array is a collection of all the parameters that are going to be used on the display. Each element on the array is of type 
// * MDL_Parameter_DefinitionTypeDef. Each parameter must be accessed by its parameterID memeber.
// *  
// */  
//MDL_Parameter_DefinitionTypeDef parameterInformation[MAX_NUM_OF_PARAMETERS];



/*****************************************************ICON ID DEFINITIONS************************************************/
///** 
// * @brief  MDL Element's (held) / MDL supported Icon IDs 
// *
// * The following enum specifies the IDs assigned to each one of the icons that can be shown on the DM. Only the icons mentioned below 
// * are supported by the DM, and no other different icons can be supported (static or dynamic). A modified icon holds same ID even after
// *  it has been modified (dynamically), it is NOT given a new ID.
// *
// */  
typedef enum 
{
  ETA_FLAG      = 1,                  /**< \brief Icon ID 1. */
  ETA_LOCATE      = 2,                  /**< \brief Icon ID 2. */
  MENUBAR1OF4     = 3,                  /**< \brief Icon ID 3. */
  ICONID4         = 4,                  /**< \brief Icon ID 4. */
  ICONID5         = 5,                  /**< \brief Icon ID 5. */
  ICONID6         = 6,                  /**< \brief Icon ID 6. */
  ICONID7         = 7,                  /**< \brief Icon ID 7. */
  ICONID8         = 8,                  /**< \brief Icon ID 8. */
  ICONID9         = 9,                  /**< \brief Icon ID 9. */
  ICONID10      = 10,                 /**< \brief Icon ID 10. */
} MDL_Widget_IconIDTypeDef;



///** 
// * @brief  Structural definition of an 'Icon' component that is to be shown on DM
// *
// * The following structure specifies the complete definition of a icon, which in turn includes its ID (refer #MDL_Widget_IconIDTypeDef) and 
// * its data. Every icon shall be referenced with its uniquely defined number and the data is stored in the flash. 
// *  
// */  
typedef struct 
{
  MDL_Widget_IconIDTypeDef iconID;                            /**< \brief Unique ID for the icon (refer #MDL_Widget_IconIDTypeDef). */
  void * data;                                                /**< \brief Pointer to where data has been stored.  */    
} MDL_Icon_DefinitionTypeDef;



///** 
// * @brief  Array definition of all 'Icon' components together 
// *
// * The following array is a collection of all the icons that are going to be used on the display. Each element on the array is of type 
// * MDL_Icon_DefinitionTypeDef. For any change to be done in the icon data, it must be accessed by its iconID.
// *  
// */  
//MDL_Icon_DefinitionTypeDef iconInformationFlash[MAX_NUM_OF_ICONS];



/*****************************************************ELEMENT DEFINITIONS********************************************/
///**
// * @brief  Nodal Structure defining an 'Element' component (space) on a screen in its crude/ raw form
// *
// * An element is nothing but a space reserved on a particular screen which is then dedicated to show either text, value or icon.
// * The following structure specifies the attributes that are characteristic to an element. It comprises of simply element's
// * UID (Unique ID), its width and height measures.
// *
// */
typedef struct
{
  uint16_t elementID;                       /**< \brief Unique ID for the element. */
  uint16_t elementHeight;                   /**< \brief Height of the element (max 240).  */
  uint16_t elementWidth;                    /**< \brief Width of the element (max 400).  */
} MDL_Element_TypeDef;



/** 
 * @brief  Array definition of all 'Element' components together 
 *
 * The following array is a collection of all the 'Elements' that are going to be used on the display. Each element on the array is of type 
 * MDL_Element_AttributesTypeDef. For any change to be done in the element's data, it must be accessed by its elementID.
 *  
 */  
//MDL_Element_AttributesTypeDef elementInformationFlash[MAX_NUM_OF_ELEMENTS] = {{1,100,20},{2, 160,160}};


/*****************************************************WIDGET DEFINITIONS********************************************/
/** 
 * @brief  MDL Element's (held) Object Type description  
 *
 * The following union indicates the 'type' of the object that an element on a particular screen is capable 
 * of displaying. It can either be a 'Textual' type object, a 'Value' type object or an 'Icon' type object at a time.
 * Proper specifications must be adhered to, to make sure that the object comfortably fits into the element and is clearly
 * visible on the screen.
 */  
typedef union objectType 
{
//  MDL_Widget_ParamIDTypeDef parameter;          /**< \brief Element holds a pre-defined parameter's value. */
//  MDL_Widget_IconIDTypeDef icon;                /**< \brief Element holds an icon . */
  char * textString;                            /**< \brief Element holds a text string that has come from phone. */
} OBJECTTYPE;



///**
// * @brief  Structure defining widget's object related definitions
// *
// * The following structure specifies the attributes that are to be defined for the object inside any element. The first
// * value defines the 'type' of the object (refer union #OBJECTTYPE). If it is a parameter, its value is shown in permissible
// * format. If it is an icon, then relevant icon is displayed. If it is a text string, then it is shown as per what has been
// * sent from phone via BLE.
// *
// * The second value defines the UID of either parameter or icon that has been chosen to be displayed in the element. <b> It
// * shall be zero if there is a text entry inside the element. </b>
// *
// * The third value defines the data of the particular chosen object for that element. For a parameter, it is parameter's value;
// * for an icon it is icon data and for a <b>text string </b> to be displayed, this pointer holds the address of the string to
// * be displayed.
// *
// * The fourth value is a pointer to the callback function of the object (in case it needs to be updated).
// *
// */
typedef struct
{
  void * data;                              /**< \brief Pointer to the data to be shown inside the element as per the type specified. */
//  void * updateCB;                            /**< \brief Pointer to the update callback function of the parameter. */
//will have a generic callback function handleWidgetCB(void * data)
} MDL_Widget_ObjectDefsTypeDef;



///**
// * @brief  Structure defining animation for a MDL Widget (Name to be changed)
// *
// * The following structure specifies the parameters that are to be given to enable and define animation of a widget on a
// * particular screen. In order to enable animation for a widget, first off set the 'animationEnable' parameter. If it is
// * set to zero all other settings are ignored (even if entered) and hence, no animation is set for that widget. Hence,
// * animation settings are applicable if and only if 'animationEnable' is set.
// *
// * It encompasses and defines values like 'animationEnable' bit, the 'type' of animation to be set for that widget, which is
// * defined as per only the animations that are supported for the widget (refer #MDL_Widget_AnimationTypeDef) and the last
// * parameter defines the time duration for which the animation will last for that widget.
// *
// */
typedef struct
{
  uint8_t animationEnable;                /**< \brief Defines whether widget has any animation defined or not. */
  uint16_t duration;                      /**< \brief Defines the duration (in seconds) of animation for the widget. */
} MDL_Widget_AnimationParamTypeDef;


///**
// * @brief  MDLF Widget Animation characteristic description
// *
// * The following enum describes the animation types that the widget supports. Only the below mentioned animation types
// * are supported. In order for the widget to show any sort of animation, ensure that the 'animationEnable' is set to 1
// * (refer #MDL_Widget_AnimationParamTypeDef).
// */
typedef enum
{
  WIDGET_NOANIMATION        = 0x00,       /**< \brief No animation is supported by the widget. */
  WIDGET_SLIDEUP              = 0x01,       /**< \brief Widget slides upward in the screen. */
  WIDGET_SLIDEDOWN              = 0x02,       /**< \brief Widget slides downward in the screen. */
  WIDGET_FADEIN               = 0x03,       /**< \brief Widget fades into the screen. */
  WIDGET_FADEOUT              = 0x04,       /**< \brief Widget fades out of the screen. */
} MDL_WidgetAnimationTypeDef;


///**
// * @brief  MDLF Widget Color Inversion characteristic description
// *
// * The following enum describes the color inversion that the widget is capable of displaying. It can either
// * be displayed as 'Black (parameter) over white (background)' type or 'White (parameter) over black (background)'
// * type. If it is zero, it means no inversion is there. That means, widget is dislpayed in its default skin (White
// * over black combination). If it is one, it means inversion is present for the widget and it is displayed in
// * inverted color form (Black over white).
// */
typedef enum
{
  WIDGET_NORMAL         = 0x00,             /**< \brief Widget displayed in white over black skin. */
  WIDGET_INVERTED       = 0x01,               /**< \brief Widget displayed in Black over white skin. */
} MDL_WidgetColorInversionTypeDef;


///**
// * @brief  Structure defining a MDL 'Widget' component on a particular screen (Name to be changed)
// *
// * Basically, keeping explanation straightforward and lucid, an element comes alive when extra attributes are clubbed to it
// * which culminates into a @b widget on the screen. Hence, an element in itself is nothing but a reserved space on screen or,
// * in other words, rectangular boundary defined for the object to be shown. To create a widget, following characteristics are
// * mandatory to be provided to complete its existence by its definition.
// *
// * - Element ID (skeleton of the widget)
// * - Object ID (body of the widget) and other related information
// * - extra attributes (like animation, color inversion etc.)
// *
// * The first value signifies Widget ID, acting as a unique Identification number for the widget; basically its identity.
// *
// * The second value signifies Element ID, as mentioned above, upon which element it will rest upon (skeleton), referenced from
//// * array elementInformation.
// *
//// * The third value holds all the information about the object inside the widget (refer #MDL_Widget_ObjectDefsTypeDef).
// *
// *  The fourth value holds the color inverion information for the widget (refer #MDL_Widget_ColorInversionTypeDef).
// *
// * The fifth value holds the animation related information for the widget (refer #MDL_Widget_AnimationParamTypeDef).
// */

typedef struct
{
    uint8_t LiveFlag;                   /**< \brief Whether info is stale or fresh. */
  uint16_t widgetId;                                /**< \brief Identification number for widget. */
  uint8_t elementID;                                /**< \brief Identification number for the element. */
  uint8_t widgetObjectType;                         /**< \brief Type of object to be put into the widget (icon = 0, text = 1). */
  uint8_t objectID;                                 /**< \brief ID of object being stored (Text (Parameter) ID, Icon ID). */
  uint8_t verticalAlignment;                        /**< \brief Vertical Alignment of the object being put into the widget (0-bottom, 1-Centre, 2-Top). */
  uint8_t horizontalAlignment;                      /**< \brief Horizontal Alignment of the object being put into the widget (0-Left, 1-Centre, 2-Right). */
  MDL_WidgetColorInversionTypeDef widgetInversion;  /**< \brief No Inversion = 0, Inversion = 1. */
  MDL_WidgetAnimationTypeDef widgetAnimation;       /**< \brief ID of object being stored (Text ID, Icon ID). */
  MDL_Widget_ObjectDefsTypeDef objectDefinition;    /**< \brief Object related data and its callback. */
  MDL_Widget_AnimationParamTypeDef widgetAnimationDefinition;   /**< \brief Animation related data. */
} MDL_Widget_TypeDef;



/***********************************************SCREEN RELATED DEFINITIONS*********************************************/

///**
// * @brief  MDLF Screen Color Inversion characteristic description
// *
// * The following enum describes the color inversion that the widget is capable of displaying. It can either
// * be displayed as 'Black (parameter) over white (background)' type or 'White (parameter) over black (background)'
// * type. If it is zero, it means no inversion is there. That means, widget is dislpayed in its default skin (White
// * over black combination). If it is one, it means inversion is present for the widget and it is displayed in
// * inverted color form (Black over white).
// */
typedef enum
{
  MDL_SCREEN_NORMAL         = 0x00,             /**< \brief Widget displayed in white over black skin. */
  MDL_SCREEN_INVERTED       = 0x01,             /**< \brief Widget displayed in Black over white skin. */
} MDL_ScreenInversionTypeDef;
//
//
//
///**
// * @brief  MDL 'Screen' component Transition Parameter description
// *
// * The following enum describes the transition types that the screen supports. Only the below mentioned transition types
// * are supported. In order for the screen to show any sort of transition, ensure that the 'transitionEnable' is set to 1
// * (refer #MDL_Screen_TransitionParamTypeDef) .
// */
typedef enum
{
  MDL_SCREEN_NOTRANSITION         = 0x00,             /**< \brief Screen supports no transition. */
  MDL_SCREEN_SLIDEUP              = 0x01,             /**< \brief Screen slides upward. */
  MDL_SCREEN_SLIDEDOWN            = 0x02,             /**< \brief Screen slides downward. */
  MDL_SCREEN_SLIDERIGHT           = 0x03,             /**< \brief Screen slides towards the right. */
  MDL_SCREEN_SLIDELEFT            = 0x04,             /**< \brief Screen slides towards the left. */
} MDL_ScreenTransitionTypeDef;
//
//
//
///**
// * @brief  Structure defining transition for a MDL 'Screen' component (Name to be changed)
// *
// * The following structure specifies the parameters that are to be given to enable and define transition of a screen in a particular
// * particular carousel. In order to define transition for the screen, first off set the 'transitionEnable' parameter. If it is set to
// * zero all other settngs are ignored (even if entered) and hence, no transition is set for that screen. Hence, transition settings
// * are applicable if and only if 'transitionEnable' is set.
// *
// * It encompasses and defines values like 'transitionEnable' value, the 'type' of transition to be set for that screen, which is
// * defined as per only the transitions that are supported for the screen(refer #MDL_Screen_TransitionTypeDef) and the last
// * parameter defines the time duration for which the transition will take for the screen.
// *
// */
typedef struct
{
  uint8_t transitionEnable;                   /**< \brief Defines whether screen has any transition defined or not. */
  MDL_ScreenTransitionTypeDef transition;     /**< \brief Defines the type of transition that screen shall have. */
  uint16_t duration;                  /**< \brief Defines the duration of transition for that screen until next screen apperance. */
} MDL_Screen_TransitionParamTypeDef;
//
//
//
///**
// * @brief  Structure defining Widget related information for a MDL 'Screen' component (Name to be changed)
// *
// * The following structure specifies the parameters that are to be given to define the placement of a widget on a screen with proper coordinates.
// * The structure consists of:
// *
// * - Widget ID; that is going to be placed on the screen (refer #MDL_Widget_TypeDef)
// * - Widgets X & Y coordinates on the screen (ensure it fits perfectly and does not overlap any other object on the screen and maintains clear
// *   visibility.
// *
// */
typedef struct
{
  uint16_t widgetId;                                /**< \brief Information about all widgets on the screen. */
  uint16_t widgetXPos;                              /**< \brief X-Coordinate for the widget (max = 240 - width).  */
  uint16_t widgetYPos;                              /**< \brief Y-Coordinate for the widget (max = 400 - height).  */
} MDL_Screen_WidgetPlacementTypeDef;



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
//MDL_Screen_WidgetPlacementTypeDef widgetPlacementInformation[MAX_NUM_OF_WIDGETS_ON_A_SCREEN];



///**
// * @brief  Structure defining a MDL 'Screen' component (Name to be changed)
// *
// * The following structure specifies the attributes of the 'screen' component of the MDL. It comprises its Identifcation
// * number, its resolution height and width, number of widgets that are to be shown on the screen and their complete
// * information and transition related definition for that particular screen. Following attributes are a mandate to define
// * a screen completely in compliance with its definition.
// *
// * - Screen ID (its UID)
// * - Resolution width and height (size of the screen)
// * - total number of widgets on the screen and their complete information
// * - placement information about each widget with its X & Y coordinates defined properly.
// * - extra attributes but not necessary (like transitions etc.)
// *
// * The first value signifies Screen ID, acting as a unique Identification number for the screen; basically its identity.
// *
// * The second and third values signify its width and height resolution.
// *
// * The fourth value specifies the total number of widgets on the screen.
// *
// * The fifth value holds complete info about the widgets' placements to be shown on the screen.
// *
// * The sixth value holds complete info about screen's transitions (if there is any defined).
// *
// */
typedef struct
{
  uint16_t screenId;                                      /**< \brief Identification number of a screen. */
  uint16_t screenWidth;                                   /**< \brief Width resolution of the screen (default = max value). */
  uint16_t screenHeight;                                  /**< \brief Height resolution of the screen (default = max value). */
  uint8_t numOfWidgets;                                   /**< \brief Number of widgets on the screen. */
  MDL_Screen_WidgetPlacementTypeDef widgetPlacementInformation[MAX_NUM_OF_WIDGETS_ON_A_SCREEN];                           /**< \brief Information about all widgets on the screen. */
  MDL_Screen_TransitionParamTypeDef screenTransition;     /**< \brief Transition information by the screen. */
  MDL_ScreenInversionTypeDef screenInversion;             /**< \brief Inversion supported by the screen. */
} MDL_Screen_TypeDef;



/***********************************************CAROUSEL RELATED DEFINITIONS*********************************************/


///**
// * @brief  Structure defining Screen's transition related information inside a MDL 'Carousel' component (Name to be changed)
// *
// * The following structure specifies the parameters that are to be given to define the transition of a screen into another screen.
// * The structure consists of:
// *
// * - Screen ID; which identifies which screen the tansition is going to be applied to (refer #MDL_Screen_TypeDef).
// * - Transitional information of the screen in hand (refer #MDL_Screen_TransitionParamTypeDef).
// *
// */
typedef struct
{
  uint16_t screenId;                                      /**< \brief Identification number of a screen. */
  MDL_Screen_TransitionParamTypeDef transitionParam;      /**< \brief Information about transition of the screen. */
} MDL_Carousel_ScreenTransitionTypeDef;



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




///**
// * @brief  Structure defining a MDL 'Carousel' component (Name to be changed)
// *
// * The following structure specifies the attributes of the 'Carousel' component of the MDL. It comprises its Identifcation
// * number, number of screens that are to be grouped into the carousel and their transitional information. Following attributes
// * are a mandate to define a carousel completely in compliance with its definition.
// *
// * - Carousel ID (its UID).
// * - total number of screens in the carousel and their complete information.
// * - transitions defined for all screens.
// *
// * The first value signifies Carousel ID, acting as a unique Identification number for the carousel; basically its identity.
// *
// * The second value specifies the total number of screens inside the carousel.
// *
// * The third value holds transitional info about the screens to be grouped inside the carousel.
// *
// */
typedef struct
{
  uint8_t carouselId;                       /**< \brief Identification number for a carousel. */
  uint8_t numOfScreens;                     /**< \brief Number of screens in the carousel. */
  uint8_t screenIdArray[MAX_NUM_OF_SCREENS_IN_A_CAROUSEL];    /**< \brief Number of screen IDs same as the number of screens in carousel. */
//  MDL_Screen_TypeDef screenInfo[numOfScreens];          /**< \brief Information about all screens in the carousel. */
//  screenTransitionInformation[numOfScreens];            /**< \brief Information about transitions of all screens in the carousel. */
} MDL_Carousel_TypeDef;



/** 
 * @brief  Array definition of all 'Carousel' components together 
 *
 * The following array is a collection of all the 'Carousels' that exist in the DM. Each element on the array is of type MDL_Carousel_TypeDef. 
 * For any change to be done in the carousel's data, it must be accessed by its carouselId.
 *  
 */  
//MDL_Carousel_TypeDef carouselInformationFromFlash[MAX_NUM_OF_CAROUSELS];


/* Function prototypes -------------------------------------------------------*/
list_t * elementListInit(void);
list_t * widgetListInit(void);
list_t * screenListInit(void);
list_t * carouselListInit(void);
int matchScreenID(uint16_t idToMatch, uint16_t idToBeMatchedWith );
list_node_t * addScreenNode(list_t * screenList, MDL_Screen_TypeDef * newData);
list_node_t * modifyScreenNode(list_t * screenList, uint16_t screenIdToModify, MDL_Screen_TypeDef * modifiedData);
void deleteScreenNode(list_t * screenList, uint16_t screenIdToDelete);


#ifdef __cplusplus
}
#endif
#endif /*__ MDL_H */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT KPIT TECHNOLOGIES LTD*****END OF FILE*******************************************/

