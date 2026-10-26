# libPowerTuner

PowerTuner client and daemon shared library.  
This is the library you can use in your own client implementation.

### Structure

**[Feature.h](src/enums/Feature.h)**: enum of implemented features in daemon.

**[DeviceData.h](src/DeviceData.h)**: structure your client fills and send to daemon, not all fields must be filled, data to set only.

**[YamlKeys.h](src/YamlKeys.h)**: collection of all yaml key static strings.

### Usage

The daemon will output a yaml string serialized in this library, a client can either deserialize it in this library or parse it itself.