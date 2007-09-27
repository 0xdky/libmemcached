#include <memcached.h>

void parse_opt_servers(memcached_st *memc,
                       char *server_strings)
{
  char *string;
  unsigned int port;
  char *begin_ptr;
  char *end_ptr;

  assert(server_strings);
  assert(memc);

  end_ptr= server_strings + strlen(server_strings);

  for (begin_ptr= server_strings, string= index(server_strings, ','); 
       begin_ptr != end_ptr; 
       string= index(begin_ptr, ','))
  {
    char buffer[HUGE_STRING_LEN];
    char *ptr;
    port= 0;

    memset(buffer, 0, HUGE_STRING_LEN);
    if (string)
    {
      memcpy(buffer, begin_ptr, string - begin_ptr);
      begin_ptr= string+1;
    }
    else
    {
      size_t length= strlen(server_strings);
      memcpy(buffer, begin_ptr, length);
      string= server_strings+length;
      begin_ptr= end_ptr;
    }

    ptr= index(buffer, ':');

    if (ptr)
    {
      ptr[0]= 0;

      ptr++;

      port= strtol(ptr, (char **)NULL, 10);
    }

    memcached_server_add(memc, buffer, port);
  }
}