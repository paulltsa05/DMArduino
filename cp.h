/*****************************************************************************
 * Copyright (C) 2017 KPIT Technologies Ltd.                                 *
 *                                                                           *
 * This file contains all the preprocessor directives,structures  and function
 * declaration related to communication protocol.                                        *
 *                                                                           *
 *****************************************************************************/

/**
 * \mainpage %Display Module
 */

 /**
 * \defgroup CP CP Component
 *
 * \author Imran Pathan
 * \date :  05/18/2017
 *
 * communication protocol (CP) component is library where parsing of commands based on command group is done on receiving packets over BLE(payload
 * data of command is received in multiple packets as BLE has limitation to recieve 20 bytes maximum at a time,here extra fields are attached before
 * header that are total packet and current packet ).Same library on sending part of packets forms header ,crc calculaton + footer  for actual payload
 * data.Packets are recieved on DM or Mobile side until total packets are equal to current packet.
 * Timer on sending device is started ,so that within timeout of timer if  acknowledgement doesnt come from receiving device ,on sending device we can say that payload data is not recieved
 * on receiving device.
 *
 */


 /**
 * \ingroup CP
 * \defgroup CPInfra CP Infra
 *
 * \author Imran Pathan
 * \date :  05/18/2017
 * \file communication_protocol.h
 * \brief CP Infra implementation
 *
 *On receiving device : function that recieves packet data are implemented on recieving side and ultimately parsing of packets takes place .Here
 *indication callback function is called where we get command group ,command ,size of payload and pointer to actual payload buffer.
 *At the same time response/acknowledgement is sent to sending device so that it can understand if command(all the data packet) is recieved correctly
 *on receiving side.
 *On sendind device : API are called,here for every command API are defined through which we can send data specific to commnads.here formation of packet takes place (header+payload data +(crc+footer))
 *timeout timer is started on sending device so  that within certain time if we dont get response from receiving device then sending device can confirm that payload data(command specific data)is not
 *received on receiving device.
 */

 /**
 * \addtogroup CP Infra
 * @{
 *
 */


#ifdef __cplusplus
extern "C" {
#endif


//#ifndef CP_H_
//#define CP_H_

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>

#include "crc16_calc.h"

#define __linux__


#ifdef __linux__
//#include <android/log.h>
#include <Arduino.h>
#define  LOG_TAG   "communication-protocol"
//
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)
#define  LOGW(...)  __android_log_print(ANDROID_LOG_WARN,LOG_TAG,__VA_ARGS__)
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#elif __APPLE__
 #define arooooor 0
#else
#ifdef STM32L151xE
#include "stm32l1xx.h"
#else
#include "stm32l0xx.h"
#endif
//#include "stm32l0xx_hal.h"

#endif


/**
 * @brief     cp infra action' Below preprocessor directives are to used only by communication protocol.
 *
 */


/* Source ID */
#define SOURCE_ID_PHONE    0x10
#define SOURCE_ID_CM     0x11
#define SOURCE_ID_DM       0x12

#define SOP                0xBBBB   // Start of packet
#define EOP                0xEEEE // End of packet

#define TRUE             0x01
#define FALSE            0x00

#define CP_BUFFER_SIZE     1172  //1152 +13(header+footer)+10(extra buffer)

#define NO_CMD_DATA '\0'
#define ZERO_PAYLOAD_SIZE 0x00

#define REQUEST_TIME_OUT 6000 //mSec

/* KBike Display Protocol Error Definitions */
#define COMMUNICATION_PROTOCOL_VALID_DATA     0x10
#define COMMUNICATION_PROTOCOL_BAD_HEADER_FORMAT  0x11
#define COMMUNICATION_PROTOCOL_BAD_LENGTH     0x12
#define COMMUNICATION_PROTOCOL_INVALID_COMMAND      0x13
#define COMMUNICATION_PROTOCOL_NO_BUFFER_SPACE      0x14
#define COMMUNICATION_PROTOCOL_REQUEST_TIME_OUT     0x15
#define CRC16_CHECKSUM_ERROR                        0x16

/* Response from Display */
#define COMMUNICATION_PROTOCOL_SUCCESS_ACK        0x4F
#define COMMUNICATION_PROTOCOL_FAIL_ACK           0x46
#define COMMUNICATION_PROTOCOL_HEARTBEAT_ACK      0xFF

#define COMMUNICATION_PROTOCOL_MSG_TYPE_COMMAND       0x01
#define COMMUNICATION_PROTOCOL_MSG_TYPE_GEN_REJECT      0x02
#define COMMUNICATION_PROTOCOL_MSG_TYPE_RSP_ACCEPT      0x03
#define COMMUNICATION_PROTOCOL_MSG_TYPE_RSP_REJECT      0x04

#define COMMUNICATION_PROTOCOL_INVALID_CMD          0x00

#ifndef MAX
# define MAX(x, y) ((x) > (y) ? (x) : (y))
#endif



/* Command Groups for Display Module (LCD) */

/**
 * @brief     cp infra action' Below preprocessor directives are to used to didentify command group and their commands
 *
 */

#define COMMUNICATION_PROTOCOL_CMD_GRP_DM_FLASH_ICON              0x8C
//DMV2 start
#define COMMUNICATION_PROTOCOL_CMD_GRP_DM_NEW_PARAMETERS          0x2B
#define COMMUNICATION_PROTOCOL_CMD_GRP_DM_ALERTS_WARNINGS         0x9C
#define COMMUNICATION_PROTOCOL_CMD_GRP_DM_BATTERY_STATUS          0x7E
#define COMMUNICATION_PROTOCOL_CMD_GRP_DM_MENU_COMMANDS           0x6E
//DMV2 end
#define COMMUNICATION_PROTOCOL_CMD_GRP_DM_FIRMWARE_UPDATE         0x1F

#define COMMUNICATION_PROTOCOL_CMD_GRP_DM_HID                     0x48



#define COMMUNICATION_PROTOCOL_CMD_DEFAULT                  0xFF
#define COMMUNICATION_PROTOCOL_CMD_GRP_CM_MOTION_SENSOR           0X6D
#define COMMUNICATION_PROTOCOL_CMD_GRP_CM_GPS_LOCATION            0X4C
#define COMMUNICATION_PROTOCOL_CMD_GRP_CM_ENVIORMENTAL_SENSOR     0X65
#define COMMUNICATION_PROTOCOL_CMD_GRP_CM_ENGINE_PARAMETERS       0X76


/* Commands for Group-> DM Flash icon */

#define COMMUNICATION_PROTOCOL_CMD_UPDATE_ICON                    0x46

//DMV2 start
/* Commands for Group-> DM NEW PARAMETERS */
#define COMMUNICATION_PROTOCOL_CMD_CURRENT_DATE_TIME                     0x03
#define COMMUNICATION_PROTOCOL_CMD_VEHICLE_BATTERY_VOLTAGE               0x05

#define COMMUNICATION_PROTOCOL_CMD_SOURCE_NAME                           0x07
#define COMMUNICATION_PROTOCOL_CMD_DESTINATION_NAME                      0x08
#define COMMUNICATION_PROTOCOL_CMD_ETA                                   0x09
#define COMMUNICATION_PROTOCOL_CMD_CURRENT_MANUEVER_ICON                 0x10
#define COMMUNICATION_PROTOCOL_CMD_CURRENT_MANUEVER_DISTANCE_UNIT        0x11
#define COMMUNICATION_PROTOCOL_CMD_NEXT_MANUEVER_ICON                    0x13
#define COMMUNICATION_PROTOCOL_CMD_NEXT_MANUEVER_DISTANCE_UNIT           0x14
#define COMMUNICATION_PROTOCOL_CMD_BIKE_FULE_LEVEL                       0x16
#define COMMUNICATION_PROTOCOL_CMD_BIKE_MILEAGE_DISTANCE_UNIT            0x17
#define COMMUNICATION_PROTOCOL_CMD_TRAVELLED_DISTANCE_UNIT               0x19
#define COMMUNICATION_PROTOCOL_CMD_CM_HEALTH_STATUS_PARAMETERS           0x21
#define COMMUNICATION_PROTOCOL_CMD_DM_INFO_PARAMETERS                    0x22
#define COMMUNICATION_PROTOCOL_CMD_DM_USER_NAME                          0x23
#define COMMUNICATION_PROTOCOL_CMD_DM_PASSKEY                            0x24

/* Commands for Group-> DM ALERTS AND WARNINGS */
#define COMMUNICATION_PROTOCOL_CMD_DM_URGENT_ALERTS                      0x01
#define COMMUNICATION_PROTOCOL_CMD_DM_NON_URGENT_ALERTS                  0x02
#define COMMUNICATION_PROTOCOL_CMD_DM_MISCELLANEOUS_ALERTS               0x03
#define COMMUNICATION_PROTOCOL_CMD_DM_WARNINGS                           0x04



/* Commands for Group-> DM MENU COMMANDS */
#define COMMUNICATION_PROTOCOL_CMD_DM_ELEMENT                            0x01
#define COMMUNICATION_PROTOCOL_CMD_DM_WIDGET                             0x02
#define COMMUNICATION_PROTOCOL_CMD_DM_SCREEN                             0x03
#define COMMUNICATION_PROTOCOL_CMD_DM_CAROUSEL                           0x04


//DMv2 end
/* Commands for Group-> DM firmware update Commands */
#define COMMUNICATION_PROTOCOL_CMD_FIRMWARE_UPDATE_START    0x11

/* Commands for Group-> DM HID Commands */

#define COMMUNICATION_PROTOCOL_CMD_KEY_PRESS                0x02


/**
 * @brief     cp infra action' global variables to store total packet count and current packet count in case of more then on packet received over BLE.
 *
 */
static uint8_t gPrevious_tpck=0;
static uint8_t gTpck_count=0;



/**
 * @brief     cp infra action' parse status code
 * This enumeration describes the status of the parsing of command.
 */

enum communication_protocol_parse_result {
  PARSE_ERROR, PARSE_SUCCESS
};

struct kbike_communication_protocol;


/**
 * @brief Structure defining header format of communication protocol
 *
 */

typedef struct {
  uint16_t sop;   /**< \brief start of packet. */
  uint8_t src_id; /**< \brief source id(data source : dm or cm). */
  uint8_t session_id; /**< \brief The session identifier. */
  uint8_t msg_type; /**< \briefCOMMAND, RSP_ACCEPT OR RSP_REJECT. */
  uint8_t cmd_group;  /**< \brief command group. */
  uint8_t cmd;       /**< \brief command . */
  uint16_t size_payload; /**< \brief payload size of payload data. */
}__attribute__ ((packed)) communication_protocol_header;

/**
 * @brief Structure defining footer format of communication protocol
 *
 */
typedef struct {
  uint16_t crc;  /**< \brief CRC 16 value. */
  uint16_t eop;  /**< \brief end of packet. */
}__attribute__ ((packed)) communication_protocol_footer;

typedef struct {
  uint8_t total_packets; /**< \brief Total packets */
  uint8_t packet_num;  /**< \brief Current packet number of total packet. */
}__attribute__ ((packed)) packet_header;

/* prototype for end connection*/
void end_connection(struct kbike_communication_protocol *session);


/**
 *  @brief CP Infra confirmation callback function
 *  Callbacks for when a reply is received to a command that we sent
 *
 */
struct communication_protocol_cfm {

    void (*callback_cfm)(struct kbike_communication_protocol *, uint8_t);

}__attribute__ ((packed));

/**
 * @brief CP Infra structure defining callback function Indication callback function
 * Callbacks for indicating when we received a new command. The return value
 * indicates whether the command should be rejected or accepted
 */
struct communication_protocol_ind {

    bool (*callback_ind)(struct kbike_communication_protocol *session);
  
}__attribute__ ((packed));

/**
 * @brief CP Infra structure defining callback function try send
 * Callback to send protocol packet to remote device
 */
struct transport_cb {
  bool (*try_send)(void *, size_t);
};

/**
 * @brief CP Infra structure defining buffer that will store all the useful  data related to recieved  command
 * Callback to send protocol packet to remote device
 */
struct in_buf {
  bool active;
  uint8_t message_type; /**< \brief COMMAND, RSP_ACCEPT OR RSP_REJECT. */
  uint8_t buf[CP_BUFFER_SIZE]; /**< \brief payload buffer to store complete command data */
  uint16_t data_size;    /**< \brief refer to data size of payload buffre  */
};

/**
 * @brief CP Infra structure defining out message info (response on receiving command)
 *
 */
struct out_msg_info {
  uint8_t msg_type;  /**< \brief COMMAND, RSP_ACCEPT OR RSP_REJECT. */
  uint8_t cmd_grp;  /**< \brief command group. */
  uint8_t cmd;    /**< \brief command . */
};

struct communication_cp_callbacks {
  struct communication_protocol_ind *ind_cb;
  struct communication_protocol_cfm *cfm_cb;
  struct transport_cb *transport_cb;
}__attribute__ ((packed));

/**
 * @brief CP Infra structure defining complete session data
 *
 */
struct kbike_communication_protocol {

  uint16_t ref;

  char inbuf[20];   /**< \brief buffer to collet packet data on receiving ,20 bytes can be received at a time as its BlE limitation. */
  char outbuf[20];  /**< \brief buffer to collet packet data on sending ,20 bytes can be sent at a time as its BlE limitation. */

  uint16_t imtu;
  uint16_t omtu;

  struct in_buf in;   /**< \brief structure containing payload buffer and payload size etc. */

  struct out_msg_info msginfo;

  bool shutdown;

  struct communication_cp_callbacks endpoint;

}__attribute__ ((packed));

/******************************************************************************************
 *        Display Protocol Interface to UL -> Upper Layer - Start
 *    Function Calls declared below are APIs to call from application level.
 * ****************************************************************************************/

/***********************************************************************************
 * API - communication_protocol_new
 *      This API is call to initialize display protocol.
 *      This is use to register MTU size, callback functions used to
 *      indicate & provide confirmation about various Commands.
 ***********************************************************************************/
struct kbike_communication_protocol* communication_protocol_new(uint8_t imtu, uint8_t omtu,
    struct communication_protocol_ind *ind_cb, struct communication_protocol_cfm *cfm_cb,
    struct transport_cb *transport_cb);

/***********************************************************************************
 * API - communication_protocol_receive_payload - Wrapper function.
 *      This function is called from application to receive data from remote device.
 * *********************************************************************************/
bool communication_protocol_receive_payload(void *session_data,
    size_t size_recv_data);


/***********************************************************************************
 * API - Dmfirmware update Commands - START
 *    Commands Supported:
 *    firmware_update_start
***********************************************************************************/


bool communication_protocol_firmware_update_start(struct kbike_communication_protocol *session,
    uint8_t source_id, uint8_t session_id,void *firmware_update_id, uint8_t size) ;



/***********************************************************************************
 *            Response Handler Functionality prototype- Start
 ***********************************************************************************/

static bool cp_parse_resp(struct kbike_communication_protocol *session);


/************************** API -Dmsensor Commands - END *****************************/
/***********************************************************************************
 * API - HID Commands - START
 *    Commands Supported:

 *    key_press

***********************************************************************************/


bool communication_protocol_key_press(struct kbike_communication_protocol *session,
        uint8_t src_id, uint8_t session_id, void *skey, uint8_t size);



/************************** API -HID Commands - END *****************************/



/***********************************************************************************
 * API - Flash Icon Commands - START
 *    Commands Supported:
 *        flash Icon
**********************************************************************************/
bool communication_protocol_flash_icon(struct kbike_communication_protocol *session,
    uint8_t source_id, uint8_t session_id, void *flash_icon, uint16_t size);

/************************** API - Image Commands - END *****************************/
/***********************************************************************************
 * API - dm new parameters Commands - START
 *    Commands Supported:
 *    current_date_time
 *    vehicle_battery_voltage
 *    source_name
 *    destination_name
 *    eta
 *    current_maneuver_icon
 *    current_maneuver_distance_unit
 *    current_maneuver_unit
 *    next_maneuver_icon
 *    next_maneuver_distance
 *    next_maneuver_unit
 *    bike_fuel_level
 *    bike_milage_distance
 *    bike_milage_unit
 *    travelled_distance
 *    travelled_unit
 *    cm_health_parameters_status
 *    dm_info_parameters
 *    user_name 
 ***********************************************************************************/

bool communication_protocol_current_date_time(struct kbike_communication_protocol *session,
    uint8_t source_id, uint8_t session_id,void *scurrentdate_time, uint16_t size) ;

bool communication_protocol_vehicle_battery_voltage(struct kbike_communication_protocol *session,
    uint8_t source_id, uint8_t session_id, void *svehicle_battery_voltage, uint16_t size) ;

bool communication_protocol_source_name(struct kbike_communication_protocol *session,
    uint8_t source_id, uint8_t session_id, void *ssource_name, uint16_t size) ;

bool communication_protocol_destination_name(struct kbike_communication_protocol *session,
    uint8_t source_id, uint8_t session_id, void *sdestination_name, uint16_t size);

bool communication_protocol_eta(struct kbike_communication_protocol *session,
    uint8_t source_id, uint8_t session_id, void *seta, uint16_t size);


bool communication_protocol_current_manuever_icon(struct kbike_communication_protocol *session,
    uint8_t source_id, uint8_t session_id, void *scurrent_manuever_icon, uint16_t size) ;


bool communication_protocol_current_manuever_distance_unit(struct kbike_communication_protocol *session,
    uint8_t source_id, uint8_t session_id, void *scurrent_manuever_distance_unit, uint16_t size) ;


bool communication_protocol_next_manuever_icon(struct kbike_communication_protocol *session,
    uint8_t source_id, uint8_t session_id, void *snext_manuever_icon, uint16_t size) ;


bool communication_protocol_next_manuever_distance_unit(struct kbike_communication_protocol *session,
    uint8_t source_id, uint8_t session_id, void *snext_manuever_distance_unit, uint16_t size) ;

    
bool communication_protocol_bike_fuel_level(struct kbike_communication_protocol *session,
    uint8_t source_id, uint8_t session_id, void *sbike_fuel_level, uint16_t size) ;


bool communication_protocol_next_milage_distance_unit(struct kbike_communication_protocol *session,
    uint8_t source_id, uint8_t session_id, void *smilage_distance_unit, uint16_t size) ;


bool communication_protocol_travelled_distance_unit(struct kbike_communication_protocol *session,
    uint8_t source_id, uint8_t session_id,void *stravelled_distance_unit, uint16_t size) ;



bool communication_protocol_cm_health_status_parameters(struct kbike_communication_protocol *session,
    uint8_t source_id, uint8_t session_id, void *scm_health_status_parameters, uint16_t size) ;


bool communication_protocol_dm_user_name(struct kbike_communication_protocol *session,
    uint8_t source_id, uint8_t session_id,void *sdm_user_name, uint16_t size) ;


/************************** API - dm new parameters Commands - END *****************************/



/***********************************************************************************
 * API - dm alerts and warnings Commands - START
 *    Commands Supported:
 *     urgent alerts
 *     non urgent alerts
 *     miscellaneous alerts
 *     dm warnings

 
 ***********************************************************************************/

bool communication_protocol_urgent_alerts(struct kbike_communication_protocol *session,
    uint8_t source_id, uint8_t session_id, void *surgent_alerts, uint16_t size) ;


bool communication_protocol_non_urgent_alerts(struct kbike_communication_protocol *session,
    uint8_t source_id, uint8_t session_id, void *snon_urgent_alerts, uint16_t size) ;


bool communication_protocol_miscellaneous_alerts(struct kbike_communication_protocol *session,
    uint8_t source_id, uint8_t session_id, void *smiscellaneous_alerts, uint16_t size) ;


bool communication_protocol_dm_warnings(struct kbike_communication_protocol *session,
    uint8_t source_id, uint8_t session_id, void *sdm_warnings, uint16_t size);

/************************** API - dm alerts and warnings Commands - END *****************************/



/***********************************************************************************
 * API - dm menu Commands - START
 *    Commands Supported:
 *   dm element
 *   dm widget
 *   dm screen 
 *   dm carousel


 
 ***********************************************************************************/
bool communication_protocol_dm_element(struct kbike_communication_protocol *session,
    uint8_t source_id, uint8_t session_id, void *sdm_element, uint16_t size);
bool communication_protocol_dm_widget(struct kbike_communication_protocol *session,
    uint8_t source_id, uint8_t session_id, void *sdm_widget, uint16_t size) ;
bool communication_protocol_dm_screen(struct kbike_communication_protocol *session,
    uint8_t source_id, uint8_t session_id, void *screen_data, uint16_t size) ;
bool communication_protocol_dm_carousel(struct kbike_communication_protocol *session,
    uint8_t source_id, uint8_t session_id, void *carousel_data, uint16_t size) ;
/************************** API - dm menu Commands - END *****************************/




/*****************  Display Protocol Interface to UL -> Upper Layer - End *******************/


//#endif /* CP_H_ */

#ifdef __cplusplus
}
#endif

