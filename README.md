# webcam_point_features

Detection of ORB features from online webcam images.

## Information about ORB Features

First of all, ORB is an acronym of **Oriented FAST and Rotated BRIEF**. Published in 2011 by Ethan Rublee, Vincent Rabaud, Kurt Konolige and Gary R. Bradski in their paper _ORB: An efficient alternative to SIFT or SURF_.

> ORB is basically a fusion of FAST keypoint detector and BRIEF descriptor with many modifications to enhance the performance.

Not fully understanding how ORB works, I'm going to list some points:

- Use of **FAST** as a keypoint detector (with a Harris corner measure) does not gives you the orientation of the keypoints.
  - To find the orientation, the code find the vector from the corner center to a certain _centroid_.

- Use of **BRIEF** as a descriptor have some problems to handle orientations.
  - It uses the orientation calculated early in **FAST** to create rotation matrix and improve the calculations.

Last interesting point about ORB is that is completely free, no payed licenses needed to use it, against SIFT or SURF that are patented.

### References

- https://docs.opencv.org/3.0-beta/doc/py_tutorials/py_feature2d/py_orb/py_orb.html
