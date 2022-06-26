import socket
import os
import subprocess

SEP = "<SEPERATE>"
BUFFER_SIZE = 4096
server_ip = "192.168.56.104"
port = 8888
while True:
    command = "ls"
    output = subprocess.run(command)
    print(output)
    filename = input("\nPlease enter which file to send: ")
    filesize = os.path.getsize(filename)
    con = input(f"Choosen file: {filename}\nConfirm (Y/N)?")
    if con == "Y" or con == "y":
        break;
s = socket.socket()
print(f"Connecting to {server_ip}:{port}")
try:
    s.connect((server_ip,port))
    print("Connected.")
    print(f"Sending:\nFile: {filename}")
    s.send(f"{filename}".encode())
    print(f"Size: {filesize} bytes")
    s.send(f"{filesize}".encode())
    with open(filename, "rb") as f:
        while True:
            bytes_read = f.read(BUFFER_SIZE)
            if not (bytes_read):
                break
            s.sendall(bytes_read)
    print("Sending Successful")
except:
    print("Connection Failed. Terminating Program")
s.close()
