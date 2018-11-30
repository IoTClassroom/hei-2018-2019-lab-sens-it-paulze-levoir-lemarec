/*!******************************************************************
 * \file main.c
 * \brief Sens'it SDK template
 * \author Sens'it Team
 * \copyright Copyright (c) 2018 Sigfox, All Rights Reserved.
 *
 * This file is an empty main template.
 * You can use it as a basis to develop your own firmware.
 *******************************************************************/
/******* INCLUDES **************************************************/
#include "sensit_types.h"
#include "sensit_api.h"
#include "error.h"
#include "button.h"
#include "battery.h"
#include "radio_api.h"
#include "hts221.h"
#include "ltr329.h"
#include "fxos8700.h"
#include "discovery.h"



/******* GLOBAL VARIABLES ******************************************/
u8 firmware_version[] = "VIBR_v2.0.0";

#define VIBRATION_THRESHOLD                0x10 /* With 2g range, 3,9 mg threshold */
#define VIBRATION_COUNT                    2



/*******************************************************************/

int main()
{
    error_t err;
    button_e btn;
    u16 battery_level;
    bool send = FALSE;

    /* Discovery payload variable */
    discovery_data_s data = {0};
    discovery_payload_s payload;

    /* Start of initialization */

    /* Initialize accelerometer */
    err = FXOS8700_init();
    ERROR_parser(err);

    /* Clear pending interrupt */
    pending_interrupt = 0;

    /* End of initialization */


    FXOS8700_set_transient_mode (FXOS8700_RANGE_2G, VIBRATION_THRESHOLD, VIBRATION_COUNT);

    while (TRUE)
    {
        /* Execution loop */

/* Check of battery level */
        BATTERY_handler(&(data.battery));
        
     if(FXOS8700_clear_transient_interrupt(&(data.vibration)));
        {
            /* Build the payload */
            DISCOVERY_build_payload(&payload, MODE_VIBRATION, &data);

            /* Send the message */
            err = RADIO_API_send_message(RGB_YELLOW, (u8*)&payload, DISCOVERY_PAYLOAD_SIZE, FALSE, NULL);
            /* Parse the error code */
            ERROR_parser(err);
    }

      
}

}

/*******************************************************************/
