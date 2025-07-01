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

struct JsonValue {
 JsonSpec value;

 union {
   int jbool;
   double jnum;
   char * jstr;

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
