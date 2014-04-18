import serial
import requests
import json
import time

url = 'http://localhost:8085/telemachus/datalink?ap=o.ApA&al=v.altitude&sV=v.surfaceVelocity&tV=tar.o.relativeVelocity&cM=r.resourceMax[ElectricCharge]&cC=r.resource[ElectricCharge]&fC=r.resource[fuel]&fM=r.resourceMax[fuel]'
ser = serial.Serial('/dev/ttyACM0', 38400, timeout = 1)

def toSerial(value):
    ser.write(value)

def getContent():
    try:
        r = requests.get(url)
        return r.content
    except ValueError:
        pass

def formatNumber(data):
    data = round(data,1)
    # To get decimal numbers on the LED-displays
    output = str(int(data*10)) + 's'
    return output

while(1>0):
    content = getContent()
    content = json.loads(content)
    dataRequested = ser.read(2)
    toSerial(formatNumber(content[dataRequested]))
    time.sleep(0.01)
