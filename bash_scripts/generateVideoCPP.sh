#!/bin/bash

FILE_NAME="$1"
FRAME_PATH="$2"
OUT_FILE="$3"

if [ -z "$FILE_NAME" ] || [ -z "$FRAME_PATH" ] || [ -z "$OUT_FILE" ]; then
    echo "Usage: $0 <file_name> <frame_path> <out_file>"
    exit 1
fi

OUT_HEADER="$(dirname "$OUT_FILE")/$FILE_NAME.h"

# --- Generate .cpp file ---
# Get list of .bmp files, sorted by filename
FRAME_FILES=($(find "$FRAME_PATH" -maxdepth 1 -type f -name '*.bmp' | sort))
NUM_FRAMES=${#FRAME_FILES[@]}

# Write headers
{
  echo "#include \"$FILE_NAME\""
  echo ''
  echo '#include "bn_array.h"'
  echo ''
  for bmp_file in "${FRAME_FILES[@]}"; do
    frame_num=$(basename "$bmp_file" | sed -E 's/[^0-9]*([0-9]+)\.bmp/\1/')
    frame_num=$((10#$frame_num))
		printf '#include "bn_regular_bg_items_output_%05d.h"\n' "$frame_num"
  done
  echo ''
  echo "const bn::array<bn::regular_bg_item, $NUM_FRAMES> frames = {"
} > "$OUT_FILE"

# Write frame array
for index in "${!FRAME_FILES[@]}"; do
  bmp_file="${FRAME_FILES[$index]}"
  frame_num=$(basename "$bmp_file" | sed -E 's/[^0-9]*([0-9]+)\.bmp/\1/')
	frame_num=$((10#$frame_num))
  if [ "$index" -eq "$((NUM_FRAMES - 1))" ]; then
    printf '    bn::regular_bg_items::output_%05d\n' "$frame_num" >> "$OUT_FILE"
  else
    printf '    bn::regular_bg_items::output_%05d,\n' "$frame_num" >> "$OUT_FILE"
  fi
done

# End array and function
cat <<EOF >> "$OUT_FILE"
};

bn::regular_bg_item StartVideo::getFrame(unsigned frame) {
  return frames[frame];
}
EOF

# --- Generate .h file ---
GUARD_NAME=$(echo "$FILE_NAME" | tr '[:lower:]' '[:upper:]' | tr '.' '_' | tr '-' '_')

cat <<EOF > "$OUT_HEADER"
#ifndef $GUARD_NAME
#define $GUARD_NAME

#include "bn_regular_bg_item.h"

namespace StartVideo {

bn::regular_bg_item getFrame(unsigned frame);

}

#endif
EOF