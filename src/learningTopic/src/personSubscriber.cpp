/*
 * Filename: /home/skywalker/Documents/code/ros/catkin_ws/src/learning_topic/src/personSubscriber.cpp
 * Path: /home/skywalker/Documents/code/ros/catkin_ws/src/learning_topic/src
 * Created Date: Saturday, April 17th 2021, 9:24:45 pm
 * Author: Skywalker Wang
 * 
 * Copyright (c) 2021 Skywalker Inc.
 */



/*
 * Filename: /home/skywalker/Documents/code/ros/catkin_ws/src/learning_topic/src/poseSubscriber.cpp
 * Path: /home/skywalker/Documents/code/ros/catkin_ws/src/learning_topic/src
 * Created Date: Saturday, April 17th 2021, 8:34:54 pm
 * Author: Skywalker Wang
 * Function: 订阅turtle1/pose topic, 消息类型turtlesim::Pose
 * Copyright (c) 2021 Skywalker Inc.
 */

#include <ros/ros.h>
#include "learning_topic/Person.h"

//回调函数
void infoCallback(const learning_topic::Person::ConstPtr& msg){
    //打印出接收到的消息
    ROS_INFO("Publich Person Info: name:%s age:%d sex:%d", msg->name.c_str(), msg->age, msg->sex);
}

int main(int argc, char **argv){
    // 初始化ROS节点
    ros::init(argc, argv, "person_subscriber");
    //创建节点
    ros::NodeHandle n;
    //创建一个subscriber， 订阅turtle1/pose的topic，注册回调函数
    ros::Subscriber person_info_sub = n.subscribe("/person_info", 10, infoCallback);
    //循环等待回调函数
    ros::spin();

    return 0;
}