/*
 * @Author: MingshanHe 
 * @Date: 2021-12-05 04:08:58 
 * @Last Modified by: MingshanHe
 * @Last Modified time: 2021-12-05 04:13:10
 * @Licence: MIT Licence
 */
#include <ros/ros.h>
#include <geometry_msgs/Pose.h>
#include <tf2_geometry_msgs/tf2_geometry_msgs.h>

#define POSE_TOPIC    "/desired_carteisan_pose_cmd"
#define TOPIC_HZ        5.0



/*
rostopic pub /desired_carteisan_pose_cmd geometry_msgs/Pose \
"
position: 
    x: 0
    y: 0.30 
    z: 0.30 
orientation: 
    x: 0 
    y: 1 
    z: 0.0 
    w: 0.0"
*/
int main(int argc, char ** argv)
{
    ros::init(argc, argv, "generate_traj");
    ros::NodeHandle nh;

    ros::Publisher pose_pub = nh.advertise<geometry_msgs::Pose>(POSE_TOPIC, 5);
    ros::Duration Sleep(5.0);
    Sleep.sleep();
    ros::Rate   loop_rate(TOPIC_HZ);
    geometry_msgs::Pose pose_msg;

    tf2::Quaternion q_rot;
    double r=0, p=-M_PI, y=M_PI;  // Rotate the previous pose by 180* about X
    q_rot.setRPY(r, p, y);
    
    double _x = q_rot.getX();
    double _y = q_rot.getY();
    double _z = q_rot.getZ();
    double _w = q_rot.getW();
  

    
    double t = 0;
    while (ros::ok())
    {
        
        pose_msg.position.x = 0.3;
        pose_msg.position.y = 0.3;
        pose_msg.position.z = 0.3;

        pose_msg.orientation.x = _x;
        pose_msg.orientation.y = _y;
        pose_msg.orientation.z = _z;
        pose_msg.orientation.w = _w;

        t += 1/TOPIC_HZ;
        pose_pub.publish(pose_msg);
        loop_rate.sleep();
    }
    /*
    pose_msg.position.x = 0.3;
    pose_msg.position.y = 0.3;
    pose_msg.position.z = 0.3;

    pose_msg.orientation.x = _x;
    pose_msg.orientation.y = _y;
    pose_msg.orientation.z = _z;
    pose_msg.orientation.w = _w;

    pose_pub.publish(pose_msg);
    */
}