#include <stdio.h>
#include <unistd.h>
#include <getopt.h>
#include <memcached.h>
#include "client_options.h"
#include "utilities.h"

static int opt_verbose= 0;
static time_t opt_expire= 0;
static char *opt_servers= NULL;

/* Prototypes */
void options_parse(int argc, char *argv[]);

int main(int argc, char *argv[])
{
  memcached_st *memc;
  memcached_return rc;

  options_parse(argc, argv);

  memc= memcached_init(NULL);

  if (opt_servers)
    parse_opt_servers(memc, opt_servers);
  
  while (optind < argc) 
  {
    if (opt_verbose) 
      printf("key: %s\nexpires: %llu\n", argv[optind], (unsigned long long)opt_expire);
    rc = memcached_delete(memc, argv[optind], strlen(argv[optind]), opt_expire);

    if (rc != MEMCACHED_SUCCESS) 
    {
      fprintf(stderr, "memrm: %s: memcache error %s\n", 
	      argv[optind], memcached_strerror(memc, rc));
    }

    optind++;
  }

  memcached_deinit(memc);

  free(opt_servers);

  return 0;
}


void options_parse(int argc, char *argv[])
{
  static struct option long_options[]=
  {
    {"version", no_argument, NULL, OPT_VERSION},
    {"help", no_argument, NULL, OPT_HELP},
    {"verbose", no_argument, &opt_verbose, OPT_VERBOSE},
    {"debug", no_argument, &opt_verbose, OPT_DEBUG},
    {"servers", required_argument, NULL, OPT_SERVERS},
    {"expire", required_argument, NULL, OPT_EXPIRE},
    {0, 0, 0, 0},
  };
  int option_index= 0;
  int option_rv;

  while (1) 
  {
    option_rv= getopt_long(argc, argv, "Vhvds:", long_options, &option_index);
    if (option_rv == -1) break;
    switch (option_rv)
    {
    case 0:
      break;
    case OPT_VERBOSE: /* --verbose or -v */
      opt_verbose = OPT_VERBOSE;
      break;
    case OPT_DEBUG: /* --debug or -d */
      opt_verbose = OPT_DEBUG;
      break;
    case OPT_VERSION: /* --version or -V */
      printf("memcache tools, memrm, v1.0\n");
      exit(0);
      break;
    case OPT_HELP: /* --help or -h */
      printf("useful help messages go here\n");
      exit(0);
      break;
    case OPT_SERVERS: /* --servers or -s */
      opt_servers= strdup(optarg);
      break;
    case OPT_EXPIRE: /* --expire */
      opt_expire= (time_t)strtoll(optarg, (char **)NULL, 10);
      break;
    case '?':
      /* getopt_long already printed an error message. */
      exit(1);
    default:
      abort();
    }
  }
}