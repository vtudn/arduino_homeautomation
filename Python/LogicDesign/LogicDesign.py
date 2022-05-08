import serial . tools . list_ports
import random
import time
import sys
from Adafruit_IO import MQTTClient
import serial
AIO_FEED_ID = ["Arduino-Temp","Arduino-Humi","Arduino-Led","Arduino-Pir","Arduino-Pir","Arduino-Gas"]
AIO_USERNAME = "NghiGiaBK"
AIO_KEY ="aio_ZDWp35cSDtVefLs4hA2LBTFCeiiD"
def connected ( client ) :
    print ("Ket noi thanh cong ...")
    for feed in AIO_FEED_ID:
        client.subscribe(feed)

def subscribe ( client , userdata , mid , granted_qos ) :
    print ("Subcribe thanh cong ...")

def disconnected ( client ) :
    print (" Ngat ket noi ...")
    sys . exit (1)

def message ( client , feed_id , payload ):
    print ("Nhan du lieu : " + payload +" from feed "+ feed_id)
    ser.write (( str( payload ) ) . encode () )
client = MQTTClient(AIO_USERNAME, AIO_KEY )
client.on_connect = connected
client.on_disconnect = disconnected
client.on_message = message
client.on_subscribe = subscribe
client.connect ()
client.loop_background()

def getPort () :
    ports = serial . tools . list_ports . comports ()
    N = len ( ports )
    commPort = "COM5"
    for i in range (0 , N) :
        port = ports [ i ]
        print(port)
        strPort = str( port )
        if "com0com" in strPort :
            splitPort = strPort . split (" ")
            commPort = ( splitPort [0])
    print(commPort)
    return commPort
ser = serial . Serial ( port = getPort () , baudrate =9600)
mess = ""

preTemp=0
preHumi=0
def processData ( data ) :
    global preTemp
    global preHumi
    data = data.replace("!", "")
    data = data.replace("#", "")
    splitData = data.split(":")
    print(splitData)
    if splitData [0] == "TEMP":
        if(preTemp==0) or (splitData[1] != preTemp):
            preTemp=splitData[1]
            client.publish ("Arduino-Temp", splitData[1])
    if splitData [0] == "HUMI":
        if(preHumi == 0) or (splitData[1] != preHumi):
            preHumi = splitData[1]
            client.publish("Arduino-Humi", splitData[1])
    if splitData [0] == "LED":
            client.publish("Arduino-Led", splitData[1])
    if splitData[0] == "PIR":
        if splitData[1] == "DETECTED":
            client.publish("Arduino-Pir", splitData[1])
        if splitData[1] == "UNDETECTED":
            client.publish("Arduino-Pir", splitData[1])
    if splitData [0] == "SOIL":
            client.publish("Arduino-Soil", splitData[1])
    if splitData [0] == "GAS":
            client.publish("Arduino-Gas", splitData[1])
mess = ""
def readSerial () :
 bytesToRead = ser . inWaiting ()
 if ( bytesToRead > 0) :
        global mess
        mess = mess + ser . read ( bytesToRead ).decode ("UTF -8")
        while ("#" in mess ) and ("!" in mess ) :
           start = mess . find ("!")
           end = mess . find ("#")
           processData ( mess [ start : end + 1])
           if ( end == len( mess )) :
                mess = ""
           else :
                mess = mess [ end +1:]

while True :
    readSerial ()
    time . sleep (1)
