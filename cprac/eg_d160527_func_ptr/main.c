#include <stdint.h>
#include <string.h>
#include <stdio.h>

#include "m_coms.h"
#include "m_coms_ble.h"
#include "m_mouse.h"

#define SCHED_QUEUE_SIZE           15
#define SCHED_MAX_EVENT_DATA_SIZE    MAX(sizeof(ble_evt_t), MAX(APP_TIMER_SCHED_EVT_SIZE, sizeof(m_coms_evt_t)))      /**< Maximum size of scheduler events. */
 
#define APP_TIMER_MAX_TIMERS    13 	// One for each module + one for ble_conn_params 
#define APP_TIMER_OP_QUEUE_SIZE 14 	// Maximum number of timeout handlers pending execution

#define PACKET_BUFFER_SIZE SCHED_QUEUE_SIZE + 1 // Include empty element

typedef struct {
    uint8_t rep[4];
    uint8_t rep_len;
    uint8_t interface_idx;
    uint8_t rep_idx;
}hid_send_data_t;

static enum
{
    state_disconnected,
    state_connected
} s_connection_state = state_disconnected;

static struct
{
    m_mouse_data_t buffer[PACKET_BUFFER_SIZE];
    uint32_t     start_idx;
    uint32_t     end_idx;
} s_packet_buffer;

static bool            s_buffer_timer_running = false;

static bool	s_cold_start = false;
static protocol_mode_t s_protocol_mode;
static uint8_t s_oob_key[16];

// Static function declarations
static void m_batt_meas_handler(void * p_event_data, uint16_t event_size);
static void m_coms_handler(void * p_event_data, uint16_t event_size);
static void m_mouse_handler(void * p_event_data, uint16_t event_size);

#define APP_ERROR_HANDLER(ERR_CODE)                         \
    do                                                      \
    {                                                       \
        app_error_handler((ERR_CODE), 0, 0);  \
    } while (0)

void app_error_handler(uint32_t error_code, uint32_t line_num, const uint8_t * p_file_name){
    for (;;)
    {
        // Loop forever. On assert, the system can only recover on reset.
    }
}
	
#define APP_ERROR_CHECK_BOOL(BOOLEAN_VALUE)                   \
    do                                                        \
    {                                                         \
        const uint32_t LOCAL_BOOLEAN_VALUE = (BOOLEAN_VALUE); \
        if (!LOCAL_BOOLEAN_VALUE)                             \
        {                                                     \
            APP_ERROR_HANDLER(0);                             \
        }                                                     \
    } while (0)  

	

static void modules_enable(void)
{
    m_mouse_init_t            mouse_params;

    mouse_params.event_handler   = m_mouse_handler;
    mouse_params.sensor_pollrate = M_MOUSE_SENSOR_POLLRATE;
    mouse_params.button_pollrate = M_MOUSE_BTN_POLLRATE;
    
    m_mouse_init(&mouse_params);
    m_coms_enable();
    
    return;
}

static void m_coms_handler(void * p_event_data, uint16_t event_size)
{
    printf("[m_coms_handler\r\n");
    
    modules_enable();
    return;     
}

static void modules_init(void)
{
    m_coms_init_t             m_coms_params;
    
    printf("[modules_init\r\n");
    m_coms_params.protocol = protocol_mode_auto;
    m_coms_params.event_callback = m_coms_handler;
    
    m_coms_init(&m_coms_params);
    
}

static void m_mouse_handler(void * p_event_data, uint16_t event_size){

	m_mouse_data_t	 *mouse_data;

	APP_ERROR_CHECK_BOOL(event_size == sizeof(m_mouse_data_t));

	mouse_data = (m_mouse_data_t *)p_event_data;
	printf("[Debug] mouse_data.type = %d\r\n", mouse_data->type);
    return;
}

int main(void)
{   
    modules_init();
    m_coms_trigger();
    
    return 0;   
}


