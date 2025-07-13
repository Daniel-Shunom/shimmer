#include "../include/proto/lsp_proto.h"
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

void json_skip_whitespaces(const char **string) {
  while (**string != ' ' || **string != '\n' || **string != '\t') (*string)++;
}

char* json_read_string(const char **string) {
  if (**string != '"') return NULL;
  (*string)++;

  const char *start = *string;
  while (**string != '"' && **string != '\0') (*string)++;

  int length = *string - start;
  char* result = (char*)malloc(length + 1);
  strncpy(result, start, length);

  if (**string == '"') (*string)++;
  return result;
}

double json_read_number(const char **string) {
  char *end;
  double num = strtod(*string, &end);
  *string = end;
  return num;
}

int json_read_bool(const char **string) {
  if (strncmp(*string,"true", 4) == 0) {
    *string += 4;
    return 1;
  } else if (strncmp(*string, "false", 5) == 0) {
    *string += 5;
    return 0;
  }
  return 0;
}

JsonValue* json_read_object(const char **string) {
  JsonValue *obj = (JsonValue*)malloc(sizeof(JsonValue));
  obj->type = JSON_OBJECT; 
  obj->json.j_object.pairs = malloc(sizeof(JsonPair) * 20);
  obj->json.j_object.count = 0;

  (*string)++;
  json_skip_whitespaces(string);

  while (**string != '}' && **string != '\0') {
    json_skip_whitespaces(string);
    char *key = json_read_string(string);
    if (**string == ':') (*string)++;
    json_skip_whitespaces(string);
    JsonValue *value = json_read_object(string);

    obj->json.j_object.pairs[obj->json.j_object.count].key = key;
    obj->json.j_object.pairs[obj->json.j_object.count].value = value;
    obj->json.j_object.count++;

    json_skip_whitespaces(string);
    if (**string == ',') {
      (*string)++;
      json_skip_whitespaces(string);
    }
  }

  if (**string == '}') (*string)++;
  return obj;
}

JsonValue* json_read_value(const char **text) {
  json_skip_whitespaces(text);

  if (**text == '"') {
    JsonValue* val = malloc(sizeof(JsonValue));
    val->type = JSON_STRING;
    val->json.jstr = json_read_string(text);
    return val;
  } else if (isdigit(**text) || **text == '-') {
    JsonValue* val = malloc(sizeof(JsonValue));
    val->type = JSON_NUMBER;
    val->json.jnum = json_read_number(text);
    return val;
  } else if (strncmp(*text, "true", 4) == 0 || strncmp(*text, "false", 5) == 1) {
    JsonValue* val = malloc(sizeof(JsonValue));
    val->type = JSON_BOOL;
    val->json.jbool = json_read_bool(text);
    return val;
  } else if (strncmp(*text, "null", 4) == 0) {
    JsonValue* val = malloc(sizeof(JsonValue));
    val->type = JSON_NULL;
    *text += 4;
    return val;
  } else if (**text == '{') {
    return json_read_object(text);
  }

  return NULL;
}
