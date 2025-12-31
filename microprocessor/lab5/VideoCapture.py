import cv2 # type: ignore
import numpy as np

cam = cv2.VideoCapture(0) # Webacm

while True:
    ret, frame = cam.read()
    
    # convert BGR to HSV
    hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)

    # Blue Mask
    lower_blue = np.array([110, 50, 50]) # hue 110, saturation 50, value 50
    upper_blue = np.array([130, 255, 255]) # hue 130, saturation 255, value 255

    blue_mask = cv2.inRange(hsv, lower_blue, upper_blue) # mask blue colors
    blue_res = cv2.bitwise_and(frame, frame, mask=blue_mask) # bitwiswe-and mask and frame
    cv2.imshow('Blue Mask', blue_res) # show blue mask

    # Red Mask
    lower_red1 = np.array([0, 50, 50]) # hue 0, saturation 50, value 50
    upper_red1 = np.array([10, 255, 255]) # hue 10, saturation 255, value 255
    lower_red2 = np.array([170, 50, 50]) # hue 170, saturation 50, value 50
    upper_red2 = np.array([180, 255, 255]) # hue 180, saturation 255, 255
    
    red_mask1 = cv2.inRange(hsv, lower_red1, upper_red1) 
    red_mask2 = cv2.inRange(hsv, lower_red2, upper_red2)
    red_mask = red_mask1 + red_mask2 # wrap-around red colors
    red_res = cv2.bitwise_and(frame, frame, mask=red_mask) # bitwise-and mask and frame
    cv2.imshow('Red Mask', red_res) # show red mask
    
    # erode
    kernel = np.ones((5, 5), np.uint8) # erode the frame to reduce noises
    eroded = cv2.erode(frame, kernel, iterations=1)
    cv2.imshow('Eroded', eroded) # show eroded

    # dilate
    dilated = cv2.dilate(frame, kernel, iterations=1) # dilate to recover object size
    cv2.imshow('Dilated', dilated) # show dilated

    # GaussianBlur 
    blurred = cv2.GaussianBlur(frame, (15, 15), 0) # apply gaussian blur to frame
    cv2.imshow('Blurred', blurred) # show GaussianbBlur

    # drawContours
    gray_frame = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY) # convert to grayscale
    _, threshold = cv2.threshold(gray_frame, 100, 255, cv2.THRESH_BINARY)
    contours, _ = cv2.findContours(threshold, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE) 
    contour_frame = frame.copy() # draw contours
    cv2.drawContours(contour_frame, contours, -1, (255, 255, 255), 3)
    cv2.imshow('Contours', contour_frame) # show drawContours

    # cv2.imshow('frame', frame) # show original video
    
    # break the loop if q is pressed
    if cv2.waitKey(1) == ord('q'):
        break

cam.release()
cv2.destroyAllWindows()