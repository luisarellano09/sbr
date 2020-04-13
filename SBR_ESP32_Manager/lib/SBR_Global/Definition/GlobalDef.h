#ifndef ENUMTEST_H
#define ENUMTEST_H


enum REQ { READ, WRITE };



/*******************************************************************************************************************************************
 *  												RESULT CODE
 *******************************************************************************************************************************************/

/** \brief  Enumeration for TLF errors.  */
typedef enum{
	SUCCESS						= 0,
	ERROR,
    ERROR_SPI_CB,													/**< \brief Error TLF SPI Callback. 						*/
	ERROR_SPI_BYTE_SWAP,											/**< \brief Error TLF SPI Byte swap. 						*/
	ERROR_SPINLOCK_WAIT,											/**< \brief Error TLF SPI Spinlock waiting. 				*/
	ERROR_QUESTION_LIMIT,											/**< \brief Error TLF Functional Watchdog question Limit. 	*/
	ERROR_RESPONSE_NUMBER_LIMIT										/**< \brief Error TLF Functional Watchdog response Limit.	*/
} RC_t;


/*******************************************************************************************************************************************
 *  												REQUEST
 *******************************************************************************************************************************************/

/** \brief Defines if a read or write operation shall be performed on the TLF*/
typedef enum{
	TLF_READ							=0b0,							/**< \brief Read operation*/
	TLF_WRITE							=0b1,							/**< \brief Write operation*/
}TLF_CMD_BIT_t;


/*******************************************************************************************************************************************
 *  												TLF REGISTER ADDRESSES
 *******************************************************************************************************************************************/

/** \brief  Enumeration for TLF registers. The number defines the register offset */
typedef enum{
	TLF_DEVCFG0							=0x00,							/**< \brief Device configuration 0 *R2 (DEVCFG0) Register*/
	TLF_DEVCFG1							=0x01,							/**< \brief Device configuration 1 *R0 (DEVCFG1) Register*/
	TLF_DEVCFG2							=0x02,							/**< \brief Device configuration 2 *R2 (DEVCFG2) Register*/
	TLF_PROTCFG							=0x03,							/**< \brief Protection register *R2 (PROTCFG) Register*/
	TLF_SYSPCFG0						=0x04,							/**< \brief Protected System configuration request 0 *R1 (SYSPCFG0) Register*/
	TLF_SYSPCFG1						=0x05,							/**< \brief Protected System configuration request 1 *R2 (SYSPCFG1) Register*/
	TLF_WDCFG0							=0x06,							/**< \brief Protected Watchdog configuration request 0 *R2 (WDCFG0) Register*/
	TLF_WDCFG1							=0x07,							/**< \brief Protected Watchdog configuration request 1 *R2 (WDCFG1) Register*/
	TLF_FWDCFG							=0x08,							/**< \brief Protected Functional watchdog configuration request *R2 (FWDCFG) Register*/
	TLF_WWDCFG0							=0x09,							/**< \brief Protected Window watchdog configuration request 0 *R2 (WWDCFG0) Register*/
	TLF_WWDCFG1							=0x0A,							/**< \brief Protected Window watchdog configuration request 1 *R2 (WWDCFG1) Register*/
	TLF_RSYSPCFG0						=0x0B,							/**< \brief System configuration 0 status *R0 (RSYSPCFG0) Register*/
	TLF_RSYSPCFG1						=0x0C,							/**< \brief System configuration 1 status *R3 (RSYSPCFG1) Register*/
	TLF_RWDCFG0							=0x0D,							/**< \brief Watchdog configuration 0 status *R3 (RWDCFG0) Register*/
	TLF_RWDCFG1							=0x0E,							/**< \brief Watchdog configuration 1 status *R3 (RWDCFG1) Register*/
	TLF_RFWDCFG							=0x0F,							/**< \brief Functional watchdog configuration status *R3 (RFWDCFG) Register*/
	TLF_RWWDCFG0						=0x10,							/**< \brief Window watchdog configuration 0 status *R3 (RWWDCFG0) Register*/
	TLF_RWWDCFG1						=0x11,							/**< \brief Window watchdog configuration 1 status *R3 (RWWDCFG1) Register*/
	TLF_WKTIMCFG0						=0x12,							/**< \brief Wake timer configuration 0 *R2 (WKTIMCFG0) Register*/
	TLF_WKTIMCFG1						=0x13,							/**< \brief Wake timer configuration 1 *R2 (WKTIMCFG1) Register*/
	TLF_WKTIMCFG2						=0x14,							/**< \brief Wake timer configuration 2 *R2 (WKTIMCFG2) Register*/
	TLF_DEVCTRL							=0x15,							/**< \brief Device control request *R2 (DEVCTRL) Register*/
	TLF_DEVCTRLN						=0x16,							/**< \brief Device control inverted request *R2 (DEVCTRLN) Register*/
	TLF_WWDSCMD							=0x17,							/**< \brief Window watchdog service command *R2 (WWDSCMD) Register*/
	TLF_FWDRSP							=0x18,							/**< \brief Functional watchdog response command *R2 (FWDRSP) Register*/
	TLF_FWDRSPSYNC						=0x19,							/**< \brief Functional watchdog response command with synchronization *R2 (FWDRSPSYNC) Register*/
	TLF_SYSFAIL							=0x1A,							/**< \brief Failure status flags *R1 (SYSFAIL) Register*/
	TLF_INITERR							=0x1B,							/**< \brief Init error status flags *R2 (INITERR) Register*/
	TLF_IF								=0x1C,							/**< \brief Interrupt flags *R2 (IF) Register*/
	TLF_SYSSF							=0x1D,							/**< \brief System status flags *R2 (SYSSF) Register*/
	TLF_WKSF							=0x1E,							/**< \brief Wakeup status flags *R2 (WKSF) Register*/
	TLF_SPISF							=0x1F,							/**< \brief SPI status flags *R2 (SPISF) Register*/
	TLF_MONSF0							=0x20,							/**< \brief Monitor status flags 0 *R1 (MONSF0) Register*/
	TLF_MONSF1							=0x21,							/**< \brief Monitor status flags 1 *R1 (MONSF1) Register*/
	TLF_MONSF2							=0x22,							/**< \brief Monitor status flags 2 *R2 (MONSF2) Register*/
	TLF_MONSF3							=0x23,							/**< \brief Monitor status flags 3 *R1 (MONSF3) Register*/
	TLF_OTFAIL							=0x24,							/**< \brief Over temperature failure status flags *R1 (OTFAIL) Register*/
	TLF_OTWRNSF							=0x25,							/**< \brief Over temperature warning status flags *R2 (OTWRNSF) Register*/
	TLF_VMONSTAT						=0x26,							/**< \brief Voltage monitor status *R2 (VMONSTAT) Register*/
	TLF_DEVSTAT							=0x27,							/**< \brief Device status *R2 (DEVSTAT) Register*/
	TLF_PROTSTAT						=0x28,							/**< \brief Protection status *R1 (PROTSTAT) Register*/
	TLF_WWDSTAT							=0x29,							/**< \brief Window watchdog status *R3 (WWDSTAT) Register*/
	TLF_FWDSTAT0						=0x2A,							/**< \brief Functional watchdog status 0 *R3 (FWDSTAT0) Register*/
	TLF_FWDSTAT1						=0x2B,							/**< \brief Functional watchdog status 1 *R3 (FWDSTAT1) Register*/
	TLF_ABIST_CTRL0						=0x2C,							/**< \brief ABIST control0 *R2 (ABIST_CTRL0) Register*/
	TLF_ABIST_CTRL1						=0x2D,							/**< \brief ABIST control1 *R2 (ABIST_CTRL1) Register*/
	TLF_ABIST_SELECT0					=0x2E,							/**< \brief ABIST select 0 *R2 (ABIST_SELECT0) Register*/
	TLF_ABIST_SELECT1					=0x2F,							/**< \brief ABIST select 1 *R2 (ABIST_SELECT1) Register*/
	TLF_ABIST_SELECT2					=0x30,							/**< \brief ABIST select 2 *R2 (ABIST_SELECT2) Register*/
	TLF_BCK_FREQ_CHANGE					=0x31,							/**< \brief Buck switching frequency change *R2 (BCK_FREQ_CHANGE) Register*/
	TLF_BCK_FRE_SPREAD					=0x32,							/**< \brief Buck Frequency spread *R2 (BCK_FRE_SPREAD) Register*/
	TLF_BCK_MAIN_CTRL					=0x33,							/**< \brief Buck main control *R2 (BCK_MAIN_CTRL) Register*/
	TLF_GTM								=0x3F,							/**< \brief Global testmode *R2 (GTM) Register*/
	TLF_LENGTH_SEQUENCE					=-1
}TLF_reg_t;




#endif // ENUMTEST_H