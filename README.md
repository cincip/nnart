# 🌈 neural art go brrr
A tiny C script that generates cool neural net random art.

### what is this?
it’s a CPPN (Compositional Pattern Producing Network)(Apparently, I don't actually know if this is true, I am too lazy to check, I generated readme using gemini), it basically does this for every single pixel:
1. "yo math, here is a coordinate (x, y) and the current time." <- AAHHAHAHAH, shoutout gemini
2. the neural net does some random math $(\tanh, \sin, \text{etc.})$
3. it spits out an RGB value.
4. we paint the pixel.

since neural nets are basically just big continuous functions, the output looks like organic trippy soup instead of random noise.

### Demos
If you don't want to compile this right now, check out the `demos/` folder. It has a few recordings of what this thing actually spits out. 

![Sample Demo](demos/demo_1.mp4) 

### how to run
1. check if you have `gcc` and `ffmpeg`.
2. **Make sure you have a video player** like `mpv` or `vlc` installed, otherwise the script will finish but nothing will pop up.
3. run the magic script:
   ```bash
   chmod +x run.sh
   ./run.sh
   ```

### inspiration
I don't really have much to say to be honest, so here are random videos that made me think of this:
* [coding a machine learning library in c from scratch](https://www.youtube.com/watch?v=hL_n_GljC0I) by [Magicalbat](https://github.com/Magicalbat).
* [Implementing Scientific Paper in C](https://www.youtube.com/watch?v=3D_h2RE0o0E) by [Tsoding Daily](https://github.com/tsoding).
