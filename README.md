# Density-Based-Traffic-Signal-using-Image-Processing
------------------------------------------------------------------------------------------------------------------------------------
Due to the increase in the number of vehicles day by day, traffic congestions and traffic jams are very common. One method to overcome the traffic problem is to develop an intelligent traffic control system which is based on the measurement of traffic density on the road using real time video and image processing techniques. The theme is to control the traffic by determining the traffic density on each side of the road and control the traffic signal intelligently by using the density information. This paper presents the algorithm to determine the number of vehicles on the road. The density counting algorithm works by comparing the real time frame of live video by the reference image and by searching vehicles only in the region of interest    (i.e. road area). The computed vehicle density can be compared with other direction of the traffic in order to control the traffic signal smartly.
In this method, a webcam is used in each stage of the traffic light in order to take pictures of the roads where traffic is bound to occur. Count of vehicles in these images is calculated using image processing tools in Matlab and different timings are allocated according to the count along with a green signal for vehicles to pass. In the proposed prototype, the green and red signals are represented using LEDs and the decrementing timer for the green signal is represented by a seven segment display. 
