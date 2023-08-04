#include <ros/ros.h>
#include <sensor_msgs/image_encodings.h>
#include <cv_bridge/cv_bridge.h>
#include <image_transport/image_transport.h>
#include <sensor_msgs/CompressedImage.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>

int main(int argc, char **argv)
{
    setlocale(LC_ALL,"");
    if(argv[1] == NULL)
    {
        ROS_INFO("argv[1]=NULL\n");
        ROS_INFO("请输入参数！");
        return 1;
    }
    std::istringstream video_sourceCMD(argv[1]);
    int video_source;
    if(!(video_sourceCMD >> video_source))
    {
        ROS_INFO("video_source is %d\n",video_source);
        return 1;
    }
    ros::init(argc, argv, "ImagePub");
    ros::NodeHandle nh;
    image_transport::ImageTransport it(nh);
    image_transport::Publisher image_pub = it.advertise("/monocamera/image", 1);
    
    bool ret = false;
    cv::VideoCapture cap(video_source);
    cv::Mat img;
    sensor_msgs::ImagePtr img_ptr;
    while(ros::ok())
    {
        ret = cap.read(img);
        if(ret)
        {
            img_ptr = cv_bridge::CvImage(std_msgs::Header(), "bgr8", img).toImageMsg();
            image_pub.publish(img_ptr);
        }
    }
    return 0;
}
