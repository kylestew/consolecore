# Obra - Interactive Terminal Music Tracker

Obra is an interactive terminal-based music tracker focused on sample playback and step sequencing. Built with C, it provides a real-time pattern editor with support for multiple tracks and WAV sample playback.

## Features

- **16-step pattern sequencer** with up to 8 tracks
- **Real-time sample playback** using PortAudio
- **WAV file support** (mono files only) via dr_wav
- **Interactive ncurses UI** with keyboard navigation
- **BPM control** with real-time tempo adjustment
- **Visual step highlighting** showing current playback position

## Controls

- **hjkl** or **Arrow keys** - Navigate between tracks and steps
- **Enter** - Toggle step on/off
- **Space** - Start/stop playback
- **+/-** - Increase/decrease BPM (5 BPM increments)
- **q** - Quit the application

## Building

### Prerequisites

You'll need the following dependencies:

#### macOS
```bash
brew install portaudio ncurses
```

#### Ubuntu/Debian
```bash
sudo apt-get install libportaudio2 libportaudio-dev libncurses5-dev libncursesw5-dev
```

#### Manual dr_wav Installation
Since dr_wav is header-only, you can download it manually:
```bash
wget https://raw.githubusercontent.com/mackron/dr_libs/master/dr_wav.h
```

### Compilation

```bash
make
```

Or install dependencies and build:
```bash
make install-deps  # macOS
make install-deps-ubuntu  # Ubuntu/Debian
make
```

## Usage

```bash
./obra <sample1.wav> [sample2.wav] [sample3.wav] ...
```

### Example

```bash
./obra samples/kick.wav samples/snare.wav samples/hihat.wav
```

## Project Structure

```
Obra/
├── main.c          # Main entry point and application loop
├── ui.c            # ncurses-based user interface
├── ui.h            # UI function declarations and structures
├── audio.c         # PortAudio integration and sample playback
├── audio.h         # Audio function declarations
├── engine.c        # Pattern sequencing and timing logic
├── engine.h        # Engine function declarations
├── Makefile        # Build configuration
└── README.md       # This file
```

## Architecture

The application is built with a modular architecture:

- **UI Module** (`ui.c/ui.h`): Handles all ncurses-based user interface, keyboard input, and visual rendering
- **Audio Module** (`audio.c/audio.h`): Manages PortAudio stream, sample loading via dr_wav, and real-time audio mixing
- **Engine Module** (`engine.c/engine.h`): Controls pattern sequencing, timing, and step triggering
- **Main** (`main.c`): Orchestrates the application loop and coordinates between modules

## Technical Details

- **Sample Rate**: 44.1 kHz
- **Audio Format**: 32-bit float, mono
- **Buffer Size**: 256 frames
- **Pattern Length**: 16 steps
- **Max Tracks**: 8
- **Max Sample Length**: 10 seconds
- **BPM Range**: 60-200 BPM

## Creating Sample Files

Obra supports mono WAV files. You can create sample files using any audio editor that exports WAV format. For best results:

- Use 44.1 kHz sample rate
- Export as mono (single channel)
- Keep samples under 10 seconds
- Use 16-bit or 24-bit PCM format

## Troubleshooting

### Audio Issues
- Ensure your system's audio output is working
- Check that PortAudio is properly installed
- Verify WAV files are mono format

### Build Issues
- Make sure all dependencies are installed
- On some systems, you may need to install development headers
- For dr_wav issues, try downloading the header file manually

### Runtime Issues
- Ensure your terminal supports ncurses
- Check that WAV files exist and are readable
- Verify file permissions

## License

This project is open source. Feel free to modify and distribute according to your needs.

## Contributing

Contributions are welcome! Please feel free to submit issues, feature requests, or pull requests.
