import socket
import time
from threading import Thread

def get_ip():
    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    try:
        # doesn't even have to be reachable
        s.connect(('10.255.255.255', 1))
        IP = s.getsockname()[0]
    except:
        IP = '127.0.0.1'
    finally:
        s.close()
    return IP

class wifi_socket():
    def __init__(self, recipient_address, port_server, port_client):

        #---- Connection variables ----#
        self.recipient_address = recipient_address
        self.PORT_SERVER = port_server
        self.PORT_CLIENT = port_client
        
        #---- FLAGS ----#
        self.CONN_ESTABLISHED = False

    def run_server(self):
        #Initializing the server
        self.sck = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.sck.bind((get_ip(), self.PORT_SERVER))
        print("Server created!\n")
        self.sck.listen(5)

        #Accepting connection from ESAT
        self.esat_client, address = self.sck.accept()
        print("Connection from " + str(address) + " established!\n")

        while True:
            data = self.esat_client.recv(1024)
            print(data.decode("ascii"))

    def run_client(self):
        self.sckc = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        print("Ok")
        self.sckc.connect((self.recipient_address, self.PORT_CLIENT))
        print("Connection to " + str(self.recipient_address) + " established!\n")
        self.CONN_ESTABLISHED = True


    def send(self,data: str):
        #Sending data only if the connection was established
        if self.CONN_ESTABLISHED:
            self.sckc.send(data.encode("ascii"))
        else:
            print("No connection established!\n")

    def start_server(self):
        self.t1 = Thread(target=self.run_server)
        self.t1.start()

    def start_client(self):
        self.t2 = Thread(target=self.run_client)
        self.t2.start()

sock = wifi_socket('192.168.1.63', 1234, 1235)
sock.start_server()
time.sleep(5)
sock.start_client()
time.sleep(3)
sock.send("ciao")