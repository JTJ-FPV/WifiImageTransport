#include <ros/ros.h>
#include <sensor_msgs/image_encodings.h>
#include <cv_bridge/cv_bridge.h>
#include <image_transport/image_transport.h>
#include <sensor_msgs/CompressedImage.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>

cv::Mat img;
static const char WINDOW[] = "TRACKER SUB";

void CompressImagecb(const sensor_msgs::CompressedImageConstPtr &msg)
{
    try
    {
        cv_bridge::CvImagePtr cv_ptr_compressed = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
        img = cv_ptr_compressed->image;
        cv::imshow(WINDOW, img);
    }
    catch(cv_bridge::Exception &e)
    {
        ROS_ERROR("convert fail");
    }
    
}

int main(int argc, char  **argv)
{
    ros::init(argc, argv, "ImageSub");
    ros::NodeHandle nh;
    // MonoCamera
    // std::string image_sub_topic = "/monocamera/image/compressed";
    // D435i
    std::string image_sub_topic = "/camera/color/image_raw/compressed";
    ros::Subscriber image_sub = nh.subscribe<sensor_msgs::CompressedImage>(image_sub_topic, 1, CompressImagecb);
    cv::namedWindow(WINDOW);
    cv::startWindowThread();
    ros::spin();
    cv::destroyAllWindows();
    return 0;
}
