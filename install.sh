#!/bin/bash

set -e  # Exit on any error

# Colors for status messages
GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m' # No color

# Check if cmake is installed
if ! command -v cmake &> /dev/null; then
    echo -e "${RED}Error: cmake is not installed.${NC}"
    exit 1
fi

# Install dependencies
echo -e "${GREEN}Installing ncurses...${NC}"
sudo apt install libncurses-dev -y

# Create build directory
echo -e "${GREEN}Creating build directory...${NC}"
mkdir -p build
cd build || { echo -e "${RED}Failed to enter build directory.${NC}"; exit 1; }

# Configure and build
echo -e "${GREEN}Running cmake and make...${NC}"
cmake ..
make

# Move binary to /usr/local/bin
echo -e "${GREEN}Installing binary to /usr/local/bin...${NC}"
sudo mv mano /usr/local/bin/mano

echo -e "${GREEN}Installation complete. You can now run 'mano' from anywhere.${NC}"

