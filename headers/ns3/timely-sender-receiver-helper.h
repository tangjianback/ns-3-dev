/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2008 INRIA
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Author: Mohamed Amine Ismail <amine.ismail@sophia.inria.fr>
 */
#ifndef TIMELY_SENDER_RECIVER_HELPER_H
#define TIMELY_SENDER_RECEIVER_HELPER_H

#include <stdint.h>
#include "ns3/application-container.h"
#include "ns3/node-container.h"
#include "ns3/object-factory.h"
#include "ns3/ipv4-address.h"
#include "ns3/timely-receiver.h"
#include "ns3/timely-sender.h"
#include "ns3/timely-trace-client.h"

namespace ns3 {
/**
 * \brief Create a server application which waits for input udp packets
 *        and uses the information carried into their payload to compute
 *        delay and to determine if some packets are lost.
 */
class TimelyReceiverHelper
{
public:
  /**
   * Create TimelyReceiverHelper which will make life easier for people trying
   * to set up simulations with udp-client-server application.
   *
   */
  TimelyReceiverHelper ();

  /**
   * Create TimelyReceiverHelper which will make life easier for people trying
   * to set up simulations with udp-client-server application.
   *
   * \param port The port the server will wait on for incoming packets
   */
  TimelyReceiverHelper(uint16_t port);
  TimelyReceiverHelper(uint16_t port, uint16_t pg);

  /**
   * Record an attribute to be set in each Application after it is is created.
   *
   * \param name the name of the attribute to set
   * \param value the value of the attribute to set
   */
  void SetAttribute (std::string name, const AttributeValue &value);

  /**
   * Create one udp server application on each of the Nodes in the
   * NodeContainer.
   *
   * \param c The nodes on which to create the Applications.  The nodes
   *          are specified by a NodeContainer.
   * \returns The applications created, one Application per Node in the
   *          NodeContainer.
   */
  ApplicationContainer Install (NodeContainer c);
  Ptr<TimelyReceiver> GetServer (void);
private:
  ObjectFactory m_factory;
  Ptr<TimelyReceiver> m_receiver;
};

/**
 * \brief Create a client application which sends udp packets carrying
 *  a 32bit sequence number and a 64 bit time stamp.
 *
 */
class TimelySenderHelper
{

public:
  /**
   * Create TimelySenderHelper which will make life easier for people trying
   * to set up simulations with udp-client-server.
   *
   */
  TimelySenderHelper ();

  /**
   *  Create TimelySenderHelper which will make life easier for people trying
   * to set up simulations with udp-client-server.
   *
   * \param ip The IP address of the remote udp server
   * \param port The port number of the remote udp server
   */

  TimelySenderHelper (Ipv4Address ip, uint16_t port);
  TimelySenderHelper (Ipv4Address ip, uint16_t port, uint16_t pg);
  TimelySenderHelper (Ipv6Address ip, uint16_t port);
  TimelySenderHelper (Address ip, uint16_t port);

  /**
   * Record an attribute to be set in each Application after it is is created.
   *
   * \param name the name of the attribute to set
   * \param value the value of the attribute to set
   */
  void SetAttribute (std::string name, const AttributeValue &value);

  /**
     * \param c the nodes
     *
     * Create one udp client application on each of the input nodes
     *
     * \returns the applications created, one application per input node.
     */
  ApplicationContainer Install (NodeContainer c);

private:
  ObjectFactory m_factory;
};
/**
 * Create TimelyTraceClient application which sends udp packets based on a trace
 * file of an MPEG4 stream. Trace files could be downloaded form :
 * http://www.tkn.tu-berlin.de/research/trace/ltvt.html (the 2 first lines of
 * the file should be removed)
 * A valid trace file is a file with 4 columns:
 * -1- the first one represents the frame index
 * -2- the second one indicates the type of the frame: I, P or B
 * -3- the third one indicates the time on which the frame was generated by the encoder
 * -4- the fourth one indicates the frame size in byte
*/
class TimelyTraceClientHelper
{
public:
  /**
   * Create TimelyTraceClientHelper which will make life easier for people trying
   * to set up simulations with udp-client-server.
   *
   */
  TimelyTraceClientHelper ();

  /**
   * Create TimelyTraceClientHelper which will make life easier for people trying
   * to set up simulations with udp-client-server.
   *
   * \param ip The IP address of the remote udp server
   * \param port The port number of the remote udp server
   * \param filename the file from which packet traces will be loaded
   */
  TimelyTraceClientHelper (Address ip, uint16_t port, std::string filename);
  TimelyTraceClientHelper (Ipv4Address ip, uint16_t port, std::string filename);
  TimelyTraceClientHelper (Ipv6Address ip, uint16_t port, std::string filename);

  /**
    * Record an attribute to be set in each Application after it is is created.
    *
    * \param name the name of the attribute to set
    * \param value the value of the attribute to set
    */
  void SetAttribute (std::string name, const AttributeValue &value);

  /**
    * \param c the nodes
    *
    * Create one udp trace client application on each of the input nodes
    *
    * \returns the applications created, one application per input node.
    */
  ApplicationContainer Install (NodeContainer c);

private:
  ObjectFactory m_factory;
};

} // namespace ns3

#endif 
