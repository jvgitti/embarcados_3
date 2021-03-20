/**
 * \file
 * \brief Configuration header file for I2CSpy
 *
 * This header file is used to configure settings the External I2C EEPROM module.
 */

#ifndef __Memoria_CONFIG_H
#define __Memoria_CONFIG_H

/* actual device */
#ifndef Memoria_CONFIG_DEVICE_ID
  #define Memoria_CONFIG_DEVICE_ID      8
    /*!< Supported Device IDs: 8 (24AA08, 24LC08), 16 (24AA16, 24LC16), 32 (24AA32, 24LC32), 256 (24AA256, 24LC256, 24FC256), 512 (24AA512, 24LC512, 24FC256) or 1025 (24AA1025, 24LC1025, 24FC1025) */
#endif

#ifndef Memoria_CONFIG_HAS_WP_PIN
  #define Memoria_CONFIG_HAS_WP_PIN      (0)
    /*!<< 1: Write Protect Pin available. 0: no Write Protect pin */
#endif

#ifndef Memoria_CONFIG_DEVICE_I2C_ADDRESS_BITS
  #define Memoria_CONFIG_DEVICE_I2C_ADDRESS_BITS   (0)
    /* Address bits for I2C address, usually formed by the A0, A1 and A3 pins. Admissible range: 0..7 */
#endif

#ifndef Memoria_CONFIG_BLOCK_BUF_SIZE
  #define Memoria_CONFIG_BLOCK_BUF_SIZE   (16)
    /*!< buffer used for block read/write. Max is 128. Keep it small to reduce stack consumption. */
#endif

#ifndef Memoria_CONFIG_DO_ACKNOWLEDGE_POLLING
  #define Memoria_CONFIG_DO_ACKNOWLEDGE_POLLING    (1)
    /*!< 1: Perform acknowledge polling in the driver. 0: no acknowledge polling */
#endif

#ifndef Memoria_CONFIG_PAGE_WRITE_TIME_MS
  #define Memoria_CONFIG_PAGE_WRITE_TIME_MS        (5)
    /*!< Page Write Time as per data sheet, used with Memoria_CONFIG_DO_ACKNOWLEDGE_POLLING */
#endif

#ifndef Memoria_CONFIG_ACK_POLLING_TIME_US
  #define Memoria_CONFIG_ACK_POLLING_TIME_US       (100)
    /*!< Acknowledge polling time in the I2C driver, used with Memoria_CONFIG_DO_ACKNOWLEDGE_POLLING  */
#endif

#ifndef Memoria_CONFIG_USE_TIMEOUT
  #define Memoria_CONFIG_USE_TIMEOUT               (0)
    /*!< 1: use timeout, 0: do not use timeout */
#endif

#ifndef Memoria_CONFIG_TIMEOUT_BYTE_MS
  #define Memoria_CONFIG_TIMEOUT_BYTE_MS           (10)
    /*!< number of milli seconds for timeout using byte write */
#endif

#ifndef Memoria_CONFIG_TIMEOUT_BLOCK_MS
  #define Memoria_CONFIG_TIMEOUT_BLOCK_MS          (60)
    /*!< number of milliseconds for timeout using for block write */
#endif

#endif /* __Memoria_CONFIG_H */
