
#include <AP_HAL.h>
#if CONFIG_HAL_BOARD == HAL_BOARD_REVOMINI

#include <AP_HAL_REVOMINI.h>
#include "AP_HAL_REVOMINI_Namespace.h"
#include "HAL_REVOMINI_Class.h"
#include "AP_HAL_REVOMINI_Private.h"
#include "Util.h"
#include <AP_HAL_Empty.h>
#include <AP_HAL_Empty_Private.h>
#include <pwm_in.h>
#include <usart.h>
#include <i2c.h>

using namespace REVOMINI;

//_USART1 PIN 3 AND 4 OF THE INPUT RAIL
//_USART2 INTERNAL SERIAL PORT
//_USART3 PIN 1 AND 2 OF THE INPUT RAIL


// XXX make sure these are assigned correctly
static REVOMINIUARTDriver uartADriver(_USART1,1);
static REVOMINIUARTDriver uartBDriver(_USART3,0);
static REVOMINIUARTDriver uartCDriver(_USART2,0);
static REVOMINISemaphore  i2cSemaphore;
//static REVOMINISemaphore  i2c2Semaphore;
static REVOMINII2CDriver  i2cDriver(_I2C1,&i2cSemaphore);
//static REVOMINII2CDriver  i2c2Driver(_I2C1,&i2c2Semaphore);
static REVOMINISPIDeviceManager spiDeviceManager;
static REVOMINIAnalogIn analogIn;
static REVOMINIStorage storageDriver;
static REVOMINIGPIO gpioDriver;
static REVOMINIRCInput rcinDriver;
static REVOMINIRCOutput rcoutDriver;
static REVOMINIScheduler schedulerInstance;
static REVOMINIUtil utilInstance;



HAL_REVOMINI::HAL_REVOMINI() :
    AP_HAL::HAL(
      &uartADriver,
      &uartBDriver,
      &uartCDriver,
      &i2cDriver,
//      &i2c2Driver,
      &spiDeviceManager,
      &analogIn,
      &storageDriver,
      &uartADriver,
      &gpioDriver,
      &rcinDriver,
      &rcoutDriver,
      &schedulerInstance,
      &utilInstance
	  )
{}

void HAL_REVOMINI::init(int argc,char* const argv[]) const
{
  /* initialize all drivers and private members here.
   * up to the programmer to do this in the correct order.
   * Scheduler should likely come first. */
  //delay_us(2000000);

  scheduler->init(NULL);
  //uartA->begin(115200);

  uartA->begin(57600);

  //_member->init();
  i2c->begin();
  //hal.i2c2->begin();
  spi->init(NULL);
  storage->init(NULL);
  rcin->init(NULL);

  rcout->init((void *)&_is_ppmsum);

}

const HAL_REVOMINI AP_HAL_REVOMINI;

#endif
