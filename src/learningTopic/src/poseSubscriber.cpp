/*
 * Filename: /home/skywalker/Documents/code/ros/catkin_ws/src/learningTopic/src/poseSubscriber.cpp
 * Path: /home/skywalker/Documents/code/ros/catkin_ws/src/learningTopic/src
 * Created Date: Saturday, April 17th 2021, 8:34:54 pm
 * Author: Skywalker Wang
 * Function: 订阅turtle1/pose topic, 消息类型turtlesim::Pose
 * Copyright (c) 2021 Skywalker Inc.
 */

#include <ros/ros.h>
#include "turtlesim/Pose.h"

//回调函数
void poseCallback(const turtlesim::Pose::ConstPtr& msg){
    //打印出接收到的消息
    ROS_INFO("Turtle pos: x: %0.6f, y: %0.6f", msg->x, msg->y);
}

int main(int argc, char **argv){
    // 初始化ROS节点
    ros::init(argc, argv, "pose_subscriber");
    //创建节点
    ros::NodeHandle n;
    //创建一个subscriber， 订阅turtle1/pose的topic，注册回调函数
    ros::Subscriber pose_sub = n.subscribe("/turtle1/pose", 10, poseCallback);
    //循环等待回调函数
    ros::spin();

    return 0;
}
