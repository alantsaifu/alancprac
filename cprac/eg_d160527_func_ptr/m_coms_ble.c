#include "m_coms_ble.h"
#include "app_scheduler.h"
#include <stdio.h>

static app_sched_event_handler_t     s_event_callback = 0; /** Event callback used to notify m_coms */

static uint8_t                       s_num_inp_reports;
static uint8_t                       s_hid_notif_enabled_count = 0;
static int8_t                        s_tx_buf_cnt;         /** Number of packets in SoftDevice TX buffer. Used to limit amount of buffered packets */
static bool                          s_encrypted;          /** Link encryption status */
static bool                          s_sec_params_requested; /** Auth key requested */
static bool                          s_boot_mode_active;   /** In Boot or Report mode? */

static uint16_t                      s_conn_handle;        /** Handle value of current connection */

#define WAITING_REASON_INIT                     (1UL << 0)
#define WAITING_REASON_INIT_BONDS_DELETE        (1UL << 1)
#define WAITING_REASON_DISABLE                  (1UL << 2)
#define WAITING_REASON_APP_CONTEXT_WRITE        (1UL << 3)
#define WAITING_REASON_SERVICE_CONTEXT_WRITE    (1UL << 4)
#define WAITING_REASON_APP_CONTEXT_NOTIFY       (1UL << 5)
#define WAITING_REASON_ADVERTISING_START        (1UL << 6)

static bool s_waiting_for_flash      = false;
static bool s_waiting_for_disconnect = false;
static bool s_wait_to_notify_ble_addr = false;
static uint32_t s_waiting_reason     = 0;

bool    s_ble_dongle_auto = false;

uint32_t m_coms_ble_init(const app_sched_event_handler_t p_event_callback)
{
    s_event_callback     = p_event_callback;
    printf("[m_coms_ble_init\r\n");
    
    return 0;
}

static void on_ble_evt(void)
{
    printf("[on_ble_evt\r\n");
    //s_event_callback(0, 0);
    
    return;
}

static void ble_evt_dispatch(void *p_evt_data, uint16_t evt_size)
{   
    printf("[ble_evt_dispatch\r\n");
    on_ble_evt();
    
    return;
}

static void ble_evt_manager(void)
{
    printf("[ble_evt_manager\r\n");
    ble_evt_dispatch(0,0); 
    
    return;
}

static uint32_t ble_stack_init(void)
{

    printf("[ble_stack_init\r\n");
    ble_evt_manager();
    
    return 0;
}

uint32_t m_coms_ble_enable(bool p_advertise)
{
    
    printf("[m_coms_ble_enable\r\n");
    ble_stack_init();
    
    return 0;
}
