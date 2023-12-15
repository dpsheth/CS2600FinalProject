#!/bin/bash

# Check if an argument is provided
if [ $# -ne 1 ]; then
  echo "Usage: $0 <file_path>"
  exit 1
fi

filepath=$1

# Create directory structure
mkdir -p "$filepath/north/east/west"\
         "$filepath/north/east/south/north" \
         "$filepath/north/east/south/south/north" \
         "$filepath/north/east/south/south/west" \
         "$filepath/north/east/south/south/east" "$filepath/north/east/south/south/west/east"\
         "$filepath/north/east/south/south/east/west" \
         "$filepath/north/east/south/south/east/east/west" \
         "$filepath/north/east/south/south/east/east/east/west" \
         "$filepath/north/east/south/south/east/east/north/south" \
         "$filepath/north/east/south/south/east/east/north/north/south" \
         "$file_path/north/south" \


# Create description.txt files
echo "Crisis city looms ahead." > "$filepath/north/description.txt"
echo "The whole city's on fire!" > "$filepath/north/east/description.txt"
echo "You walk through the broken city." > "$filepath/north/east/south/description.txt"
echo "The buildings are on fire." > "$filepath/north/east/south/south/description.txt"
echo "Item found! Phantom Ruby" > "$filepath/north/east/south/south/west/description.txt"
echo "You are on a broken road." > "$filepath/north/east/south/south/east/description.txt"
echo "Creatures come out of the ground." > "$filepath/north/east/south/south/east/east/description.txt"
echo "You feel the depths of the fire." > "$filepath/north/east/south/south/east/east/north/description.txt"
echo "Solaris is gone. Move on?" > "$filepath/north/east/south/south/east/east/north/north/description.txt"
echo "A tornado is carrying a car!" > "$filepath/north/east/south/south/east/east/east/description.txt"

ln -s "$filepath/north" "$filepath/north/east/west/back"
ln -s "$filepath/north/east" "$filepath/north/east/south/north/back"
ln -s "$filepath/north/east/south" "$filepath/north/east/south/south/north/back"
ln -s "$filepath/north/east/south/south" "$filepath/north/east/south/south/west/east/back"
ln -s "$filepath/north/east/south/south" "$filepath/north/east/south/south/east/west/back"
ln -s "$filepath/north/east/south/south/east" "$filepath/north/east/south/south/east/east/west/back"
ln -s "$filepath/north/east/south/south/east/east" "$filepath/north/east/south/south/east/east/east/west/back"
ln -s "$filepath/north/east/south/south/east/east" "$filepath/north/east/south/south/east/east/north/south/back"
ln -s "$filepath/north/east/south/south/east/east/north" "$filepath/north/east/south/south/east/east/north/north/south/back"
ln -s "$file_path” “$file_path/north/south/back"

echo "File structure created successfully!"
