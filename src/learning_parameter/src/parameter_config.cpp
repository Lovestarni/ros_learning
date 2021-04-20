/*
 * Filename: /home/skywalker/Documents/code/ros/catkin_ws/src/learning_parameter/src/parameter_config.cpp
 * Path: /home/skywalker/Documents/code/ros/catkin_ws/src/learning_parameter/src
 * Created Date: Tuesday, April 20th 2021, 2:25:54 pm
 * Author: Skywalker Wang
 * 
 * Copyright (c) 2021 Skywalker Inc.
 */



#include <ros/ros.h>
#include <string>
#include <std_srvs/Empty.h>

int main(int argc, char **argv){
    int red, green, blue;

    ros::init(argc, argv, "parameter_config");
    ros::NodeHandle node;

    ros::param::get("background_r", red);
    ros::param::get("background_g", green);
    ros::param::get("background_b", blue);

    ROS_INFO("Get default color rgb is %d, %d, %d", red, blue, green);

    ros::param::set("background_r", 0);
    ros::param::set("background_g", 255);
    ros::param::set("background_b", 255);

    ROS_INFO("Color is set to rgb 255,255,255");

    ros::param::get("background_r", red);
    ros::param::get("background_g", green);
    ros::param::get("background_b", blue);

    ROS_INFO("Re-get default color rgb is %d, %d, %d", red, blue, green);

    ros::service::waitForService("/clear");
    ros::ServiceClient clear_background = node.serviceClient<std_srvs::Empty>("/clear");
    std_srvs::Empty srv;
    clear_background.call(srv);

    sleep(1);

    return 0;
}