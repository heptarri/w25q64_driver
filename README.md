# W25Q64 Driver for ESP-IDF

## Introduction

The W25Q64 is a 64M-bit (8M-byte) serial flash memory that provides a storage solution for systems with limited space, pins, and power. It is commonly used in embedded systems for data storage due to its high performance and reliability.

This project provides a driver for interfacing the W25Q64 flash memory with the ESP32 using the ESP-IDF framework. The driver handles the communication between the ESP32 and the W25Q64, allowing for operations such as reading, writing, and erasing data.

### Directory Layout

- `main/`: Contains the main application code that demonstrates the usage of the W25Q64 driver.
- `components/`: Contains the components code.
  - `w25q64/`: The upper-level driver implementation for the W25Q64 flash memory.
    - `include/`: Header files for the driver.
    - `src/`: Source files for the driver.
  - `spi_basic/`: The underlying driver of SPI.
    - `include/`: Header files for the driver.
    - `src/`: Source files for the driver.



### Getting Started

1. **Setup ESP-IDF**: Follow the [ESP-IDF setup guide](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/get-started/index.html) to configure your development environment.
2. **Clone the Repository**: Clone this repository to your local machine.
3. **Build the Project**: Navigate to the project directory and run `idf.py build` to build the project.
4. **Flash the Project**: Use `idf.py flash` to upload the firmware to your ESP32 board.
5. **Monitor the Output**: Use `idf.py monitor` to view the output from the ESP32.

6. Looking for the main application which demonstrates basic operations with the W25Q64 flash memory. Refer to the code in the `main/` directory for examples on how to use the driver.

### API Introduction




### Contributing

Contributions are welcome! Please open an issue or submit a pull request with your changes.

### Acknowledgments

Special thanks to the Espressif's ESP-IDF library.
