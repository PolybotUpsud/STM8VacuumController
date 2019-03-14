void uart_init();
uint8_t uart_read();
bool uart_read_available();
uint8_t uart_read_nonblocking();
void uart_write(uint8_t data);
void uart_writes(const char *str);
bool uart_write_available();
void uart_write_nonblocking(uint8_t data);