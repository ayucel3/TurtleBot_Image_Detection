#include "watermelon_finder.hpp"

using std::vector;
using std::make_tuple;

bool found_watermelon() {
  return false;
}

std::ostream &operator<<(std::ostream &os, const Goal &g) {
  os << "(" << std::get<0>(g) << ", " << std::get<1>(g) << ") (" <<
    std::get<2>(g) << ", " << std::get<3>(g) << ")";
  return os;
}

int main(int argc, char** argv){
  ros::init(argc, argv, "watermelon_finder");

  //tell the action client that we want to spin a thread by default
  MoveBaseClient ac("move_base", true);

  //wait for the action server to come up
  while(!ac.waitForServer(ros::Duration(5.0))){
    ROS_INFO("Waiting for the move_base action server to come up");
  }

  move_base_msgs::MoveBaseGoal goal;
  vector<Goal> goals;
  goals.push_back(make_tuple(5.42, 2.72, -0.7, 0.7));
  goals.push_back(make_tuple(4.05, -4.43, 1.0, 0.0));
  goals.push_back(make_tuple(-6.38, -1.5, 1.0, 0.0));

  for(auto it = goals.begin(); it != goals.end(); ++it) {
    goal.target_pose.header.frame_id = "map";
    goal.target_pose.header.stamp = ros::Time::now();
    
    std::tie(goal.target_pose.pose.position.x,
	     goal.target_pose.pose.position.y,
	     goal.target_pose.pose.orientation.z,
	     goal.target_pose.pose.orientation.w) = *it;

    ROS_INFO("Sending goal");
    ac.sendGoal(goal);

    ac.waitForResult();

    if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED) {
      ROS_INFO("The base successfully moved to (%.2f, %.2f)", std::get<0>(*it), std::get<1>(*it));
      ROS_INFO("%s", found_watermelon()?"True":"False");
    }
    else
      ROS_INFO("The base failed to move to (%.2f, %.2f)", std::get<0>(*it), std::get<1>(*it));
    ros::Duration(1.0).sleep();
  }

  return 0;
}
