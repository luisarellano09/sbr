/**
 * @file RegisterTableDef.h
 * @author Luis Arellano (luis.arellano09@gmail.com)
 * @brief Register Table
 * @version 1.0
 * @date 08.02.2023
 * 
 */

#ifndef REGISTERTABLEDEF_H
#define REGISTERTABLEDEF_H


/**
 * @brief Enumeration for SBR registers IDs. The number defines the register offset
 * 
 */
enum COM_REQUEST_REG_ID_e {
    NONE_REG_ID = 0,
	NODE_ESP32_HEART_BIT01,             /**@brief REGISTER 01 */
    NODE_ESP32_HEART_BIT02,	            /**@brief REGISTER 02 */
    NODE_ESP32_HEART_BIT_STATUS,	    /**@brief REGISTER 03 */
    NODE_ESP32_HEART_BIT_ERRORS,	    /**@brief REGISTER 04 */
    REGISTER_05,	                    /**@brief REGISTER 05 */
    REGISTER_06,	                    /**@brief REGISTER 06 */
    REGISTER_07,	                    /**@brief REGISTER 07 */
    REGISTER_08,	                    /**@brief REGISTER 08 */
    REGISTER_09,	                    /**@brief REGISTER 09 */
    REGISTER_10,	                    /**@brief REGISTER 10 */
    REGISTER_11,                        /**@brief REGISTER 11 */
    REGISTER_12,	                    /**@brief REGISTER 12 */
    REGISTER_13,	                    /**@brief REGISTER 13 */
    REGISTER_14,	                    /**@brief REGISTER 14 */
    REGISTER_15,	                    /**@brief REGISTER 15 */
    REGISTER_16,	                    /**@brief REGISTER 16 */
    REGISTER_17,	                    /**@brief REGISTER 17 */
    REGISTER_18,	                    /**@brief REGISTER 18 */
    REGISTER_19,	                    /**@brief REGISTER 19 */
    REGISTER_20,	                    /**@brief REGISTER 20 */
    REGISTER_21,                        /**@brief REGISTER 21 */
    REGISTER_22,	                    /**@brief REGISTER 22 */
    REGISTER_23,	                    /**@brief REGISTER 23 */
    REGISTER_24,	                    /**@brief REGISTER 24 */
    REGISTER_25,	                    /**@brief REGISTER 25 */
    REGISTER_26,	                    /**@brief REGISTER 26 */
    REGISTER_27,	                    /**@brief REGISTER 27 */
    REGISTER_28,	                    /**@brief REGISTER 28 */
    REGISTER_29,	                    /**@brief REGISTER 29 */
    REGISTER_30,                        /**@brief REGISTER 30 */
    REGISTER_31,                        /**@brief REGISTER 31 */
    REGISTER_32,	                    /**@brief REGISTER 32 */
    REGISTER_33,	                    /**@brief REGISTER 33 */
    REGISTER_34,	                    /**@brief REGISTER 34 */
    REGISTER_35,	                    /**@brief REGISTER 35 */
    REGISTER_36,	                    /**@brief REGISTER 36 */
    REGISTER_37,	                    /**@brief REGISTER 37 */
    REGISTER_38,	                    /**@brief REGISTER 38 */
    REGISTER_39,	                    /**@brief REGISTER 39 */
    REGISTER_40,	                    /**@brief REGISTER 40 */
    REGISTER_41,                        /**@brief REGISTER 41 */
    REGISTER_42,	                    /**@brief REGISTER 42 */
    REGISTER_43,	                    /**@brief REGISTER 43 */
    REGISTER_44,	                    /**@brief REGISTER 44 */
    REGISTER_45,	                    /**@brief REGISTER 45 */
    REGISTER_46,	                    /**@brief REGISTER 46 */
    REGISTER_47,	                    /**@brief REGISTER 47 */
    REGISTER_48,	                    /**@brief REGISTER 48 */
    REGISTER_49,	                    /**@brief REGISTER 49 */
    REGISTER_50,	                    /**@brief REGISTER 50 */
    REGISTER_51,                        /**@brief REGISTER 51 */
    REGISTER_52,	                    /**@brief REGISTER 52 */
    REGISTER_53,	                    /**@brief REGISTER 53 */
    REGISTER_54,	                    /**@brief REGISTER 54 */
    REGISTER_55,	                    /**@brief REGISTER 55 */
    REGISTER_56,	                    /**@brief REGISTER 56 */
    REGISTER_57,	                    /**@brief REGISTER 57 */
    REGISTER_58,	                    /**@brief REGISTER 58 */
    REGISTER_59,	                    /**@brief REGISTER 59 */
    REGISTER_60,	                    /**@brief REGISTER 60 */
    REGISTER_61,                        /**@brief REGISTER 61 */
    REGISTER_62,	                    /**@brief REGISTER 62 */
    REGISTER_63,	                    /**@brief REGISTER 63 */
    REGISTER_64,	                    /**@brief REGISTER 64 */
    REGISTER_65,	                    /**@brief REGISTER 65 */
    REGISTER_66,	                    /**@brief REGISTER 66 */
    REGISTER_67,	                    /**@brief REGISTER 67 */
    REGISTER_68,	                    /**@brief REGISTER 68 */
    REGISTER_69,	                    /**@brief REGISTER 69 */
    REGISTER_70,	                    /**@brief REGISTER 70 */
    REGISTER_71,                        /**@brief REGISTER 71 */
    REGISTER_72,	                    /**@brief REGISTER 72 */
    REGISTER_73,	                    /**@brief REGISTER 73 */
    REGISTER_74,	                    /**@brief REGISTER 74 */
    REGISTER_75,	                    /**@brief REGISTER 75 */
    REGISTER_76,	                    /**@brief REGISTER 76 */
    REGISTER_77,	                    /**@brief REGISTER 77 */
    REGISTER_78,	                    /**@brief REGISTER 78 */
    REGISTER_79,	                    /**@brief REGISTER 79 */
    REGISTER_80,	                    /**@brief REGISTER 80 */
    REGISTER_81,                        /**@brief REGISTER 81 */
    REGISTER_82,	                    /**@brief REGISTER 82 */
    REGISTER_83,	                    /**@brief REGISTER 83 */
    REGISTER_84,	                    /**@brief REGISTER 84 */
    REGISTER_85,	                    /**@brief REGISTER 85 */
    REGISTER_86,	                    /**@brief REGISTER 86 */
    REGISTER_87,	                    /**@brief REGISTER 87 */
    REGISTER_88,	                    /**@brief REGISTER 88 */
    REGISTER_89,	                    /**@brief REGISTER 89 */
    REGISTER_90,                        /**@brief REGISTER 90 */
    REGISTER_91,                        /**@brief REGISTER 91 */
    REGISTER_92,	                    /**@brief REGISTER 92 */
    REGISTER_93,	                    /**@brief REGISTER 93 */
    REGISTER_94,	                    /**@brief REGISTER 94 */
    REGISTER_95,	                    /**@brief REGISTER 95 */
    REGISTER_96,	                    /**@brief REGISTER 96 */
    REGISTER_97,	                    /**@brief REGISTER 97 */
    REGISTER_98,	                    /**@brief REGISTER 98 */
    REGISTER_99,	                    /**@brief REGISTER 99 */
    REGISTER_100,	                    /**@brief REGISTER 100 */
	LENGTH_REG_ID                       /**@brief Number of registers */					            
};

#endif /* REGISTERTABLEDEF_H */