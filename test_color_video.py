import cv2
import numpy as np
import statistics
from picamera import PiCamera


cap = cv2.VideoCapture(0)





while(1):
    _, frame = cap.read()
    
    hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
    
    r,g,b = cv2.split(frame)

    
    r = np.array([119,200,255])
    g = np.array([79,80,200])
    b = np.array([10,100,150])
    
    if np.all((r >= 115) & (r <= 255)):
        if np.all((g >= 65) & (r <= 255)):
            if np.all((b >= 0) & (r <= 255)):
                print('BULE')
 
    print("Center pixel RGB values:", frame[240, 320])
    
        
    lower_bule = np.array([0,0,0])
    upper_bule = np.array([255,255,255])
    
   
    
    mask = cv2.inRange(hsv, lower_bule, upper_bule)
    res = cv2.bitwise_and(frame, frame, mask = mask)
    

    cv2.imshow('frame',frame)
    
    k = cv2.waitKey(100) & 0xFF
    
    if k == 27:
        break
        
cv2.destroyALLWindows()
