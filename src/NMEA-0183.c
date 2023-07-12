#include <stdint.h>
#include <string.h>

#include <stdio.h>

#include "NMEA-0183.h"
#include "NMEA-0183-types.h"




char MsgIDs[MAX_MESSAGES][ID_LEN+1] =
{
    "$GPGGA",
    "$GPGLL",
    "$GPGSA",
    "$GPGSV",
    "$GPRMC",
    "$GPVTG"
};




GGA_Message_Data_Raw_t GGA_Msg_Raw_Data = {0};


/** Reconize Message by compare MsgIn and MsgIDs */
static int8_t ReconizeMessageID(const char *MsgIn, const char *MsgIDs)
{
    uint8_t i;
    uint8_t MsgReconized;

    for(i=0; i<MAX_MESSAGES; i++)
    {
        MsgReconized = memcmp(MsgIn, MsgIDs + i*ID_LEN, 6) == 0 ? 1 : 0;
        if (MsgReconized)
        {
            return i;
        }
        else
        {
            return Unknow_Msg;
        }
    }
}

/** GGA message parse */
static int8_t GGA_Parse(char *Msg)
{
    int8_t IsGGA = memcmp(Msg, "$GPGGA", 6) == 0 ? 1 : 0;

    if (IsGGA)
    {
        memcpy(GGA_Msg_Raw_Data.ID, Msg, 20);
        memcpy(GGA_Msg_Raw_Data.UTC_Time, Msg + 20, 20);
    }
    else
    {
        return -1;
    }
}

/** Parse Message */
static int8_t Message_Parse(const char *MsgIn, int8_t MsgID)
{
    uint8_t IsCorrectMsgID = MsgID >= 0 && MsgID <= MAX_MESSAGES;

    if (IsCorrectMsgID)
    {

    }
    else
    {
        return -1;
    } 
}

/** Extract Message to data structs*/
static int8_t Message_Extract(const char *MsgIn, MsgReconizeID_t MsgReconizeID, MsgParse_t MsgParse) 
{
    uint8_t i, k;
    int8_t j;

    char Msg_Data[20][20] = {0};

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

        MsgParse(MsgIn, MsgReconizeID(MsgIn, MsgIDs[0]));
    }
    else
    {
        return -1;
    }    
}




void test(void)
{
    char *GGA_Msg_Example = "$GPGGA,092842.094,5215.2078,N,02054.3681,E,1,06,1.7,138.5,M,,,,0000*09";


    Message_Extract(GGA_Msg_Example, ReconizeMessageID, Message_Parse);
    printf("%s\n", GGA_Msg_Example);
    printf("\n\n");
    printf("%s\n", GGA_Msg_Raw_Data.ID);
    printf("%s\n", GGA_Msg_Raw_Data.UTC_Time       );
    printf("%s\n", GGA_Msg_Raw_Data.Latitude       );
    printf("%s\n", GGA_Msg_Raw_Data.N_S            );
    printf("%s\n", GGA_Msg_Raw_Data.Longitude      );
    printf("%s\n", GGA_Msg_Raw_Data.E_W            );
    printf("%s\n", GGA_Msg_Raw_Data.PositionFixID  );
    printf("%s\n", GGA_Msg_Raw_Data.SatellitesUsed );
    printf("%s\n", GGA_Msg_Raw_Data.HDOP           );
    printf("%s\n", GGA_Msg_Raw_Data.MSL_Altitude   );
    printf("%s\n", GGA_Msg_Raw_Data.units1         );
    printf("%s\n", GGA_Msg_Raw_Data.GeoidSeparation);
    printf("%s\n", GGA_Msg_Raw_Data.units2         );
    printf("%s\n", GGA_Msg_Raw_Data.AgeOfDiffCorr  );
    printf("%s\n", GGA_Msg_Raw_Data.DiffRefStationID);
    printf("%s\n", GGA_Msg_Raw_Data.CheckSum       );

}