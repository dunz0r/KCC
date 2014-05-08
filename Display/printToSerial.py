import serial
import requests
import json
import time

velocities = 'sV=v.surfaceVelocity&oV=v.orbitalVelocity&tV=tar.o.relativeVelocity'
altitudes = '&ap=o.ApA&al=v.altitude&pe=o.PeA'
toggleables = '&sS=v.sasValue&rS=v.rcsValue'
consumeables = '&cM=r.resourceMax[ElectricCharge]&cC=r.resource[ElectricCharge]&fC=r.resource[fuel]&fM=r.resourceMax[fuel]'
url = 'http://localhost:8085/telemachus/datalink?' + velocities + altitudes + consumeables + toggleables
ser = serial.Serial('/dev/ttyACM1', 38400, timeout = 1)

def toSerial(value):
    ser.write(value)

def getContent():
    try:
        r = requests.get(url)
        return r.content
    except ValueError:
        pass

def formatData(data):
    data = round(data,1)
    # To get decimal numbers on the LED-displays
    output = str(int(data*10)) + 's'
    return output

while(1>0):
    content = getContent()
    content = json.loads(content)
    dataRequested = ser.read(2)
    toSerial(formatData(content[dataRequested.decode("ascii")]))
