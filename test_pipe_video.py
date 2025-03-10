import cv2
import numpy as np
from socket import socket, AF_INET, SOCK_STREAM

# Raspberry Pi カメラを使う場合は、以下のインポートが必要
from picamera import PiCamera 

# ソケット通信設定
HOST = 'localhost'
PORT = 51000

CHR_CAN = '\x18'
CHR_EOT = '\x04'

# カメラ初期化
cap = cv2.VideoCapture(0)

def com_send(mess):
    """
    サーバーにメッセージを送信する関数
    """
    while True:
        try:
            # ソケット通信の確立
            sock = socket(AF_INET, SOCK_STREAM)
            sock.connect((HOST, PORT))

            # メッセージ送信
            sock.send(mess.encode('utf-8'))

            # 通信の終了
            sock.close()
            break
        except:
            print('通信リトライ中: ' + mess)

def detect_color(frame):
    """
    フレーム中央のピクセルを取得して色を判定
    """
    # フレームの中央ピクセルを取得
    center_pixel = frame[240, 320]
    r, g, b = center_pixel

    # 色の判定ロジック
    if 115 <= r <= 255 and 65 <= g <= 255 and 0 <= b <= 255:
        print('BLUE')
    else:
        print('Other Color')
    return center_pixel

def main():
    """
    メイン処理
    """
    while True:
        ret, frame = cap.read()
        if not ret:
            print("カメラが接続されていません")
            break

        # フレームの色空間をHSVに変換
        hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)

        # 色判定
        captured_color = detect_color(frame)

        # 色の範囲を設定してマスクを作成
        lower_blue = np.array([100, 50, 50])  # 青の範囲（例）
        upper_blue = np.array([130, 255, 255])
        mask = cv2.inRange(hsv, lower_blue, upper_blue)

        # フレームをマスク
        res = cv2.bitwise_and(frame, frame, mask=mask)

        # フレーム表示
        cv2.imshow('Original', frame)
        cv2.imshow('Masked', res)

        # キー入力待ち
        k = cv2.waitKey(100) & 0xFF
        if k == 27:  # ESCキーで終了
            break

        # サーバーに色情報を送信
        com_send(f"Captured Color: {captured_color}")

    # リソースの解放
    cap.release()
    cv2.destroyAllWindows()

if __name__ == "__main__":
    main()
