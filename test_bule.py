import cv2
import numpy as np

cap = cv2.VideoCapture(0)

while(1):
    _, frame = cap.read()
    
    hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
    
    lower_bule = np.array([150,50,100])
    upper_bule = np.array([250,255,255])
    
    
    mask = cv2.inRange(hsv, lower_bule, upper_bule)
    res = cv2.bitwise_and(frame, frame, mask = mask)
    
    cv2.imshow('res',res)
    cv2.imshow('frame',frame)
    
    k = cv2.waitKey(100) & 0xFF
    
    if k == 27:
        break
        
cv2.destroyALLWindows()
