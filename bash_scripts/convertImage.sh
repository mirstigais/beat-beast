 #!/bin/bash

INPUT_IMAGE="$1"

if [ -z "$INPUT_IMAGE" ]; then
  echo "Missing input image file name"
  exit 1
fi

mkdir -p converted_images

INPUT_IMAGE_NAME=${INPUT_IMAGE%.*}
OUTPUT_IMAGE="converted_images/${INPUT_IMAGE_NAME}.bmp"

if [ ! -f black.bmp ]; then
  convert -size 3x1 xc:black black.bmp
fi

# Step 1: Create palette
convert "$INPUT_IMAGE" -resize 240x160! -colors 253 -unique-colors tmpPalette.bmp

# Step 2: Combine black and palette
convert black.bmp tmpPalette.bmp +append tmpPalette.bmp

# Step 3: Resize and remap with palette
convert "$INPUT_IMAGE" -resize 240x160! -background black -gravity northwest -extent 256x256 -colors 253 -remap tmpPalette.bmp "$OUTPUT_IMAGE"

# Step 4: Convert to BMP3 format with palette
convert "$OUTPUT_IMAGE" -define bmp:format=bmp3 -compress None -type Palette "$OUTPUT_IMAGE"

# Cleanup
rm tmpPalette.bmp