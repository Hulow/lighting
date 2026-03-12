# install prerequises


# step 2: get esp-idf
clone the repo

# Set up the Tools
in esp-idf directory:
 - ./install.sh esp32
 - . ./export.sh (activating esp-idf)

# Set up the Environment Variables

in esp-idf directory: . $HOME/esp/esp-idf/export.sh

in lighting repo: source esp-idf/export.sh

create main/main.c
CMakeLists.txt in root directory and in main

execute idf.py build in main directory

idf.py flash