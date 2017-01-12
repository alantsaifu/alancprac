 /* Copyright (c) 2012 Nordic Semiconductor. All Rights Reserved.
 *
 * The information contained herein is property of Nordic Semiconductor ASA.
 * Terms and conditions of usage are described in detail in NORDIC
 * SEMICONDUCTOR STANDARD SOFTWARE LICENSE AGREEMENT.
 *
 * Licensees are granted free, non-transferable use of the information. NO
 * WARRANTY of ANY KIND is provided. This heading must NOT be removed from
 * the file.
 *
 * $LastChangedRevision$
 */
 
#include "m_mouse.h"



static app_sched_event_handler_t s_event_handler        = 0;

static volatile bool             s_btn_timer_running    = false;
static volatile bool             s_sensor_timer_running = false;
static uint32_t                  s_sensor_pollrate      = M_MOUSE_SENSOR_POLLRATE;
static uint32_t                  s_button_pollrate      = M_MOUSE_BTN_POLLRATE;
static bool                      s_mouse_sensor_enabled = false;
static bool                      s_mouse_initialized = false;
#ifdef HOSTPRENT
static uint8_t 					 s_connected_ctrl;
#endif

//&*&*&*G1093015_ADD
static protocol_mode_t 	s_switch_protocol = protocol_mode_gzll;


//&*&*&*G2093015_ADD
//&*&*&*G1110615_ADD
extern bool               ext_coms_bonding;
//&*&*&*G1110615_ADD

#ifdef HOSTPRENT
extern bool               gzp_addr_req_clr;
#endif


uint32_t m_mouse_init(m_mouse_init_t *init)
{
    s_sensor_pollrate = init->sensor_pollrate;
    s_button_pollrate = init->button_pollrate;
    s_event_handler   = init->event_handler;
       
    return 0;
}
