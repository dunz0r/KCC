import serial
import requests
import re
import time

url = 'http://localhost:8085/telemachus/datalink?a=v.altitude'
ser = serial.Serial('/dev/ttyACM1', 38400, timeout = 1)

def toSerial(value):
    ser.write(value)

def getContent():
    r = requests.get(url)
    output = re.sub('[{}:a"]+', '',r.content)
    return output

def formatData(data):
    output = str(round(float(data),1))
    return output

while(1>0):
    content = getContent()
    content = formatData(content)
    toSerial(re.sub('\..', 'S', content))
    time.sleep(0.05)
