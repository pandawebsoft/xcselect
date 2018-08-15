#!/bin/sh

TOOLS_DIRECTORY="$(cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd)"
PARENT_DIRECTORY="$(dirname $TOOLS_DIRECTORY)"
COMMAND_PATH=$PARENT_DIRECTORY/bin/xcselect
GREEN='\033[0;32m'
CLEARCOLOR='\033[0m'

main() {
    if ! which xcselect > /dev/null; then
        IS_UPDATE=0
        echo "Installing xcselect..."
        install
    else
        IS_UPDATE=1
        echo "Updating xcselect..."
        rm -f /usr/local/bin/xcselect
        install
    fi
    if [ $IS_UPDATE == 1 ]; then
        echo "${GREEN}xcselect has been updated.${CLEARCOLOR}"
    else
        echo "${GREEN}xcselect has been installed.${CLEARCOLOR}"
    fi
    if which xcselect > /dev/null; then
        echo "version: $(xcselect --version)\n"
    fi
}

install() {
    cp -f $COMMAND_PATH /usr/local/bin
}

main
