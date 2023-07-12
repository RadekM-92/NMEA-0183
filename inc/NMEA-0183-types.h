#ifndef _NMEA_0183_TYPES_
#define _NMEA_0183_TYPES_

#define MAX_MESSAGES 6
#define ID_LEN 6


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



typedef int8_t (*callback_t)(char *ptr);
typedef int8_t (*MsgReconizeID_t)(const char *, const char *);

static int8_t ReconizeMessageID(const char *MsgIn, const char *MsgIDs);

static int Message_Extract(const char *MsgIn, MsgReconizeID_t MsgReconizeID, callback_t callback); 



#endif