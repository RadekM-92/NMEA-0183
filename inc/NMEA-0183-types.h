#ifndef _NMEA_0183_TYPES_
#define _NMEA_0183_TYPES_

#define MAX_MESSAGES 6
#define ID_LEN 6
#define MESSAGE_MAX_LEN 82
#define DATA_FIELD_MAX_LEN 20
#define FIELDS_MAX 20


#define GGA_ID_LEN 6
#define GGA_UTC_TIME_LEN 10
#define GGA_LATITUDE_LEN 9
#define GGA_N_S_LEN 1
#define GGA_LONGITUDE_LEN 10
#define GGA_E_W_LEN 1
#define GGA_POSITION_FIX_ID_LEN 1
#define GGA_SATTELITES_USED_LEN 2
#define GGA_HDOP_LEN 3
#define GGA_MSL_ALTITUDE_LEN 5
#define GGA_UNITS1_LEN 1
#define GGA_GEOID_SEPARATION_LEN 1
#define GGA_UNITS2_LEN 1
#define GGA_AGE_OF_DIFF_CORR_LEN 1
#define GGA_DIFF_REF_STATION_ID_LEN 4
#define GGA_CHECK_SUM_LEN 2

/** GGA Message raw - Global Positioning System fixed data */
typedef struct
{
    char ID[GGA_ID_LEN + 1];                            /** Message ID */
    char UTC_Time[GGA_UTC_TIME_LEN + 1];                /** Time in format hhmmss.sss */
    char Latitude[GGA_LATITUDE_LEN + 1];                /** Latitude in format ddmm.mmmm */
    char N_S[GGA_N_S_LEN + 1];                          /** N-north, S-south */
    char Longitude[GGA_LONGITUDE_LEN + 1];              /** Longitude in format dddmm.mmmm */
    char E_W[GGA_E_W_LEN + 1];                          /** E-east, W-west */
    char PositionFixID[GGA_POSITION_FIX_ID_LEN + 1];    /** 0-Not available, 1-SPS, 2-DGPS, 3-PPS */
    char SatellitesUsed[GGA_SATTELITES_USED_LEN + 1];   /** Range 0..12 */
    char HDOP[GGA_HDOP_LEN + 1];                        /** Horizontal Dilution of Precision */
    char MSL_Altitude[GGA_MSL_ALTITUDE_LEN + 1];        /** MSL Altitude; */
    char units1[GGA_UNITS1_LEN + 1];                    /** MSL_Altitude units, M-meters */
    char GeoidSeparation[GGA_GEOID_SEPARATION_LEN + 1]; /** Geoid-to-ellipsoid separation */
    char units2[GGA_UNITS2_LEN + 1];                    /** GeoidSeparation units, M-meters */
    char AgeOfDiffCorr[GGA_AGE_OF_DIFF_CORR_LEN + 1];   /** Null fields when DGPS is not used*/
    char DiffRefStationID[GGA_DIFF_REF_STATION_ID_LEN + 1]; /** DPGS ID, 0000-no DGPS */
    char CheckSum[GGA_CHECK_SUM_LEN + 1];               /** Checksum - XOR operation on all bytes from '$' to '*' */
} GGA_Message_Data_Raw_t;

/** Message IDs */
typedef enum
{
    GGA_Msg = 0,
    GLL_Msg = 1,
    GSA_Msg = 2,
    GSV_Msg = 3,
    RMC_Msg = 4,
    VTG_Msg = 5,

    Unknow_Msg = -1

} MessageIDs_t;

typedef int8_t (*MsgParse_t)(const char *, int8_t);
typedef int8_t (*MsgReconizeID_t)(const char *, const char *);
typedef int8_t (*Parse_t)(const char *);

static int8_t ReconizeMessageID(const char *MsgIn, const char *MsgIDs);
static int8_t Message_Read(const char *MsgIn, MsgReconizeID_t MsgReconizeID, MsgParse_t MsgParse); 
static int8_t Message_Parse(const char *MsgIn, int8_t MsgID);
static int8_t GGA_Parse(const char *MsgExtracted);
static int8_t GLL_Parse(const char *MsgExtracted);
static int8_t GSA_Parse(const char *MsgExtracted);
static int8_t GSV_Parse(const char *MsgExtracted);
static int8_t RMC_Parse(const char *MsgExtracted);
static int8_t VTG_Parse(const char *MsgExtracted);
static uint8_t IsCheckSumOk(const char *MsgIn);



#endif