#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "sensor_msgs/msg/image.hpp"
#include <image_transport/image_transport.hpp>

#include "cv_bridge/cv_bridge.h"
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using std::placeholders::_1;

class OpencvNode : public rclcpp::Node
{
  public:
    OpencvNode()
    : Node("opencv_node")
    {
      subscription_ = this->create_subscription<sensor_msgs::msg::Image>(
      "/image_raw", 10, std::bind(&OpencvNode::imageCallback, this, _1));

      image_pub_ = this->create_publisher<sensor_msgs::msg::Image>("image_topic", 10);
    }

  private:
    void imageCallback(const sensor_msgs::msg::Image::SharedPtr msg) const
    {     
   cv_bridge::CvImagePtr cv_ptr;

      cv_ptr = cv_bridge::toCvCopy(msg, "bgr8"/* msg->encoding */);
      cv::Mat cvImage = cv_ptr->image;
      if (cvImage.empty()) {
            RCLCPP_ERROR(this->get_logger(), "Failed to load image");
            return;
        }
      cv::resize(cvImage, cvImage, {640, 480});

      

      sensor_msgs::msg::Image::SharedPtr rosImage = cv_bridge::CvImage(msg->header, "bgr8", cvImage).toImageMsg();
      image_pub_->publish(*rosImage);


        
    }
    rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr subscription_;
    rclcpp::Publisher<sensor_msgs::msg::Image>::SharedPtr image_pub_;
    
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<OpencvNode>());
  rclcpp::shutdown();
  return 0;
}