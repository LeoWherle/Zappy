""" A class for managing subprocesses and capturing their output. """

import subprocess
import threading
import queue
from typing import List

class ProcessManager:
    """
    A class for managing subprocesses and capturing their output.
    """

    def __init__(self, command: List[str]):
        """
        Initialize the ProcessManager.

        Args:
            command (List[str]): The command to be executed as a subprocess.
        """
        self.command: List[str] = command[1:]
        self.process: subprocess.Popen | None = None
        self.stdout_queue: queue.Queue[str] = queue.Queue()
        self.stderr_queue: queue.Queue[str] = queue.Queue()
        self.cwd: str = command[0]

    def start_process(self) -> None:
        """
        Start the subprocess and capture its output.
        """
        def target() -> None:
            try:
                self.process = subprocess.Popen(
                    self.command,
                    stdout=subprocess.PIPE,
                    stderr=subprocess.PIPE,
                    stdin=subprocess.PIPE,
                    text=True,
                    bufsize=0,  # No buffering for more immediate output
                    universal_newlines=True,  # Ensure text mode
                    cwd=self.cwd
                )

                # Continuously read and queue stdout/stderr
                for line in iter(self.process.stdout.readline, ''):
                    self.stdout_queue.put(line)
                for line in iter(self.process.stderr.readline, ''):
                    self.stderr_queue.put(line)

            except FileNotFoundError:
                self.stdout_queue.put("Error: Command not found\n")
            except Exception as e:
                self.stdout_queue.put(f"Error: An exception occurred: {e}\n")

        thread = threading.Thread(target=target)
        thread.start()

    def get_output(self) -> str:
        """
        Get the captured output from stdout.

        Returns:
            str: The captured output.
        """
        output = ""
        while not self.stdout_queue.empty():
            output += self.stdout_queue.get()
        return output

    def get_errors(self) -> str:
        """
        Get the captured output from stderr.

        Returns:
            str: The captured errors.
        """
        errors = ""
        while not self.stderr_queue.empty():
            errors += self.stderr_queue.get()
        return errors

    def write_to_stdin(self, input_data: str) -> None:
        """
        Write data to the stdin of the subprocess.

        Args:
            input_data (str): The data to be written.
        """
        if self.process:
            self.process.stdin.write(input_data)
            self.process.stdin.flush()

    def stop_process(self) -> None:
        """
        Terminate the subprocess.
        """
        if self.process:
            self.process.terminate()
            self.process.wait()

    def is_running(self) -> bool:
        """
        Check if the subprocess is running.

        Returns:
            bool: True if the subprocess is running, False otherwise.
        """
        return self.process and self.process.poll() is None
