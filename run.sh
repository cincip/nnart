#!/bin/bash

OUT_DIR="output"
FRAME_DIR="frames"
TIMESTAMP=$(date +%Y%m%d_%H%M%S)
VIDEO_OUT="$OUT_DIR/art_$TIMESTAMP.mp4"

mkdir -p $OUT_DIR
mkdir -p $FRAME_DIR
rm -f $FRAME_DIR/*.ppm

echo "Compiling..."
gcc -O3 main.c -o art_gen -lm

echo "Generating frames..."
./art_gen

echo -e "\nEncoding..."
ffmpeg -y -hide_banner -loglevel error \
       -framerate 30 -i "$FRAME_DIR/%04d.ppm" \
       -c:v libx264 -pix_fmt yuv420p -crf 18 \
       "$VIDEO_OUT"

echo "Video saved to $VIDEO_OUT"

if command -v mpv &> /dev/null; then
    mpv --loop "$VIDEO_OUT"
fi
