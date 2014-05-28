# MemSim - Memory hierarchy simulator

## Components

- library: memsimlib.so
- cli: memsim-cli
- gui: memsim-gui

### Library

library interface is exported via MemSimulationObj class

### CLI
`make run-cli`

commands:
- `load <path>` - load trace with given path
- `run <id>` - run simulation of trace with id
- `add <dev>` - add device
- `remove <dev>` - remove device
- `config <dev> <param> <val>` - config device
- `show traces` - show all loaded traces
- `show devices` - show configured devices
- `show statsall` - show stats of all devices

### GUI
`make run-gui`

## Use

`memsim> add l1_i`
`memsim> add l1_d`
`memsim> add l2`
`memsim> add swap`
`memsim> show devices`
`memsim> load test/trace2`
`memsim> run 0`
`memsim> show statsall`
`memsim> ^D`
`$`

## Docs

`$ make docs`

doxygen package is required.

documentation related to model validation and testing is situated in `src/testing/`
