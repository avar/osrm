/*
    open source routing machine
    Copyright (C) Dennis Luxen, 2010

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU AFFERO General Public License as published by
the Free Software Foundation; either version 3 of the License, or
any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU Affero General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
or see http://www.gnu.org/licenses/agpl.txt.
 */

#ifndef REQUEST_HANDLER_H
#define REQUEST_HANDLER_H

#include <algorithm>
#include <cctype> // std::tolower
#include <string>
#include <iostream>
#include <boost/lexical_cast.hpp>
#include <boost/noncopyable.hpp>

#include "BasicDatastructures.h"
#include "../DataStructures/HashTable.h"
#include "../Plugins/BasePlugin.h"
#include "../Plugins/RouteParameters.h"

namespace http {

class RequestHandler : private boost::noncopyable {
public:
	explicit RequestHandler() : _pluginCount(0) { }

	~RequestHandler() {

	    for(unsigned i = 0; i < _pluginVector.size(); i++) {
	        BasePlugin * tempPointer = _pluginVector[i];
	        delete tempPointer;
	    }

	}

	void handle_request(const Request& req, Reply& rep){
		//parse command
	    std::string request(req.uri);
		std::string command;
		std::size_t firstAmpPosition = request.find_first_of("&");
		command = request.substr(1,firstAmpPosition-1);
//		std::cout << "[debug] looking for handler for command: " << command << std::endl;
		try {
			if(pluginMap.Holds(command)) {

				RouteParameters routeParameters;
				std::stringstream ss(( firstAmpPosition == std::string::npos ? "" : request.substr(firstAmpPosition+1) ));
				std::string item;
				while(std::getline(ss, item, '&')) {
				    size_t found = item.find('=');
				    if(found == std::string::npos) {
				        routeParameters.parameters.push_back(item);
				    } else {
				        std::string p = item.substr(0, found);
				        std::transform(p.begin(), p.end(), p.begin(), (int(*)(int)) std::tolower);
				        std::string o = item.substr(found+1);
				        if("jsonp" != p)
				            std::transform(o.begin(), o.end(), o.begin(), (int(*)(int)) std::tolower);
				        routeParameters.options.Set(p, o);
				    }
				}

//				std::cout << "[debug] found handler for '" << command << "' at version: " << pluginMap.Find(command)->GetVersionString() << std::endl;
//				std::cout << "[debug] remaining parameters: " << parameters.size() << std::endl;
				rep.status = Reply::ok;
				_pluginVector[pluginMap.Find(command)]->HandleRequest(routeParameters, rep );

//				std::cout << rep.content << std::endl;
			} else {
				rep = Reply::stockReply(Reply::badRequest);
			}
			return;
		} catch(std::exception& e) {
			rep = Reply::stockReply(Reply::internalServerError);
			std::cerr << "[server error] code: " << e.what() << ", uri: " << req.uri << std::endl;
			return;
		}
	};

	void RegisterPlugin(BasePlugin * plugin) {
		std::cout << "[handler] registering plugin " << plugin->GetDescriptor() << std::endl;
		pluginMap.Add(plugin->GetDescriptor(), _pluginCount);
		_pluginVector.push_back(plugin);
		_pluginCount++;
	}

private:
	HashTable<std::string, unsigned> pluginMap;
	std::vector<BasePlugin *> _pluginVector;
	unsigned _pluginCount;
};
} // namespace http

#endif // REQUEST_HANDLER_H
