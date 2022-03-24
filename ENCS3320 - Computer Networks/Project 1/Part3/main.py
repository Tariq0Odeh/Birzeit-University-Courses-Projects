# project done by:
# Tariq Odeh (1190699)
# Qays Safa (1190880)
# Mahmoud Samara (1191602)

from socket import *                                                               # Include Python’s socket library.

items = []                                                                         # Intialise an array to put all items in it.
PORT = 6500                                                                        # Listening on port 6500.
serverSocket = socket(AF_INET, SOCK_STREAM)                                        # Create TCP socket for server, remote port 6500.
serverSocket.bind(("", PORT))
serverSocket.listen(1)                                                             # Server begins listening for  incoming TCP requests.
print("\t\t{The server is ready to receive}")

                                                                                # function to read the items file and cut it to items and prices

def readfile(filename):

   with open(filename) as f:                                                       # Create inputfile to read the data in items.txt .
    item = f.readlines()                                                         # Read the data in Items.txt line.
    for sentences in item:                                                      # Split the data from the file and append it to a new list, then cut the data based on 🙂) .
        line = sentences.split(":")
        line[1] = str(line[1]).replace("\n", "")
        line[1] = int(line[1])
        items.append(line)                                                        # Add item in items array.
readfile('items.txt')


while True:

    connectionSocket, address = serverSocket.accept()                             # Server waits on accept() for incoming requests, new socket created on return .
    sentence = connectionSocket.recv(1024).decode()                               # Read bytes from socket.
    requestFile = sentence.split(' ')[1]

    printedfile = requestFile.lstrip('/')                                         # Removing the first( / )to get the requested file name .
    connectionSocket.send(f"HTTP/1.1 200 OK\r\n".encode())

    if printedfile == '' or printedfile == 'index.html':
        printedfile = 'main.html'                                                 # Load main.html file as default so if the request is / or /index.html then the server should send main.html file.

    try:
                                                                                   # Accepting different file formats
        if printedfile.endswith(".html"):                                         # If the request is a .html then the server should send the html file with Content-Type: text/html.
            requestedType = 'text/html'

        elif printedfile.endswith(".css"):                                        # If the request is a .css then the server should send the css file with Content-Type: text/css.
            requestedType = 'text/css'

        elif printedfile.endswith(".png"):                                        # If the request is a .jpg then the server should send the png image with Content-Type: image/png.
             requestedType = 'image/png'

        elif printedfile.endswith(".jpg"):                                        # If the request is a .jpg then the server should send the jpg image with Content-Type: image/jpg.
            requestedType = 'image/jpeg'

        elif printedfile == "SortByName" or printedfile == "SortByPrice":         # If the request is SortByName or SortByPrice then the server should send text page with Content-Type: text/plain.
            requestedType = 'text/plain'

        else:                                                                     # Else then server should send text page with Content-Type: text/html.
            requestedType = 'text/html'

        if printedfile == 'SortByName' or printedfile == 'SortByPrice':
                                                                                   # If the user requests to sort either by name or by price for the items, it will enter this IF condition
                                                                                   # to know to show the sort price page or sortname page depend on what the user request.

                if printedfile == 'SortByName':                                   # To sort the items depending on the names.
                    items.sort()
                    ST = '<!DOCTYPE html><html><head><style>body {background-image: url(' \
                         '"back.jpg");background-repeat: no-repeat;background-attachment: fixed; background-size: ' \
                         '100% 100%;}</style></head><head><style>#Items {font-family: Times new roman, ' \
                         'sans-serif;text-align:center;border-collapse: collapse;width: 50%;} #Items td,' \
                         '#Items th {border: 5px solid #000000;padding: 8px;} #Items tr:nth-child(even){' \
                         'background-color: darkgrey;} #Items tr:hover {background-color: darkgrey;}#Items th {' \
                         'padding-top: 12px;padding-bottom: 12px;text-align: left;text-align:center;color: ' \
                         'white;}</style></head><body><hr><center><h1>Sort By Name</h1><table id="Items"><hr><tr ' \
                         'style="background-color: royalblue;"><th>The Item</th><th>The Price</th></tr> '

                else:
                                                                                  # To sort the items depending on the pricess.
                    items.sort(key=lambda items: items[1])
                    ST = '<!DOCTYPE html><html><head><style>body {background-image: url(' \
                         '"back.jpg");background-repeat: no-repeat;background-attachment: fixed; background-size: ' \
                         '100% 100%;}</style></head><head><style>#Items {font-family: Times new roman, ' \
                         'sans-serif;text-align:center;border-collapse: collapse;width: 50%;} #Items td,' \
                         '#Items th {border: 5px solid #000000;padding: 8px;} #Items tr:nth-child(even){' \
                         'background-color: darkgrey;} #Items tr:hover {background-color: darkgrey;}#Items th {' \
                         'padding-top: 12px;padding-bottom: 12px;text-align: left;text-align:center;color: ' \
                         'white;}</style></head><body><hr><center><h1>Sort By Price</h1><table id="Items"><hr><tr ' \
                         'style="background-color: royalblue;"><th>The Item</th><th>The Price</th></tr> '


                for OurItems in items:                                          # To fill the table with items.

                 ST += '<td>' + OurItems[0] + '</td><td>' + str(OurItems[1]) + '$</td></tr>'
                ST += "</table></center></body></html>"                         # End of html code.

                printedfile = 'SortItems.html'                                    # Set the requested file name is SortItems.html.
                Sortfile = open("SortItems.html","w")                              # Create SortItems.html to write the html code after added sorrted item.
                Sortfile.write(ST)
                Sortfile.close()

        requestFile = open(printedfile,'rb')  # Open and read the requested file in byte format.
        ST = requestFile.read()
        requestFile.close()

        header = 'Content-Type: ' + str(requestedType) + '\r\n\r\n'

    except Exception as e:
                                                                              # If the request is wrong or the file doesn’t exist the server should return a simple HTML webpage with our
                                                                              # names and IDs and IP and port number of the client
        header = 'HTTP/1.1 404 Not Found\n\n'
        ST = ('<!DOCTYPE html><head><title>Error</title><style type="text/css">h1 {text-align: center;}li {font-weight: '
                    'bold;}</style></head><head><style type="text/css">p {text-align: '
                    'center;}li</style></head><head><style> body {background-image: url("back.jpg"); '
                    'background-repeat: no-repeat;background-attachment: fixed; background-size: 100% '
                    '100%;}</style></head><hr><body><h1 style="color:red">The file is not found</h1><br><hr><p '
                    'style="color:black"><b>Tariq Odeh 1190699</b></p><p style="color:black"><b>Qays Safa '
                    '1190880</b></p><p style="color:black"><b>Mahmoud Samara 1191602</b></p><hr><p><b>Client '
                    'IP:'+str(address[0])+'</b></p><p><b>Client PORT:'+str(address[1])+'</b></p><hr> '
              '</body></html>').encode('utf-8')

    connectionSocket.send(f"\r\n".encode())
    connectionSocket.send(ST)                                                    # Send the final response with all parts of header.
    connectionSocket.close()                                                     # To closes a connectionSocket socket.
    print(sentence)                                                              #Print the HTTP request on the terminal window.