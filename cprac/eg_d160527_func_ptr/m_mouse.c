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


static protocol_mode_t 	s_switch_protocol = protocol_mode_gzll;

extern bool               ext_coms_bonding;

#ifdef HOSTPRENT
extern bool               gzp_addr_req_clr;
#endif

static void button_handler(void){
	m_mouse_data_t data;
	data.type = mouse_packet_type_buttons;

	s_event_handler(&data, sizeof(m_mouse_data_t));
}

uint32_t m_mouse_init(m_mouse_init_t *init)
{
    s_sensor_pollrate = init->sensor_pollrate;
    s_button_pollrate = init->button_pollrate;
    s_event_handler   = init->event_handler;

	button_handler();
       
    return 0;
}

