# ASCII Layer Engine

A terminal-based, dynamic ASCII animation system written in C using `ncurses`.  
It features a modular layer stack architecture, blend modes, real-time animation, and math-driven visuals — all rendered with characters in your terminal.

---

## ✨ Features

- ✅ Real-time rendering with `ncurses`
- ✅ Dynamic layer stack (add/remove/customize layers)
- ✅ Blend modes: `REPLACE`, `ADD`, `MULTIPLY`, `MAX`
- ✅ Greyscale character mapping (customizable palette)
- ✅ Math-driven animation layer (`sin(x² + y² - t)`, etc.)
- ✅ Noise and gradient layers for base textures

---

## 🧱 Layer Types (So Far)

- `GradientLayer`: horizontal brightness ramp
- `NoiseLayer`: random sparkles or texture
- `MathLayer`: animated function visualization (e.g. ripple rings)
- Simple Shapes (SDF 2d)

---

## 🧰 Build

```bash
make
./ascii
```

---

## 📋 TODO

- Get aspect ratio fixed
- More layer types
- Animation system (parameters)
- Add interactive TUI for adding/removing layers
- Layer parameter adjustment (scale, speed, blend) at runtime
- Keybindings for toggling layers on/off
- Support terminal resizing
- Save/load composition

### Layers to make:

- Simplex / Perlin noise
- Warp incoming layer (FBM)
- Fire
- Fluid sim
- FBM layer (clouds)
- 3D model rasterizer
- Bytebeat visuals layer

