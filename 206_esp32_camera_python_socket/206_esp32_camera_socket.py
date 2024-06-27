import io
#from multiprocessing.dummy import Array
import socket
import time
import cv2
import numpy as np
#from PIL import Image
from math import atan2, cos, sin, sqrt, pi




serv = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
# address '0.0.0.0' or '' work to allow connections from other machines.  'localhost' disallows external connections.
# see https://www.raspberrypi.org/forums/viewtopic.php?t=62108
serv.bind(('0.0.0.0', 5005))
serv.listen(5)
print("Ready to accept 5 connections")

while True:
    conn, addr = serv.accept()
    array_from_client = bytearray()
    shape = None
    chunks_received = 0
    start = time.time()
    shape_string = ''
    while True:
        # print('waiting for data')
        # Try 4096 if unsure what buffer size to use. Large transfer chunk sizes (which require large buffers) can cause corrupted results
        data = conn.recv(4096*2)
        if not data:
            break
        else:
            chunks_received += 1
    
            array_from_client.extend(data)
            print("chunks_received {}. Number of bytes {}".format(chunks_received, len(array_from_client)))
   
    img = np.array(bytearray(array_from_client), dtype=np.uint8)
    if img.any():
        img_dec = cv2.imdecode(img, -1)
        if img_dec.any():
            cv2.imshow('win',img_dec)
            key = cv2.waitKey(1)
            if key & 0xff == ord('q'):
                break
