# lib-avr

Device driver and libraries for Microchip (Atmel) AVR Series

## I2C interface (Master mode only)

**Files:**  
i2c/i2c.h  
i2c/i2c.c

**Functions:**  
int i2c\_master\_init(uint32\_t speed)  
int i2c\_master\_send(uint8\_t addr, uint8\_t *data, int len)  
int i2c\_master\_recv(uint8\_t addr, uint8\_t *data, int len)  
int i2c\_get\_error(void)

### NXP PCF8574(A) GPIO driver

**Files:**  
i2c/pcf8574.h  
i2c/pcf8574.c

**Functions:**  
gpio\_t *pcf8574\_init(int type, uint8\_t subaddr)  
void pcf8574\_free(gpio\_t *gpio)  
int pcf8574\_write(gpio\_t *gpio, uint8\_t data)  
int pcf8574\_read(gpio\_t *gpio, uint8\_t *data)  
int pcf8574\_set\_config(gpio\_t *gpio, int pin, int config)  
int pcf8574\_get\_config(gpio\_t *gpio, int pin, int *config)  
int pcf8574\_get\_npins(gpio\_t *gpio)  
int pcf8574\_set\_pin(gpio\_t *gpio, int pin, int value)  
int pcf8574\_get\_pin(gpio\_t *gpio, int pin, int *value)

## SPI interface (Master mode only)

**Files:**  
spi/spi.h  
spi/spi.c

**Functions:**  
int spi\_master\_init(int speed)  
int spi\_master\_send(uint8\_t *data, int len)  
int spi\_master\_recv(uint8\_t *data, int len)

### ENC28J60 ethernet controller driver (Alpha Version - No receive function)

**Files:**  
spi/enc28j60.h  
spi/enc28j60.c

**Functions:**  
void enc28j60\_init(int mode, mac\_addr\_t *addr)  
uint8\_t enc28j60\_get\_revision(void)  
void enc28j60\_set\_mac(mac\_addr\_t *addr)  
void enc28j60\_get\_mac(mac\_addr\_t *addr)  
int enc28j60\_link\_up(void)  
int enc28j60\_frame\_count(void)  
uint16\_t enc28j60\_free\_space(void)  
int enc28j60\_send(eth\_frame\_t *frame)

## Network libraries

### Ethernet definitions and helper functions

**Files:**  
net/ethernet.h  
net/ethernet.c

**Functions:**  
mac\_addr\_t *ethernet\_str\_to\_mac(const char *str)  
char *ethernet\_mac\_to\_str(mac\_addr\_t *mac)  
int ethernet\_frame\_set\_dst(eth\_frame\_t *frame, const char *addr)  
int ethernet\_frame\_get\_dst(eth\_frame\_t *frame, char **str)  
int ethernet\_frame\_set\_src(eth\_frame\_t *frame, const char *addr)  
int ethernet\_frame\_get\_src(eth\_frame_t *frame, char **str)  
int ethernet\_frame\_set\_type(eth\_frame\_t *frame, uint16\_t type)  
int ethernet\_frame\_get\_type(eth\_frame\_t *frame, uint16\_t *type)  
int ethernet\_frame\_set\_payload(eth\_frame\_t *frame, uint8\_t *buffer, int length)  
int ethernet\_frame\_get\_payload(eth\_frame\_t *frame, uint8\_t **buffer, int *length)  
int ethernet\_buffer\_to\_frame(uint8\_t *buffer, int length, eth\_frame\_t **frame)  
int ethernet\_frame\_to\_buffer(eth\_frame\_t *frame, uint8\_t **buffer, int *length)

### IPv4 definitions and helper functions

**Files:**  
net/ipv4.h  
net/ipv4.c

**Functions:**  
ipv4\_addr\_t *ipv4\_str\_to\_ip(const char *str)  
char *ipv4\_ip\_to\_str(ipv4\_addr\_t *ip)
