#include <iostream>
#include <ros/ros.h>
#include <ros/topic.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include <vector>
#include <tuple>
#include <sensor_msgs/Image.h>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <string>
#include <std_msgs/String.h>

#define NAV_DEBUG 1
#define IMG_DEBUG 1

const std::string TO_TF_TOPIC = "/cpptopy", FROM_TF_TOPIC = "/pytocpp";

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;
typedef std::tuple<double, double, double, double> Goal;

bool found_watermelon();
