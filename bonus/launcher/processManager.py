import subprocess
import threading
import queue

class ProcessManager:
    def __init__(self, command):
        self.command = command[1:]
        self.process = None
        self.stdout_queue = queue.Queue()
        self.stderr_queue = queue.Queue()
        self.cwd = command[0]
        
    def start_process(self):
        def target():
            try:
                self.process = subprocess.Popen(
                    self.command, stdout=subprocess.PIPE, stderr=subprocess.PIPE, stdin=subprocess.PIPE, text=True, bufsize=1, cwd=self.cwd
                )
                for line in self.process.stdout:
                    self.stdout_queue.put(line)
                self.process.stdout.close()
                for line in self.process.stderr:
                    self.stderr_queue.put(line)
                self.process.stderr.close()
            except FileNotFoundError:
                self.stdout_queue.put("Error: Command not found\n")
            except Exception as e:
                self.stdout_queue.put(f"Error: An exception occurred: {e}\n")

        thread = threading.Thread(target=target)
        thread.start()

    def get_output(self):
        # Fetch output from stdout
        output = ""
        while not self.stdout_queue.empty():
            output += self.stdout_queue.get()
        return output

    def get_errors(self):
        # Fetch output from stderr
        errors = ""
        while not self.stderr_queue.empty():
            errors += self.stderr_queue.get()
        return errors
    
    def write_to_stdin(self, input_data):
        if self.process:
            self.process.stdin.write(input_data)
            self.process.stdin.flush()
    
    def stop_process(self):
        if self.process:
            self.process.terminate()
            self.process.wait()

    def is_running(self):
        return self.process and self.process.poll() is None
