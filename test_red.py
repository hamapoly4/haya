import cv2
import numpy as np

cap = cv2.VideoCapture(0)

while(1):
    _, frame = cap.read()
    
    hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    
 

    cv2.imshow('frame',frame)
    
    k = cv2.waitKey(100) & 0xFF
    
    if k == 27:
        break
        
cv2.destroyALLWindows()
