#include <cstdlib>
#include <arpa/inet.h>
#include <cstdlib>
#include <ros/ros.h>
#include <rovio_av/rovio_audio.h>
#include <rovio_shared/rovio_http.h>
#include <rovio_shared/wav_play.h>
#include <string>
#include <sstream>
#include <sys/socket.h>


int main(int argc, char **argv)
{
  ros::init(argc, argv, "rovio_av_test");
  if (argc != 2)
  {
    ROS_INFO("usage: rovio_av_test hello.wav");
    return 1;
  }

  ros::NodeHandle n;
  ros::ServiceClient client = n.serviceClient<rovio_shared::wav_play>("wav_play");
  rovio_shared::wav_play srv;
  std::string s_argv(argv[1]);
  srv.request.f = s_argv;
  
  ROS_INFO("srv.request.f=%s", argv[1]);
  if (client.call(srv))
  {
//    ROS_INFO("Sum: %ld", (long int)srv.response.sum);
  }
  else
  {
    ROS_ERROR("Failed to call service send_a_wav");
    return 1;
  }

  return 0;
}
