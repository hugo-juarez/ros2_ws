#include <rclcpp/rclcpp.hpp>

class MyNode : public rclcpp::Node
{
public:
    MyNode() : Node("cpp_test") 
    {
        RCLCPP_INFO(this->get_logger(), "Hello world!");
        _timer = this->create_wall_timer(
            std::chrono::seconds(1),
            [this]() {timer_callback();}
        );
    }

private:
    void timer_callback() {
        RCLCPP_INFO(this->get_logger(), "Hello %d", _counter++);
    }

    int _counter;
    rclcpp::TimerBase::SharedPtr _timer;

};

int main(int argc, char ** argv) 
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<MyNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}