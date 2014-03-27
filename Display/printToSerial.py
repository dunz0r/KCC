import serial
import requests
import json
import time

url = 'http://localhost:8085/telemachus/datalink?al=v.altitude&ve=v.orbitalVelocity&cM=r.resourceMax[ElectricCharge]&cC=r.resource[ElectricCharge]&fC=r.resource[fuel]&fM=r.resourceMax[fuel]'
ser = serial.Serial('/dev/ttyACM0', 38400, timeout = 1)

def toSerial(value):
    ser.write(value)

def getContent():
    r = requests.get(url)
    return r.content

def formatData(data):
    output = str(int(data)) + 's'
    return output

while(1>0):
    content = getContent()
    content = json.loads(content)
    dataRequested = ser.read(2)
    toSerial(formatData(content[dataRequested]))
    time.sleep(0.01)
