#if (defined(UNDER_CE) || defined(_WIN32_WCE))
    /* WinCE is only a subset of Win32 */
    #ifndef WIN32
        #define WIN32
    #endif
    #ifndef WINCE
        #define WINCE
    #endif
#endif

#if (defined (_WIN32))
    #ifndef WIN32
        #define WIN32
    #endif
#endif
#include <time.h>

#ifdef WIN32

  /* Win32 code */
  /* ---------- */
    //#include <windows.h>
    #include <winsock2.h>
    #include <winsock.h>
    //#include <tchar.h>
#if ! defined (__cplusplus)
    //#include "inttypes.h"
    #include "type.h"
#endif
    //typedef signed short SWORD;
    //typedef signed long  SDWORD;
    #define Delays_Ms(ms) Sleep ((ms))
    #define Delays_S(sec) Sleep ((sec) * 1000)
    #ifndef ODALID_LIB
        #if (defined (__GNUC__))
            #define ODALID_LIB
        #else
            #define ODALID_LIB __declspec(dllimport)
        #endif
    #endif

    #if (defined(WINCE))
        /* Under Windows CE we use the stdcall calling convention */
        #define ODALID_API __stdcall
    #else
        #if (defined(FORCE_STDCALL))
        /* stdcall is forced */
            #define ODALID_API __stdcall
        #else
            /* cdecl is the default calling convention */
            #define ODALID_API __cdecl
        #endif
    #endif

#else

  /* Not Win32 */
  /* --------- */

  /* Linkage directive : not specified, use compiler default */
    #define ODALID_API

  /* Calling convention : not specified, use compiler default */
    #define ODALID_LIB
    #include <unistd.h>
    #include <string.h>
    #include <stdint.h>
    #include <stddef.h>
    typedef uint8_t BOOL;
    typedef int16_t SOCKET;
    #define Delays_Ms(ms) usleep ((ms) * 1000)
    #define Delays_S(sec) sleep ((sec))
    #ifndef TRUE
        #define TRUE 1
    #endif
    #ifndef FALSE
        #define FALSE 0
    #endif

    #ifdef HAVE_TCHAR_H
        #include <tchar.h>
    #else
        #ifdef UNICODE
            typedef wchar_t TCHAR;
        #else
            typedef char TCHAR;
        #endif
    #endif
    typedef int16_t HANDLE;
#endif

#if defined (__cplusplus)
extern "C" {
#endif

typedef struct {
	uint8_t Type;
	uint8_t device;
	char IPReader[16];
	SOCKET hSocket;
    HANDLE g_hCOM;
	char version[40];
    uint8_t serial[11];
    char stack[30];
}ReaderName;

#define ReaderTCP           1
#define ReaderCDC           2
#define ReaderPCSC          3

ODALID_LIB int16_t OpenCOM(ReaderName *Name);
ODALID_LIB int16_t CloseCOM(ReaderName *Name);
ODALID_LIB int16_t GestionDeconnection(ReaderName *Name, int16_t statusconnection, uint8_t nbreconnection);

#define LED_ON              0x17
#define LED_OFF             0x00
#define LED_GREEN_OFF       0x00
#define LED_GREEN_ON        LED3_ON         //0x04
#define LED_YELLOW_OFF      0x00
#define LED_YELLOW_ON       LED2_ON         //0x02
#define LED_RED_OFF         0x00
#define LED_RED_ON          LED1_ON         //0x01
#define BUZZER_OFF          0x00
#define BUZZER_ON           0x08
#define GACHE1_OFF          0x00
#define GACHE1_ON           LED1_ON         //0x10
#define GACHE2_OFF          0x00
#define GACHE2_ON           LED2_ON         //0x20
#define GACHE3_OFF          0x00
#define GACHE3_ON           LED3_ON         //0x40
#define GACHE4_OFF          0x00
#define GACHE4_ON           LED4_ON         //0x80
#define LED1_ON             0x01
#define LED2_ON             0x02
#define LED3_ON             0x04
#define LED4_ON             0x10

#define TypeA               0x01
#define TypeB               0x02
#define TypeCTS             0x08
#define TypeST              0x10
#define TypeInno            0x20
#define Type15693           0x40

#define CRCA                0x01
#define CRCB                0x02

#define DIV_WITHOUT         0x00
#define DIV_MIFARE          0x01
#define DIV_AES128          0x02
#define DIV_AES192          0x03
#define DIV_AES256          0x04
#define DIV_2TDEA           0x05
#define DIV_3TDEA           0x06
#define DIV_AES_OLDMIF      0x09
/*#define DIV_TDES_AV1        0x0A
#define DIV_AES_AV1         0x0B
#define DIV_AES_AV2         0x0C*/

#define USESAMAV3           0x10
#define USECMAC             0x20
#define USEENCRYPT          0x40
#define USECMAC             0x20
#define USEFULL             0x40

ODALID_LIB char* GetErrorMessage(int16_t status);
ODALID_LIB int16_t GetLibrary(char *recv, uint16_t *len_recv);

ODALID_LIB int16_t Version(ReaderName *Name);
ODALID_LIB int16_t Get_Property(ReaderName *Name, uint8_t AddReg, uint8_t *Reg);
ODALID_LIB int16_t Set_Property(ReaderName *Name, uint8_t AddReg, uint8_t Reg);
ODALID_LIB int16_t RF_Power_Control(ReaderName *Name, BOOL RFOnOff, uint8_t Delay);
ODALID_LIB int16_t RF_Find(ReaderName *Name, uint8_t Type, uint8_t *TypeFind, uint8_t *uid, uint16_t *uid_len, uint8_t *info, uint16_t *info_len);
ODALID_LIB int16_t RF_Config_Card_Mode(ReaderName *Name, uint8_t Type);
ODALID_LIB int16_t RF_Transmit(ReaderName *Name, uint8_t *send, uint16_t len_send, uint8_t *recv, uint16_t *len_recv, uint16_t timeout);
ODALID_LIB int16_t RF_TransmitCRC(ReaderName *Name, uint8_t *send, uint16_t len_send, uint8_t *recv, uint16_t *len_recv, uint16_t timeout, uint8_t CRC);
ODALID_LIB int16_t RF_Poll(ReaderName *Name, uint8_t *send, uint16_t len_send, uint8_t *recv, uint16_t *len_recv, uint16_t timeout);
ODALID_LIB int16_t Boot(ReaderName *Name);
ODALID_LIB int16_t LEDBuzzer(ReaderName *Name, uint8_t LEDBuzzer);
ODALID_LIB int16_t LCD(ReaderName *Name, uint8_t line, char *send);
ODALID_LIB int16_t ISOA_CRC(uint8_t *Data, uint16_t Length, uint8_t *TransmitFirst, uint8_t *TransmitSecond);
ODALID_LIB int16_t ISOA_CRC(uint8_t *Data, uint16_t Length, uint8_t *TransmitFirst, uint8_t *TransmitSecond);

ODALID_LIB int16_t ISO14443_3_A_PollCard(ReaderName *Name, uint8_t *atq, uint8_t *sak, uint8_t *uid, uint16_t *uid_len);
ODALID_LIB int16_t ISO14443_3_A_PollCardWU(ReaderName *Name, uint8_t *atq, uint8_t *sak, uint8_t *uid, uint16_t *uid_len);
ODALID_LIB int16_t ISO14443_3_A_Halt(ReaderName *Name);

ODALID_LIB int16_t ISO14443_3_B_PollCard(ReaderName *Name, uint8_t afi, uint8_t param, uint8_t *CID, uint8_t *atqb, uint16_t *atqb_len);
ODALID_LIB int16_t ISO14443_3_B_Halt(ReaderName *Name, uint8_t *PUPI);

ODALID_LIB int16_t ISO14443_4_A_RATS(ReaderName *Name, uint8_t CID, uint8_t *ats, uint16_t *Len_ats);
ODALID_LIB int16_t ISO14443_4_A_PPS(ReaderName *Name, uint8_t CID, uint8_t dsi, uint8_t dri);

ODALID_LIB int16_t ISO14443_4_Deselect(ReaderName *Name, uint8_t Type);


ODALID_LIB int16_t ISO14443_4_Transparent(ReaderName *Name, uint8_t Type, uint8_t *CmdADPU, uint16_t lenCmdADPU, uint8_t *RespADPU, uint16_t *lenRespADPU);

ODALID_LIB int16_t CTS_PollCard(ReaderName *Name, uint8_t *code, uint8_t *serial);

ODALID_LIB int16_t SR_PollCard(ReaderName *Name, uint8_t *cid, uint8_t *uid);
ODALID_LIB int16_t SR_Completion(ReaderName *Name);

ODALID_LIB int16_t INNOVATRON_PollCard(ReaderName *Name, uint8_t *div, uint8_t *atr, uint8_t *atr_len);
ODALID_LIB int16_t INNOVATRON_DISC(ReaderName *Name);

ODALID_LIB int16_t ISO15693_PollCard(ReaderName *Name, uint8_t *DSFID, uint8_t *uid);

//Valid access conditions for bc0, bc1 and bc2
#define ACC_BLOCK_TRANSPORT     0x00
#define ACC_BLOCK_READWRITE     0x04
#define ACC_BLOCK_VALUE         0x06
//Valid access conditions for bc3
#define ACC_AUTH_TRANSPORT      0x01
#define ACC_AUTH_NORMAL         0x03

#define Auth_KeyA				TRUE
#define Auth_KeyB				FALSE

ODALID_LIB int16_t Mf_Classic_LoadKey(ReaderName *Name, BOOL Auth_Key, uint8_t *key, uint8_t key_index);
ODALID_LIB int16_t Mf_Classic_LoadKey2(ReaderName *Name, uint8_t *keyA, uint8_t *keyB, uint8_t key_index);
ODALID_LIB int16_t Mf_Classic_PersonalizeUID(ReaderName *Name, uint8_t Type);
ODALID_LIB int16_t Mf_Classic_Authenticate(ReaderName *Name, BOOL Auth_Key, BOOL internal_Key, uint8_t sector, uint8_t *key, uint8_t key_index);
ODALID_LIB int16_t Mf_Classic_Read_Block(ReaderName *Name, BOOL auth, uint8_t block, uint8_t *Data, BOOL Auth_Key, uint8_t key_index);
ODALID_LIB int16_t Mf_Classic_Write_Block(ReaderName *Name, BOOL auth, uint8_t block, uint8_t *Data, BOOL Auth_Key, uint8_t key_index);
ODALID_LIB int16_t Mf_Classic_Read_Sector(ReaderName *Name, BOOL auth, uint8_t sector, uint8_t *Data, BOOL Auth_Key, uint8_t key_index);
ODALID_LIB int16_t Mf_Classic_Write_Sector(ReaderName *Name, BOOL auth, uint8_t sector, uint8_t *Data, BOOL Auth_Key, uint8_t key_index);
ODALID_LIB int16_t Mf_Classic_UpdadeAccessBlock(ReaderName *Name, BOOL auth, uint8_t sector, uint8_t old_key_index, uint8_t *new_key_A, uint8_t *new_key_B, uint8_t bc0, uint8_t bc1, uint8_t bc2, uint8_t bc3, BOOL Auth_Key);
ODALID_LIB int16_t Mf_Classic_Read_Value(ReaderName *Name, BOOL auth, uint8_t block, uint32_t *value,  BOOL Auth_Key, uint8_t key_index);
ODALID_LIB int16_t Mf_Classic_Write_Value(ReaderName *Name, BOOL auth, uint8_t block, uint32_t value, BOOL Auth_Key, uint8_t key_index);
ODALID_LIB int16_t Mf_Classic_Increment_Value(ReaderName *Name, BOOL auth, uint8_t block, uint32_t valeur, uint8_t trans_block, BOOL Auth_Key, uint8_t key_index);
ODALID_LIB int16_t Mf_Classic_Decrement_Value(ReaderName *Name, BOOL auth, uint8_t block, uint32_t valeur, uint8_t trans_block, BOOL Auth_Key, uint8_t key_index);
ODALID_LIB int16_t Mf_Classic_Restore_Value(ReaderName *Name, BOOL auth, uint8_t block, uint8_t trans_block, BOOL Auth_Key, uint8_t key_index);
ODALID_LIB int16_t Mf_Transmit(ReaderName *Name, uint8_t *send, uint16_t len_send, uint8_t *recv, uint16_t *len_recv, uint16_t timeout);

ODALID_LIB int16_t Mf_Ultralight_Read(ReaderName *Name, uint8_t adr, uint8_t *data);
ODALID_LIB int16_t Mf_Ultralight_CompatilityWrite(ReaderName *Name, uint8_t adr, uint8_t *data);
ODALID_LIB int16_t Mf_UltralightC_Authenticate(ReaderName *Name, uint8_t *keyinit);

ODALID_LIB int16_t Mf_Plus_Authenticate_SL1(ReaderName *Name, uint8_t *KeyBNr);
ODALID_LIB int16_t Mf_Plus_CommitPerso_SL0(ReaderName *Name);
ODALID_LIB int16_t Mf_Plus_WritePerso_SL0(ReaderName *Name, uint16_t address, uint8_t *data);

#define DF_APPLSETTING2_ISO_EF_IDS          0x20
#define DF_APPLSETTING2_DES_OR_3DES2K       0x00
#define DF_APPLSETTING2_3DES3K              0x40
#define DF_APPLSETTING2_AES                 0x80

typedef struct
{
    uint8_t bHwVendorID;
    uint8_t bHwType;
    uint8_t bHwSubType;
    uint8_t bHwMajorVersion;
    uint8_t bHwMinorVersion;
    uint8_t bHwStorageSize;
    uint8_t bHwProtocol;
    uint8_t bSwVendorID;
    uint8_t bSwType;
    uint8_t bSwSubType;
    uint8_t bSwMajorVersion;
    uint8_t bSwMinorVersion;
    uint8_t bSwStorageSize;
    uint8_t bSwProtocol;
    uint8_t abUid[7];
    uint8_t abBatchNo[5];
    uint8_t bProductionCW;
    uint8_t bProductionYear;
} DF_VERSION_INFO;


typedef union
{
    struct
    {
        uint16_t eFileSize;
    } stDataFileSettings;

    struct
    {
        int32_t lLowerLimit;
        int32_t lUpperLimit;
        uint16_t eLimitedCredit;
        uint8_t bLimitedCreditEnabled;
    } stValueFileSettings;

    struct
    {
        uint16_t eRecordSize;
        uint16_t eMaxNRecords;
        uint16_t eCurrNRecords;
    } stRecordFileSettings;
} DF_ADDITIONAL_FILE_SETTINGS;

typedef struct
{
    uint8_t  tcl_cid;
    uint8_t  iso_wrapping;

    uint32_t current_aid;

    uint8_t  session_type;
    uint8_t  session_key[24];
    uint8_t  session_key_id;
    uint8_t  comm_mode;
    uint8_t  init_vector[16];

    uint8_t  cmac_subkey_1[16];
    uint8_t  cmac_subkey_2[16];
} DESFIRE_INFO;


typedef struct
{
    uint8_t  Type;
    uint32_t  AID;
    uint8_t SId[7];
    uint8_t UID[7];
    uint16_t LenUID;
    uint8_t MIFAREKEY[6];
    uint8_t block;
} DIV_INFO;

ODALID_LIB char* Mf_DESFire_GetErrorMessage(int16_t status);

//----------------------------Security related
ODALID_LIB int16_t Mf_DESFire_AuthenticateHost(ReaderName *Name, DESFIRE_INFO *pDESFire_Info, uint8_t DFKeyNo, uint8_t *pAccessKey);
ODALID_LIB int16_t Mf_DESFire_AuthenticateHostIso(ReaderName *Name, DESFIRE_INFO *pDESFire_Info, uint8_t DFKeyNo, uint8_t *pAccessKey);
ODALID_LIB int16_t Mf_DESFire_AuthenticateHostAes(ReaderName *Name, uint8_t Type, DESFIRE_INFO *pDESFire_Info, uint8_t DFKeyNo, uint8_t *pAccessKey);
ODALID_LIB int16_t Mf_DESFire_AutenticateSAM(ReaderName *Name, DESFIRE_INFO *pDESFire_Info, uint8_t DFKeyNo, uint8_t SAMKeyNo, uint8_t SAMKeyV);
ODALID_LIB int16_t Mf_DESFire_ChangeKeySettings(ReaderName *Name, DESFIRE_INFO *pDESFire_Info, uint8_t  key_settings);
ODALID_LIB int16_t Mf_DESFire_GetKeySettings(ReaderName *Name, DESFIRE_INFO *pDESFire_Info, uint8_t *DFKeySettings, uint8_t *DFMaxNoKey);
ODALID_LIB int16_t Mf_DESFire_ChangeKey(ReaderName *Name, DESFIRE_INFO *pDESFire_Info, uint8_t key_number, uint8_t *new_key, uint8_t *old_key);
ODALID_LIB int16_t Mf_DESFire_ChangeKeyIso(ReaderName *Name, DESFIRE_INFO *pDESFire_Info, uint8_t key_number, uint8_t *new_key, uint8_t *old_key);
ODALID_LIB int16_t Mf_DESFire_ChangeKeyAes(ReaderName *Name, DESFIRE_INFO *pDESFire_Info, uint8_t key_number, uint8_t key_version, uint8_t *new_key, uint8_t *old_key);
ODALID_LIB int16_t Mf_DESFire_GetKeyVersion(ReaderName *Name, DESFIRE_INFO *pDESFire_Info, uint8_t KeyNumber, uint8_t *pKeyVersion);

//----------------------------Picc level command
ODALID_LIB int16_t Mf_DESFire_CreateApplication(ReaderName *Name, DESFIRE_INFO *pDESFire_Info, uint32_t aid, uint8_t Key1, uint8_t Key2);
ODALID_LIB int16_t Mf_DESFire_DeleteApplication(ReaderName *Name, DESFIRE_INFO *pDESFire_Info, uint32_t aid);
ODALID_LIB int16_t Mf_DESFire_GetApplicationIDs(ReaderName *Name, DESFIRE_INFO *pDESFire_Info, uint8_t aid_max_count, uint32_t *aid_list, uint8_t *aid_count);
ODALID_LIB int16_t Mf_DESFire_GetDFNames(ReaderName *Name, DESFIRE_INFO *pDESFire_Info);
ODALID_LIB int16_t Mf_DESFire_SelectApplication(ReaderName *Name, DESFIRE_INFO *pDESFire_Info, uint32_t aid);
ODALID_LIB int16_t Mf_DESFire_FormatPICC(ReaderName *Name, DESFIRE_INFO *pDESFire_Info);
ODALID_LIB int16_t Mf_DESFire_GetVersion(ReaderName *Name, DESFIRE_INFO *pDESFire_Info, DF_VERSION_INFO *pVersionInfo);
ODALID_LIB int16_t Mf_DESFire_FreeMem(ReaderName *Name, DESFIRE_INFO *pDESFire_Info, uint8_t *pFreeMem);
ODALID_LIB int16_t Mf_DESFire_SetConfiguration(ReaderName *Name, DESFIRE_INFO *pDESFire_Info, uint8_t option, uint8_t *data, uint8_t length);
ODALID_LIB int16_t Mf_DESFire_GetCardUID(ReaderName *Name, DESFIRE_INFO *pDESFire_Info, uint8_t *uid);

//----------------------------application level
ODALID_LIB int16_t Mf_DESFire_GetFileIDs(ReaderName *Name, DESFIRE_INFO *pDESFire_Info, uint8_t *file_id, uint8_t nb_file_id);
ODALID_LIB int16_t Mf_DESFire_GetISOIDs(ReaderName *Name, DESFIRE_INFO *pDESFire_Info, uint8_t *file_id, uint8_t nb_file_id);
ODALID_LIB int16_t Mf_DESFire_GetFileSettings(ReaderName *Name, DESFIRE_INFO *pDESFire_Info, uint8_t file_id);
ODALID_LIB int16_t Mf_DESFire_ChangeFileSettings(ReaderName *Name, DESFIRE_INFO *pDESFire_Info, uint8_t file_id, uint8_t  comm_mode, uint16_t  access_rights);
ODALID_LIB int16_t Mf_DESFire_CreateStdDataFile(ReaderName *Name, DESFIRE_INFO *pDESFire_Info, uint8_t File_No, uint8_t comm_mode, uint16_t access_rights, uint32_t file_size);
ODALID_LIB int16_t Mf_DESFire_CreateBackupDataFile(ReaderName *Name, DESFIRE_INFO *pDESFire_Info, uint8_t File_No, uint8_t comm_mode, uint16_t access_rights,uint32_t file_size);
ODALID_LIB int16_t Mf_DESFire_CreateValueFile(ReaderName *Name, DESFIRE_INFO *pDESFire_Info, uint8_t File_No, uint8_t comm_mode, uint16_t access_rights, uint32_t lower_limit, uint32_t upper_limit, uint32_t initial_value, uint8_t limited_credit_enabled);
//ODALID_LIB int16_t Mf_DESFire_CreatelinearRecordFile
ODALID_LIB int16_t Mf_DESFire_CreateCyclicRecordFile(ReaderName *Name, DESFIRE_INFO *pDESFire_Info, uint8_t File_No, uint8_t comm_mode, uint16_t access_rights, uint32_t record_size, uint32_t max_records);
ODALID_LIB int16_t Mf_DESFire_DeleteFile(ReaderName *Name, DESFIRE_INFO *pDESFire_Info, uint8_t File_No);

//----------------------------Data manipulation command
ODALID_LIB int16_t Mf_DESFire_ReadData(ReaderName *Name, DESFIRE_INFO *pDESFire_Info, uint8_t File_No,  uint8_t comm_mode, uint32_t Offset, uint32_t Lenght, uint8_t *Data);
ODALID_LIB int16_t Mf_DESFire_WriteData(ReaderName *Name, DESFIRE_INFO *pDESFire_Info, uint8_t File_No, uint8_t comm_mode, uint32_t Offset, uint32_t Lenght, uint8_t *Data);
ODALID_LIB int16_t Mf_DESFire_Credit(ReaderName *Name, DESFIRE_INFO *pDESFire_Info, uint8_t File_No, uint8_t comm_mode, uint32_t Value);
ODALID_LIB int16_t Mf_DESFire_Debit(ReaderName *Name, DESFIRE_INFO *pDESFire_Info, uint8_t File_No, uint8_t comm_mode, uint32_t Value);
ODALID_LIB int16_t Mf_DESFire_LimitedCredit(ReaderName *Name, DESFIRE_INFO *pDESFire_Info, uint8_t File_No, uint8_t comm_mode, uint32_t Value);
ODALID_LIB int16_t Mf_DESFire_GetValue(ReaderName *Name, DESFIRE_INFO *pDESFire_Info, uint8_t File_No, uint8_t comm_mode, uint32_t *Value);
ODALID_LIB int16_t Mf_DESFire_WriteRecord(ReaderName *Name, DESFIRE_INFO *pDESFire_Info, uint8_t File_No, uint8_t comm_mode, uint32_t Offset, uint32_t Lenght, uint8_t *Data);
ODALID_LIB int16_t Mf_DESFire_ReadRecord(ReaderName *Name, DESFIRE_INFO *pDESFire_Info, uint8_t File_No,  uint8_t comm_mode, uint32_t Offset, uint32_t Lenght, uint8_t *Data);
ODALID_LIB int16_t Mf_DESFire_ClearRecordFile(ReaderName *Name, DESFIRE_INFO *pDESFire_Info, uint8_t File_No);
ODALID_LIB int16_t Mf_DESFire_CommitTransaction(ReaderName *Name, DESFIRE_INFO *pDESFire_Info);
ODALID_LIB int16_t Mf_DESFire_AbortTransaction(ReaderName *Name, DESFIRE_INFO *pDESFire_Info);

//----------------------------ISO
ODALID_LIB int16_t Mf_DESFire_CreateIsoApplication(ReaderName *Name, DESFIRE_INFO *pDESFire_Info, uint32_t aid, uint8_t key_setting_1, uint8_t key_setting_2, uint16_t iso_df_id, uint8_t *iso_df_name, uint8_t iso_df_namelen);
///////////



ODALID_LIB int16_t SR176_ReadBlock(ReaderName *Name, uint8_t block, uint8_t *Data);
ODALID_LIB int16_t SR176_WriteBlock(ReaderName *Name, uint8_t block, uint8_t *Data);
ODALID_LIB int16_t SR176_GetUID(ReaderName *Name, uint8_t *UID);
ODALID_LIB int16_t SR176_GetProtection(ReaderName *Name, uint8_t *LockReg);
ODALID_LIB int16_t SR176_ProtectBlock(ReaderName *Name, uint8_t cid, uint8_t LockReg);

ODALID_LIB int16_t SRixK_ReadBlock(ReaderName *Name, uint8_t block, uint8_t *Data);
ODALID_LIB int16_t SRixK_WriteBlock(ReaderName *Name, uint8_t block, uint8_t *Data);
ODALID_LIB int16_t SRixK_GetUID(ReaderName *Name, uint8_t *UID);

ODALID_LIB int16_t CTS_ReadBlock(ReaderName *Name, uint8_t block, uint8_t *Data);

ODALID_LIB int16_t ISO15693_ReadSingleBlock(ReaderName *Name, uint8_t *UID, uint8_t block, uint8_t *Data);
ODALID_LIB int16_t ISO15693_WriteSingleBlock(ReaderName *Name, uint8_t *UID, uint8_t block, uint8_t *Data);
ODALID_LIB int16_t ISO15693_LockBblock(ReaderName *Name, uint8_t *UID, uint8_t block);
ODALID_LIB int16_t ISO15693_ReadMultipleBlocks(ReaderName *Name, uint8_t *UID, uint8_t start_block, uint8_t nbre_block, uint8_t *Data);
ODALID_LIB int16_t ISO15693_WriteMultipleBlocks(ReaderName *Name, uint8_t *UID, uint8_t start_block, uint8_t nbre_block, uint8_t *Data);

ODALID_LIB int16_t ISO7816_SelectApplication(ReaderName *Name, uint8_t Type, uint8_t P1, uint8_t P2, char *AID, uint16_t AID_len, uint8_t *Data, uint16_t *Datalen);
ODALID_LIB int16_t ISO7816_ReadRecord(ReaderName *Name, uint8_t Type, uint8_t rec_no, uint8_t sfi, uint8_t rec_size, uint8_t *Data, uint16_t *Datalen);
ODALID_LIB int16_t ISO7816_GetProcessingOption(ReaderName *Name, uint8_t Type, uint8_t *pdol, uint16_t pdol_len, uint8_t *Data, uint16_t *Datalen);
ODALID_LIB int16_t ISO7816_ReadSecured(ReaderName *Name, uint8_t Type, uint8_t *AccessId, uint8_t *HostCryptogram, uint8_t *HostChallenge, uint8_t *resp, uint16_t *len_resp);
ODALID_LIB int16_t ISO7816_Read(ReaderName *Name, uint8_t Type, uint8_t *AccessId, uint8_t *resp, uint16_t *len_resp);


typedef struct
{
    uint8_t card_slot;
    uint8_t sam_slot;
    uint8_t pcd_addr;
    uint8_t picc_addr;
    uint8_t picc_seq;
    uint8_t in_session;
    uint8_t card_sw[2];
    uint8_t sam_sw[2];
} CALYPSO_SEQ;

typedef struct
{
    uint8_t Fci[127];
    uint8_t FciLen;
    uint8_t DFName[16];
    uint8_t DFNameLen;
    uint8_t FciPropierty[32];
    uint8_t FciPropiertyLen;
    uint8_t FciIssuer[19];
    uint8_t FciIssuerLen;
    uint8_t ASN[8];
    uint8_t ASNLen;
    uint8_t Data[7];
    uint8_t DataLen;
    uint8_t NumberModification;
    uint8_t Platform;
    uint8_t Type;
    uint8_t SubType;
    uint8_t SoftIssuer;
    uint8_t SoftVersion;
    uint8_t SoftRevision;
    uint8_t Revision;
    uint8_t UID[8];
    BOOL  SessionActive : 1;
    BOOL Invalidated : 1;
    BOOL WithStoredValue : 1;
    BOOL NeedRatificationFrame : 1;
    BOOL WithPin : 1;
    uint8_t SessionCurMods;
    uint8_t CurrentPin[4];
    uint8_t CurrentKif;
    uint8_t CurrentKvc;
}CALYPSO_INFO;

#define CALYPSO_MIN_SESSION_MODIFS 3
#define CALYPSO_MIN_RECORD_SIZE    29


#define CALYPSO_SFI_ENVIRONMENT         0x07
#define CALYPSO_SFI_CONTRACTS           0x09
#define CALYPSO_SFI_CONTRACTS_EXT       0x06
#define CALYPSO_SFI_COUNTERS            0x19
#define CALYPSO_SFI_COUNTERS_CD97       0x0A
#define CALYPSO_SFI_EVENTS_LOG          0x08
#define CALYPSO_SFI_SPECIAL_EVENTS      0x1D
#define CALYPSO_SFI_CONTRACTS_LIST      0x1E

#define CALYPSO_KEY_ISSUER              0x01
#define CALYPSO_KIF_ISSUER              0x21
#define CALYPSO_KNO_ISSUER              0x0C

#define CALYPSO_KEY_LOAD                0x02
#define CALYPSO_KIF_LOAD                0x27
#define CALYPSO_KNO_LOAD                0x02

#define CALYPSO_KEY_DEBIT               0x03
#define CALYPSO_KIF_DEBIT               0x30
#define CALYPSO_KNO_DEBIT               0x0D

#define CALYPSO_INS_GET_RESPONSE        0xC0
#define CALYPSO_INS_SELECT              0xA4
#define CALYPSO_INS_INVALIDATE          0x04
#define CALYPSO_INS_REHABILITATE        0x44
#define CALYPSO_INS_APPEND_RECORD       0xE2
#define CALYPSO_INS_DECREASE            0x30
#define CALYPSO_INS_INCREASE            0x32
#define CALYPSO_INS_READ_BINARY         0xB0
#define CALYPSO_INS_READ_RECORD         0xB2
#define CALYPSO_INS_UPDATE_BINARY       0xD6
#define CALYPSO_INS_UPDATE_RECORD       0xDC
#define CALYPSO_INS_WRITE_RECORD        0xD2
#define CALYPSO_INS_OPEN_SESSION        0x8A
#define CALYPSO_INS_CLOSE_SESSION       0x8E
#define CALYPSO_INS_GET_CHALLENGE       0x84
#define CALYPSO_INS_CHANGE_PIN          0xD8
#define CALYPSO_INS_VERIFY_PIN          0x20

#define CALYPSO_INS_SV_GET              0x7C
#define CALYPSO_INS_SV_DEBIT            0xBA
#define CALYPSO_INS_SV_RELOAD           0xB8
#define CALYPSO_INS_SV_UN_DEBIT         0xBC

#define CALYPSO_INS_SAM_SV_DEBIT        0x54
#define CALYPSO_INS_SAM_SV_RELOAD       0x56


//ODALID_LIB int16_t Calypso_GetResponse(ReaderName *Name, uint8_t Type, uint8_t *Data, uint8_t Datalen);
ODALID_LIB int16_t Calypso_SelectApplication(ReaderName *Name, uint8_t Type, CALYPSO_SEQ *pSeq, char *AID, uint8_t AID_len, CALYPSO_INFO *pInfo_Card);

ODALID_LIB int16_t Calypso_AppendRecord(ReaderName *Name, uint8_t Type, CALYPSO_SEQ *pSeq, CALYPSO_INFO *pInfo_Card, uint8_t sfi, uint8_t *Data, uint8_t Datalen);
ODALID_LIB int16_t Calypso_Decrease(ReaderName *Name, uint8_t Type, CALYPSO_SEQ *pSeq, CALYPSO_INFO *pInfo_Card, uint8_t rec_no, uint8_t sfi, uint32_t DecValue, uint32_t *NewValue);
//ODALID_LIB int16_t Calypso_DecreaseMultiple(ReaderName *Name, uint8_t Type, uint8_t sfi, uint32_t DecValue);
ODALID_LIB int16_t Calypso_Increase(ReaderName *Name, uint8_t Type, CALYPSO_SEQ *pSeq, CALYPSO_INFO *pInfo_Card, uint8_t rec_no, uint8_t sfi, uint32_t IncValue, uint32_t *NewValue);
//ODALID_LIB int16_t Calypso_IncreaseMultiple(ReaderName *Name, CALYPSO_SEQ *pSeq, uint8_t Type, uint8_t sfi, uint32_t DecValue);
ODALID_LIB int16_t Calypso_ReadRecord(ReaderName *Name, uint8_t Type, CALYPSO_SEQ *pSeq, CALYPSO_INFO *pInfo_Card, uint8_t rec_no, uint8_t sfi, uint8_t rec_size, uint8_t *Data, uint16_t *Datalen);
ODALID_LIB int16_t Calypso_UpdateRecord(ReaderName *Name, uint8_t Type, CALYPSO_SEQ *pSeq, CALYPSO_INFO *pInfo_Card, uint8_t rec_no, uint8_t sfi, uint8_t *Data, uint8_t Datalen);
ODALID_LIB int16_t Calypso_WriteRecord(ReaderName *Name, uint8_t Type, CALYPSO_SEQ *pSeq, CALYPSO_INFO *pInfo_Card, uint8_t rec_no, uint8_t sfi, uint8_t rec_size, uint8_t *Data, uint8_t Datalen);

ODALID_LIB int16_t Calypso_OpenSecureSession1(ReaderName *Name, uint8_t Type, CALYPSO_SEQ *pSeq, CALYPSO_INFO *pInfo_Card, uint8_t kvc, uint8_t rec_no, uint8_t sfi, uint8_t *Sam_Challenge, uint8_t *Card_Challenge, uint8_t *Ratification, uint8_t *Resp, uint16_t *Resplen, uint8_t *Data, uint16_t *Datalen);
ODALID_LIB int16_t Calypso_OpenSecureSession2(ReaderName *Name, uint8_t Type, CALYPSO_SEQ *pSeq, CALYPSO_INFO *pInfo_Card, uint8_t kvc, uint8_t rec_no, uint8_t sfi, uint8_t *Sam_Challenge, uint8_t *Card_Challenge, uint8_t *Ratification, uint8_t *Resp, uint16_t *Resplen, uint8_t *Data, uint16_t *Datalen, uint8_t *kvc_resp);
ODALID_LIB int16_t Calypso_OpenSecureSession3(ReaderName *Name, uint8_t Type, CALYPSO_SEQ *pSeq, CALYPSO_INFO *pInfo_Card, uint8_t kvc, uint8_t rec_no, uint8_t sfi, uint8_t *Sam_Challenge, uint8_t *Card_Challenge, uint8_t *Ratification, uint8_t *Resp, uint16_t *Resplen, uint8_t *Data, uint16_t *Datalen, uint8_t *kvc_resp, uint8_t *kif_resp);
ODALID_LIB int16_t Calypso_CloseSecureSession(ReaderName *Name, uint8_t Type, CALYPSO_SEQ *pSeq, CALYPSO_INFO *pInfo_Card, BOOL ratify_now, uint8_t *Sam_Sign, uint8_t *Resp, uint16_t *Resplen);
ODALID_LIB int16_t Calypso_Invalidate(ReaderName *Name, uint8_t Type, CALYPSO_SEQ *pSeq, CALYPSO_INFO *pInfo_Card);
ODALID_LIB int16_t Calypso_Ratification(ReaderName *Name, uint8_t Type, CALYPSO_SEQ *pSeq, CALYPSO_INFO *pInfo_Card);

#define TypeISO         0x00
#define TypeISO_T0      0x00
#define TypeISO_T1      0x01
#define TypeHSP         0x02

typedef struct
{
    uint16_t sam_Datalen;		// Recieved Data length from smart card(excluding SW1 and SW2 bytes)
    uint8_t sam_sw[2];
} SC_APDU_RESPONSE;

ODALID_LIB int16_t SAM_SelectSlot(ReaderName *Name, uint8_t Slot);
ODALID_LIB int16_t SAM_GetATR(ReaderName *Name, uint8_t Type, uint8_t *atr, uint16_t *atrlen);
ODALID_LIB int16_t SAM_Transmit(ReaderName *Name, uint8_t *send, uint16_t len_send, uint8_t *recv, uint16_t *len_recv, uint16_t timeout);



typedef struct
{
    uint8_t bHwVendorID;
    uint8_t bHwType;
    uint8_t bHwSubType;
    uint8_t bHwMajorVersion;
    uint8_t bHwMinorVersion;
    uint8_t bHwStorageSize;
    uint8_t bHwProtocol;
    uint8_t bSwVendorID;
    uint8_t bSwType;
    uint8_t bSwSubType;
    uint8_t bSwMajorVersion;
    uint8_t bSwMinorVersion;
    uint8_t bSwStorageSize;
    uint8_t bSwProtocol;
    uint8_t serial[7];
    uint8_t abBatchNo[5];
    uint8_t bProductionCW;
    uint8_t bProductionYear;

    uint8_t  session_type;
    uint8_t  session_key[24];
    uint8_t  session_key_id;
    uint8_t  comm_mode;
    uint8_t  init_vector[16];

    uint8_t  cmac_subkey_1[16];
    uint8_t  cmac_subkey_2[16];

    uint8_t  SV1[16];
    uint8_t  SV2[16];

    uint8_t  Ke[16];
    uint8_t  Km[16];
} SAMAV2_INFO;


typedef struct
{
    uint8_t VarA;
    uint8_t VarB;
    uint8_t VarC;
    uint32_t DF_AID;
    uint8_t DF_KeyNo;
    uint8_t KeyNoCEK;
    uint8_t KeyVCEK;
    uint8_t RefNoKUC;
    uint16_t SET;
    uint16_t ExtSET;
} SAMAV2_KEY;

typedef struct
{
    uint8_t bHwVendorID;
    uint8_t bHwType;
    uint8_t bHwSubType;
    uint8_t bHwMajorVersion;
    uint8_t bHwMinorVersion;
    uint8_t bHwStorageSize;
    uint8_t bHwProtocol;
    uint8_t bSwVendorID;
    uint8_t bSwType;
    uint8_t bSwSubType;
    uint8_t bSwMajorVersion;
    uint8_t bSwMinorVersion;
    uint8_t bSwStorageSize;
    uint8_t bSwProtocol;
    uint8_t serial[7];
    uint8_t abBatchNo[5];
    uint8_t bProductionCW;
    uint8_t bProductionYear;

    uint8_t  session_type;
    uint8_t  session_key[24];
    uint8_t  session_key_id;
    uint8_t  comm_mode;
    uint8_t  init_vector[16];

    uint8_t  cmac_subkey_1[16];
    uint8_t  cmac_subkey_2[16];

    uint8_t  SV1[16];
    uint8_t  SV2[16];

    uint8_t  Ke[16];
    uint8_t  Km[16];
} SAMAV3_INFO;

typedef struct
{
    uint8_t VarA;
    uint8_t VarB;
    uint8_t VarC;
    uint32_t DF_AID;
    uint8_t DF_KeyNo;
    uint8_t KeyNoCEK;
    uint8_t KeyVCEK;
    uint8_t RefNoKUC;
    uint16_t SET;
    uint16_t ExtSET;
} SAMAV3_KEY;

#define DumpSessionKey          0x0001
#define KeepIV                  0x0004

#define DESFire4                0x0000
#define ISO_TDEA16              0x0008
#define MIFARE                  0x0010
#define TTDEA                   0x0018
#define AES_128                 0x0020
#define AES_192                 0x0028
#define ISO_TDEA32              0x0030
#define AES_256                 0x0038
#define AES_128LRP              0x0040

#define PLKey                   0x0080
#define AuthKey                 0x0100
#define DisableKeyEntry         0x0200
#define LockKey                 0x0400
#define DisableWritingKeyPICC   0x0800
#define DisableDecryption       0x1000
#define DisableEncryption       0x2000
#define DisableVerifyMAC        0x4000
#define DisableGenerateMAC      0x8000

#define Unlock                  0x00
#define LockWO                  0x01
#define Lock                    0x02
#define ActivateMIFARESAM       0x03
#define UnlockPL                0x04

ODALID_LIB int16_t SAMAV1_AuthenticateHostAes(ReaderName *Name, SAMAV2_INFO *pSAMAV2_Info, uint8_t KeyNo, uint8_t KeyVer, uint8_t HostMode, uint8_t *Key);
ODALID_LIB int16_t SAMAV1_ChangeKeyEntry(ReaderName *Name, SAMAV2_INFO *pSAMAV2_Info, uint8_t KeyNo, uint8_t *KeyA, uint8_t *KeyB, uint8_t *KeyC, uint32_t aid,
                                        uint8_t DF_KeyNo, uint8_t KeyNoCEK, uint8_t KeyVCEK, uint8_t RefNoKUC, uint16_t SET, uint8_t VKPosA, uint8_t VKPosB, uint8_t VKPosC);

ODALID_LIB int16_t SAMAV2_GetVersion(ReaderName *Name, uint8_t *pVersion);
ODALID_LIB int16_t SAMAV2_SwitchToAV2Mode(ReaderName *Name, SAMAV2_INFO *pSAMAV2_Info, uint8_t P1, uint8_t *Key);
ODALID_LIB int16_t SAMAV2_AuthenticateHost(ReaderName *Name, SAMAV2_INFO *pSAMAV2_INFO, uint8_t KeyNo, uint8_t KeyVer, uint8_t HostMode, uint8_t *Key);
ODALID_LIB int16_t SAMAV2_AuthenticateHostAes(ReaderName *Name, SAMAV2_INFO *pSAMAV2_Info, uint8_t KeyNo, uint8_t KeyVer, uint8_t HostMode, uint8_t *Key);
ODALID_LIB int16_t SAMAV2_ActivateOfflineKey(ReaderName *Name, SAMAV2_INFO *pSAMAV2_Info, uint8_t KeyNo, uint8_t KeyVer);
ODALID_LIB int16_t SAMAV2_GetKeyEntry(ReaderName *Name, SAMAV2_KEY *pSAMAV2_KEY, uint8_t KeyNo);
ODALID_LIB int16_t SAMAV2_GetKeyUCEntry(ReaderName *Name, SAMAV2_KEY *pSAMAV2_KEY, uint8_t RefNoKUC);
ODALID_LIB int16_t SAMAV2_ChangeKeyEntry(ReaderName *Name, SAMAV2_INFO *pSAMAV2_Info, uint8_t KeyNo, uint8_t *KeyA, uint8_t *KeyB, uint8_t *KeyC, uint32_t aid,
                                         uint8_t DF_KeyNo, uint8_t KeyNoCEK, uint8_t KeyVCEK, uint8_t RefNoKUC, uint16_t SET, uint8_t VKPosA, uint8_t VKPosB, uint8_t VKPosC,
                                         uint16_t ExtSET, uint8_t KeyNoAEK, uint8_t KeyVerAEK);

ODALID_LIB int16_t SAMAV3_GetVersion(ReaderName *Name, uint8_t *pVersion);
ODALID_LIB int16_t SAMAV3_LockUnlock(ReaderName *Name, SAMAV3_INFO *pSAMAV3_Info, uint8_t P1, uint8_t *Key, uint8_t KeyNo, uint8_t KeyVer, uint8_t UnlockKeyNo, uint8_t UnlockKeyVer);
ODALID_LIB int16_t SAMAV3_AuthenticateHost(ReaderName *Name, SAMAV3_INFO *pSAMAV3_INFO, uint8_t KeyNo, uint8_t KeyVer, uint8_t HostMode, uint8_t *Key);
ODALID_LIB int16_t SAMAV3_AuthenticateHostAes(ReaderName *Name, SAMAV3_INFO *pSAMAV3_Info, uint8_t KeyNo, uint8_t KeyVer, uint8_t HostMode, uint8_t *Key);
ODALID_LIB int16_t SAMAV3_ActivateOfflineKey(ReaderName *Name, SAMAV3_INFO *pSAMAV3_Info, uint8_t KeyNo, uint8_t KeyVer);
ODALID_LIB int16_t SAMAV3_GetKeyEntry(ReaderName *Name, SAMAV3_KEY *pSAMAV3_KEY, uint8_t KeyNo);
ODALID_LIB int16_t SAMAV3_GetKeyUCEntry(ReaderName *Name, SAMAV3_KEY *pSAMAV3_KEY, uint8_t RefNoKUC);
ODALID_LIB int16_t SAMAV3_ChangeKeyEntry(ReaderName *Name, SAMAV3_INFO *pSAMAV3_Info, uint8_t KeyNo, uint8_t *KeyA, uint8_t *KeyB, uint8_t *KeyC, uint32_t aid,
                                        uint8_t DF_KeyNo, uint8_t KeyNoCEK, uint8_t KeyVCEK, uint8_t RefNoKUC, uint16_t SET, uint8_t VKPosA, uint8_t VKPosB, uint8_t VKPosC,
                                        uint16_t ExtSET, uint8_t KeyNoAEK, uint8_t KeyVerAEK);

ODALID_LIB int16_t SAM_Calypso_SelectDiversifer(ReaderName *Name, CALYPSO_SEQ *pSeq, uint8_t *UID);
ODALID_LIB int16_t SAM_Calypso_GetChallenge(ReaderName *Name, CALYPSO_SEQ *pSeq, uint8_t *Challenge);
ODALID_LIB int16_t SAM_Calypso_DigestInit(ReaderName *Name, CALYPSO_SEQ *pSeq, int8_t kif, uint8_t kvc, uint8_t *Data, uint8_t Datalen);
ODALID_LIB int16_t SAM_Calypso_DigestInitOld(ReaderName *Name, CALYPSO_SEQ *pSeq, uint8_t key, uint8_t *Data, uint8_t Datalen);
ODALID_LIB int16_t SAM_Calypso_DigestUpdate(ReaderName *Name, CALYPSO_SEQ *pSeq, uint8_t *Data, uint8_t Datalen);
ODALID_LIB int16_t SAM_Calypso_DigestClose(ReaderName *Name, CALYPSO_SEQ *pSeq, uint8_t *mac);
ODALID_LIB int16_t SAM_Calypso_DigestAuthenticate(ReaderName *Name, CALYPSO_SEQ *pSeq, uint8_t *SignLo);

ODALID_LIB uint8_t ByteToBcd(uint8_t input);
ODALID_LIB uint8_t BcdToByte(uint8_t input);

#define SECURITY_OPEN                           (0)
#define SECURITY_WEP_40                         (1)
#define SECURITY_WEP_104                        (2)
#define SECURITY_WPA_WPA2                       (8)

ODALID_LIB int16_t Wifi_Config(ReaderName *Name, uint8_t SecurityMode, uint8_t SsidLength, uint8_t *SSID, uint8_t SecurityKeyLength, uint8_t *SecurityKey);

#define Inc_Value				TRUE
#define Dec_Value				FALSE

ODALID_LIB int16_t AutoReader_SetRTC(ReaderName *Name, BOOL TimeHost, uint8_t *Time);
ODALID_LIB int16_t AutoReader_FindCard(ReaderName *Name, BOOL FindCard);
ODALID_LIB int16_t AutoReader_DeleteUser(ReaderName *Name, uint8_t *User);
ODALID_LIB int16_t AutoReader_AddUser(ReaderName *Name, uint8_t *User);
ODALID_LIB int16_t AutoReader_ClearFullUser(ReaderName *Name);
ODALID_LIB int16_t AutoReader_LoadKeyMifare(ReaderName *Name, BOOL Auth_Key, uint8_t *key, uint8_t key_index);
ODALID_LIB int16_t AutoReader_AccessMifare(ReaderName *Name, uint8_t Block, BOOL Auth_Key, uint8_t key_index);
ODALID_LIB int16_t AutoReader_ComptMifare(ReaderName *Name, uint8_t Block, BOOL Auth_Key, uint8_t key_index, BOOL Compt, uint32_t Value);
ODALID_LIB int16_t AutoReader_AfficheValueMifare(ReaderName *Name, uint8_t Block, BOOL Auth_Key, uint8_t key_index);
ODALID_LIB int16_t AutoReader_TempoGache(ReaderName *Name, uint8_t Temps);
ODALID_LIB int16_t AutoReader_BlackList(ReaderName *Name, BOOL BlackList);
ODALID_LIB int16_t AutoReader_SendInfo(ReaderName *Name, BOOL SendInfo, uint8_t *IPServeur, uint16_t Port);
ODALID_LIB int16_t AutoReader_LCD1(ReaderName *Name, BOOL option, uint8_t *LCD);
ODALID_LIB int16_t AutoReader_LCD2A(ReaderName *Name, BOOL option, uint8_t *LCD);
ODALID_LIB int16_t AutoReader_LCD2B(ReaderName *Name, BOOL option, uint8_t *LCD);
ODALID_LIB int16_t AutoReader_LCD2C(ReaderName *Name, BOOL option, uint8_t *LCD);
ODALID_LIB int16_t AutoReader_Download(ReaderName *Name, uint16_t PremierDownload, uint8_t NbreDownload, BOOL TraitementMIFARE, uint8_t *data, uint16_t *data_len);
ODALID_LIB int16_t AutoReader_ClearSave(ReaderName *Name);
ODALID_LIB int16_t AutoReader_NbreSave(ReaderName *Name, BOOL TraitementMIFARE, uint16_t *NbreSave);
ODALID_LIB int16_t AutoReader_Download_FULL(ReaderName *Name, BOOL ClearSave, BOOL TraitementMIFARE, char *FilePath);
ODALID_LIB int16_t AutoReader_GetInfo(ReaderName *Name, BOOL *SendInfo, char *IPServeur, uint16_t *Port, uint8_t *info, uint16_t *info_len);
ODALID_LIB int16_t AutoReader_Reset(ReaderName *Name);
ODALID_LIB int16_t AutoReader_Transmit(ReaderName *Name, uint8_t *send, uint16_t len_send, uint8_t *recv, uint16_t *len_recv, uint16_t timeout);

/*ODALID_LIB uint16_t AesSetKey(Aes* aes, const byte* key, word32 len, const byte* iv, int16_t dir);
ODALID_LIB uint16_t AesCbcEncrypt(Aes* aes, byte* out, const byte* in, word32 sz);
ODALID_LIB uint16_t RotatesLeft(uint8_t *_pbyDataOut, uint8_t *_pbyDataIn, uint8_t nbre);*/

#if defined (__cplusplus)
}
#endif
