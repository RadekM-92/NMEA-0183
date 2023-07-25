#include <stdint.h>
#include <string.h>
#include <stdlib.h>
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

Parse_t ParsePointer[MAX_MESSAGES] = 
{
    GGA_Parse,
    GLL_Parse,
    GSA_Parse,
    GSV_Parse,
    RMC_Parse,
    VTG_Parse
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
static int8_t GGA_Parse(const char *MsgExtracted)
{
    int8_t IsGGA = memcmp(MsgExtracted, MsgIDs[GGA_Msg], GGA_ID_LEN) == 0 ? 1 : 0;
    int16_t seek = 0;
    if (IsGGA)
    {
        memcpy(GGA_Msg_Raw_Data.ID, MsgExtracted, GGA_ID_LEN);
        seek += DATA_FIELD_MAX_LEN;
        memcpy(GGA_Msg_Raw_Data.UTC_Time, MsgExtracted + seek, GGA_UTC_TIME_LEN);
        seek += DATA_FIELD_MAX_LEN;
        memcpy(GGA_Msg_Raw_Data.Latitude, MsgExtracted + seek, GGA_LATITUDE_LEN);
        seek += DATA_FIELD_MAX_LEN;
        memcpy(GGA_Msg_Raw_Data.N_S, MsgExtracted + seek, GGA_N_S_LEN);
        seek += DATA_FIELD_MAX_LEN;
        memcpy(GGA_Msg_Raw_Data.Longitude, MsgExtracted + seek, GGA_LONGITUDE_LEN);
        seek += DATA_FIELD_MAX_LEN;
        memcpy(GGA_Msg_Raw_Data.E_W, MsgExtracted + seek, GGA_E_W_LEN);
        seek += DATA_FIELD_MAX_LEN;
        memcpy(GGA_Msg_Raw_Data.PositionFixID, MsgExtracted + seek, GGA_POSITION_FIX_ID_LEN);
        seek += DATA_FIELD_MAX_LEN;
        memcpy(GGA_Msg_Raw_Data.SatellitesUsed, MsgExtracted + seek, GGA_SATTELITES_USED_LEN);
        seek += DATA_FIELD_MAX_LEN;
        memcpy(GGA_Msg_Raw_Data.HDOP, MsgExtracted + seek, GGA_HDOP_LEN);
        seek += DATA_FIELD_MAX_LEN;
        memcpy(GGA_Msg_Raw_Data.MSL_Altitude, MsgExtracted + seek, GGA_MSL_ALTITUDE_LEN);
        seek += DATA_FIELD_MAX_LEN;
        memcpy(GGA_Msg_Raw_Data.units1, MsgExtracted + seek, GGA_UNITS1_LEN);
        seek += DATA_FIELD_MAX_LEN;
        memcpy(GGA_Msg_Raw_Data.GeoidSeparation, MsgExtracted + seek, GGA_GEOID_SEPARATION_LEN);
        seek += DATA_FIELD_MAX_LEN;
        memcpy(GGA_Msg_Raw_Data.units2, MsgExtracted + seek, GGA_UNITS2_LEN);
        seek += DATA_FIELD_MAX_LEN;
        memcpy(GGA_Msg_Raw_Data.AgeOfDiffCorr, MsgExtracted + seek, GGA_AGE_OF_DIFF_CORR_LEN);
        seek += DATA_FIELD_MAX_LEN;
        memcpy(GGA_Msg_Raw_Data.DiffRefStationID, MsgExtracted + seek, GGA_DIFF_REF_STATION_ID_LEN);
        seek += DATA_FIELD_MAX_LEN;
        memcpy(GGA_Msg_Raw_Data.CheckSum, MsgExtracted + seek, GGA_CHECK_SUM_LEN);
       
    }
    else
    {
        return -1;
    }
}
/** GLL message parse */
static int8_t GLL_Parse(const char *MsgExtracted)
{

}
/** GSA message parse */
static int8_t GSA_Parse(const char *MsgExtracted)
{

}
/** GSV message parse */
static int8_t GSV_Parse(const char *MsgExtracted)
{

}
/** RMC message parse */
static int8_t RMC_Parse(const char *MsgExtracted)
{

}
/** VTG message parse */
static int8_t VTG_Parse(const char *MsgExtracted)
{

}
/** Calculate and compare checksum */
static int8_t IsCheckSumOk(const char *MsgIn)
{
    uint8_t IsMessageStartSign=0;
    uint8_t IsMessageStopSign=0;
    uint8_t IsMessageEnd=0;
    uint8_t i, j;
    uint8_t CheckSumCalc=0;
    int8_t CheckSumStatus=0;
    char CheckSumRead[3] = {0};
    int CheckSumReadNum;

    IsMessageStartSign = '$' == *(MsgIn) ? 1 : 0;

    if (IsMessageStartSign)
    {
        for(i=1, j=0; i<MESSAGE_MAX_LEN; i++)
        {
            if ('*' == *(MsgIn +i))
            {
                IsMessageStopSign = 1;
            }

            if (IsMessageStopSign && 2==j)
            {
                IsMessageEnd = 1;
            }

            if (IsMessageStopSign)
            {
                if (IsMessageEnd)
                {
                    CheckSumReadNum = atoi(CheckSumRead);
                    
                    if (CheckSumReadNum == (int)CheckSumCalc)
                    {
                        CheckSumStatus = 1;
                    }
                    else
                    {
                        CheckSumStatus = -1;
                    }

                    break;
                }
                else
                {
                    CheckSumRead[j] = *(MsgIn + i + 1);
                    j++;
                }
            } 
            else
            {
                CheckSumCalc ^= *(MsgIn + i);
            }
        }
    }
    else
    {
        CheckSumStatus = -2;
    }

    return CheckSumStatus;

}

/** Parse Message */
static int8_t Message_Parse(const char *MsgIn, int8_t MsgID)
{
    uint8_t IsCorrectMsgID = MsgID >= 0 && MsgID <= MAX_MESSAGES;

    if (IsCorrectMsgID)
    {
        ParsePointer[MsgID](MsgIn);
    }
    else
    {
        return -1;
    } 
}

/** Message_Read 
 * MsgIn - input message pointer,
 * MsgReconizeID - message ID comparison function callback
 * MsgParse - message parse function callback
*/
static int8_t Message_Read(const char *MsgIn, MsgReconizeID_t MsgReconizeID, MsgParse_t MsgParse) 
{
    uint8_t i, k;
    int8_t j;
    uint8_t IsSeparatorSign;
    uint8_t IsMessageStartSign = '$' == *(MsgIn);
    char Msg_Data[FIELDS_MAX][DATA_FIELD_MAX_LEN] = {0};

    if (IsMessageStartSign)
    {
        for(i=0, j=0, k=0; i<MESSAGE_MAX_LEN; i++, j++)
        {
            IsSeparatorSign = ',' == *(MsgIn + i) || '*' == *(MsgIn + i); 
            
            if (IsSeparatorSign)
            {
                k++;
                j=-1;
                continue;
            }

            Msg_Data[k][j] = *(MsgIn + i);
        }

        MsgParse(Msg_Data[0], MsgReconizeID(MsgIn, MsgIDs[0]));
    }
    else
    {
        return -1;
    }    
}




void test(void)
{
    char *GGA_Msg_Example = "$GPGGA,092842.094,5215.2078,N,02054.3681,E,1,06,1.7,138.5,M,,,,0000*09";


    Message_Read(GGA_Msg_Example, ReconizeMessageID, Message_Parse);


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