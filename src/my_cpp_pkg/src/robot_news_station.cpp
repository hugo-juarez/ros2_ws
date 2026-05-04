#include <rclcpp/rclcpp.hpp>
#include <example_interfaces/msg/string.hpp>

using example_interfaces::msg::String;
using namespace std::chrono_literals;


class RobotNewsStation : public rclcpp::Node
{
public:
    RobotNewsStation() : Node("robot_news_station") 
    {
        _robot_name = "R2D2";
        _publisher = this->create_publisher<String>("robot_news", 10);
        _timer = this->create_wall_timer(
            0.5s,
            [this](){publish_news();} 
        );
        RCLCPP_INFO(this->get_logger(), "Robot News Started!");
    }

private:

    void publish_news() {
        String msg;
        msg.data = std::string("Hi, this is ") + _robot_name + 
            std::string("from robot news station");
        _publisher->publish(msg);
    }


    std::string _robot_name;
    rclcpp::Publisher<String>::SharedPtr _publisher;
    rclcpp::TimerBase::SharedPtr _timer;
};

int main(int argc, char ** argv) 
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<RobotNewsStation>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}