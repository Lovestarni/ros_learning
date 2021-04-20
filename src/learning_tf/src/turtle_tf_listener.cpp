/*
 * Filename: /home/skywalker/Documents/code/ros/catkin_ws/src/learning_tf/src/turtle
 * Path: /home/skywalker/Documents/code/ros/catkin_ws/src/learning_tf/src
 * Created Date: Tuesday, April 20th 2021, 6:38:15 pm
 * Author: Skywalker Wang
 * 监听tf数据，并计算发布turtle2速度指令
 * Copyright (c) 2021 Skywalker Inc.
 */



#include <ros/ros.h>
#include <tf/transform_listener.h>
#include <geometry_msgs/Twist.h>
#include <turtlesim/Spawn.h>

int main(int argc, char **argv){
    ros::init(argc, argv, "my_tf_lisenner");
    ros::NodeHandle node;

    // 请求产生turtle2
    ros::service::waitForService("/spawn");
    ros::ServiceClient add_turtle = node.serviceClient<turtlesim::Spawn>("/spawn");
    turtlesim::Spawn srv;
    add_turtle.call(srv);

    // 创建发布速度控制指令的publisher
    ros::Publisher turtle_vel = node.advertise<geometry_msgs::Twist>("turtle2/cmd_vel", 10);

    // 创建tf监听器
    tf::TransformListener listener;
    // 设置循环频率
    ros::Rate rate(10.0);
    while(node.ok()){
        tf::StampedTransform transform;
        try{
            // 等待时间设置为3秒超时
            listener.waitForTransform("/turtle2", "/turtle1", ros::Time(0), ros::Duration(3.0));
            listener.lookupTransform("/turtle2", "/turtle1", ros::Time(0), transform);
        }
        catch(tf::TransformException& ex){
            ROS_ERROR("%s", ex.what());
            ros::Duration(1.0).sleep();
            continue;
        }

        // 根据turtle1和turtle2坐标系之间的位置关系，发布turtle2的速度指令
        geometry_msgs::Twist vel_msg;
        vel_msg.angular.z = 4 * atan2(transform.getOrigin().y(), transform.getOrigin().x());
        vel_msg.linear.x = 0.5 * sqrt(pow(transform.getOrigin().y(), 2) + pow(transform.getOrigin().x(), 2));
        turtle_vel.publish(vel_msg);

        rate.sleep();
    }
    return 0;
}