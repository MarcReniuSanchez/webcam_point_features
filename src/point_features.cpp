
//OpenCV
#include "opencv2/opencv.hpp"
#include "opencv2/core.hpp"
#include "opencv2/features2d.hpp"

//std
#include <iostream>
#include <cstdlib>
#include <vector>

//consts
const unsigned int MIN_NUM_FEATURES = 30; // Decresed minimum number of point features

int main(int argc, char *argv[]){
  cv::VideoCapture camera; //OpenCV video capture object
  cv::Mat image; //OpenCV image object
  cv::Mat mask; // OpenCV image to be shown
  int cam_id; //camera id . Associated to device number in /dev/videoX
  int width, height, mask_width, mask_height;
  cv::Ptr<cv::ORB> orb_detector = cv::ORB::create(); //ORB point feature detector
  // orb_detector->setScoreType(1); // MMM: change type
  orb_detector->setMaxFeatures(MIN_NUM_FEATURES);
  std::vector<cv::KeyPoint> point_set; //set of point features
  cv::Mat descriptor_set; //set of descriptors, for each feature there is an associated descriptor
  //check user args
  switch(argc){
    case 1: //no argument provided, so try /dev/video0
      cam_id = 0;
      break;
    case 2: //an argument is provided. Get it and set cam_id
      cam_id = atoi(argv[1]);
      break;
    default:
      std::cout << "Invalid number of arguments. Call program as: webcam_capture [video_device_id]. " << std::endl;
      std::cout << "EXIT program." << std::endl;
      break;
  }

  //advertising to the user
  std::cout << "Opening video device " << cam_id << std::endl;

    //open the video stream and make sure it's opened
  if( !camera.open(cam_id) ){
    std::cout << "Error opening the camera. May be invalid device id. EXIT program." << std::endl;
    return -1;
  }

    //Process loop. Capture and point feature extraction. User can quit pressing a key
  while(1){
    //Read image and check it. Blocking call up to a new image arrives from camera.
    if(!camera.read(image)){
      std::cout << "No image" << std::endl;
      cv::waitKey();
    }

    width = image.cols;
    height = image.rows;
    mask_width = width / 4;
    mask_height = height / 3;

    for (size_t i = 0; i < 4; i++) {
      int height_ini, height_fi;
      height_ini = mask_height * i;
      height_fi = mask_height * (i + 1);
      if (height_fi > height) {height_fi = height;}

      for (size_t j = 0; j < 3; j++) {
        int width_ini, width_fi;
        width_ini = mask_width * i;
        width_fi = mask_width * (i + 1);
        if (width_fi > width) {width_fi = width;}
        mask = cv::Mat::zeros(height, width, mask.type());

        // FILL MASK
        for (size_t ii = height_ini; ii <= height_fi; ii++) {
          for (size_t jj = width_ini; jj <= width_fi; jj++) {
            mask.at<uchar>(ii,jj) = 1;
          }
        }

        //**************** Find ORB point features and descriptors for this mask ****************************
        point_set.clear();
        orb_detector->detectAndCompute(image, mask, point_set, descriptor_set);
        cv::drawKeypoints( image, point_set, image, 255, cv::DrawMatchesFlags::DEFAULT );
        //********************************************************************
      }
    }

    //show image
    cv::imshow("Output Window", image);

    //Waits 30 millisecond to check if 'q' key has been pressed. If so, breaks the loop. Otherwise continues.
    if( (unsigned char)(cv::waitKey(30) & 0xff) == 'q' ) break;
  }
}
