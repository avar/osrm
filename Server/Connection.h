/*
    open source routing machine
    Copyright (C) Dennis Luxen, others 2010

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

#ifndef CONNECTION_H
#define CONNECTION_H

#include <vector>

#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/bind.hpp>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>

#include "../DataStructures/Util.h"
#include "BasicDatastructures.h"
#include "RequestHandler.h"
#include "RequestParser.h"

#include "zlib.h"

namespace http {

/// Represents a single connection from a client.
class Connection : public boost::enable_shared_from_this<Connection>, private boost::noncopyable {
public:
    explicit Connection(boost::asio::io_service& io_service, RequestHandler& handler) : strand(io_service), TCPsocket(io_service), requestHandler(handler) {}

    boost::asio::ip::tcp::socket& socket() {
        return TCPsocket;
    }

    /// Start the first asynchronous operation for the connection.
    void start() {
        TCPsocket.async_read_some(boost::asio::buffer(incomingDataBuffer), strand.wrap( boost::bind(&Connection::handleRead, this->shared_from_this(), boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred)));
    }

private:
    void handleRead(const boost::system::error_code& e, std::size_t bytes_transferred) {
        if (!e) {
            CompressionType compressionType(none);
            boost::tribool result;
            boost::tie(result, boost::tuples::ignore) = requestParser.Parse( request, incomingDataBuffer.data(), incomingDataBuffer.data() + bytes_transferred, &compressionType);

            if (result) {
//                std::cout << "----" << std::endl;
//                if(compressionType == gzipRFC1952)
//                    std::cout << "[debug] supports gzip" << std::endl;
//                if(compressionType == deflateRFC1951)
//                    std::cout << "[debug] Supports deflate" << std::endl;

                requestHandler.handle_request(request, reply);

                if(compressionType == deflateRFC1951) {
                    Header compressionHeader;
                    compressionHeader.name = "Content-Encoding";
                    compressionHeader.value = "deflate";
                    reply.headers.insert(reply.headers.begin(), compressionHeader);   //push_back(compressionHeader);

                    std::vector<unsigned char> compressed;
//                    double time = get_timestamp();
                    compressCharArray(reply.content.c_str(), strlen(reply.content.c_str()), compressed);
//                    std::cout << "[info] compression took " << get_timestamp() - time << " seconds." << std::endl;

                    reply.setSize(compressed.size());
                    std::vector<boost::asio::const_buffer> outputBuffer = reply.HeaderstoBuffers();
                    outputBuffer.push_back(boost::asio::buffer(compressed));
//                    std::cout << "[debug] outbuffer.size(): " << outputBuffer.size() << std::endl;
                    boost::asio::async_write(TCPsocket, outputBuffer, strand.wrap( boost::bind(&Connection::handleWrite, this->shared_from_this(), boost::asio::placeholders::error)));

                } else {
                    boost::asio::async_write(TCPsocket, reply.toBuffers(), strand.wrap( boost::bind(&Connection::handleWrite, this->shared_from_this(), boost::asio::placeholders::error)));
                }

            } else if (!result) {
                reply = Reply::stockReply(Reply::badRequest);
                boost::asio::async_write(TCPsocket, reply.toBuffers(), strand.wrap( boost::bind(&Connection::handleWrite, this->shared_from_this(), boost::asio::placeholders::error)));
            } else {
                TCPsocket.async_read_some(boost::asio::buffer(incomingDataBuffer), strand.wrap( boost::bind(&Connection::handleRead, this->shared_from_this(), boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred)));
            }
        }
    }

    /// Handle completion of a write operation.
    void handleWrite(const boost::system::error_code& e) {
        if (!e) {
            // Initiate graceful connection closure.
            boost::system::error_code ignoredEC;
            TCPsocket.shutdown(boost::asio::ip::tcp::socket::shutdown_both, ignoredEC);
        }
        // No new asynchronous operations are started. This means that all shared_ptr
        // references to the connection object will disappear and the object will be
        // destroyed automatically after this handler returns. The connection class's
        // destructor closes the socket.
    }

    void compressCharArray(const void *in_data, size_t in_data_size, std::vector<unsigned char> &buffer) {
//        std::vector<unsigned char> buffer;

        const size_t BUFSIZE = 128 * 1024;
        unsigned char temp_buffer[BUFSIZE];

        z_stream strm;
        strm.zalloc = 0;
        strm.zfree = 0;
        strm.next_in = (unsigned char *)(in_data);
        strm.avail_in = in_data_size;
        strm.next_out = temp_buffer;
        strm.avail_out = BUFSIZE;

        deflateInit(&strm, Z_BEST_SPEED);

        while (strm.avail_in != 0) {
            int res = deflate(&strm, Z_NO_FLUSH);
            assert(res == Z_OK);
            if (strm.avail_out == 0) {
                buffer.insert(buffer.end(), temp_buffer, temp_buffer + BUFSIZE);
                strm.next_out = temp_buffer;
                strm.avail_out = BUFSIZE;
            }
        }

        int deflate_res = Z_OK;
        while (deflate_res == Z_OK) {
            if (strm.avail_out == 0) {
                buffer.insert(buffer.end(), temp_buffer, temp_buffer + BUFSIZE);
                strm.next_out = temp_buffer;
                strm.avail_out = BUFSIZE;
            }
            deflate_res = deflate(&strm, Z_FINISH);
        }

        assert(deflate_res == Z_STREAM_END);
        buffer.insert(buffer.end(), temp_buffer, temp_buffer + BUFSIZE - strm.avail_out);
        deflateEnd(&strm);

//        out_data.swap(buffer);
    }

    boost::asio::io_service::strand strand;
    boost::asio::ip::tcp::socket TCPsocket;
    RequestHandler& requestHandler;
    boost::array<char, 8192> incomingDataBuffer;
    Request request;
    RequestParser requestParser;
    Reply reply;
};

} // namespace http

#endif // CONNECTION_H
