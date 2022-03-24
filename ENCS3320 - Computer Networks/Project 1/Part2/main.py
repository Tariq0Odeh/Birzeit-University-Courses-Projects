# project done by:
# Tariq Odeh (1190699)
# Qays Safa (1190880)
# Mahmoud Samara (1191602)

import time
from socket import *

print("--------------------------------------------------------------------------")
print("\t\t\t\t\t\t{Welcome to our program}")
print("\n\t\t{This program get HTTP response from a specific webserver}")

while True:
  print("--------------------------------------------------------------------------")
  print("Menu")
  print("1- to get HTTP response from a specific webserver")
  print("2- to exit")

  x = int(input("\nPlease Enter 1 or 2 form menu:"))

  if(x == 1):
    url = input("\nPlease Enter the url like this formula (www.WebsiteName.com) :")
    NameOFServer = url
    PortOfServer = 80

    clinetSoket = socket(AF_INET, SOCK_STREAM)  # Create a socket object

    clinetSoket.connect((NameOFServer, PortOfServer))  # Connect the client
    StartTime = time.time()  # Time when send requst

    clinetSoket.send("HEAD / HTTP/1.1 \r\n".encode())  # Send some data
    clinetSoket.send(("Hostname:" + url + " \r\n\r\n").encode())

    modifiedSentence = clinetSoket.recv(1024)  # receive some data

    EndTime = time.time()  # Time when recive response

    print("From server:", modifiedSentence.decode())  # Display the response

    ElapsedTime = EndTime - StartTime  # Response time
    print(f"Elapsed time = {ElapsedTime * 1000} ms ")  # Display the response time

    clinetSoket.close()

  elif(x == 2):
    break
