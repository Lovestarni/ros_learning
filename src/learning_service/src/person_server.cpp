/*
 * Filename: /home/skywalker/Documents/code/ros/catkin_ws/src/learning_service/src/person_server.cpp
 * Path: /home/skywalker/Documents/code/ros/catkin_ws/src/learning_service/src
 * Created Date: Monday, April 19th 2021, 6:58:41 pm
 * Author: Skywalker Wang
 * 执行show_person服务，服务数据类型learning_service::Person
 * Copyright (c) 2021 Skywalker Inc.
 */



#include <ros/ros.h>
#include "learning_service/Person.h"


// 回调函数
bool personCallback(learning_service::Person::Request &req, learning_service::Person::Response &res)
{
    ROS_INFO("Person: name: %s, age: %d, sex: %d", req.name.c_str(), req.age, req.sex);
    
    //设置反馈数据
    res.result = "OK";

    return true;
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "person_server");
    ros::NodeHandle node;

    // 创建一个名为/turtle_command的server，并注册回调函数
    ros::ServiceServer command_service = node.advertiseService("/show_person", personCallback);

    ROS_INFO("Ready to show person information.");

    // 循环等待回调函数
    ros::spin();

    return 0;
}