import cv2
import numpy as np

def resize01(frame, fx, fy):
    # bilinear interpolation
    return cv2.resize(frame, dsize=(0, 0), fx=fx, fy=fy, interpolation=cv2.INTER_LINEAR)

def resize02(frame, width, height):
    # resampling using pixel area relation
    return cv2.resize(frame, dsize=(width, height), interpolation=cv2.INTER_AREA)

def BGR2GRAY(frame):
    # converts the colour space of the image to a single channel of greyscale
    return cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

def BGR2HSV(frame):
    # converts the image's colour space into hue, saturation, and value channels
    return cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)

def skintoneMask(frame, hsv):
    lower_skintone = np.array([0, 50, 80])
    upper_skintone = np.array([20, 150, 255])
    mask = cv2.inRange(hsv, lower_skintone, upper_skintone)
    return cv2.bitwise_and(frame, frame, mask=mask)

def blueMask(frame, hsv):
    lower_blue = np.array([100, 50, 50])
    upper_blue = np.array([140, 255, 255])
    mask = cv2.inRange(hsv, lower_blue, upper_blue)
    return cv2.bitwise_and(frame, frame, mask=mask)

def redMask(frame, hsv):
    lower_red1 = np.array([0, 50, 50])
    upper_red1 = np.array([10, 255, 255])
    lower_red2 = np.array([170, 50, 50])
    upper_red2 = np.array([180, 255, 255])
    mask1 = cv2.inRange(hsv, lower_red1, upper_red1)
    mask2 = cv2.inRange(hsv, lower_red2, upper_red2)
    mask = mask1 + mask2
    return cv2.bitwise_and(frame, frame, mask=mask)

def edgeDetection(gray):
    # detect edges using cv2's edge detection function.
    return cv2.Canny(gray, 100, 200)

def drawSquares():
    # initialize the image with a black background
    img = np.zeros((512, 512, 3), np.uint8)

    cv2.line(img, (0, 0), (511, 511), (255, 0, 0), 5)
    cv2.rectangle(img, (384, 0), (510, 128), (0, 255, 0), 3)
    cv2.circle(img, (447, 63), 63, (0, 0, 255), -1)
    cv2.ellipse(img, (256, 256), (100, 50), 0, 0, 180, 255, -1)

    pts = np.array([[10, 5], [20, 30], [70, 20], [50, 10]], np.int32)
    pts = pts.reshape((-1, 1, 2))
    cv2.polylines(img, [pts], True, (0, 255, 255))

    font = cv2.FONT_HERSHEY_SIMPLEX
    cv2.putText(img, 'OpenCV', (10, 200), font, 4, (255, 255, 255), 2, cv2.LINE_AA)

    return img

cam = cv2.VideoCapture(0)

while True:
    ret, frame = cam.read()
    if not ret:
        break

    # Show original video
    #cv2.imshow('nanoCam', frame)

    # rs01 = resize01(frame, fx=0.3, fy=0.7)
    # rs02 = resize02(frame, 200, 480)
    # gray = BGR2GRAY(frame)
    # hsv = BGR2HSV(frame)
    # skin_res = skintoneMask(frame, hsv)
    # blue_res = blueMask(frame, hsv)
    # red_res = redMask(frame, hsv)
    # edges = edgeDetection(gray)
    squares = drawSquares()

    cv2.imshow('drawSqaures', squares)

    # break the loop if q is pressed
    if cv2.waitKey(1) == ord('q'):
        break

cam.release()
cv2.destroyAllWindows()
