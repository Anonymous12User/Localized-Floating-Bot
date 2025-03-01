# Localized-Floating-Bot
Repository containing Arduino and Python programs required for running the localized floating bot. Following are the important Arduino codes/python notebooks used in the project :

## Client.ino:
Code running on the ESP8266 module present at the station present on the banks of the water body. This ESP module sends HTTP GET requests to the server ESP module (present on the water bot) to fetch the readings of the various parameters (such as temperature, humidity, pH, etc). This code is responsible for sending those HTTP GET requests and handling the values received from the sensors.

## Server.ino:
Code running on the ESP8266 modules present on the water bot. This ESP module receives HTTP GET requests from the client ESP module (present on the banks of the water body) and responds to those requests by sending the readings picked up by the various sensors back to the client.

## Calibration.ipynb:
Python notebook used to obtain the distortion matrix of the camera which is to be placed on the banks of the water body for the purpose of localization. This distortion matrix is obtained by displaying a regular chessboard to the camera while holding it in different orientations.

## Track_excel.ipynb:
Python notebook used to track the ArUco tags while using OpenCV package. This program is used to obtain two vectors : translational and rotational vector, of the ArUco tag with respect to the stationay camera on the banks of the water body. These two vectors and then processed to give us the real life coordinates of the ArUco tags (which in this case also gives us the real life coordinates of the water bot) with respect to the camera. These real life coordinates are then stored in an Excel file for further use (useful while plotting trajectories and heatmaps)

## Plot_trajectory.ipynb:
Python notebook used to fetch the real life coordinates of the water bot (obtained using the Track_excel.ipynb python notebook) and use those coordinates to plot the trajectory of the water bot and also to generate heatmaps of the water body for the purpose of water profiling. 
