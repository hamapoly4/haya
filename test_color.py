import cv2
import numpy as np
import statistics
from picamera import PiCamera
import subprocess
import time
import sys


cap = cv2.VideoCapture(0)


hasamaru = 0
    
    
color_ranges = { 

    "red": ([120,100,100], [180,255, 255]), 
    "green": ([35, 100, 100], [85, 255, 255]), 
    "blue": ([100, 170, 0], [130, 255, 255])
}


for i in range(100):
    

    
    ret, frame = cap.read() 
    hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
    
    execution_time = 360 # 例: 1時間（3600秒） 
    start_time = time.time() 
    
    detected_colors = [] 
    
    for color_name, (lower, upper) in color_ranges.items(): 
 
        mask = cv2.inRange(hsv, np.array(lower), np.array(upper)) 
                 
        if cv2.countNonZero(mask) > 0:
             detected_colors.append(color_name)
             res = cv2.bitwise_and(frame, frame, mask=mask)
             cv2.imshow(f'res_{color_name}', res)
                  
    cv2.imshow('frame', frame[240, 320]) 
   # if detected_colors: 
    #    print("Detected colors: ", detected_colors)
    
    if color_name == 'red':
        hasamaru = 1
        
    elif color_name == 'blue':
        hasamaru = 2
        
    else : 
        hasamaru = 'default'
        
    with open("hasamaru.txt", "w") as file: 
        file.write(str(hasamaru))
    
        
    if i == 100: 
        print("中断します")
        sys.exit()
    print(i)
        

    

cap.release()
cv2.destroyALLWindows()
