/*********************************************************************
 *
 * Software License Agreement (BSD License)
 *
 *  Copyright (c) 2012, Worcester Polytechnic Institute
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above
 *     copyright notice, this list of conditions and the following
 *     disclaimer in the documentation and/or other materials provided
 *     with the distribution.
 *   * Neither the name of the Worcester Polytechnic Institute nor the
 *     names of its contributors may be used to endorse or promote
 *     products derived from this software without specific prior
 *     written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 *  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 *  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 *  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 *  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 *
 *********************************************************************/

/*!
 * \file rovio_teleop.h
 * \brief Allows for control of the Rovio with a joystick.
 *
 * rovio_teleop creates a ROS node that allows the control of a Rovio with a joystick.
 * This node listens to a joy topic and sends messages to the cmd_vel topic in the rovio_move node, head_ctrl service in the rovio_head node, and wav_play service in the rovio_audio node.
 *
 * \author Russell Toris, WPI - rctoris@wpi.edu
 * \date November 22, 2011
 */

#ifndef ROVIO_TELEOP_H_
#define ROVIO_TELEOP_H_

#include <ros/ros.h>
#include <rovio_shared/wav_play.h>
#include <sensor_msgs/Joy.h>

/*!
 * \def ROVIO_WAV
 * The rovio_av wav directory location ROS parameter name
 */
#define ROVIO_WAV "/rovio_shared/rovio_wav"

/*!
 * \def ROVIO_WAV
 * The speed throttle constant
 */
#define THROTTLE 0.66

/*!
 * \class teleop_controller
 * \brief Provides a bridge between the joy topic and the Rovio nodes.
 *
 * The teleop_controller handles the translation between joystick commands and communication to the Rovio nodes.
 */
class teleop_controller
{
public:
  /*!
   * \brief Creates a teleop_controller.
   *
   * Creates a teleop_controller object that can be used control the Rovio with a joystick. ROS nodes, services, and publishers are created and maintained within this object.
   */
  teleop_controller();

private:
  /*!
   * \brief joy topic callback function.
   *
   * Process the joystick command and send messages/service requests to the appropriate Rovio nodes.
   *
   * \param joy the message for the joy topic
   */
  void joy_cback(const sensor_msgs::Joy::ConstPtr& joy);

  ros::NodeHandle node; /*!< a handle for this ROS node */

  ros::Publisher cmd_vel; /*!< the cmd_vel topic */
  ros::ServiceClient head_ctrl, wav_play; /*!< the head_ctrl and wav_play services */
  ros::Subscriber joy_sub; /*!< the joy topic */

  std::string rovio_wav; /*!< the rovio_av wav directory location */
};

/*!
 * Creates and runs the rovio_teleop node.
 *
 * \param argc argument count that is passed to ros::init
 * \param argv arguments that are passed to ros::init
 * \return EXIT_SUCCESS if the node runs correctly
 */
int main(int argc, char **argv);

#endif
