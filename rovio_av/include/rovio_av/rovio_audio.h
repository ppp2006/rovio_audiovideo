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
 * \file rovio_audio.h
 * \brief Communication node to the Rovio's audio devices.
 *
 * rovio_audio creates a ROS node that listens for the name of a .wav file as a string. The file is then streamed and played on the Rovio's speaker.
 *
 * \author Russell Toris, WPI - rctoris@wpi.edu
 * \date November 22, 2011
 */

#ifndef ROVIO_AUDIO_H_
#define ROVIO_AUDIO_H_

#include <ros/ros.h>
#include <rovio_shared/wav_play.h>
#include <string>

/*!
 * \class audio_controller
 * \brief Provides direct communication to the Rovio's audio devices.
 *
 * The audio_controller handles communication to the Rovio's audio devices. ROS nodes and services are created and maintained within this object.
 */
class audio_controller
{
public:
  /*!
   * \brief Creates an audio_controller using ROS parameters.
   *
   * Creates an audio_controller object that can be used to stream .wav files to the Rovio. A valid username, password, and host must be set as ROS parameters.
   */
  audio_controller();

private:
  /*!
   * \brief wav_play service callback function.
   *
   * Process the service request and attempt to stream the given file to the Rovio. This call will block until the file has finished being sent.
   *
   * \param req the request for the wav_play service
   * \param resp the response for the wav_play service; this does not contain any information for this service
   * \return if the file was successfully streamed to the Rovio
   */
  bool wav_play_callback(rovio_shared::wav_play::Request &req, rovio_shared::wav_play::Response &resp);

  std::string host; /*!< host of the Rovio */
  std::string user; /*!< username authentication information for the Rovio */
  std::string pass; /*!< password authentication information for the Rovio */

  ros::NodeHandle node; /*!< a handle for this ROS node */

  ros::ServiceServer wav_play; /*!< the wav_play service */
};

/*!
 * Creates and runs the rovio_audio node.
 *
 * \param argc argument count that is passed to ros::init
 * \param argv arguments that are passed to ros::init
 * \return EXIT_SUCCESS if the node runs correctly
 */
int main(int argc, char **argv);

#endif
