/*
 * Filename: /home/skywalker/Documents/code/ros/catkin_ws/src/learning_service/src/person_client.cpp
 * Path: /home/skywalker/Documents/code/ros/catkin_ws/src/learning_service/src
 * Created Date: Tuesday, April 20th 2021, 9:56:38 am
 * Author: Skywalker Wang
 * 请求/show_person服务，服务数据类型learning_service::Person
 * Copyright (c) 2021 Skywalker Inc.
 */



#include <ros/ros.h>
#include "learning_service/Person.h"

int main(int argc, char ** argv){
    ros::init(argc, argv, "person_client");
    ros::NodeHandle node;
    // 发现/spawn服务后，创建客户端，连接名称为/spawn的service
    ros::service::waitForService("/show_person");
    ros::ServiceClient person_client = node.serviceClient<learning_service::Person>("/show_person");
    //初始化turtlesim::Spawn的请求数据
    learning_service::Person srv;
    srv.request.name = "Tom";
    srv.request.age = 15;
    srv.request.sex = learning_service::Person::Request::female;

    //请求服务调用
    ROS_INFO("Person: name: %s, age: %d, sex: %d", srv.request.name.c_str(), srv.request.age, srv.request.sex);
    person_client.call(srv);
    //显示调用结果
    ROS_INFO("show person information result: %s", srv.response.result.c_str());
    return 0;
}