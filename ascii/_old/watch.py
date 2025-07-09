import subprocess
from watchdog.observers import Observer
from watchdog.events import FileSystemEventHandler
import time
import os
import signal

SCRIPT_TO_RUN = "ascii_art.py"
current_process = None


class ReloadHandler(FileSystemEventHandler):
    def on_modified(self, event):
        global current_process
        if event.src_path.endswith(SCRIPT_TO_RUN):
            if current_process:
                print("🛑 Stopping previous run...")
                current_process.send_signal(signal.SIGINT)  # Ctrl+C equivalent
                try:
                    current_process.wait(timeout=1)
                except subprocess.TimeoutExpired:
                    current_process.kill()

            os.system("clear")
            print(f"🔁 Detected change in {SCRIPT_TO_RUN}, restarting...\n")
            current_process = subprocess.Popen(["python", SCRIPT_TO_RUN])


if __name__ == "__main__":
    path = "."
    event_handler = ReloadHandler()
    observer = Observer()
    observer.schedule(event_handler, path=path, recursive=False)
    observer.start()
    print(f"👀 Watching {SCRIPT_TO_RUN} for changes...\n")
    try:
        while True:
            time.sleep(1)
    except KeyboardInterrupt:
        if current_process:
            current_process.terminate()
        observer.stop()
    observer.join()
