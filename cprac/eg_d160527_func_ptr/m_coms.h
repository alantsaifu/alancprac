/** @file 
 *
 * @defgroup modules_coms
 * @{
 * @ingroup nrfready_modules
 * @brief Communications module.
 *
 * @details This module deals with protocol handling and data transmission
 *          Different sub-modules handle protocol-specific behaviour.
 *          The figure below depicts how this module operates:
 * @image html flow_m_coms.png Communications module flow
 */
#ifndef __M_COMS_H__
#define __M_COMS_H__

#include <stdint.h>
#include <stdbool.h>


#include "m_coms_ble.h"

/**@brief The available protocol modes */
typedef enum
{
    protocol_mode_void,
    protocol_mode_gzll,
    protocol_mode_ble,
    protocol_mode_auto
} protocol_mode_t;

/**@brief Events generated by this module */
typedef enum
{
    com_event_none = 0,
    com_event_init_finished,
    com_event_connected,
    com_event_disconnected,
	//&*&*&*G1082715, ADD for Tx failed handle	
		com_event_txfailed,
		com_event_bonding_start,	
		com_event_dm_appl_context_stored,
	//&*&*&*G2082715, ADD for Tx failed handle	
    com_event_data_received,
    com_event_data_read,       /** Read request which requires a response */
    com_event_timing_update,
    com_event_advertising_timeout,
    com_event_advertising_bondable, /** Bondable advertising is running */
    com_event_address_changed, /** Depending on BLE bond parameters a new address might be generated. */
    com_event_passkey_req,    /** Passkey needed from the application/user. Used in BLE mode */
    com_event_oobkey_req,
    com_event_key_sent,
    com_event_disabled
} com_events_t;

/**@Brief Connection update event details */
typedef struct
{
    uint16_t min_conn_interval;   /** Min Connection interval [1.25 ms units] */
    uint16_t max_conn_interval;   /** Max Connection interval [1.25 ms units] */
    uint16_t slave_latency;       /** Slave latency */
    uint16_t supervision_timeout; /** Link timeout [10 ms units] */
} m_coms_evt_timing_update_t;

/**@Brief Read request event details */
typedef struct
{
    uint8_t interface_idx;
    uint8_t report_idx;
} m_coms_evt_data_read_t;

/**@brief Data received event details */
typedef struct
{
    uint8_t   interface_idx; /** Which interface data was received on */
    uint8_t   report_type;   /** Type of report. Input, output or feature */
    uint8_t   report_idx;    /** Which report index data was received on */ 
    uint8_t   len;           /** Length of received data */
    uint8_t * data;          /** Received data */
} m_coms_evt_data_recv_t;

typedef struct
{
    com_events_t type;
    union
    {
        m_coms_evt_timing_update_t timing_update;
        m_coms_evt_data_read_t     data_read;
        m_coms_evt_data_recv_t     data_received;
    } data;
} m_coms_evt_t;

/**@brief Gazell parameters. See @ref M_COMS_GZLL_PARAMS_FILL for to initialize default values. */
typedef struct
{
    bool     encrypt;         /** Make encrypted pipe available */
    uint32_t tx_attempts;     /** Number of retransmission attempts per packet */
    uint32_t timeslot_period; /** Gazell timing parameter. Needs to match Host side */
    uint32_t sync_lifetime;   /** Number of timeslot periods to stay in sync */
} m_coms_gzll_params_t;

/**@brief m_coms initialization parameters */
typedef struct
{
    protocol_mode_t           protocol; /** Which protocol to use. Use protocol_mode_auto for "don't care". */
    app_sched_event_handler_t event_callback; /** Event callback which is scheduled upon data received events. Also disconnects and connects and inactivity_timeout. */
} m_coms_init_t;

/**@brief Initializes communication parameters. Does not start communicating (@ref m_coms_enable).
 * 
 * @details 
 *
 * @param[in] params
 * @return
 * @retval NRF_SUCCESS
 * @retval NRF_ERROR_INVALID_PARAM
 */
uint32_t m_coms_init(const m_coms_init_t * params);

/**@brief Enable communication
 * 
 * @details Depending on protocol: start advertising and establish a connection
 *
 * @return
 * @retval NRF_SUCCESS
 * @retval NRF_ERROR_INVALID_STATE
 */
uint32_t m_coms_enable(void);

/**@brief Disable communication
 * 
 * @details Depending on protocol: drop connection/stop advertising.
 *
 * @return
 * @retval NRF_SUCCESS
 * @retval NRF_ERROR_INVALID_STATE
 */
uint32_t m_coms_disable(void);

/**@brief Start pairing/bonding procedure.
 *
 * @details When using BLE, advertising for a new bond will be started according to parameters (@ref m_coms_init).
 *          When using Gazell, the 
 *
 * @note When using Gazell, close proximity to the Host device is required to complete the pairing procedure.
 *
 * @return
 * @retval NRF_SUCCESS
 * @retval NRF_ERROR_INVALID_STATE
 * @retval NRF_ERROR_INTERNAL
 */
uint32_t m_coms_bonding_start(void);

/**@brief Set passkey. Typically used only in BLE.
 * 
 * @details When the application receives a @ref com_even_passkey_needed event, this function should be called.
 *          For a keyboard application the main application should gather keypresses from the keyboard Matrix,
 *          format the data correctly and call this function.
 *
 * @note The key should be in ASCII format, <b>not</b> USB HID format.
 * 
 * @param[in] p_key     Array of ASCII formatted passkey characters.
 * @param[in] p_key_len Length of key array. For BLE length should be 6.
 * @return
 * @retval NRF_SUCCESS
 * @retval NRF_ERROR_INVALID_STATE
 * @retval NRF_ERROR_INVALID_PARAM
 */
uint32_t m_coms_passkey_set(uint8_t * p_key, uint8_t p_key_len);

/**@brief Add new BLE HID (HID over GATT) descriptor
 * 
 * @note USB Dongle interface is not configured by this.
 * @note Max report descriptor length is 512 bytes.
 *
 * @param[in]  p_descriptor         Pointer to HID report descriptor.
 * @param[in]  p_descriptor_len     Length of descriptor.
 * @param[in]  p_boot_type_bitmask  Boot type avilable (keyboard or mouse boot device). See @ref p_boot_type_bitmask for valid types.
 * @param[out] p_interface_id       Reference to the generated HID interface. Used in all subsequent HID operations.
 * @return
 * @retval NRF_SUCCESS
 * @retval NRF_ERROR_INVALID_PARAM
 */
uint32_t m_coms_hid_report_descriptor_add(const uint8_t * p_descriptor, 
                                          uint16_t        p_descriptor_len, 
                                          uint8_t         p_boot_type_bitmask, 
                                          uint8_t *       p_interface_idx);




#endif /* __M_COMS_H__ */

/** @} */
