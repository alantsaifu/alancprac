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
 
#include "m_coms.h"

#include <string.h>
#include <stdio.h>


#include "m_coms_ble.h"
#include "m_mouse.h"


#define M_COMS_ADV_TIMEOUTS     2



static protocol_mode_t        m_coms_protocol_scheme; /** Which protocol(s) to use. */
static protocol_mode_t        m_coms_protocol_used;   /** Currently used protocol. */
static uint32_t               m_coms_timeouts;        /** How many advertising timeouts has occured. Used in protocol_mode_auto. */

//&*&*&*G1110615_ADD, to share to m_mouse.c
				bool              ext_coms_bonding = false;
//&*&*&*G2110615_ADD, to share to m_mouse.c
static protocol_mode_t        m_coms_protocol_switch_pending = protocol_mode_void;
app_sched_event_handler_t     m_coms_event_callback;  /** Event handler used to notify application of events. */

/* Static function prototypes */
static void m_coms_switch_protocol(void);
static void m_coms_ble_evt_handler(void * p_event_data, uint16_t event_size);
static void m_coms_gzll_evt_handler(void * p_event_data, uint16_t event_size);
static void m_coms_bonding_handler(void * p_event_data, uint16_t event_size);


static void m_coms_bonding_handler(void * p_event_data, uint16_t event_size)
{
    printf("[m_coms_bonding_handler\r\n");
    m_coms_event_callback(0,0);
    
    return;
}

static void m_coms_ble_evt_handler(void * p_event_data, uint16_t event_size)
{
    printf("[m_coms_ble_evt_handler\r\n");
    m_coms_bonding_handler(0, 0);
    
    return;
}

uint32_t m_coms_init(const m_coms_init_t* params)
{
    
    m_coms_protocol_scheme    = params->protocol;
    m_coms_event_callback     = params->event_callback;
    m_coms_timeouts           = 0;  

    printf("[m_coms_init\r\n");
    m_coms_ble_init(m_coms_ble_evt_handler);
    
    return 0;
}

uint32_t m_coms_enable(void)
{
    printf("[m_coms_enable\r\n");
    m_coms_ble_enable(true);
    
    return 0;
}

uint32_t m_coms_trigger(void)
{
    printf("[m_coms_trigger\r\n");
    m_coms_ble_evt_handler(0,0);

    return 0;
}

