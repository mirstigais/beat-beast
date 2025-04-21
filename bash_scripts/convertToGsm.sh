 #!/bin/bash

INPUT_AUDIO="$1"

if [ -z "$INPUT_AUDIO" ]; then
  echo "Missing input audio file"
  exit 1
fi

mkdir -p converted_audio_gsm

INPUT_AUDIO_NAME=${INPUT_AUDIO%.*}
OUTPUT_AUDIO="converted_audio_gsm/${INPUT_AUDIO_NAME}.gsm"

ffmpeg -y -i $INPUT_AUDIO -ac 1 -af 'aresample=18157' -strict unofficial -c:a gsm $OUTPUT_AUDIO