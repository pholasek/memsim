TEMPLATE = subdirs
SUBDIRS = memsimlib memsim-cli memsim-gui
CONFIG += ordered
memsim-cli.depends = memsimlib
# memsim-gui.depends = memsimlib
