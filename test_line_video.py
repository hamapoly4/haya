import cv2
import numpy as np
import statistics
from picamera.array import PiRGBArray
from picamera import PiCamera
import time


cap = cv2.VideoCapture(0)
camera = PiCamera()
camera.resolution = (640,480)
camera.framerate = 30
raw_capture = PiRGBArray(camera, size=(640, 480))

time.sleep(0.1)




# カメラからフレームを逐次取得
for frame in camera.capture_continuous(raw_capture, format="bgr", use_video_port=True):
    # フレームを取得
    image = frame.array
    
    # グレースケール変換
    gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
    
    # Cannyエッジ検出
    edges = cv2.Canny(gray, 50, 150)
    
    # 確率的Hough変換で直線を検出
    lines = cv2.HoughLinesP(edges, 1, np.pi/180, threshold=50, minLineLength=100, maxLineGap=10)
    
    # 検出された直線を描画
    if lines is not None:
        for line in lines:
            x1, y1, x2, y2 = line[0]
            cv2.line(image, (x1, y1), (x2, y2), (0, 255, 0), 2)
    
    # 結果を表示
    cv2.imshow("Frame", image)
    
    # 'q'キーが押されたら終了
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break
    
    # フレームをクリア
    raw_capture.truncate(0)

# 終了処理
cv2.destroyAllWindows()
