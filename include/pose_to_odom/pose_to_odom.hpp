#ifndef _pose_to_odom_hpp
#define _pose_to_odom_hpp

#include <ros/ros.h>
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/PoseWithCovarianceStamped.h>

#include <string>

class pose_to_odom
{
public:
	pose_to_odom( const ros::NodeHandle &_nh, const ros::NodeHandle &_nh_priv );
	
	bool start();

private:
	ros::NodeHandle nh;
	ros::NodeHandle nh_priv;
	ros::Publisher odometry_pub;
	ros::Subscriber pose_with_covariance_stamped_sub;

	std::string given_parent_frame_id;
	std::string given_child_frame_id;

	void pose_with_covariance_stamped_cb(const geometry_msgs::PoseWithCovarianceStampedPtr &msg);
};

#endif   // _pose_to_odom_hpp
