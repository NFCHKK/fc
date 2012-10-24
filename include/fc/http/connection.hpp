#pragma once
#include <fc/vector.hpp>
#include <fc/string.hpp>
#include <fc/shared_impl.hpp>

namespace fc { 
  namespace ip { class endpoint; }
  class tcp_socket;

  namespace http {

  struct header {
    fc::string key;
    fc::string val;
  };

  struct reply {
     enum status_code {
         OK                  = 200,
         NotFound            = 404,
         Found               = 302,
         InternalServerError = 500
     };
     int                     status;
     fc::vector<header>      headers;
     fc::vector<char>        body;
  };

  struct request {
     fc::string              method;
     fc::string              domain;
     fc::string              path;
     fc::vector<header>      headers;
     fc::vector<char>        body;
  };

  /**
   *  Connections have reference semantics, all copies refer to the same
   *  underlying socket.  
   */
  class connection {
    public:
      // used for clients
      void         connect_to( const fc::ip::endpoint& ep );
      http::reply  request( const fc::string& method, const fc::string& url, const fc::string& body );

      // used for servers
      fc::tcp_socket& get_socket();

      http::request    read_request();
      void             send_reply( const http::reply& );

      FC_REFERENCE_TYPE(connection)
  };

} } // fc::http

