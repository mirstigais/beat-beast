 #!/bin/bash

INPUT_VIDEO="$1"

if [ -z "$INPUT_VIDEO" ]; then
  echo "Missing input video file name"
  exit 1
fi

INPUT_VIDEO_NAME=${INPUT_VIDEO%.*}

mkdir -p converted_video

ffmpeg -y -i "$INPUT_VIDEO" -r 30 "converted_video/output_%05d.png"
for file in converted_video/*.png; do
  convert $file -resize 240x160! -colors 253 -unique-colors tmpPalette.bmp && convert black.bmp tmpPalette.bmp +append tmpPalette.bmp && convert $file -resize 240x160! -background black -gravity northwest -extent 256x256 -colors 253 -remap tmpPalette.bmp "$file" && rm tmpPalette.bmp
done
for file in converted_video/*.png; do
  output="${file%.png}.bmp"
  convert "$file" -define bmp:format=bmp3 -compress None -type Palette "$output"
done

rm converted_video/*.png

for bmp_file in converted_video/*.bmp; do
  base_name=$(basename "${bmp_file}" .bmp)
  json_file="converted_video/${base_name}.json"

  cat <<EOF > "$json_file"
{
  "type": "regular_bg"
}
EOF
done

echo "Generating .cpp and .h"
bash generateVideoCPP.sh "$INPUT_VIDEO_NAME" "converted_video/" "converted_video/${INPUT_VIDEO_NAME}.cpp"
