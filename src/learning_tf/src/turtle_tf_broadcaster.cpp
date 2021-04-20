/*
 * Filename: /home/skywalker/Documents/code/ros/catkin_ws/src/learning_tf/src/turtle_
 * Path: /home/skywalker/Documents/code/ros/catkin_ws/src/learning_tf/src
 * Created Date: Tuesday, April 20th 2021, 5:12:04 pm
 * Author: Skywalker Wang
 * 产生tf数据并计算，发布turtle2的速度指令
 * Copyright (c) 2021 Skywalker Inc.
 */



#include <ros/ros.h>
#include <tf/transform_broadcaster.h>
#include <turtlesim/Pose.h>

std::string turtle_name;

void poseCallback(const turtlesim::PoseConstPtr& msg){
    // 创建广播器
    static tf::TransformBroadcaster br;

    // 初始化tf数据
    tf::Transform transform;
    // 设置平移
    transform.setOrigin(tf::Vector3(msg->x, msg->y, 0.0));
    tf::Quaternion q;
    q.setRPY(0, 0, msg->theta);
    // 设置旋转量
    transform.setRotation(q);

    //广播world与海龟坐标系间的tf数据(打上时间戳)
    br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), "world", turtle_name));
}

int main(int argc, char **argv){
    ros::init(argc, argv, "my_tf_broadcaster");

    if(argc != 2){
        ROS_ERROR("need turtle name as argument");
        return -1;
    }

    turtle_name = argv[1];

    // 订阅海龟位置话题
    ros::NodeHandle node;
    ros::Subscriber sub = node.subscribe(turtle_name+"/pose", 10, &poseCallback);

    // 循环等待
    ros::spin();

    return 0;
}