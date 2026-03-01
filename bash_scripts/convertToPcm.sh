 #!/bin/bash

INPUT_AUDIO="$1"

if [ -z "$INPUT_AUDIO" ]; then
  echo "Missing input audio file"
  exit 1
fi

mkdir -p converted_audio_pcm

INPUT_AUDIO_NAME=${INPUT_AUDIO%.*}
OUTPUT_AUDIO="converted_audio_pcm/${INPUT_AUDIO_NAME}.pcm"

ffmpeg -y -i $INPUT_AUDIO -ar 36314 -af "aresample=dither_method=triangular_hp" -f s8 -acodec pcm_s8 $OUTPUT_AUDIO