from picamera import PiCamera
import numpy as np
import cv2

# Raspberry Piカメラのセットアップ
camera = PiCamera()

# 解像度の設定（任意）
camera.resolution = (640, 480)

# 画像をnumpy配列に格納するための準備
image = np.empty((480, 640, 3), dtype=np.uint8)  # 640x480のRGB画像

# 画像を取得
camera.capture(image, 'rgb')  # 'rgb'フォーマットでキャプチャ

# カメラの終了
camera.close()

# 画像の一部のRGB値を確認する
print("Top left pixel RGB values:", image[0, 0])  # 左上のピクセル
print("Center pixel RGB values:", image[240, 320])  # 中央のピクセル

# OpenCVで画像を表示（必要な場合）
cv2.imshow("Captured Image",image)
cv2.waitKey(0)
cv2.destroyAllWindows()


