struct Header {
  int content_length;
  char content_type[];
};


typedef enum {
  JSON_NULL,
  JSON_BOOL,
  JSON_STRING,
  JSON_NUMBER,
  JSON_ARRAY,
  JSON_OBJECT,
} JsonSpec;

typedef enum {
  PARSE_ERROR = -32700,
  INVALID_REQUEST = -32600,
  METHOD_NOT_FOUND = -32601,
  INVALID_PARAMS = -32602,
  INTERNAL_ERROR = -32603,
  JSONRPC_RESERVED_ERROR_RANGE_START = -320999,
  JSONRPC_RESERVED_ERROR_RANGE_END = -32000,
  SERVER_NOT_INITIALIZED = -32002,
  UNKNOWN_ERROR_CODE = -32001,
  LSP_RESERVED_ERROR_RANGE_START = -32899,
  REQUEST_FAILED = -32803,
  SERVER_CANCELLED = -32802,
  CONTENT_MODIFIED = -32801,
  REQUEST_CANCELLED = -32800,
  LSP_RESERVED_ERROR_RANGE_END = -32800,
} LSPErrorCodes;

typedef struct JsonValue JsonValue;

struct JsonValue {
 JsonSpec value;

 union {
   int jbool;
   double jnum;
   char *jstr;

   struct {
     struct JsonValue **jvals;
     int count;
   } j_array;

   struct {
     char **keys;
     struct JsonValue **jvals;
   } j_object;
 } json;

};

typedef struct {
 LSPErrorCodes code;
 char *message;
 JsonValue data;
} JRPCError;

typedef struct {} JRPCResult;

typedef struct {
  char *jsonrpc;
  char *method;
  
  union {
    char *id_str;
    double *id_num;
    int id_null;
  } id;

} JRPCRequest;

typedef struct {
  char *jsonrpc;

  union {
    JRPCResult result;
    JRPCError error;
  } response;

  union {
    char *id_str;
    double *id_num;
    int id_null;
  } id;

} JRPCResponse;
