/* -*- mode: c++; c-basic-offset: 4; indent-tabs-mode: nil -*-

   this file is part of rcssserver3D
   Fri May 9 2003
   Copyright (C) 2002,2003 Koblenz University
   Copyright (C) 2003 RoboCup Soccer Server 3D Maintenance Group
   $Id: communit.cpp,v 1.2.2.1 2003/12/22 15:21:53 rollmark Exp $

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; version 2 of the License.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*/
#include "communit.h"
#include <netinet/in.h>
#include <iostream>
#include <rcssbase/net/exception.hpp>

using namespace std;
using namespace rcss::net;

CommUnit::CommUnit()
{
}

CommUnit::~CommUnit()
{
  CloseConnection ();
}

void CommUnit::CloseConnection()
{
  mSocket.close();
}

bool CommUnit::OpenConnection(std::string host, int port)
{
  mSocket.open();

  cout << "(CommUnit) connecting to ";
  cout << host << ":" << port << endl;

  Addr local(INADDR_ANY,INADDR_ANY);
  mSocket.bind(local);

  try
    {
      Addr server(port,string(host));
      mSocket.connect(server);
    }

  catch (ConnectErr error)
    {
      cerr << "(CommUnit) connection failed with: \n\t"
           << strerror(errno) << endl;
      return false;
    }

  if (mSocket.isConnected())
    {
      cout << "(CommUnit) connected successfully" << endl;
      return true;
    }

  return false;
}


bool
CommUnit::SendMessage(const std::string& msg)
{
    return SendMessage(msg.c_str());
}

bool
CommUnit::SendMessage(const char* buf)
{
  int l = strlen(buf);
  return (mSocket.send(buf, l) == l);
}

int CommUnit::GetMessage (char* buf, int size)
{
  int l = mSocket.recv(0,buf,size,0);

  if (l < 0)
    {
      // non blocking socket, no data available
      l = 0;
    }

  return l;
}
