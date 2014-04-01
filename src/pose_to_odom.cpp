#include "pose_to_odom/pose_to_odom.hpp"

pose_to_odom::pose_to_odom( const ros::NodeHandle &_nh, const ros::NodeHandle &_nh_priv ) :
	nh( _nh ),
	nh_priv( _nh_priv ),
	given_child_frame_id("base_footprint"),
	given_parent_frame_id("lidar_odom")
{
}

bool pose_to_odom::start()
{
	if( !pose_with_covariance_stamped_sub )
		pose_with_covariance_stamped_sub = nh.subscribe( "poseupdate", 1, &pose_to_odom::pose_with_covariance_stamped_cb, this );

	if( !odometry_pub )
		odometry_pub = nh.advertise<nav_msgs::Odometry>( "lidar_odom", 2);

	return true;
}

void pose_to_odom::pose_with_covariance_stamped_cb(const geometry_msgs::PoseWithCovarianceStampedPtr &msg)
{
	nav_msgs::OdometryPtr odom_msg(new nav_msgs::Odometry);
	odom_msg->header = msg->header;
	odom_msg->header.frame_id = given_parent_frame_id;
	
	odom_msg->pose = msg->pose;
	odom_msg->pose.covariance[14] = FLT_MAX;
	odom_msg->pose.covariance[21] = FLT_MAX;
	odom_msg->pose.covariance[28] = FLT_MAX;
	
	odom_msg->child_frame_id = given_child_frame_id;

	odometry_pub.publish(odom_msg);
}
