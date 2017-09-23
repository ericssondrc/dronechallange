import zbar

from PIL import Image
import cv2


def main():
    capture = cv2.VideoCapture('D:/Dropbox/python/drone_code_chn/teszt.mp4')
    ## capture = cv2.VideoCapture("D:/Dropbox/python/drone_code_chn/test.mp4")
    index = 0
    while True:
        if cv2.waitKey(1) & 0xFF == ord('q'):
            break

        # Framelteti a videot
        ret, frame = capture.read()

        # Megjelenit egy framet
        cv2.imshow('Current', frame)

        # openCV gray konvertalas
        gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

        # Gray a ZBAR-hoz
        image = Image.fromarray(gray)
        width, height = image.size
        zbar_image = zbar.Image(width, height, 'Y800', image.tobytes())

        # ZBAR image vizsgalat
        scanner = zbar.ImageScanner()
        scanner.scan(zbar_image)

        # Adatkiiratas
        for decoded in zbar_image:
            index += 1
            print(str(index) + ". " + decoded.data)


if __name__ == "__main__":
    main()