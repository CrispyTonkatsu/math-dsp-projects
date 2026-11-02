#!/bin/sh
echo "Converting $1 to match format under file name $2"

ffmpeg -i $1 -ac 1 -ar 44100 -sample_fmt s16 -map_metadata -1 $2
