/*
 * Filename: /home/skywalker/Documents/code/ros/catkin_ws/src/learning_service/src/turtle_client.cpp
 * Path: /home/skywalker/Documents/code/ros/catkin_ws/src/learning_service/src
 * Created Date: Monday, April 19th 2021, 10:28:07 am
 * Author: Skywalker Wang
 * 
 * Copyright (c) 2021 Skywalker Inc.
 */



#include <ros/ros.h>
#include <turtlesim/Spawn.h>

int main(int argc, char ** argv){
    ros::init(argc, argv, "turtle_spawn");
    ros::NodeHandle node;
    // 发现/spawn服务后，创建客户端，连接名称为/spawn的service
    ros::service::waitForService("/spawn");
    ros::ServiceClient add_turtle = node.serviceClient<turtlesim::Spawn>("/spawn");
    //初始化turtlesim::Spawn的请求数据
    turtlesim::Spawn srv;
    srv.request.x = 2.0;
    srv.request.y = 2.0;
    srv.request.name = "turtle2";

    //请求服务调用
    ROS_INFO("Call service to spawn turtle[x:%0.6f, y:%0.6f, name:%s]", srv.request.x, srv.request.y, srv.request.name.c_str());
    add_turtle.call(srv);
    //显示调用结果
    ROS_INFO("Spawn turtle successfully [name:%s]", srv.response.name.c_str());
    return 0;
}