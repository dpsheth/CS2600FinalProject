#!/bin/bash

# Check if an argument is provided
if [ $# -ne 1 ]; then
  echo "Usage: $0 <file_path>"
  exit 1
fi

filepath=$1

# Create directory structure
mkdir -p "$filepath/north/east/west" "$filepath/north/east/east/west" "$filepath/north/east/east/north/south" \
         "$filepath/north/east/east/north/east/west" \
         "$filepath/north/east/south/south/east/west" "$filepath/north/east/south/south/east/east/west" \
         "$filepath/north/east/south/north" "$filepath/north/east/south/south/north" \
         "$filepath/north/east/south/south/east/east/east/west" "$filepath/north/south"

# Create description.txt files
echo "The forest entrance..." > "$filepath/north/description.txt"
echo "A clearing surrounded by fog." > "$filepath/north/east/description.txt"
echo "A fairy ring is beside you." > "$filepath/north/east/east/description.txt"
echo "You hear strange sounds east." > "$filepath/north/east/east/north/description.txt"
echo "A portal to the north!" > "$filepath/north/east/east/north/east/description.txt"
echo "A witch's hut." > "$filepath/north/east/south/description.txt"
echo "A mountain blocks your path." > "$filepath/north/east/south/south/description.txt"
echo "An old graveyard." > "$filepath/north/east/south/south/east/description.txt"
echo "A lush clearing." > "$filepath/north/east/south/south/east/east/description.txt"
echo "Item found! Red Cap Mushroom" > "$filepath/north/east/south/south/east/east/east/description.txt"

# Create soft links

ln -s "$filepath/north" "$filepath/north/east/west/back"
ln -s "$filepath/north/east" "$filepath/north/east/east/west/back"
ln -s "$filepath/north/east/east" "$filepath/north/east/east/north/south/back"
ln -s "$filepath/north/east/east/north" "$filepath/north/east/east/north/east/west/back"
ln -s "$filepath/north/east" "$filepath/north/east/south/north/back"
ln -s "$filepath/north/east/south" "$filepath/north/east/south/south/north/back"
ln -s "$filepath/north/east/south/south" "$filepath/north/east/south/south/east/west/back"
ln -s "$filepath/north/east/south/south/east" "$filepath/north/east/south/south/east/east/west/back"
ln -s "$filepath/north/east/south/south/east/east" "$filepath/north/east/south/south/east/east/east/west/back"
ln -s "$filepath" "$filepath/north/south/back"

echo "File structure created successfully!"
