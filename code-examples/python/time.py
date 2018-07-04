import time
import datetime
from math import trunc

scale=1000000
target=trunc(time.time()/scale)*scale+scale
print(round((target-time.time())/(60*60),2),"hours","until",target)
print(time.time())
