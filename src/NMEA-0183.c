#include <stdint.h>
#include <string.h>

#include "NMEA-0183.h"
#include "NMEA-0183-types.h"





/** Extract GGA Message to GGA_Message_Data_Raw */
static int GGA_Message_Extract(const char *MsgIn);



/** Extract Message */
static int Message_Extract(const char *MsgIn)
{
    char Msg_Data[20][20] = {0};
    uint8_t i, k;
    int8_t j;

    if ('$' == *(MsgIn))
    {
        for(i=0, j=0, k=0; i<82; i++, j++)
        {
            if (',' == *(MsgIn + i))
            {
                k++;
                j=-1;
                continue;
            }
            Msg_Data[k][j] = *(MsgIn + i);
        }
    }
    else
    {
        return -1;
    }    
}