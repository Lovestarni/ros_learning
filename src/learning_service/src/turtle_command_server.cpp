/*
 * Filename: /home/skywalker/Documents/code/ros/catkin_ws/src/learning_service/src/turtle_command_server
 * Path: /home/skywalker/Documents/code/ros/catkin_ws/src/learning_service/src
 * Created Date: Monday, April 19th 2021, 2:21:21 pm
 * Author: Skywalker Wang
 * 执行/turtle_command服务，服务数据类型为std_srvs/Trigger
 * Copyright (c) 2021 Skywalker Inc.
 */

#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <std_srvs/Trigger.h>

ros::Publisher turtle_vel_pub;
// 资源占用变量，标志是否要发布指令
bool pubCommand = false;

// 回调函数
bool commandCallback(std_srvs::Trigger::Request &req, std_srvs::Trigger::Response &res)
{
    //标志位重置
    pubCommand = !pubCommand;
    ROS_INFO("Publish turtle velocity command [%s]", pubCommand==true?"Yes":"No");
    
    //设置反馈数据
    res.success = true;
    res.message = "Change the turtle velocity";

    return true;
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "turtle_command_server");
    ros::NodeHandle node;

    // 创建一个名为/turtle_command的server，并注册回调函数
    ros::ServiceServer command_service = node.advertiseService("/turtle_command", commandCallback);
    // 创建一个Publisher, 发布/turtle1/cmd_vel的topic, 消息类型为Twist，队列长度是10
    turtle_vel_pub = node.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 10);

    ROS_INFO("Ready to receive tutle command.");

    ros::Rate loop_rate(10);

    while (ros::ok())
    {
        // 查看一次回调函数序列
        ros::spinOnce();
        // 如果标志为true, 则发布命令
        if (pubCommand)
        {
            geometry_msgs::Twist vel_msg;
            vel_msg.linear.x = 0.5;
            vel_msg.angular.z = 0.2;
            turtle_vel_pub.publish(vel_msg);
        }

        loop_rate.sleep();
    }

    return 0;
}