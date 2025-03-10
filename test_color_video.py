import cv2
import numpy as np
import statistics
from picamera import PiCamera
import subprocess


cap = cv2.VideoCapture(0)


global hasamaru
    


while(1):
    _, frame = cap.read()
    
    hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
    
    r,g,b = cv2.split(frame)

    
    r = np.array([119,200,255])
    g = np.array([79,80,200])
    b = np.array([10,100,150])
    
    if np.all((r >= 0) & (r <= 20)):
        if np.all((g >= 120) & (r <= 160)):
            if np.all((b >= 160) & (r <= 255)):
                print('BLUE')
 
    print("Center pixel RGB values:", frame[240, 320])
    
        
    lower_bule = np.array([0,0,0])
    upper_bule = np.array([255,255,255])
    
   
    
    mask = cv2.inRange(hsv, lower_bule, upper_bule)
    res = cv2.bitwise_and(frame, frame, mask = mask)
    

    cv2.imshow('frame',frame)



    if cv2.waitKey(1) & 0xFF == ord('q'):
        break
        
cv2.destroyALLWindows()
