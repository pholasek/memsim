# MemSim - Memory hierarchy simulator

## Components

	- library: memsimlib.so
	- cli: memsim-cli
	- gui: memsim-gui

### Library

	library interface is exported via MemSimulationObj class

### CLI

	commands:
		- `load <path>` - load trace with given path
		- `run <id>` - run simulation of trace with id
		- `show traces` - show all loaded traces
		- `show devices` - show configured devices
		- `show statsall` - show stats of all devices

## Use

Example: `$ make && make run-cli`
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

doxygen package is required.

generating docs: `$ make docs`
