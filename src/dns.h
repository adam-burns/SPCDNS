
#ifndef DNS_H
#define DNS_H

#define MAX_DNS_QUERY_SIZE	512

enum dns_type
{
  RR_A     =  1,	/* IPv4 Address 		*/
  RR_NS    =  2,	/* Name server			*/
  RR_MD    =  3,	/* Mail Destination (obsolete)	*/
  RR_MF    =  4,	/* Mail Forwarder (obsolete)	*/
  RR_CNAME =  5,	/* Canonical name		*/
  RR_SOA   =  6,	/* Start of Authority		*/
  RR_MB    =  7,	/* Mailbox (experimental)	*/
  RR_MG    =  8,	/* Mailgroup (experimental)	*/
  RR_MR    =  9,	/* Mailrename (experimental)	*/
  RR_NULL  = 10,	/* NULL resource (experimental)	*/
  RR_WKS   = 11,	/* Well Known Service		*/
  RR_PTR   = 12,	/* Pointer			*/
  RR_HINFO = 13,	/* Host Info			*/
  RR_MINFO = 14,	/* Mailbox/mail list info	*/
  RR_MX    = 15,	/* Mail Exchange		*/
  RR_TXT   = 16		/* Text				*/
};

enum dns_class
{
  CLASS_IN = 1,		/* Internet			*/
  CLASS_CS = 2,		/* CSNET - obsolete		*/
  CLASS_CH = 3,		/* CHAOS			*/
  CLASS_HS = 4		/* Hesiod			*/
};

enum dns_op
{
  OP_QUERY  = 0,
  OP_IQUERY = 1,
  OP_STATUS = 2
};

enum dns_rcode
{
  RCODE_OKAY            = 0,
  RCODE_FORMAT_ERROR    = 1,
  RCODE_SERVER_FAILURE  = 2,
  RCODE_NAME_ERROR      = 3,
  RCODE_NOT_IMPLEMENTED = 4,
  RCODE_REFUSED         = 5
};  

typedef uint32_t TTL;

typedef struct dns_question_t
{
  const char     *name;
  enum dns_type   type;
  enum dns_class  class;
} dns_question_t;

typedef struct dns_generic_t
{
  const char     *name;
  enum dns_type   type;
  enum dns_class  class;
  TTL             ttl;
} dns_generic_t;


typedef struct dns_mx_rec_t
{
  int         preference;
  const char *name;
} dns_mx_rec_t;

typedef struct dns_mx_t
{
  const char     *name;
  enum dns_type   type;
  enum dns_class  class;
  TTL             ttl;
  size_t          numrec;
  dns_mx_rec_t   *recs;
} dns_mx_t;

typedef union dns_answer_t
{
  struct dns_generic_t generic;
  struct dns_mx_t      mx;
} dns_answer_t;

typedef struct dns_query_t
{
  int             id;
  bool            query;
  enum dns_op     opcode;
  bool            aa;
  bool            tc;
  bool            rd;
  bool            ra;
  enum dns_rcode  rcode;
  int             qdcount;
  int             ancount;
  int             nscount;
  int             arcount;
  dns_question_t *questions;
  dns_answer_t   *answers;
  dns_answer_t   *nameservers;
  dns_answer_t   *addtional;
} dns_query_t;

/**********************************************************************/

extern const char *const c_dns_rec_names   [];
extern const char *const c_dns_class_names [];
extern const char *const c_dns_op_names    [];
extern const char *const c_dns_result_names[];

int	dns_encode	(
			  uint8_t           *restrict,
			  size_t            *restrict,
			  const dns_query_t *const restrict
			) __attribute__ ((nonnull));

int	dns_decode	(
			  dns_query_t *restrict,
			  const uint8_t *const restrict,
			  const size_t
			) __attribute__ ((nonnull(1,2)));

#endif
