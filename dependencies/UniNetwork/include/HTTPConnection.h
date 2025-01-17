/*/*************************************************************************
 *                                                                         *
 * UniNetwork, Library for Netwerk Communication for my					   *
 * Gameproject Spacecraft												   *			 
 * Copyright (C) 2014, 2015, 2016, 2017 Dario Rekowski.					   *
 * Email: dario.rekowski@gmx.de   Web: www.spacecrafting.de                *
 *                                                                         *
 * This program is free software: you can redistribute it and/or modify    *
 * it under the terms of the GNU General Public License as published by    *
 * the Free Software Foundation, either version 3 of the License, or       *
 * any later version.													   *
 *																		   *
 * This program is distributed in the hope that it will be useful,	       *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of	       *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the	       *
 * GNU General Public License for more details.							   *
 *																		   *
 * You should have received a copy of the GNU General Public License	   *
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.   *
 *                                                                         *
 ***************************************************************************/

#ifndef __UNI_NETWORK_HTTP_CONNECTION_H
#define __UNI_NETWORK_HTTP_CONNECTION_H

#include "Connection.h"

#include "Poco/Net/Net.h"
#include "Poco/Net/HTTPClientSession.h"
#include "Poco/Mutex.h"



class UNI_NETWORK_API HTTPConnection : public Connection
{
public:
	HTTPConnection(const DRNetServerConfig& cfg);
	~HTTPConnection();

	virtual DRReturn run();

	virtual DRNet_Status send(const DRNetRequest&  sendRequest);
	virtual DRNet_Status send(const DRNetRequest& sendRequest, UniLib::server::RequestCommand* command);
	virtual DRNet_Status recv(std::string& recvDatas);

protected:
	Poco::Mutex mRequestMutex;
	Poco::Mutex mRecvMutex;
	Poco::Net::HTTPClientSession mClientSession;

	struct RequestWithReturnCommand {
		RequestWithReturnCommand(const DRNetRequest& sendRequest, UniLib::server::RequestCommand* command)
			: request(sendRequest), command(command) {}
		DRNetRequest request;
		UniLib::server::RequestCommand* command;
	};

	std::queue<DRNetRequest> mSendRequests;
	std::queue<RequestWithReturnCommand> mSendCommandRequests;
	std::queue<std::string> mReciveDatas;
};

#endif __UNI_NETWORK_HTTP_CONNECTION_H