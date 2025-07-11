#!/usr/bin/env python3

import random
import time
from noise import pnoise2, snoise3
from rich.console import Console
from rich.live import Live
from rich.text import Text


def generate_random_ascii(width: int, height: int, time_offset: float = 0.0) -> Text:
    """Generate a grid of ASCII characters using Perlin noise."""
    text = Text()
    # ASCII characters from most dense to least dense
    chars = "█▓▒░⌂☺☻♠♣♦♥◘○◙♂♀♪♫☼►◄↕‼¶§▬↨↑↓→←∟↔▲▼ "  # Dwarf Fortress-inspired characters

    for y in range(height):
        line = []
        for x in range(width):
            # Generate noise value (-1 to 1)
            noise_val = snoise3(
                x * 0.01,  # x coordinate
                y * 0.03,  # y coordinate
                time_offset * 0.001,  # z coordinate (time)
                3,  # octaves
            )

            # Normalize noise value to 0-1
            normalized = (noise_val + 1) / 2

            # Map to ASCII character
            char_index = int(normalized * (len(chars) - 1))
            line.append(chars[char_index])

        text.append("".join(line) + "\n")
    return text


def main():
    console = Console()

    # Fixed dimensions
    width = 80
    height = 40

    time_offset = 0.0

    with Live(console=console, refresh_per_second=32) as live:
        try:
            while True:
                # Generate new random ASCII art
                ascii_art = generate_random_ascii(width, height, time_offset)
                live.update(ascii_art)
                time_offset += 0.1  # Increment time for animation
        except KeyboardInterrupt:
            console.print("\n[bold red]Exiting...[/bold red]")


if __name__ == "__main__":
    main()
