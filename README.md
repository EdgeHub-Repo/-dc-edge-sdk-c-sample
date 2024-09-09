# EdgeSync360 EdgeHub C SDK Example

This C application demonstrates the usage of dynamic library functions and handling of events in an embedded system context. It interfaces with a shared library `EdgeHubEdge.so.1.0.5`, sets up event handlers, and performs actions like configuration, status updates, and data sending.

## Overview

The application performs the following tasks:

1. Loads a shared library (`EdgeHubEdge.so.1.0.5`) at runtime.
2. Retrieves function pointers from the loaded library using `dlsym`.
3. Sets up event handlers for connection, disconnection, and message reception.
4. Configures options, device configurations, and device statuses.
5. Sends configuration data, device statuses, and edge data.
6. Cleans up allocated resources and closes the library.

## Compilation

To compile the `sample.c` file, use the provided `Makefile`. Follow these steps:

1. Ensure the shared library `EdgeHubEdge.so.1.0.5` is available in the same directory as the Makefile or in a directory specified by `LD_LIBRARY_PATH`.

2. Run `make` to build the project:

   ```sh
   make
   ```

   This will compile sample.c and link it with libdl, producing the executable sample.

## Makefile

The Makefile provides the following targets:

- all: Builds the project by running the openvpn and build targets.
- build: Compiles sample.c and links it with libdl to create the sample executable. Assumes EdgeHubEdge.so.1.0.5 is available.
- cJSON.o: Compiles cJSON.c into a position-independent object file cJSON.o.
- clean: Removes generated files and directories (sample, recover.db3, and ./sample.dSYM).
- test: Placeholder for any test-related commands.

## Usage

1.Ensure the shared library EdgeHubEdge.so.1.0.5 is available in the same directory as the executable or in a directory specified by LD_LIBRARY_PATH.

2. Run the compiled executable:
   ```sh
   ./sample
   ```

## Functions

- int nsleep(long milliseconds);: Suspends execution for a specified number of milliseconds.
- void edgeAgent_Connected();: Callback function called when the agent connects.
- void edgeAgent_Disconnected();: Callback function called when the agent disconnects.
- void edgeAgent_Receive(char *cmd, char *val);: Callback function called when a message is received.
- void loadLibraryFunctions(void \*handle);: Loads function pointers from the shared library.
- TOPTION_STRUCT setupOptions();: Sets up the options for the edge agent.
- TNODE_CONFIG_STRUCT setupConfig(int device_num, int analog_tag_num, int discrete_tag_num, int text_tag_num);: Sets up the device configuration.
- TEDGE_DEVICE_STATUS_STRUCT setupDeviceStatus(int device_num);: Sets up the device status.
- TEDGE_DATA_STRUCT setupData(int device_num, int analog_tag_num, int discrete_tag_num, int text_tag_num, int array_size);: Sets up the data to be sent.

## Dependencies

- EdgeHubEdge.so.1.0.5: Ensure this shared library is available and correctly linked.
- cJSON.c: The Makefile assumes that cJSON.c is available for compiling cJSON.o.

## Notes

- The application uses dynamic loading of library functions (dlopen and dlsym).
- The setupConfig, setupDeviceStatus, and setupData functions allocate memory dynamically. Ensure proper deallocation of these resources to avoid memory leaks.
- The nsleep function is used to introduce delays in the execution, which may be useful for timing-related operations.
