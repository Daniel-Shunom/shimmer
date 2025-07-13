typedef enum {
  JSON_NULL,
  JSON_BOOL,
  JSON_STRING,
  JSON_NUMBER,
  JSON_ARRAY,
  JSON_OBJECT,
} JsonSpec;

typedef struct JsonValue JsonValue;

typedef struct {
  char      *key;
  JsonValue *value;
} JsonPair;

struct JsonValue {
 JsonSpec type;
 union {
   int    jbool;
   double jnum;
   char   *jstr;

   struct {
     JsonValue **jvals;
     int       count;
   } j_array;

   struct {
     JsonPair *pairs;
     int      count;
   } j_object;
 } json;
};

typedef enum {
  LSP_REQUEST,
  LSP_RESPONSE,
  LSP_NOTIFICATION,

} LspMessageType;

typedef enum {
  PARSE_ERROR                        = -32700,
  INVALID_REQUEST                    = -32600,
  METHOD_NOT_FOUND                   = -32601,
  INVALID_PARAMS                     = -32602,
  INTERNAL_ERROR                     = -32603,
  JSONRPC_RESERVED_ERROR_RANGE_START = -32099,
  JSONRPC_RESERVED_ERROR_RANGE_END   = -32000,
  SERVER_NOT_INITIALIZED             = -32002,
  UNKNOWN_ERROR_CODE                 = -32001,
  LSP_RESERVED_ERROR_RANGE_START     = -32899,
  REQUEST_FAILED                     = -32803,
  SERVER_CANCELLED                   = -32802,
  CONTENT_MODIFIED                   = -32801,
  REQUEST_CANCELLED                  = -32800,
  LSP_RESERVED_ERROR_RANGE_END       = -32800,
} LSPErrorCodes;

typedef enum { 
  ID_NULL, 
  ID_NUM, 
  ID_STR 
} JRPCIDKind;

typedef struct {
  JRPCIDKind id_kind;

  union {
    double num;
    char   *str;
  } id_value;
} JRPCid;


typedef struct {
 LSPErrorCodes code;
 char *message;
 JsonValue data;
} JRPCError;

typedef struct {
  JsonValue result;
} JRPCResult;

typedef struct {
  char *jsonrpc;
  char *method;
  JRPCid id; 
  union {
    JsonValue value;
    void* empty;
  } params;
} JRPCRequest;

typedef struct {
  char *jsonrpc;
  union {
    JRPCResult result;
    JRPCError  error;
  } response;
  JRPCid id;
} JRPCResponse;

typedef struct {
  int  content_length;
  char content_type[32];
} LSPHeader;

typedef struct {
  char      *method;
  JsonValue params;
} LSPNotificationMessage;

typedef struct {
  union {
    int  id_num;
    char *id_str;
  } id;
} LSPCancelParams;

typedef struct {
  union {
    int  token_num;
    char *token_str;
  } progress_token;
  // ideally this should be any value for now but I
  // haven't yet figured out how to do that :)
  int value;
} LSPProgressParams;

typedef struct {
  LSPHeader header;
  LspMessageType type;
  union {
    JRPCRequest            request;
    JRPCResponse           response;
    LSPProgressParams      progress_params;
    LSPCancelParams        cancel_params;
    LSPNotificationMessage notification_message;
  } value;
} LSPMessage;

JRPCRequest* jrpc_parse_request(const char *json_text);
char*        jrpc_serialize_response(const JRPCResponse *res);
char*        jrpc_serialize_request(const JRPCRequest *req);
void         jrpc_free_request(JRPCRequest *r);
void         jrpc_free_response(JRPCResponse *r);
void         lsp_serialize_message(LSPMessage *message);
LSPMessage*  lsp_parse_message(const char *text);

