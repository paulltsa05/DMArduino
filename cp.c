  /*
 * KBike_DisplayProtocol.c
 *
 *  Created on: 1-April-2016
 *      Author: kpit
 */

#include "cp.h"

#ifdef __cplusplus
extern "C" {
#endif

//#ifdef __APPLE__
//#include <sys//LOG.h>
//#endif
//
//#if !defined(__linux__) && !defined (__APPLE__)                          
//#include "cmsis_os.h"
//#include "mpu_wrappers.h"
//#include "osal.h"
//#include "task.h"
//#include "crc.h"
//#define K//LOG_CATEGORY COMM_PROTOCOL
//#include "k//LOG.h"
//#include "osal.h"
//#include "task.h"
//#else
//#include "timer.h"
//#include <signal.h>
//#endif




#ifdef __linux__
/* Function Prototypes */
void cp_request_timeout(void *);
void cp_cancel_request(struct kbike_communication_protocol *);
#elif __APPLE__
/* Function Prototypes */
void cp_request_timeout(void *);
void cp_cancel_request(struct kbike_communication_protocol *);
#else     
/* Function Prototypes */
void cp_request_timeout(const void *);
void cp_cancel_request(struct kbike_communication_protocol *);
extern osTimerId cpRequestTimeoutTimerHandle;

osTimerDef(cpRequestTimeoutTimerHandle,cp_request_timeout);

#endif


/******************************************************************************************
 *         Static Function - Prototype
 *    Function declared below are used only within this file.
 * ****************************************************************************************/

static bool communication_protocol_send(struct kbike_communication_protocol *, void *,
    size_t);

static void prepare_payload_pkt_header(packet_header *, uint32_t, uint32_t);
static void prepare_communication_protocol_header(communication_protocol_header *, uint16_t,
    uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint16_t);
static void prepare_communication_protocol_footer(communication_protocol_footer *, uint16_t,
    uint16_t);

static void cp_start_request_timeout_timer(struct kbike_communication_protocol *);
static void cp_stop_request_timeout_timer(struct kbike_communication_protocol *);

static bool communication_protocol_request(struct kbike_communication_protocol *, uint8_t,
    uint8_t, uint8_t, uint8_t, uint8_t, void *, uint16_t);

static void cp_handle_low_buffer(void *, void *);
static uint8_t is_valid_data(struct kbike_communication_protocol *);
/*static void display_data(communication_protocol_header *, communication_protocol_footer *);*/
static struct kbike_communication_protocol* communication_protocol_ref(
    struct kbike_communication_protocol *);

static enum communication_protocol_parse_result communication_protocol_parse_payload(void *,
    size_t);
static void communication_protocol_parse_data(struct kbike_communication_protocol *);

static bool cp_parse_cmd(struct kbike_communication_protocol *);








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
struct kbike_communication_protocol* communication_protocol_new(uint8_t imtu, uint8_t omtu,  //data type of imtu and omtu changed to uint8_t bcoz they are #define 
    struct communication_protocol_ind *ind_cb,
    struct communication_protocol_cfm *cfm_cb, struct transport_cb *transport_cb) {
  struct kbike_communication_protocol *session;

#ifdef __linux__
  //LOGI("Entry -> communication_protocol_new\r\n");
#elif __APPLE__
   fprintf(stdout,"Entry ->communication_protocol_new\r\n");  
#else
  KLOG(INFO,"Entry -> communication_protocol_new\r\n");
#endif


#ifdef __linux__
  session = (struct kbike_communication_protocol *) malloc(
      sizeof(struct kbike_communication_protocol));
#elif __APPLE__
  session = (struct kbike_communication_protocol *) malloc(
      sizeof(struct kbike_communication_protocol));
#else
  session = (struct kbike_communication_protocol *) pvPortMalloc(
      sizeof(struct kbike_communication_protocol));
#endif
  session->imtu = imtu;
  session->omtu = omtu;

/* Commented this code section
  * As buf is replaces with inbuf[20] in communication protocol.h 
  * Now dynamic memory allocation is not required, 
  * this will avoid memory corruption issue for sending and receiving packets */
#if 0 
#ifdef __linux__
  session->buf = (char *) malloc(
  MAX(session->imtu, session->omtu) * sizeof(char));
#elif __APPLE__
  session->buf = (char *) malloc(
  MAX(session->imtu, session->omtu) * sizeof(char));
#else   
  session->buf = (char *) pvPortMalloc(
      MAX(session->imtu, session->omtu) * sizeof(char));
#endif
#endif //End of if 0
  
  session->endpoint.ind_cb = ind_cb;
  session->endpoint.cfm_cb = cfm_cb;
  session->endpoint.transport_cb = transport_cb;



#ifdef __linux__
  //LOGI("Exit -> communication_protocol_new\r\n");
#elif __APPLE__
   fprintf(stdout,"Exit -> communication_protocol_new\r\n");  
#else    
  KLOG(INFO,"Exit -> communication_protocol_new\r\n");
#endif
  return communication_protocol_ref(session);
}

/***********************************************************************************
 * API - communication_protocol_receive_payload - Wrapper function.
 *     This function is called from application to receive data from remote device.
 * *********************************************************************************/
bool communication_protocol_receive_payload(void *session_data, size_t size_recv_data) {
  bool res = FALSE;


#ifdef __linux__
  //LOGI("Entry -> communication_protocol_receive_payload\r\n");
#elif __APPLE__
   fprintf(stdout,"Entry -> communication_protocol_receive_payload\r\n");
#else  
  KLOG(INFO,"Entry -> communication_protocol_receive_payload\r\n");
#endif

  switch (communication_protocol_parse_payload(session_data, size_recv_data)) {
  case PARSE_ERROR:
    //connection_lost(session_data, EIO);

    res = FALSE;
  case PARSE_SUCCESS:
    res = TRUE;
  }


#ifdef __linux__
  //LOGI("Exit -> communication_protocol_receive_payload\r\n");
#elif __APPLE__
   fprintf(stdout,"Exit -> communication_protocol_receive_payload\r\n");
#else     
KLOG(INFO,"Exit -> communication_protocol_receive_payload\r\n");
#endif
  return res;
}

/***********************************************************************************
 * API - firmware_update_start Commands - START
 *    Commands Supported:
 
 *    firmware_update_start
  
***********************************************************************************/

bool communication_protocol_firmware_update_start(struct kbike_communication_protocol *session,
    uint8_t source_id, uint8_t session_id,void *firmware_update_id, uint8_t size) {


#ifdef __linux__
  //LOGI("Entry-> communication_protocol_firmware_update_start\n\r\r\n");
#elif __APPLE__
   fprintf(stdout,"Entry-> communication_protocol_firmware_update_start\n\r\r\n");    
#else  
  //KLOG(INFO,"->communication_protocol_firmware_update_start\n\r\r\n");
#endif

  return (communication_protocol_request(session, source_id, session_id,
  COMMUNICATION_PROTOCOL_MSG_TYPE_COMMAND,
  COMMUNICATION_PROTOCOL_CMD_GRP_DM_FIRMWARE_UPDATE, COMMUNICATION_PROTOCOL_CMD_FIRMWARE_UPDATE_START,
      firmware_update_id, size));
}
/************************** API - dm firmware update Command - END *****************************/



/***********************************************************************************
 * API - flash icon Commands - START
 *    Commands Supported:
 
 *    flash_icon
  
***********************************************************************************/

bool communication_protocol_flash_icon(struct kbike_communication_protocol *session,
    uint8_t source_id, uint8_t session_id, void *flash_icon, uint16_t size) {


#ifdef __linux__
  //LOGI("Entry-> communication_protocol_flash_icon\r\n");
#elif __APPLE__
   fprintf(stdout,"Entry-> communication_protocol_flash_icon\r\n");   
#else     
  //KLOG(INFO,"Entry-> communication_protocol_flash_icon\r\n");

#endif

  return (communication_protocol_request(session, source_id, session_id,
  COMMUNICATION_PROTOCOL_MSG_TYPE_COMMAND,
  COMMUNICATION_PROTOCOL_CMD_GRP_DM_FLASH_ICON, COMMUNICATION_PROTOCOL_CMD_UPDATE_ICON, flash_icon, size));
}
/************************** API - flash icon Commands - END *****************************/

/***********************************************************************************
 * API - DM new parameters Commands - START
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
    uint8_t source_id, uint8_t session_id, void *scurrentdate_time, uint16_t size) {


#ifdef __linux__
  //LOGI("Entry-> communication_protocol_current_date_time\r\n");
#elif __APPLE__
   fprintf(stdout,"Entry-> communication_protocol_current_date_time\r\n");
#else     
  //KLOG(INFO,"Entry-> communication_protocol_current_date_time");

#endif

  return (communication_protocol_request(session, source_id, session_id,
  COMMUNICATION_PROTOCOL_MSG_TYPE_COMMAND,
  COMMUNICATION_PROTOCOL_CMD_GRP_DM_NEW_PARAMETERS, COMMUNICATION_PROTOCOL_CMD_CURRENT_DATE_TIME, scurrentdate_time, size));
}


bool communication_protocol_vehicle_battery_voltage(struct kbike_communication_protocol *session,
    uint8_t source_id, uint8_t session_id, void *svehicle_battery_voltage, uint16_t size) {


#ifdef __linux__
  //LOGI("Entry-> communication_protocol_vehicle_battery_voltage\r\n");
#elif __APPLE__
   fprintf(stdout,"Entry-> communication_protocol_vehicle_battery_voltage\r\n");    
#else     
  //KLOG(INFO,"Entry-> communication_protocol_vehicle_battery_voltage\r\n");

#endif

  return (communication_protocol_request(session, source_id, session_id,
  COMMUNICATION_PROTOCOL_MSG_TYPE_COMMAND,
  COMMUNICATION_PROTOCOL_CMD_GRP_DM_NEW_PARAMETERS, COMMUNICATION_PROTOCOL_CMD_VEHICLE_BATTERY_VOLTAGE, svehicle_battery_voltage, size));
}


bool communication_protocol_source_name(struct kbike_communication_protocol *session,
    uint8_t source_id, uint8_t session_id, void *ssource_name, uint16_t size) {


#ifdef __linux__
  //LOGI("Entry-> communication_protocol_source_name\r\n");
#elif __APPLE__
   fprintf(stdout,"Entry-> communication_protocol_source_name\r\n");    
#else     
  //KLOG(INFO,"Entry-> communication_protocol_source_name\r\n");

#endif

  return (communication_protocol_request(session, source_id, session_id,
  COMMUNICATION_PROTOCOL_MSG_TYPE_COMMAND,
  COMMUNICATION_PROTOCOL_CMD_GRP_DM_NEW_PARAMETERS, COMMUNICATION_PROTOCOL_CMD_SOURCE_NAME, ssource_name, size));
}

bool communication_protocol_destination_name(struct kbike_communication_protocol *session,
    uint8_t source_id, uint8_t session_id, void *sdestination_name, uint16_t size) {


#ifdef __linux__
  //LOGI("Entry-> communication_protocol_destination_name\r\n");
#elif __APPLE__
   fprintf(stdout,"Entry-> communication_protocol_destination_name\r\n");   
#else     
  //KLOG(INFO,"Entry-> communication_protocol_destination_name\r\n");

#endif

  return (communication_protocol_request(session, source_id, session_id,
  COMMUNICATION_PROTOCOL_MSG_TYPE_COMMAND,
  COMMUNICATION_PROTOCOL_CMD_GRP_DM_NEW_PARAMETERS, COMMUNICATION_PROTOCOL_CMD_DESTINATION_NAME, sdestination_name, size));
}

bool communication_protocol_eta(struct kbike_communication_protocol *session,
    uint8_t source_id, uint8_t session_id, void *seta, uint16_t size) {


#ifdef __linux__
  //LOGI("Entry-> communication_protocol_eta\r\n");
#elif __APPLE__
   fprintf(stdout,"Entry-> communication_protocol_eta\r\n");    
#else     
  //KLOG(INFO,"Entry-> communication_protocol_eta\r\n");

#endif

  return (communication_protocol_request(session, source_id, session_id,
  COMMUNICATION_PROTOCOL_MSG_TYPE_COMMAND,
  COMMUNICATION_PROTOCOL_CMD_GRP_DM_NEW_PARAMETERS, COMMUNICATION_PROTOCOL_CMD_ETA, seta, size));
}

bool communication_protocol_current_manuever_icon(struct kbike_communication_protocol *session,
    uint8_t source_id, uint8_t session_id, void *scurrent_manuever_icon, uint16_t size) {


#ifdef __linux__
  //LOGI("Entry-> communication_protocol_current_manuever_icon\r\n");
#elif __APPLE__
   fprintf(stdout,"Entry-> communication_protocol_current_manuever_icon\r\n");    
#else     
  //KLOG(INFO,"Entry-> communication_protocol_current_manuever_icon\r\n");

#endif

  return (communication_protocol_request(session, source_id, session_id,
  COMMUNICATION_PROTOCOL_MSG_TYPE_COMMAND,
  COMMUNICATION_PROTOCOL_CMD_GRP_DM_NEW_PARAMETERS, COMMUNICATION_PROTOCOL_CMD_CURRENT_MANUEVER_ICON, scurrent_manuever_icon, size));
}
    
bool communication_protocol_current_manuever_distance_unit(struct kbike_communication_protocol *session,
    uint8_t source_id, uint8_t session_id, void *scurrent_manuever_distance_unit, uint16_t size) {


#ifdef __linux__
  //LOGI("Entry-> communication_protocol_current_manuever_distance_unit\r\n");
#elif __APPLE__
   fprintf(stdout,"Entry-> communication_protocol_current_manuever_distance_unit\r\n");
#else     
  //KLOG(INFO,"Entry-> communication_protocol_current_manuever_distance\r\n");

#endif

  return (communication_protocol_request(session, source_id, session_id,
  COMMUNICATION_PROTOCOL_MSG_TYPE_COMMAND,
  COMMUNICATION_PROTOCOL_CMD_GRP_DM_NEW_PARAMETERS, COMMUNICATION_PROTOCOL_CMD_CURRENT_MANUEVER_DISTANCE_UNIT, scurrent_manuever_distance_unit, size));
}


    
bool communication_protocol_next_manuever_icon(struct kbike_communication_protocol *session,
    uint8_t source_id, uint8_t session_id, void *snext_manuever_icon, uint16_t size) {


#ifdef __linux__
  //LOGI("Entry-> communication_protocol_next_manuever_icon\r\n");
#elif __APPLE__
   fprintf(stdout,"Entry-> communication_protocol_next_manuever_icon\r\n");   
#else     
  //KLOG(INFO,"Entry-> communication_protocol_next_manuever_icon\r\n");

#endif

  return (communication_protocol_request(session, source_id, session_id,
  COMMUNICATION_PROTOCOL_MSG_TYPE_COMMAND,
  COMMUNICATION_PROTOCOL_CMD_GRP_DM_NEW_PARAMETERS, COMMUNICATION_PROTOCOL_CMD_NEXT_MANUEVER_ICON, snext_manuever_icon, size));
}

bool communication_protocol_next_manuever_distance_unit(struct kbike_communication_protocol *session,
    uint8_t source_id, uint8_t session_id, void *snext_manuever_distance_unit, uint16_t size) {


#ifdef __linux__
  //LOGI("Entry-> communication_protocol_next_manuever_distance_unit\r\n");
#elif __APPLE__
   fprintf(stdout,"Entry-> communication_protocol_next_manuever_distance_unit\r\n");
#else     
  //KLOG(INFO,"Entry-> communication_protocol_next_manuever_distance_unit\r\n");

#endif

  return (communication_protocol_request(session, source_id, session_id,
  COMMUNICATION_PROTOCOL_MSG_TYPE_COMMAND,
  COMMUNICATION_PROTOCOL_CMD_GRP_DM_NEW_PARAMETERS, COMMUNICATION_PROTOCOL_CMD_NEXT_MANUEVER_DISTANCE_UNIT, snext_manuever_distance_unit, size));
}
    


bool communication_protocol_bike_fuel_level(struct kbike_communication_protocol *session,
    uint8_t source_id, uint8_t session_id, void *sbike_fuel_level, uint16_t size) {


#ifdef __linux__
  //LOGI("Entry-> communication_protocol_bike_fuel_level\r\n");
#elif __APPLE__
   fprintf(stdout,"Entry-> communication_protocol_bike_fuel_level\r\n");    
#else     
  //KLOG(INFO,"Entry-> communication_protocol_bike_fuel_level\r\n");

#endif

  return (communication_protocol_request(session, source_id, session_id,
  COMMUNICATION_PROTOCOL_MSG_TYPE_COMMAND,
  COMMUNICATION_PROTOCOL_CMD_GRP_DM_NEW_PARAMETERS, COMMUNICATION_PROTOCOL_CMD_BIKE_FULE_LEVEL, sbike_fuel_level, size));
}

bool communication_protocol_next_milage_distance_unit(struct kbike_communication_protocol *session,
    uint8_t source_id, uint8_t session_id, void *smilage_distance_unit, uint16_t size) {


#ifdef __linux__
  //LOGI("Entry-> communication_protocol_next_milage_distance_unit\r\n");
#elif __APPLE__
   fprintf(stdout,"Entry-> communication_protocol_next_milage_distance_unit\r\n");    
#else     
  //KLOG(INFO,"Entry-> communication_protocol_next_milage_distance_unit\r\n");

#endif

  return (communication_protocol_request(session, source_id, session_id,
  COMMUNICATION_PROTOCOL_MSG_TYPE_COMMAND,
  COMMUNICATION_PROTOCOL_CMD_GRP_DM_NEW_PARAMETERS, COMMUNICATION_PROTOCOL_CMD_BIKE_MILEAGE_DISTANCE_UNIT, smilage_distance_unit, size));
}
    
bool communication_protocol_travelled_distance_unit(struct kbike_communication_protocol *session,
    uint8_t source_id, uint8_t session_id, void *stravelled_distance_unit, uint16_t size) {


#ifdef __linux__
  //LOGI("Entry-> communication_protocol_travelled_distance_unit\r\n");
#elif __APPLE__
   fprintf(stdout,"Entry-> communication_protocol_travelled_distance_unit\r\n");
#else     
  //KLOG(INFO,"Entry-> communication_protocol_travelled_distance_unit\r\n");

#endif

  return (communication_protocol_request(session, source_id, session_id,
  COMMUNICATION_PROTOCOL_MSG_TYPE_COMMAND,
  COMMUNICATION_PROTOCOL_CMD_GRP_DM_NEW_PARAMETERS, COMMUNICATION_PROTOCOL_CMD_TRAVELLED_DISTANCE_UNIT, stravelled_distance_unit, size));
}
    
    
bool communication_protocol_cm_health_status_parameters(struct kbike_communication_protocol *session,
    uint8_t source_id, uint8_t session_id, void *scm_health_status_parameters, uint16_t size) {


#ifdef __linux__
  //LOGI("Entry-> communication_protocol_cm_health_status_parameters\r\n");
#elif __APPLE__
   fprintf(stdout,"Entry-> communication_protocol_cm_health_status_parameters\r\n");    
#else     
  //KLOG(INFO,"Entry-> communication_protocol_cm_health_status_parameters\r\n");

#endif

  return (communication_protocol_request(session, source_id, session_id,
  COMMUNICATION_PROTOCOL_MSG_TYPE_COMMAND,
  COMMUNICATION_PROTOCOL_CMD_GRP_DM_NEW_PARAMETERS, COMMUNICATION_PROTOCOL_CMD_CM_HEALTH_STATUS_PARAMETERS, scm_health_status_parameters, size));
}
  
bool communication_protocol_dm_info_parameters(struct kbike_communication_protocol *session,
    uint8_t source_id, uint8_t session_id, void *sdm_info_parameters, uint16_t size) {


#ifdef __linux__
  //LOGI("Entry-> communication_protocol_dm_info_parameters\r\n");
#elif __APPLE__
   fprintf(stdout,"Entry-> communication_protocol_dm_info_parameters\r\n");   
#else     
  //KLOG(INFO,"Entry-> communication_protocol_dm_info_parameters\r\n");

#endif

  return (communication_protocol_request(session, source_id, session_id,
  COMMUNICATION_PROTOCOL_MSG_TYPE_COMMAND,
  COMMUNICATION_PROTOCOL_CMD_GRP_DM_NEW_PARAMETERS, COMMUNICATION_PROTOCOL_CMD_DM_INFO_PARAMETERS, sdm_info_parameters, size));
}
    
bool communication_protocol_dm_user_name(struct kbike_communication_protocol *session,
    uint8_t source_id, uint8_t session_id, void *sdm_user_name, uint16_t size) {


#ifdef __linux__
  //LOGI("Entry-> communication_protocol_user_name\r\n");
#elif __APPLE__
   fprintf(stdout,"Entry-> communication_protocol_user_name\r\n");    
#else     
  //KLOG(INFO,"Entry-> communication_protocol_user_name\r\n");

#endif

  return (communication_protocol_request(session, source_id, session_id,
  COMMUNICATION_PROTOCOL_MSG_TYPE_COMMAND,
  COMMUNICATION_PROTOCOL_CMD_GRP_DM_NEW_PARAMETERS, COMMUNICATION_PROTOCOL_CMD_DM_USER_NAME, sdm_user_name, size));
}


bool communication_protocol_passkey(struct kbike_communication_protocol *session,
    uint8_t source_id, uint8_t session_id, void *spasskey, uint16_t size) {


#ifdef __linux__
  //LOGI("Entry-> communication_protocol_passkey\r\n");
#elif __APPLE__
   fprintf(stdout,"Entry-> communication_protocol_passkey\r\n");
#else
  //KLOG(INFO,"Entry-> communication_protocol_passkey\r\n");

#endif

  return (communication_protocol_request(session, source_id, session_id,
  COMMUNICATION_PROTOCOL_MSG_TYPE_COMMAND,
  COMMUNICATION_PROTOCOL_CMD_GRP_DM_NEW_PARAMETERS, COMMUNICATION_PROTOCOL_CMD_DM_PASSKEY, spasskey, size));
}
/************************** API - dm new parameters Commands - END *****************************/


/***********************************************************************************
 * API - DM Alerts & Warnings Commands - START
 *    Commands Supported:
 
 *    Urgent Alerts
 *    Non-Urgent Alerts
 *    Miscellaneous Alerts
 *    Warnings

***********************************************************************************/

bool communication_protocol_urgent_alerts(struct kbike_communication_protocol *session,
    uint8_t source_id, uint8_t session_id,void *surgent_alerts, uint16_t size) {


#ifdef __linux__
  //LOGI("Entry-> communication_protocol_urgent_alerts\r\n");
#elif __APPLE__
   fprintf(stdout,"Entry-> communication_protocol_urgent_alerts\r\n");    
#else     
  //KLOG(INFO,"Entry-> communication_protocol_urgent_alerts\r\n");

#endif

  return (communication_protocol_request(session, source_id, session_id,
  COMMUNICATION_PROTOCOL_MSG_TYPE_COMMAND,
  COMMUNICATION_PROTOCOL_CMD_GRP_DM_ALERTS_WARNINGS, COMMUNICATION_PROTOCOL_CMD_DM_URGENT_ALERTS, surgent_alerts, size));
}

bool communication_protocol_non_urgent_alerts(struct kbike_communication_protocol *session,
    uint8_t source_id, uint8_t session_id, void *snon_urgent_alerts, uint16_t size) {


#ifdef __linux__
  //LOGI("Entry-> communication_protocol_non_urgent_alerts\r\n");
#elif __APPLE__
   fprintf(stdout,"Entry-> communication_protocol_non_urgent_alerts\r\n");    
#else     
  //KLOG(INFO,"Entry-> communication_protocol_non_urgent_alerts\r\n");

#endif

  return (communication_protocol_request(session, source_id, session_id,
  COMMUNICATION_PROTOCOL_MSG_TYPE_COMMAND,
  COMMUNICATION_PROTOCOL_CMD_GRP_DM_ALERTS_WARNINGS, COMMUNICATION_PROTOCOL_CMD_DM_NON_URGENT_ALERTS, snon_urgent_alerts, size));
}

bool communication_protocol_miscellaneous_alerts(struct kbike_communication_protocol *session,
    uint8_t source_id, uint8_t session_id, void *smiscellaneous_alerts, uint16_t size) {


#ifdef __linux__
  //LOGI("Entry-> communication_protocol_miscellaneous_alerts\r\n");
#elif __APPLE__
   fprintf(stdout,"Entry-> communication_protocol_miscellaneous_alerts\r\n");   
#else     
  //KLOG(INFO,"Entry-> communication_protocol_miscellaneous_alerts\r\n");

#endif

  return (communication_protocol_request(session, source_id, session_id,
  COMMUNICATION_PROTOCOL_MSG_TYPE_COMMAND,
  COMMUNICATION_PROTOCOL_CMD_GRP_DM_ALERTS_WARNINGS, COMMUNICATION_PROTOCOL_CMD_DM_MISCELLANEOUS_ALERTS, smiscellaneous_alerts, size));
}
    
bool communication_protocol_dm_warnings(struct kbike_communication_protocol *session,
    uint8_t source_id, uint8_t session_id, void *sdm_warnings, uint16_t size) {


#ifdef __linux__
  //LOGI("Entry-> communication_protocol_dm_warnings\r\n");
#elif __APPLE__
   fprintf(stdout,"Entry-> communication_protocol_dm_warnings\r\n");    
#else     
  //KLOG(INFO,"Entry-> communication_protocol_dm_warnings\r\n");

#endif

  return (communication_protocol_request(session, source_id, session_id,
  COMMUNICATION_PROTOCOL_MSG_TYPE_COMMAND,
  COMMUNICATION_PROTOCOL_CMD_GRP_DM_ALERTS_WARNINGS, COMMUNICATION_PROTOCOL_CMD_DM_WARNINGS, sdm_warnings, size));
}



/************************** API - dm Alerts & Warnings Commands - END *****************************/


/***********************************************************************************
 * API - dm menu Commands - START
 *    Commands Supported:
 
 *    dm element
 *    dm widget
 *    dm screen
 *    dm carousal
  
***********************************************************************************/


bool communication_protocol_dm_element(struct kbike_communication_protocol *session,
    uint8_t source_id, uint8_t session_id, void *sdm_element, uint16_t size) {


#ifdef __linux__
  //LOGI("Entry-> communication_protocol_dm_element\r\n");
#elif __APPLE__
   fprintf(stdout,"Entry-> communication_protocol_dm_element\r\n");   
#else     
  //KLOG(INFO,"Entry-> communication_protocol_dm_element\r\n");

#endif

  return (communication_protocol_request(session, source_id, session_id,
  COMMUNICATION_PROTOCOL_MSG_TYPE_COMMAND,
  COMMUNICATION_PROTOCOL_CMD_GRP_DM_MENU_COMMANDS, COMMUNICATION_PROTOCOL_CMD_DM_ELEMENT, sdm_element, size));
}

bool communication_protocol_dm_widget(struct kbike_communication_protocol *session,
    uint8_t source_id, uint8_t session_id, void *sdm_widget, uint16_t size) {


#ifdef __linux__
  //LOGI("Entry-> communication_protocol_dm_widget\r\n");
#elif __APPLE__
   fprintf(stdout,"Entry-> communication_protocol_dm_widget\r\n");    
#else     
  //KLOG(INFO,"Entry-> communication_protocol_dm_widget\r\n");

#endif

  return (communication_protocol_request(session, source_id, session_id,
  COMMUNICATION_PROTOCOL_MSG_TYPE_COMMAND,
  COMMUNICATION_PROTOCOL_CMD_GRP_DM_MENU_COMMANDS, COMMUNICATION_PROTOCOL_CMD_DM_WIDGET, sdm_widget, size));
}
bool communication_protocol_dm_screen(struct kbike_communication_protocol *session,
    uint8_t source_id, uint8_t session_id, void *screen_data, uint16_t size) {


#ifdef __linux__
  //LOGI("Entry-> communication_protocol_dm_screen\r\n");
#elif __APPLE__
   fprintf(stdout,"Entry-> communication_protocol_dm_screen\r\n");    
#else     
  //KLOG(INFO,"Entry-> communication_protocol_dm_screen\r\n");

#endif

  return (communication_protocol_request(session, source_id, session_id,
  COMMUNICATION_PROTOCOL_MSG_TYPE_COMMAND,
  COMMUNICATION_PROTOCOL_CMD_GRP_DM_MENU_COMMANDS, COMMUNICATION_PROTOCOL_CMD_DM_SCREEN, screen_data, size));
}
    
bool communication_protocol_dm_carousel(struct kbike_communication_protocol *session,
    uint8_t source_id, uint8_t session_id, void *carousel_data, uint16_t size) {


#ifdef __linux__
  //LOGI("Entry-> communication_protocol_dm_carousel\r\n");
#elif __APPLE__
   fprintf(stdout,"Entry-> communication_protocol_dm_carousel\r\n");    
#else     
  //KLOG(INFO,"Entry-> communication_protocol_dm_carousel\r\n");

#endif

  return (communication_protocol_request(session, source_id, session_id,
  COMMUNICATION_PROTOCOL_MSG_TYPE_COMMAND,
  COMMUNICATION_PROTOCOL_CMD_GRP_DM_MENU_COMMANDS, COMMUNICATION_PROTOCOL_CMD_DM_CAROUSEL, carousel_data, size));
}
/************************** API - flash icon Commands - END *****************************/


/***********************************************************************************
 * API - dm hid Commands - START
 *    Commands Supported:
 *    key press
  
***********************************************************************************/

bool communication_protocol_key_press(struct kbike_communication_protocol *session,
        uint8_t src_id, uint8_t session_id, void *skey, uint8_t size) {


#ifdef __linux__
    //LOGI("Entry-> communication_protocol_key_press\r\n");
#elif __APPLE__
     fprintf(stdout,"Entry-> communication_protocol_key_press\r\n");      
#else   
    ////KLOG(INFO,"Entry-> communication_protocol_key_press\r\n");
#endif

    return (communication_protocol_request(session, src_id, session_id,
    COMMUNICATION_PROTOCOL_MSG_TYPE_COMMAND,
    COMMUNICATION_PROTOCOL_CMD_GRP_DM_HID, COMMUNICATION_PROTOCOL_CMD_KEY_PRESS,
            skey, size));
}
        



/************************** API - dm hid Commands - END *****************************/





/*****************  Display Protocol Interface to UL -> Upper Layer - End *******************/
















/******************************************************************************************
 *    communication_protocol_request - Wrapper function to initiate data transfer.
 *      This function prepares and attach display protocol headers and footers.
 * ****************************************************************************************/
static bool communication_protocol_request(struct kbike_communication_protocol *session,
    uint8_t src_id, uint8_t session_id, uint8_t msg_type, uint8_t cmd_grp,
    uint8_t cmd, void *data, uint16_t size) {

  uint8_t result = FALSE;
  uint16_t cp_crc_checksum=0x0000; //initializing checksum value to zero
  
  communication_protocol_header hdr;
  communication_protocol_footer ftr;

  size_t pkt_size;
  
  uint8_t *buffer = NULL;

  size_t hdr_size = sizeof(hdr);
  size_t ftr_size = sizeof(ftr);
  size_t data_size = (data == NULL ? 0 : size);


#ifdef __linux__
  //LOGI("Entry -> communication_protocol_request\r\n");
#elif __APPLE__
   fprintf(stdout,"Entry -> communication_protocol_request\r\n");   
#else    
  //KLOG(INFO,"Entry -> communication_protocol_request\r\n");
#endif

  pkt_size = hdr_size + data_size + ftr_size;


#ifdef __linux__
  buffer = (uint8_t*) malloc(pkt_size * sizeof(uint8_t));
#elif __APPLE__
  buffer = (uint8_t*) malloc(pkt_size * sizeof(uint8_t));
#else      
  buffer = (uint8_t*) pvPortMalloc(pkt_size * sizeof(uint8_t));
#endif

  memset(buffer, 0, pkt_size);
  
  /* 1. Verify if for Message type command, other than command CRC check sum is not required
     2. Verify data validity
     2. Calculate CRC on the actual data
     3. Save CRC checksum value, so it can be used to include in footer */
     
     //To-Do - Calculate CRC Checksum
     if(msg_type == COMMUNICATION_PROTOCOL_MSG_TYPE_COMMAND){
      //Check data
       if(data != NULL){
         
        
         #ifdef __linux__
         cp_crc_checksum=cc_calc_crc16(data, size);//Calculate CRC checksum here
         #elif __APPLE__
         cp_crc_checksum=cc_calc_crc16(data, size);//Calculate CRC checksum here
         #else     
         cp_crc_checksum=HAL_CRC_Calculate(&hcrc, (uint32_t *)data, size);
         #endif
        
      
         
       }
     }

  prepare_communication_protocol_header(&hdr, SOP, src_id, session_id, msg_type,
      cmd_grp, cmd, data_size);

  prepare_communication_protocol_footer(&ftr, cp_crc_checksum, EOP); //checksum +footer(2+2=4 bytes)

  session->msginfo.msg_type = msg_type;
  session->msginfo.cmd_grp = cmd_grp;
  session->msginfo.cmd = cmd;                                                                                                                                                                                                                                                                         

  memcpy(buffer, &hdr, hdr_size);

  if (data != NULL)
    memcpy(buffer + hdr_size, data, data_size);

  memcpy(buffer + hdr_size + data_size, &ftr, ftr_size);

  result = communication_protocol_send(session, (void*) buffer, pkt_size);

  //cp_start_request_timeout_timer(session);


#ifdef __linux__
  free(buffer);
#elif __APPLE__
  free(buffer);
#else     
  vPortFree(buffer);
#endif



#ifdef __linux__
  //LOGI("Exit -> communication_protocol_request\r\n");
#elif __APPLE__
   fprintf(stdout,"Exit -> communication_protocol_request\r\n");
#else 
  KLOG(INFO,"Exit -> communication_protocol_request\r\n");
#endif
  return result;
}
/******************************************************************************************
 *    communication_protocol_send - Wrapper function to send data.
 *      This function verify data size and fragments data if necessary,
 *      also attach payload headers and call application transport callback function
 *      to send data to remote device.
 * ****************************************************************************************/
static bool communication_protocol_send(struct kbike_communication_protocol *session,
    void *data, size_t len) {

  uint32_t sent;
  uint16_t total_fragments, current_pkt;
  packet_header header;

  bool res = FALSE;


#ifdef __linux__
  //LOGI("Entry -> communication_protocol_send\r\n");
#elif __APPLE__
   fprintf(stdout,"Entry -> communication_protocol_send\r\n");    
#else     
  //KLOG(INFO,"Entry -> communication_protocol_send\r\n");
#endif

  memset(&header, 0, sizeof(header));
  memset(session->outbuf, 0, session->omtu);

  /* Single packet - no fragmentation */
  if (len <= session->omtu - sizeof(header)) {

    prepare_payload_pkt_header(&header, 1, 1);

    memcpy(session->outbuf, &header, sizeof(header));
    memcpy(session->outbuf + sizeof(header), data, len);

    if (session->endpoint.transport_cb
        && session->endpoint.transport_cb->try_send) {
      res = (session->endpoint.transport_cb->try_send(session->outbuf,
          sizeof(header) + len));
    }
  }

  else {
    /* Count the number of needed fragments */
    if ((len % (session->omtu - sizeof(header))) == 0) {
      total_fragments = len / (session->omtu - sizeof(header));
      /*printf("\n%zu bytes split into %d fragments\n", len,
       total_fragments);*/
    } else {
      total_fragments = ((len - (session->omtu - sizeof(header)))
          / (session->omtu - sizeof(header)) + 1) + 1;
      /*printf("\n%zu bytes split into %d fragments\n", len,
       total_fragments);*/
    }

    /* Send the fragments till end */
    sent = 0;
    current_pkt = 1;

    while (sent < len) {
      int left, to_copy;

      left = len - sent;
      if (left + sizeof(header) > session->omtu) {
        to_copy = session->omtu - sizeof(header);
      } else {
        to_copy = left;
      }

      prepare_payload_pkt_header(&header, total_fragments, current_pkt);

      memcpy(session->outbuf, &header, sizeof(header));
    //  memcpy(session->outbuf + sizeof(header), data + sent, to_copy);
      memcpy(session->outbuf + sizeof(header), ((uint8_t *)data) + sent, to_copy);

      if (session->endpoint.transport_cb
          && session->endpoint.transport_cb->try_send) {
        /*if (!session->endpoint.transport_cb->try_send(session->outbuf,
         sizeof(header) + to_copy))*/
        res = session->endpoint.transport_cb->try_send(session->outbuf,
            sizeof(header) + to_copy);
      }
      sent += to_copy;
      ++current_pkt;
    }
  }

#ifdef __linux__
  //LOGI("Exit -> communication_protocol_send\r\n");
#elif __APPLE__
   fprintf(stdout,"Exit -> communication_protocol_send\r\n");   
#else     
  //KLOG(INFO,"Exit -> communication_protocol_send\r\n");
#endif

  return res;
}

/******************************************************************************************
 *    communication_protocol_ref - Utility function. Keeps reference count for initialized
 *      display protocol instance;
 *      the functionality is not in use but can be utilize in future.
 * ****************************************************************************************/
static struct kbike_communication_protocol* communication_protocol_ref(
    struct kbike_communication_protocol *session) {
  session->ref++;
  return session;
}

/******************************************************************************************
 *    prepare_payload_pkt_header - Prepares payload header,
 *      the header contains total packets and current packet number.
 * ****************************************************************************************/
static void prepare_payload_pkt_header(packet_header *header,
    uint32_t total_pkt, uint32_t pkt_num) {


#ifdef __linux__
  //LOGI("Entry -> prepare_payload_pkt_header\r\n");
#elif __APPLE__
   fprintf(stdout,"Entry -> prepare_payload_pkt_header\r\n");   
#else     
  //KLOG(INFO,"Entry -> prepare_payload_pkt_header\r\n");
#endif

  header->total_packets = total_pkt;
  header->packet_num = pkt_num;

#ifdef __linux__
  //LOGI("Exit -> prepare_payload_pkt_header\r\n");
#elif __APPLE__
   fprintf(stdout,"Exit -> prepare_payload_pkt_header\r\n");    
#else     
  //KLOG(INFO,"Exit -> prepare_payload_pkt_header\r\n");
#endif
}

/******************************************************************************************
 *    prepare_communication_protocol_header - Prepares display protocol header,
 *      the header contains Start of Packet, Command info, data size etc.
 * ****************************************************************************************/
static void prepare_communication_protocol_header(communication_protocol_header *hdr,
    uint16_t sop, uint8_t src_id, uint8_t session_id, uint8_t msg_type,
    uint8_t cmd_grp, uint8_t cmd, uint16_t size) {


#ifdef __linux__
  //LOGI("Entry -> prepare_communication_protocol_header\r\n");
#elif __APPLE__
   fprintf(stdout,"Entry -> prepare_communication_protocol_header\r\n");    
#else     
  //KLOG(INFO,"Entry -> prepare_communication_protocol_header\r\n");
#endif

  hdr->sop = sop;
  hdr->src_id = src_id;
  hdr->session_id = session_id;
  hdr->msg_type = msg_type;
  hdr->cmd_group = cmd_grp;
  hdr->cmd = cmd;
  hdr->size_payload = size;

#ifdef __linux__
  //LOGI("Exit -> prepare_communication_protocol_header\r\n");
#elif __APPLE__
   fprintf(stdout,"Exit -> prepare_communication_protocol_header\r\n");   
#else     
  //KLOG(INFO,"Exit -> prepare_communication_protocol_header\r\n");
#endif
}

/******************************************************************************************
 *    prepare_communication_protocol_footer - Prepares display protocol footer,
 *      the footer contains CRC and End of Packet byte code.
 * ****************************************************************************************/
static void prepare_communication_protocol_footer(communication_protocol_footer *ftr,
    uint16_t crc, uint16_t eop) {


#ifdef __linux__
  //LOGI("Entry -> prepare_communication_protocol_footer\r\n");
#elif __APPLE__
   fprintf(stdout,"Entry -> prepare_communication_protocol_footer\r\n");    
#else     
  //KLOG(INFO,"Entry -> prepare_communication_protocol_footer\r\n");
#endif

  ftr->crc = crc;
  ftr->eop = eop;

#ifdef __linux__
  //LOGI("Exit -> prepare_communication_protocol_footer\r\n");
#elif __APPLE__
   fprintf(stdout,"Exit -> prepare_communication_protocol_footer\r\n");   
#else     
  //KLOG(INFO,"Exit -> prepare_communication_protocol_footer\r\n");
#endif
}

/******************************************************************************************
 *    cp_start_request_timeout_timer - Starts request timeout timer.
 *      This is called after sending command,
 *      this is applicable only for sending command to remote device.
 *      Timer need require for sending acknowledgment for received command.
 * ****************************************************************************************/
static void cp_start_request_timeout_timer(struct kbike_communication_protocol *session) {


#ifdef __linux__
  //LOGI("Entry -> cp_start_request_timeout_timer\r\n");
#elif __APPLE__
   fprintf(stdout,"Entry -> cp_start_request_timeout_timer\r\n");
#else     
  //KLOG(INFO,"Entry -> cp_start_request_timeout_timer\r\n");
#endif

  /*
   * Enable Request timeout timer only after Request sending Commands
   * Timer is not required for sending Reponse for received Commands
   * */
  if (session->msginfo.msg_type == COMMUNICATION_PROTOCOL_MSG_TYPE_COMMAND) {
    /*printf("\nRequest Timer Started [Req CMD ID: %x]\n",
     session->msginfo.cmd);*/
#ifdef __linux__
//start_timer(REQUEST_TIME_OUT, &cp_request_timeout, session);  
#elif __APPLE__
start_timer(REQUEST_TIME_OUT, &cp_request_timeout, session);
#else     
//osTimerStart( cpRequestTimeoutTimerHandle, REQUEST_TIME_OUT );
osTimerStart( cpRequestTimeoutTimerHandle, REQUEST_TIME_OUT );
#endif
  }

#ifdef __linux__
  //LOGI("Exit -> cp_start_request_timeout_timer\r\n");
#elif __APPLE__
   fprintf(stdout,"Exit -> cp_start_request_timeout_timer\r\n");
#else     
  //KLOG(INFO,"Exit -> cp_start_request_timeout_timer\r\n");
#endif
}

/******************************************************************************************
 *    cp_stop_request_timeout_timer - To stop currently active request timeout timer.
 * ****************************************************************************************/
static void cp_stop_request_timeout_timer(struct kbike_communication_protocol *session) {

  communication_protocol_header *hdr = (communication_protocol_header*) session->in.buf;


#ifdef __linux__
  //LOGI("Entry -> cp_stop_request_timeout_timer\r\n");
#elif __APPLE__
   fprintf(stdout,"Entry -> cp_stop_request_timeout_timer\r\n");
#else     
  //KLOG(INFO,"Entry -> cp_stop_request_timeout_timer\r\n");
#endif
  /*
   * Disable/Stop Request timeout timer only after receiving CMD Response
   * Timer is not required for sending Reponse for received Commands
   * */
  if (hdr->msg_type != COMMUNICATION_PROTOCOL_MSG_TYPE_COMMAND) {

#ifdef __linux__
    stop_timer();
#elif __APPLE__
    stop_timer();
#else    
    //osTimerStop(cpRequestTimeoutTimerHandle);
    osTimerStop(cpRequestTimeoutTimerHandle);
#endif
    //printf("\nRequest Timer Stopped [Req CMD ID: %x]", hdr->cmd);
  }

#ifdef __linux__
  //LOGI("Exit -> cp_stop_request_timeout_timer\r\n");
#elif __APPLE__
   fprintf(stdout,"Exit -> cp_stop_request_timeout_timer\r\n");
#else     
  //KLOG(INFO,"Exit -> cp_stop_request_timeout_timer\r\n");
#endif
}

/******************************************************************************************
 *    cp_request_timeout - To timer elspase callback function.
 * ****************************************************************************************/

#ifdef __linux__
void cp_request_timeout(void *session_info) {
  struct kbike_communication_protocol *session =
      (struct kbike_communication_protocol *) session_info;


  //LOGI("Entry -> cp_request_timeout\r\n");


  //printf("\nRequest Timed out [Req ID: %x]", session->msginfo.cmd);
  stop_timer();
  cp_cancel_request(session);
  memset(session->outbuf, 0, session->omtu);


  //LOGI("Exit -> cp_request_timeout\r\n");


  return;
}
#elif __APPLE__
void cp_request_timeout(void *session_info) {
  struct kbike_communication_protocol *session =
      (struct kbike_communication_protocol *) session_info;
 

  
   fprintf(stdout,"Entry -> cp_request_timeout\r\n");

  //printf("\nRequest Timed out [Req ID: %x]", session->msginfo.cmd);
  stop_timer();
  cp_cancel_request(session);
  memset(session->outbuf, 0, session->omtu);



   fprintf(stdout,"Exit -> cp_request_timeout\r\n");

  return;
}
#else     
void cp_request_timeout(const void *session_info) {
  struct kbike_communication_protocol *session = (struct kbike_communication_protocol *)session_info;

  KLOG(INFO,"Entry -> cp_request_timeout\r\n");

  //printf("\nRequest Timed out [Req ID: %x]", session->msginfo.cmd);
  //osTimerStop(cpRequestTimeoutTimerHandle);
  osTimerStop(cpRequestTimeoutTimerHandle);
  cp_cancel_request(session);
  memset(session->outbuf, 0, session->omtu);


  KLOG(INFO,"Exit -> cp_request_timeout\r\n");

  return;
}
#endif

/******************************************************************************************
 *    communication_protocol_parse_payload - parse payload data once received.
 *      This function verify data based on payload header.
 *      Reassembles multiple packets and construct actual data.
 * ****************************************************************************************/
static enum communication_protocol_parse_result communication_protocol_parse_payload(
    void *session_data, size_t len) { 
  static uint32_t current_pkt, recv_size;
  
  struct kbike_communication_protocol *session = session_data;
  packet_header *header = (packet_header*) session->inbuf;
  void *payload;
  size_t payload_size;


#ifdef __linux__
  //LOGI("Entry -> communication_protocol_parse_payload\r\n");
#elif __APPLE__
   fprintf(stdout,"Entry -> communication_protocol_parse_payload\r\n");   
#else     
  KLOG(INFO,"Entry -> communication_protocol_parse_payload\r\n");
#endif
    
    if(gTpck_count == 0)  
    {     
    gPrevious_tpck=header->total_packets;  //store total packet  value in  previous_tpack variable
    ++gTpck_count;    
    }
    
  
    if(gPrevious_tpck !=  header->total_packets) //check if total packet matching previous stored value
    {                                            //if not free buffer and  make current_pkt zero.
        current_pkt = 0;
        recv_size = 0;
        gPrevious_tpck=0;
        gTpck_count=0;
#if 0   
     #ifdef __linux__
        free(gRecv_buffer);
     #elif __APPLE__
      free(gRecv_buffer);
     #else     
        vPortFree(gRecv_buffer);
      #endif
        gRecv_buffer = NULL;
#endif
      memset(session->in.buf, 0, CP_BUFFER_SIZE);
    }

  if (header->total_packets == 1) {
    if (header->packet_num > 1 || header->packet_num <= 0) {
    
        
       #ifdef __linux__
        //LOGI("Exit -> communication_protocol_parse_payload\r\n");
       #elif __APPLE__
         fprintf(stdout,"Exit -> communication_protocol_parse_payload\r\n");
       #else    
        KLOG(INFO,"Exit -> communication_protocol_parse_payload\r\n");
      #endif
      return PARSE_ERROR;
    }
    
    payload = session->inbuf + sizeof(*header);
    payload_size = len - sizeof(*header);

    session->in.data_size = payload_size;
    memcpy(session->in.buf, payload, payload_size);

    communication_protocol_parse_data(session);
    
      gPrevious_tpck=0; //reseting previous totat packet stored value
      gTpck_count=0;       //count for ensuring total packet value get copied in  previous_tpack only once
    
      #ifdef __linux__
      //LOGI("Exit -> communication_protocol_parse_payload\r\n");
      #elif __APPLE__
       fprintf(stdout,"Exit -> communication_protocol_parse_payload\r\n");
      #else     
      //KLOG(INFO,"Exit -> communication_protocol_parse_payload\r\n");
      #endif
    return PARSE_SUCCESS;
  } else { /* Receive all packets and reassemble data */
    uint32_t total_pkts = header->total_packets;
    

    if ((header->packet_num <= 0) || header->total_packets <= 0) {
      
      #ifdef __linux__
      //LOGI("Exit -> communication_protocol_parse_payload\r\n");
      #elif __APPLE__
      fprintf(stdout,"Exit -> communication_protocol_parse_payload\r\n");
      #else  
      KLOG(INFO,"Exit -> communication_protocol_parse_payload\r\n");
      #endif
      return PARSE_ERROR;
    }


    
    memcpy(session->in.buf + recv_size, session->inbuf + sizeof(*header),
        len - sizeof(*header));
    
    recv_size += (len - sizeof(*header));
    ++current_pkt;

    if (current_pkt == total_pkts) {
      if (recv_size > sizeof(session->in.buf)) {

        cp_handle_low_buffer(session, session->in.buf);
         
        current_pkt = 0;
        recv_size = 0;
        
      


      #ifdef __linux__
      //LOGI("Exit -> communication_protocol_parse_payload\r\n");
      #elif __APPLE__
       fprintf(stdout,"Exit -> communication_protocol_parse_payload\r\n");
      #else    
      KLOG(INFO,"Exit -> communication_protocol_parse_payload\r\n");
      #endif
        return PARSE_ERROR;
      }

      session->in.data_size = recv_size;
      communication_protocol_parse_data(session);

      current_pkt = 0;
      recv_size = 0;
      gPrevious_tpck=0; //reseting previous totat packed stored value
      gTpck_count=0;       //count for ensuring total packet value get copied in  previous_tpack only once
    
}
    
    #ifdef __linux__
      //LOGI("Exit -> communication_protocol_parse_payload\r\n");
    #elif __APPLE__
       fprintf(stdout,"Exit -> communication_protocol_parse_payload\r\n");
    #else    
      KLOG(INFO,"Exit -> communication_protocol_parse_payload\r\n");
    #endif
    return PARSE_SUCCESS;
  }

}

/******************************************************************************************
 *    communication_protocol_parse_data - parse protocol data.
 *      Extracts protocol header and process data.
 * ****************************************************************************************/
static void communication_protocol_parse_data(struct kbike_communication_protocol *session) {
  uint8_t result;
  communication_protocol_header *hdr = (communication_protocol_header*) session->in.buf;

#ifdef __linux__
  //LOGI("Entry -> communication_protocol_parse_data\r\n");
#elif __APPLE__
   fprintf(stdout,"Entry -> communication_protocol_parse_data\r\n");
#else    
  //KLOG(INFO,"Entry -> communication_protocol_parse_data\r\n");
#endif
  result = is_valid_data(session);
  if (result != COMMUNICATION_PROTOCOL_VALID_DATA) {
    communication_protocol_request(session, hdr->src_id, hdr->session_id, result,
        hdr->cmd_group, hdr->cmd, NULL, ZERO_PAYLOAD_SIZE);
    //perror("Invalid data received\r\n");
#ifdef __linux__
  //LOGI("Exit -> communication_protocol_parse_data\r\n");
#elif __APPLE__
   fprintf(stdout,"Exit -> communication_protocol_parse_data\r\n");
#else    
  //KLOG(INFO,"Exit -> communication_protocol_parse_data\r\n");
#endif
    return;
  }

  session->in.message_type = hdr->msg_type;

  if (session->in.message_type == COMMUNICATION_PROTOCOL_MSG_TYPE_COMMAND) {
    /*if (!cp_parse_cmd(session)) {
     perror("Unable to handle command. Disconnecting\r\n");
     }*/
    cp_parse_cmd(session);
  } else {

    /* Request timeout timer need to stop after receiving command response */
    //cp_stop_request_timeout_timer(session);

    switch (session->in.message_type) {

    case COMMUNICATION_PROTOCOL_SUCCESS_ACK:
    case COMMUNICATION_PROTOCOL_HEARTBEAT_ACK:
    case COMMUNICATION_PROTOCOL_FAIL_ACK:
    case COMMUNICATION_PROTOCOL_MSG_TYPE_GEN_REJECT:
    case COMMUNICATION_PROTOCOL_BAD_HEADER_FORMAT:
    case COMMUNICATION_PROTOCOL_BAD_LENGTH:
    case COMMUNICATION_PROTOCOL_INVALID_COMMAND:
    case COMMUNICATION_PROTOCOL_NO_BUFFER_SPACE:
      /*if (!cp_parse_resp(session)) {
       perror("Unable to parse accept response\r\n");
       }*/
      cp_parse_resp(session);
      break;

    default:
      //perror("Unknown response type\r\n");
      break;
    }
  }

#ifdef __linux__
  //LOGI("Exit -> communication_protocol_parse_data\r\n");
#elif __APPLE__
   fprintf(stdout,"Exit -> communication_protocol_parse_data\r\n");
#else    
  //KLOG(INFO,"Exit -> communication_protocol_parse_data\r\n");
#endif
}


/***********************************************************************************
 *            Response Handler Functionality - Start
 ***********************************************************************************/
static bool cp_parse_resp(struct kbike_communication_protocol *session) {

  bool res = FALSE;
  communication_protocol_header *hdr = (communication_protocol_header*) session->in.buf;


#ifdef __linux__
  //LOGI("Entry -> cp_parse_resp\r\n");
#elif __APPLE__
   fprintf(stdout,"Entry -> cp_parse_resp\r\n");
#else     
  //KLOG(INFO,"Entry -> cp_parse_resp\r\n");
#endif

  if (session->endpoint.cfm_cb && session->endpoint.cfm_cb->callback_cfm) {
    session->endpoint.cfm_cb->callback_cfm(session, session->in.message_type);
    res = TRUE;
  }


#ifdef __linux__
  //LOGI("Exit -> cp_parse_resp\r\n");
#elif __APPLE__
   fprintf(stdout,"Exit -> cp_parse_resp\r\n");
#else     
  //KLOG(INFO,"Exit -> cp_parse_resp\r\n");
#endif

  return res;
}








/******************************************************************************************
 *    cp_handle_low_buffer - utility function to verify and handle low buffer condition.
 * ****************************************************************************************/
static void cp_handle_low_buffer(void *session, void *recv_buffer) {
  communication_protocol_header *hdr = (communication_protocol_header*) recv_buffer;


#ifdef __linux__
  //LOGI("Entry -> cp_handle_low_buffer\r\n");
#elif __APPLE__
   fprintf(stdout,"Entry -> cp_handle_low_buffer\r\n");
#else     
  //KLOG(INFO,"Entry -> cp_handle_low_buffer\r\n");
#endif

  communication_protocol_request(session, hdr->src_id, hdr->session_id,
  COMMUNICATION_PROTOCOL_NO_BUFFER_SPACE, hdr->cmd_group, hdr->cmd, NULL,
  ZERO_PAYLOAD_SIZE);


#ifdef __linux__
  //LOGI("Exit -> cp_handle_low_buffer\r\n");
#elif __APPLE__
   fprintf(stdout,"Exit -> cp_handle_low_buffer\r\n");
#else     
  //KLOG(INFO,"Exit -> cp_handle_low_buffer\r\n");
#endif
}

/******************************************************************************************
 *    cp_parse_cmd - Function to Send Payload data to Indication Function
 * ****************************************************************************************/
static bool cp_parse_cmd(struct kbike_communication_protocol *session) {
  bool res = FALSE;
  communication_protocol_header *hdr = (communication_protocol_header*) session->in.buf;
  

#ifdef __linux__
  //LOGI("Entry -> cp_parse_cmd\r\n");
#elif __APPLE__
   fprintf(stdout,"Entry -> cp_parse_cmd\r\n");
#else     
  KLOG(INFO,"Entry -> cp_parse_cmd\r\n");
#endif
  
  
      if (session->endpoint.ind_cb && session->endpoint.ind_cb->callback_ind) {
        res = session->endpoint.ind_cb->callback_ind(session);
      }
        
  
  if (!res) {
    res = communication_protocol_request(session, hdr->src_id, hdr->session_id,
    COMMUNICATION_PROTOCOL_FAIL_ACK, hdr->cmd_group, hdr->cmd, NULL,
    ZERO_PAYLOAD_SIZE);
  } else {
    res = communication_protocol_request(session, SOURCE_ID_PHONE,
        hdr->session_id, COMMUNICATION_PROTOCOL_SUCCESS_ACK, hdr->cmd_group,
        hdr->cmd, NULL, ZERO_PAYLOAD_SIZE);
  }


 

#ifdef __linux__
  //LOGI("Exit -> cp_parse_cmd\r\n");
#elif __APPLE__
   fprintf(stdout,"Exit -> cp_parse_cmd\r\n");
#else     
  KLOG(INFO,"Exit -> cp_parse_cmd\r\n");
#endif
  return res;
}

/******************************************************************************************
 *    is_valid_data - Function to validate data integrity.
 * ****************************************************************************************/
static uint8_t is_valid_data(struct kbike_communication_protocol *session) {
  uint8_t result = COMMUNICATION_PROTOCOL_VALID_DATA;
  uint8_t *gBuff_msgpayload;
  
  uint16_t cp_crc_checksum=0x0000;  ////initializing checksum value to zero
  communication_protocol_header *hdr = (communication_protocol_header*) session->in.buf;
  communication_protocol_footer *ftr = (communication_protocol_footer*) (session->in.buf
      + sizeof(*hdr) + hdr->size_payload);


#ifdef __linux__
  //LOGI("Entry -> is_valid_data\r\n");
#elif __APPLE__
   fprintf(stdout,"Entry -> is_valid_data\r\n");
#else     
  KLOG(INFO,"Entry -> is_valid_data\r\n");
#endif

  if (hdr->sop == SOP && ftr->eop == EOP)
  {
    if(hdr->msg_type == COMMUNICATION_PROTOCOL_MSG_TYPE_COMMAND)
    {
        gBuff_msgpayload = session->in.buf + sizeof(*hdr);  //  gBuff_msgpayload is pointer to payload
    
    #ifdef __linux__
        cp_crc_checksum=cc_calc_crc16(gBuff_msgpayload, hdr->size_payload);
    #elif __APPLE__
        cp_crc_checksum=cc_calc_crc16(gBuff_msgpayload, hdr->size_payload);
    #else     
      //  cp_crc_checksum=HAL_CRC_Calculate(&hcrc,(uint32_t *)gBuff_msgpayload,hdr->size_payload);
    #endif
//        if(cp_crc_checksum == ftr->crc)          //checking if crc values matching for payload integrity
//        {
//
//          #ifdef __linux__
//            //LOGI("Valid data CRC OK\r\n");
//          #elif __APPLE__
//             fprintf(stdout,"Valid data CRC OK\r\n");
//          #else
//            KLOG(INFO,"Valid data CRC OK\r\n");
//          #endif
//            result = COMMUNICATION_PROTOCOL_VALID_DATA;
//        }
//        else
//        {
//
//          #ifdef __linux__
//            //LOGI("CRC ERROR\r\n");
//          #elif __APPLE__
//             fprintf(stdout,"CRC ERROR\r\n");
//          #else
//            KLOG(INFO,"CRC ERROR\r\n");
//          #endif
//            result= CRC16_CHECKSUM_ERROR;
//        }
    }
  } else {
    if (hdr->sop != SOP)
      result = COMMUNICATION_PROTOCOL_BAD_HEADER_FORMAT;
    else if (ftr->eop != EOP)
      result = COMMUNICATION_PROTOCOL_BAD_HEADER_FORMAT;
  }

#ifdef __linux__
  //LOGI("Exit -> is_valid_data\r\n");
#elif __APPLE__
   fprintf(stdout,"Exit -> is_valid_data\r\n");
#else     
  KLOG(INFO,"Exit -> is_valid_data\r\n");
#endif
  return result;
}

/******************************************************************************************
 *    end_connection - Function to free resources on disconnection.
 * ****************************************************************************************/
void end_connection(struct kbike_communication_protocol *session) {


#ifdef __linux__
  //LOGI("Entry -> end_connection\r\n");
#elif __APPLE__
   fprintf(stdout,"Entry -> end_connection\r\n");
#else     
  //KLOG(INFO,"Entry -> end_connection\r\n");
#endif
  if (session){
    /* Free resources */


#ifdef __linux__
    /*free(session->buf);*/ /* buf is replaced with inbuf in communicationprotocol.h */
    free(session);
#elif __APPLE__
    /*free(session->buf);*/ /* buf is replaced with inbuf in communicationprotocol.h */
    free(session);  
#else    
    /*vPortFree(session->buf);*/ /* buf is replaced with inbuf in communicationprotocol.h */
    vPortFree(session);
#endif
  }


#ifdef __linux__
  //LOGI("Exit -> end_connection\r\n");
#elif __APPLE__
   fprintf(stdout,"Exit -> end_connection\r\n");
#else     
  //KLOG(INFO,"Exit -> end_connection\r\n");
#endif
}

/******************************************************************************************
 *    cp_cancel_request - Call to this will cancel request and notify
 *      Application about the cancellation with reason(error code).
 * ****************************************************************************************/
void cp_cancel_request(struct kbike_communication_protocol *session) {

  uint8_t msg_type, cmd_grp, cmd;
  bool res = FALSE;


#ifdef __linux__
  //LOGI("Entry -> cp_cancel_request\r\n");
#elif __APPLE__
   fprintf(stdout,"Entry -> cp_cancel_request\r\n");
#else     
  KLOG(INFO,"Entry -> cp_cancel_request\r\n");
#endif

  msg_type = session->msginfo.msg_type;
  cmd_grp = session->msginfo.cmd_grp;
  cmd = session->msginfo.cmd;

  //printf("\nRequest cancelled [Req ID: %x]\n", cmd);
  if (msg_type == COMMUNICATION_PROTOCOL_MSG_TYPE_COMMAND) {
    session->in.message_type = COMMUNICATION_PROTOCOL_REQUEST_TIME_OUT; //change msg type to notify UL about request timeout
  
    
    if (session->endpoint.cfm_cb && session->endpoint.cfm_cb->callback_cfm) {
    session->endpoint.cfm_cb->callback_cfm(session, session->in.message_type);
    res = TRUE;
  }

      
    }
  

#ifdef __linux__
  //LOGI("Exit -> cp_cancel_request\r\n");
#elif __APPLE__
   fprintf(stdout,"Exit -> cp_cancel_request\r\n");
#else     
  KLOG(INFO,"Exit -> cp_cancel_request\r\n");
#endif
}



/******************************************************************************************
 *    display_data - Utility function to display data on terminal
 * ****************************************************************************************/
/*void display_data(communication_protocol_header *hdr, communication_protocol_footer *ftr) {
 printf(
 "\nInit CMD \nSOP: %d \nSRC_ID: %d \nSessionID: %d \nCMD_GRP: %d \nCMD: %d \nPayLoad Size: %d\n",
 hdr->sop, hdr->src_id, hdr->session_id, hdr->cmd_group, hdr->cmd,
 hdr->size_payload);
 printf("CRC: %d \nEOP: %d\n", ftr->crc, ftr->eop);
 }*/


 #ifdef __cplusplus
}
#endif

