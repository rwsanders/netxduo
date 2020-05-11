/**************************************************************************/
/*                                                                        */
/*       Copyright (c) Microsoft Corporation. All rights reserved.        */
/*                                                                        */
/*       This software is licensed under the Microsoft Software License   */
/*       Terms for Microsoft Azure RTOS. Full text of the license can be  */
/*       found in the LICENSE file at https://aka.ms/AzureRTOS_EULA       */
/*       and in the root directory of this software.                      */
/*                                                                        */
/**************************************************************************/


/**************************************************************************/
/**************************************************************************/
/**                                                                       */
/** NetX Component                                                        */
/**                                                                       */
/**   Packet Pool Management (Packet)                                     */
/**                                                                       */
/**************************************************************************/
/**************************************************************************/

#define NX_SOURCE_CODE


/* Include necessary system files.  */

#include "nx_api.h"
#include "nx_packet.h"

/* Bring in externs for caller checking code.  */

NX_CALLER_CHECKING_EXTERNS


/**************************************************************************/
/*                                                                        */
/*  FUNCTION                                               RELEASE        */
/*                                                                        */
/*    _nxe_packet_copy                                    PORTABLE C      */
/*                                                           6.0          */
/*  AUTHOR                                                                */
/*                                                                        */
/*    Yuxin Zhou, Microsoft Corporation                                   */
/*                                                                        */
/*  DESCRIPTION                                                           */
/*                                                                        */
/*    This function checks for errors in the packet copy                  */
/*    function call.                                                      */
/*                                                                        */
/*  INPUT                                                                 */
/*                                                                        */
/*    packet_ptr                            Pointer to source packet      */
/*    new_packet_ptr                        Pointer to return packet      */
/*    pool_ptr                              Pointer to packet pool to use */
/*                                            for new packet(s)           */
/*    wait_option                           Suspension option             */
/*                                                                        */
/*  OUTPUT                                                                */
/*                                                                        */
/*    status                                Completion status             */
/*                                                                        */
/*  CALLS                                                                 */
/*                                                                        */
/*    _nx_packet_copy                       Actual packet copy function   */
/*                                                                        */
/*  CALLED BY                                                             */
/*                                                                        */
/*    Application Code                                                    */
/*                                                                        */
/*  RELEASE HISTORY                                                       */
/*                                                                        */
/*    DATE              NAME                      DESCRIPTION             */
/*                                                                        */
/*  05-19-2020     Yuxin Zhou               Initial Version 6.0           */
/*                                                                        */
/**************************************************************************/
UINT  _nxe_packet_copy(NX_PACKET *packet_ptr, NX_PACKET **new_packet_ptr,
                       NX_PACKET_POOL *pool_ptr, ULONG wait_option)
{

UINT status;


    /* Check for invalid input pointers.  */
    if ((pool_ptr == NX_NULL) || (pool_ptr -> nx_packet_pool_id != NX_PACKET_POOL_ID) ||
        (packet_ptr == NX_NULL) || (new_packet_ptr == NX_NULL))
    {
        return(NX_PTR_ERROR);
    }

    /* Check for an invalid packet prepend pointer.  */
    /*lint -e{946} suppress pointer subtraction, since it is necessary. */
    if (packet_ptr -> nx_packet_prepend_ptr < packet_ptr -> nx_packet_data_start)
    {
        return(NX_UNDERFLOW);
    }

    /* Check for an invalid packet append pointer.  */
    /*lint -e{946} suppress pointer subtraction, since it is necessary. */
    if (packet_ptr -> nx_packet_append_ptr > packet_ptr -> nx_packet_data_end)
    {
        return(NX_OVERFLOW);
    }

    /* Check for appropriate caller.  */
    NX_THREAD_WAIT_CALLER_CHECKING

    /* Call actual packet copy function.  */
    status =  _nx_packet_copy(packet_ptr, new_packet_ptr, pool_ptr, wait_option);

    /* Return completion status.  */
    return(status);
}

