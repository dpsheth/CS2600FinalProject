#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <file_path>"
    exit 1
fi

file_path=$1

# Create main structure
mkdir -p "$file_path/north/north/south"
mkdir -p "$file_path/north/north/north/south"
mkdir -p "$file_path/north/north/north/north/south"
mkdir -p "$file_path/north/west/east"
mkdir -p "$file_path/north/west/south/north"
mkdir -p "$file_path/north/east/west"
mkdir -p "$file_path/north/east/east/west"
mkdir -p "$file_path/north/east/east/north/south"
mkdir -p "$file_path/north/east/east/east/west"
mkdir -p "$file_path/north/south"

# Create description.txt files
touch "$file_path/north/description.txt"
touch "$file_path/north/north/description.txt"
touch "$file_path/north/north/north/description.txt"
touch "$file_path/north/north/north/north/description.txt"
touch "$file_path/north/west/description.txt"
touch "$file_path/north/west/south/description.txt"
touch "$file_path/north/east/description.txt"
touch "$file_path/north/east/east/description.txt"
touch "$file_path/north/east/east/north/description.txt"
touch "$file_path/north/east/east/east/description.txt"


echo "An empty throne room." > "$file_path/north/description.txt"
echo "A hallway leading north." > "$file_path/north/north/description.txt"
echo "The hallway continues." > "$file_path/north/north/north/description.txt"
echo "The jester's room." > "$file_path/north/north/north/north/description.txt"
echo "An abandoned armory." > "$file_path/north/west/description.txt"
echo "Item found! Excalibur" > "$file_path/north/west/south/description.txt"
echo "A hall lined with tapestries." > "$file_path/north/east/description.txt"
echo "The royal court room." > "$file_path/north/east/east/description.txt"
echo "An old library. Pull a book?" > "$file_path/north/east/east/north/description.txt"
echo "A banquet hall." > "$file_path/north/east/east/east/description.txt" 

# Create soft links
ln -s "$file_path/north" "$file_path/north/north/south/back"
ln -s "$file_path/north/north" "$file_path/north/north/north/south/back"
ln -s "$file_path/north/north/north" "$file_path/north/north/north/north/south/back"
ln -s "$file_path/north" "$file_path/north/west/east/back"
ln -s "$file_path/north/west" "$file_path/north/west/south/north/back"
ln -s "$file_path/north" "$file_path/north/east/west/back"
ln -s "$file_path/north/east" "$file_path/north/east/east/west/back"
ln -s "$file_path/north/east/east" "$file_path/north/east/east/east/west/back"
ln -s "$file_path/north/east/east" "$file_path/north/east/east/north/south/back"
ln -s "$file_path" "$file_path/north/south/back"

echo "File structure created successfully!"
