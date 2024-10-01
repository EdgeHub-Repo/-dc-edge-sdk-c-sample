# EdgeSync360 EdgeHub C SDK Example

## Overview

This project demonstrates a basic implementation of an edge agent using the EdgeSync360.EdgeHub.Edge.C.SDK. The edge agent connects to the IoT Hub, uploads device configurations, sends device status and data, and handles incoming messages. The project is implemented in C and utilizes CMake for building.

## Features

- Connect to Azure IoT Hub

- Upload device configurations

- Send device status

- Send data from devices

- Handle incoming commands and acknowledgments

## Requirements

- CMake 3.10 or higher

- C11 compatible C compiler

- Azure IoT Hub account

- Dynamic library `EdgeSync360.EdgeHub.Edge.C.SDK.1.0.2.dylib`

## Building the Project

1. **Clone the repository (if applicable):**

```bash
git clone https://github.com/EdgeHub-Repo/dc-edge-sdk-c-sample.git
cd dc-edge-sdk-c-sample
```

2. **Create a build directory:**

```bash
mkdir build
cd build
```

3. **Run CMake:**

```bash
cmake ..
```

4. **Build the project:**

```bash
make
```

5. **Run the executable:**

```bash
./bin/sample
```

## Code Explanation

### Main Functions

- **`main()`** : The entry point of the program where events are set, configurations are initialized, and the connection to Azure IoT Hub is established.

- **`edgeAgent_Connected()`** : Callback function for handling successful connections.

- **`edgeAgent_Disconnected()`** : Callback function for handling disconnections.

- **`edgeAgent_Receive(char *cmd, char *val)`** : Handles incoming messages and executes commands.

### Setup Functions

- **`setupOptions()`** : Initializes the connection options for the Azure IoT Hub.

- **`setupConfig(int device_num, int analog_tag_num, int discrete_tag_num, int text_tag_num)`** : Configures the devices with specified numbers of tags.

- **`setupDeviceStatus(int device_num)`** : Sets up the initial device status.

- **`setupData(int device_num, int analog_tag_num, int discrete_tag_num, int text_tag_num, int array_size)`** : Prepares the data to be sent to the IoT Hub.

### Sleep Function

- **`nsleep(long milliseconds)`** : A utility function for sleeping for a specified number of milliseconds.

## Cleanup

Ensure to properly free allocated memory and handle resource cleanup. The project includes cleanup logic at the end of the `main()` function.
