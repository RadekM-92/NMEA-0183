#ifndef _NMEA_0183_TYPES_
#define _NMEA_0183_TYPES_


/** GGA Message raw - Global Positioning System fixed data */
typedef struct
{
    char *ID;   /** Message ID */
    char *UTC_Time; /** Time in format hhmmss.sss */
    char *Latitude; /** Latitude in format ddmm.mmmm */
    char *N_S;   /** N-north, S-south */
    char *Longitude;    /** Longitude in format dddmm.mmmm */
    char *E_W;   /** E-east, W-west */
    char *PositionFixID; /** 0-Not available, 1-SPS, 2-DGPS, 3-PPS */
    char *SatellitesUsed;   /** Range 0..12 */
    char *HDOP; /** Horizontal Dilution of Precision */
    char *MSL_Altitude; /** MSL Altitude; */
    char *units1; /** MSL_Altitude units, M-meters */
    char *GeoidSeparation; /** Geoid-to-ellipsoid separation */
    char *units2; /** GeoidSeparation units, M-meters */
    char *AgeOfDiffCorr;    /** Null fields when DGPS is not used*/
    char *DiffRefStationID; /** DPGS ID, 0000-no DGPS */
    char *CheckSum; /** Checksum - XOR operation on all bytes from '$' to '*' */
} GGA_Message_Data_Raw_t;


#endif