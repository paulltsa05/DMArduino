/****************************************************************************
 * Copyright (C) 2017 KPIT Technologies Ltd.                                *
 *                                                                          *
 * This file is part of communication protocol callback Infra.                                         *
 *                                                                          *
 ****************************************************************************/

/**
 * \mainpage %Display Module
 */

 /**
 * \defgroup CP CP Component
 *
 * \author Imran Pathan
 * \date 17.05.17
 * communication protocol(CP) is library that contains logic for parsing of commands as per
 * communication protocol on receiving command .It also do packet formation while sending command as per communication protocol.
 */


 /**
 * \ingroup CP
 * \defgroup CPInfra CP Infra
 *
 * \author Imran Pathan
 * \date 17.05.17
 *
 * \brief CP Infra implementation
 *
 * communication protocol callback(CP Infra header(cp_if.h) is file that contains all the structures,enum and preprocessor directives of various commands as per communication protocol(Wiki gitlab)
 */

 /**
 * \addtogroup CP Infra
 * @{
 *
 */

#ifndef CP_IF_H_
#define CP_IF_H_



/**
 * @brief  enum defining Unit of distance
 *
 below are the units for distance
 * (refer #UNIT_TypeDef).
 */
typedef enum
{
  YARD        = 0x00,       /**< \brief No animation is supported by the widget. */
  MILES           = 0x01,       /**< \brief Widget slides upward in the screen. */
  KILOMETER       = 0x02,       /**< \brief Widget slides downward in the screen. */
  METER             = 0x03,       /**< \brief Widget fades into the screen. */
} UNIT_TypeDef;





#define MAX_NUM_OF_ELEMENTS 9           /**< \brief Maximum number of elements that the DM supports. */

#define MAX_NUM_OF_WIDGETS 38           /**< \brief Maximum number of widgets that the DM supports. */

#define MAX_NUM_OF_WIDGETS_ON_A_SCREEN 5      /**< \brief Maximum number of widgets on a screen (for now). */

#define MAX_NUM_OF_SCREENS 10           /**< \brief Maximum number of screens that the DM supports. */

#define MAX_NUM_OF_SCREENS_IN_A_CAROUSEL 10     /**< \brief Maximum number of screens in a carousel (for now). */

#define MAX_NUM_OF_CAROUSELS 1            /**< \brief Maximum number of carousels that the DM supports. */



/******command group -> Dm Menu Definition Language Commands***************************/
/**
 * @brief  Nodal Structure defining an 'Element' component (space) on a screen in its crude/ raw form
 *
 * An element is nothing but a space reserved on a particular screen which is then dedicated to show either text, value or icon.
 * The following structure specifies the attributes that are characteristic to an element. It comprises of simply element's
 * UID (Unique ID), its width and height measures.
 *
 */
typedef struct
{
  uint16_t elementID;                       /**< \brief Unique ID for the element. */
  uint16_t elementHeight;                   /**< \brief Height of the element (max 240).  */
  uint16_t elementWidth;                    /**< \brief Width of the element (max 400).  */
} MDL_Element_TypeDef;


/**
 * @brief  Structure defining widget's object related definitions
 *
 * The following structure specifies the attributes that are to be defined for the object inside any element. The first
 * value defines the 'type' of the object (refer union #OBJECTTYPE). If it is a parameter, its value is shown in permissible
 * format. If it is an icon, then relevant icon is displayed. If it is a text string, then it is shown as per what has been
 * sent from phone via BLE.
 *
 * The second value defines the UID of either parameter or icon that has been chosen to be displayed in the element. <b> It
 * shall be zero if there is a text entry inside the element. </b>
 *
 * The third value defines the data of the particular chosen object for that element. For a parameter, it is parameter's value;
 * for an icon it is icon data and for a <b>text string </b> to be displayed, this pointer holds the address of the string to
 * be displayed.
 *
 * The fourth value is a pointer to the callback function of the object (in case it needs to be updated).
 *
 */
typedef struct
{
  void * data;                              /**< \brief Pointer to the data to be shown inside the element as per the type specified. */
//  void * updateCB;                            /**< \brief Pointer to the update callback function of the parameter. */
//will have a generic callback function handleWidgetCB(void * data)
} MDL_Widget_ObjectDefsTypeDef;


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
typedef struct
{
  uint8_t animationEnable;                /**< \brief Defines whether widget has any animation defined or not. */
  uint16_t duration;                      /**< \brief Defines the duration (in seconds) of animation for the widget. */
} MDL_Widget_AnimationParamTypeDef;


/**
 * @brief  MDLF Widget Animation characteristic description
 *
 * The following enum describes the animation types that the widget supports. Only the below mentioned animation types
 * are supported. In order for the widget to show any sort of animation, ensure that the 'animationEnable' is set to 1
 * (refer #MDL_Widget_AnimationParamTypeDef).
 */
typedef enum
{
  WIDGET_NOANIMATION        = 0x00,       /**< \brief No animation is supported by the widget. */
  WIDGET_SLIDEUP              = 0x01,       /**< \brief Widget slides upward in the screen. */
  WIDGET_SLIDEDOWN              = 0x02,       /**< \brief Widget slides downward in the screen. */
  WIDGET_FADEIN               = 0x03,       /**< \brief Widget fades into the screen. */
  WIDGET_FADEOUT              = 0x04,       /**< \brief Widget fades out of the screen. */
} MDL_WidgetAnimationTypeDef;


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
  WIDGET_NORMAL         = 0x00,             /**< \brief Widget displayed in white over black skin. */
  WIDGET_INVERTED       = 0x01,               /**< \brief Widget displayed in Black over white skin. */
} MDL_WidgetColorInversionTypeDef;


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
    uint8_t LiveFlag;                   /**< \brief Whether info is stale or fresh. */
  uint16_t widgetId;                      /**< \brief Identification number for widget. */
  uint8_t elementID;                    /**< \brief Identification number for the element. */
  uint8_t widgetObjectType;                 /**< \brief Type of object to be put into the widget (icon = 0, text = 1). */
  uint8_t objectID;                   /**< \brief ID of object being stored (Text (Parameter) ID, Icon ID). */
  uint8_t verticalAlignment;                /**< \brief Vertical Alignment of the object being put into the widget (0-bottom, 1-Centre, 2-Top). */
  uint8_t horizontalAlignment;              /**< \brief Horizontal Alignment of the object being put into the widget (0-Left, 1-Centre, 2-Right). */
  MDL_WidgetColorInversionTypeDef widgetInversion;    /**< \brief No Inversion = 0, Inversion = 1. */
  MDL_WidgetAnimationTypeDef widgetAnimation;       /**< \brief ID of object being stored (Text ID, Icon ID). */
  MDL_Widget_ObjectDefsTypeDef objectDefinition;      /**< \brief Object related data and its callback. */
  MDL_Widget_AnimationParamTypeDef widgetAnimationDefinition;   /**< \brief Animation related data. */
} MDL_Widget_TypeDef;



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
  MDL_SCREEN_NORMAL         = 0x00,             /**< \brief Widget displayed in white over black skin. */
  MDL_SCREEN_INVERTED       = 0x01,             /**< \brief Widget displayed in Black over white skin. */
} MDL_ScreenInversionTypeDef;



/**
 * @brief  MDL 'Screen' component Transition Parameter description
 *
 * The following enum describes the transition types that the screen supports. Only the below mentioned transition types
 * are supported. In order for the screen to show any sort of transition, ensure that the 'transitionEnable' is set to 1
 * (refer #MDL_Screen_TransitionParamTypeDef) .
 */
typedef enum
{
  MDL_SCREEN_NOTRANSITION           = 0x00,             /**< \brief Screen supports no transition. */
  MDL_SCREEN_SLIDEUP              = 0x01,             /**< \brief Screen slides upward. */
  MDL_SCREEN_SLIDEDOWN            = 0x02,             /**< \brief Screen slides downward. */
  MDL_SCREEN_SLIDERIGHT           = 0x03,             /**< \brief Screen slides towards the right. */
  MDL_SCREEN_SLIDELEFT            = 0x04,             /**< \brief Screen slides towards the left. */
} MDL_ScreenTransitionTypeDef;



/**
 * @brief  Structure defining transition for a MDL 'Screen' component (Name to be changed)
 *
 * The following structure specifies the parameters that are to be given to enable and define transition of a screen in a particular
 * particular carousel. In order to define transition for the screen, first off set the 'transitionEnable' parameter. If it is set to
 * zero all other settngs are ignored (even if entered) and hence, no transition is set for that screen. Hence, transition settings
 * are applicable if and only if 'transitionEnable' is set.
 *
 * It encompasses and defines values like 'transitionEnable' value, the 'type' of transition to be set for that screen, which is
 * defined as per only the transitions that are supported for the screen(refer #MDL_Screen_TransitionTypeDef) and the last
 * parameter defines the time duration for which the transition will take for the screen.
 *
 */
typedef struct
{
  uint8_t transitionEnable;                   /**< \brief Defines whether screen has any transition defined or not. */
  MDL_ScreenTransitionTypeDef transition;     /**< \brief Defines the type of transition that screen shall have. */
  uint16_t duration;                  /**< \brief Defines the duration of transition for that screen until next screen apperance. */
} MDL_Screen_TransitionParamTypeDef;



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
  uint16_t widgetId;                                /**< \brief Information about all widgets on the screen. */
  uint16_t widgetXPos;                              /**< \brief X-Coordinate for the widget (max = 240 - width).  */
  uint16_t widgetYPos;                              /**< \brief Y-Coordinate for the widget (max = 400 - height).  */
} MDL_Screen_WidgetPlacementTypeDef;



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
  MDL_Screen_WidgetPlacementTypeDef widgetPlacementInformation[MAX_NUM_OF_WIDGETS_ON_A_SCREEN];                           /**< \brief Information about all widgets on the screen. */
  MDL_Screen_TransitionParamTypeDef screenTransition;     /**< \brief Transition information by the screen. */
  MDL_ScreenInversionTypeDef screenInversion;             /**< \brief Inversion supported by the screen. */
} MDL_Screen_TypeDef;



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
typedef struct
{
  uint16_t screenId;                                      /**< \brief Identification number of a screen. */
  MDL_Screen_TransitionParamTypeDef transitionParam;      /**< \brief Information about transition of the screen. */
} MDL_Carousel_ScreenTransitionTypeDef;


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
 * The third value holds transitional info about the screens to be grouped inside the carousel.
 *
 */
typedef struct
{
  uint8_t carouselId;                       /**< \brief Identification number for a carousel. */
  uint8_t numOfScreens;                     /**< \brief Number of screens in the carousel. */
  uint8_t screenIdArray[MAX_NUM_OF_SCREENS_IN_A_CAROUSEL];    /**< \brief Number of screen IDs same as the number of screens in carousel. */
//  MDL_Screen_TypeDef screenInfo[numOfScreens];          /**< \brief Information about all screens in the carousel. */
//  screenTransitionInformation[numOfScreens];            /**< \brief Information about transitions of all screens in the carousel. */
} MDL_Carousel_TypeDef;






/******command group -> Dm New Parameters***************************/
/**
 * @brief   Structure defining current date and time
 *
 * This structure contains command group,command ,payload data(it is pointer to buffer
 * holding all the payload data) and payload size.
 *
 */
struct current_date_time
{
    uint8_t LIveFlag;    /**< \brief Tells if data live(recent) or not. */
  uint8_t DD;          /**< \brief current date. */
  uint8_t MM;          /**< \brief current month. */
  uint8_t YY;          /**< \brief current year. */
  uint8_t HH;          /**< \brief current hour. */
  uint8_t MIN;         /**< \brief current minutes. */
  uint8_t SS;          /**< \brief current seconds. */
};

/**
 * @brief   Structure defining vehicle battery voltage
 *
 *
 */
struct vehicle_battery_voltage
{
    uint8_t LIveFlag;   /**< \brief Tells if data live(recent) or not. */
  uint8_t voltage;    /**< \brief info about bike battery voltage. */

};

/**
 * @brief   Structure defining source name
 *
 *
 */
struct source_name
{
    uint8_t LIveFlag;  /**< \brief Tells if data live(recent) or not. */
  uint8_t XH;        /**< \brief higer bytes X-cordinate. */
  uint8_t XL;        /**< \brief lower bytes X-cordinate. */
  uint8_t YH;        /**< \brief higer bytes Y-cordinate. */
  uint8_t YL;        /**< \brief lower bytes Y-cordinate. */
  uint8_t Letter;    /**< \brief number of letter(bytes)in string. */
  //uint8_t *

};

/**
 * @brief   Structure defining destination name
 *
 *
 */
struct destination_name
{
    uint8_t LIveFlag;  /**< \brief Tells if data live(recent) or not. */
  uint8_t XH;        /**< \brief higer bytes X-cordinate. */
  uint8_t XL;        /**< \brief lower bytes X-cordinate. */
  uint8_t YH;        /**< \brief higer bytes Y-cordinate. */
  uint8_t YL;        /**< \brief lower bytes Y-cordinate. */
  uint8_t Letter;    /**< \brief number of letter(bytes)in string. */

};

/**
 * @brief   Structure defining estimated time of arrival
 *
 *
 */
struct eta
{
    uint8_t LIveFlag;    /**< \brief Tells if data live(recent) or not. */
  uint8_t DD;          /**< \brief estimated date. */
  uint8_t MM;          /**< \brief estimated month. */
  uint8_t YY;          /**< \brief estimated year. */
  uint8_t HH;          /**< \brief estimated hour. */
  uint8_t MIN;         /**< \brief estimated minutes. */
  uint8_t SS;          /**< \brief estimated seconds. */
};

/**
 * @brief   Structure defining current maneuver icon id
 *
 *
 */
struct current_maneuver_icon
{
   uint8_t LIveFlag; /**< \brief Tells if data live(recent) or not. */
   uint8_t IconID;   /**< \brief info about icon id to display on screen. */

};

/**
 * @brief   Structure defining current maneuver distance and unit
 *
 *
 */
struct current_maneuver_distance_unit
{
   uint8_t LIveFlag;  /**< \brief Tells if data live(recent) or not. */
   uint16_t distance; /**< \brief current maneuver distance. */
   UNIT_TypeDef  UnitFlag;  /**< \brief current maneuver unit. */
};

/**
 * @brief   Structure defining next maneuver icon
 *
 *
 */
struct next_maneuver_icon
{
   uint8_t LIveFlag; /**< \brief Tells if data live(recent) or not. */
   uint8_t IconID;   /**< \brief info about icon id to display on screen. */

};
/**
 * @brief   Structure defining next maneuver  next maneuver distance and unit
 *
 *
 */
struct next_maneuver_distance_unit
{
   uint8_t LIveFlag;   /**< \brief Tells if data live(recent) or not. */
   uint16_t distance;  /**< \brief next maneuver distance. */
   UNIT_TypeDef  UnitFlag;   /**< \brief next maneuver unit. */
};

/**
 * @brief   Structure defining bike fuel level
 *
 *
 */
struct bike_fuel_level
{
   uint8_t LIveFlag;   /**< \brief Tells if data live(recent) or not. */
   uint16_t fuelLevel; /**< \brief bike fuel level. */
};

/**
 * @brief   Structure defining bike mileage distance and unit
 *
 *
 */
struct bike_mileage_distance_unit
{
   uint8_t LIveFlag;  /**< \brief Tells if data live(recent) or not. */
   uint16_t distance; /**< \brief bike mileage distance. */
   UNIT_TypeDef  UnitFlag;  /**< \brief bike mileage unit. */
};

/**
 * @brief   Structure defining total travelled distance and unit
 *
 *
 */
struct travelled_distance_unit
{
   uint8_t LIveFlag;   /**< \brief Tells if data live(recent) or not. */
   uint16_t distance;  /**< \brief travelled distance. */
   UNIT_TypeDef  UnitFlag;   /**< \brief travelled unit. */
};
/**
 * @brief   Structure defining cm health status and parameters
 *
 *
 */
struct cm_health_status_parameter
{
   uint8_t LIveFlag;              /**< \brief Tells if data live(recent) or not. */
   uint8_t GprsConnectivityflag;  /**< \brief gprs connectivity of cm. */
   uint8_t BleConnectionFlag;     /**< \brief ble connectivity of cm. */
};
/**
 * @brief   Structure defining user name
 *
 *
 */
struct user_name
{
    uint8_t LIveFlag;  /**< \brief Tells if data live(recent) or not. */
  uint8_t XH;        /**< \brief higer bytes X-cordinate. */
  uint8_t XL;        /**< \brief lower bytes X-cordinate. */
  uint8_t YH;        /**< \brief higer bytes Y-cordinate. */
  uint8_t YL;        /**< \brief lower bytes Y-cordinate. */
  uint8_t Letter;    /**< \brief number of letter(bytes)in string. */

};
/**
 * @brief   Structure defining passkey for pairing of devices(BLE)
 *
 *
 */
struct passkey
{
    uint8_t LIveFlag;  /**< \brief Tells if data live(recent) or not. */
  uint8_t XH;        /**< \brief higer bytes X-cordinate. */
  uint8_t XL;        /**< \brief lower bytes X-cordinate. */
  uint8_t YH;        /**< \brief higer bytes Y-cordinate. */
  uint8_t YL;        /**< \brief lower bytes Y-cordinate. */
  uint8_t Letter;    /**< \brief number of letter(bytes)in string. */

};

/******command group -> Dm Alerts & Warnings***************************/

struct urgent_alerts
{
  uint8_t LIveFlag;   /**< \brief Tells if data live(recent) or not. */
  uint8_t AlertID;    /**< \brief alert id out of 255 total alerts. */
  uint8_t AlertFlag;  /**< \brief gives info about alert (example battery low,battery medium etc). */
  uint16_t AlertValue;/**< \brief gives info about alert value(example battery low battery medium values etc. */
};

struct nonurgent_alerts
{
  uint8_t LIveFlag;   /**< \brief Tells if data live(recent) or not. */
  uint8_t AlertID;    /**< \brief alert id out of 255 total alerts. */
  uint8_t AlertFlag;  /**< \brief gives info about alert */
  uint16_t AlertValue;/**< \brief gives info about alert value. */
};

struct miscellaneous_alerts
{
  uint8_t LIveFlag; /**< \brief Tells if data live(recent) or not. */
  uint8_t AlertID;
  uint8_t AlertFlag;
  uint16_t AlertValue;
};

struct warnings
{
  uint8_t LIveFlag; /**< \brief Tells if data live(recent) or not. */
  uint8_t WarningID;
  uint8_t WarningFlag;
  uint16_t WarningValue;
};

#endif  //end CP_IF_H_


