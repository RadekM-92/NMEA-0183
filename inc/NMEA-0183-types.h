#ifndef _NMEA_0183_TYPES_
#define _NMEA_0183_TYPES_

#define MAX_MESSAGES 6
#define ID_LEN 6


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
    char ID[20];   /** Message ID */
    char UTC_Time[20]; /** Time in format hhmmss.sss */
    char Latitude[20]; /** Latitude in format ddmm.mmmm */
    char N_S[20];   /** N-north, S-south */
    char Longitude[20];    /** Longitude in format dddmm.mmmm */
    char E_W[20];   /** E-east, W-west */
    char PositionFixID[20]; /** 0-Not available, 1-SPS, 2-DGPS, 3-PPS */
    char SatellitesUsed[20];   /** Range 0..12 */
    char HDOP[20]; /** Horizontal Dilution of Precision */
    char MSL_Altitude[20]; /** MSL Altitude; */
    char units1[20]; /** MSL_Altitude units, M-meters */
    char GeoidSeparation[20]; /** Geoid-to-ellipsoid separation */
    char units2[20]; /** GeoidSeparation units, M-meters */
    char AgeOfDiffCorr[20];    /** Null fields when DGPS is not used*/
    char DiffRefStationID[20]; /** DPGS ID, 0000-no DGPS */
    char CheckSum[20]; /** Checksum - XOR operation on all bytes from '$' to '*' */
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




#endif