/*
 * Filename: /home/skywalker/Documents/code/ros/catkin_ws/src/learning_topic/src/personPublisher.cpp
 * Path: /home/skywalker/Documents/code/ros/catkin_ws/src/learning_topic/src
 * Created Date: Saturday, April 17th 2021, 9:14:04 pm
 * Author: Skywalker Wang
 * 
 * Copyright (c) 2021 Skywalker Inc.
 */



#include <ros/ros.h>
#include "learning_topic/Person.h"

int main(int argc, char **argv){
    //初始化
    ros::init(argc, argv, "person_publisher");
    //创建节点曲柄
    ros::NodeHandle n;
    //创建Publisher，注册发布的topic类型，消息类型为learning_topic::Person, 队列长度为10
    ros::Publisher person_info_pub = n.advertise<learning_topic::Person>("/person_info", 10);
    ros::Rate loop_rate(1);

    int count = 0;
    while (ros::ok()){
        learning_topic::Person person_msg;
        person_msg.name = "Tom";
        person_msg.age = 18;
        person_msg.sex = learning_topic::Person::male;

        person_info_pub.publish(person_msg);
        ROS_INFO("Publich Person Info: name:%s age:%d sex:%d",
        person_msg.name.c_str(), person_msg.age, person_msg.sex);

        loop_rate.sleep();
    }
}