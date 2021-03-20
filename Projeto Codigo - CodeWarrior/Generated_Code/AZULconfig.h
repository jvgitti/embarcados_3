#ifndef __AZUL_CONFIG_H
#define __AZUL_CONFIG_H

#ifndef AZUL_CONFIG_USE_GPIO_PIN
  #define AZUL_CONFIG_USE_GPIO_PIN   (1)
    /*!< 1: use GPIO pin; 0: use PWM pin */
#endif

#ifndef AZUL_CONFIG_IS_LOW_ACTIVE
  #define AZUL_CONFIG_IS_LOW_ACTIVE   (1)
    /*!< 1: LED is low active (cathode on port side), 0: LED is HIGH active (anode on port side) */
#endif

#endif /* __AZUL_CONFIG_H */
