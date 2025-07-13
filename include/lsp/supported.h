#include <stdint.h>
#include <stdbool.h>
#include "../proto/lsp_proto.h"

#define EOL ['\n', '\r\n', '\r']
#define FILE_RENAME "rename"
#define FILE_CREATE "create"
#define FILE_DELETE "delete"

typedef struct {
  char* text_document;
  struct {
    int line;
    int character;
  } position;
} HoverParams;

typedef struct {
  char* value;
} HoverResult;

typedef struct {
  char* document_uri;
} Uri, DocumentUri;

typedef struct {
  char* engine;
  char* version;
} RegularExpressionClientCapabilities;

typedef struct {
  uint32_t line;
  uint32_t character;
} Position;

typedef struct {
  const char* UTF8;
  const char* UTF16;
  const char* UTF32;
} PositionEncoding;

const PositionEncoding PositionEncodingKind = {
  .UTF8  = "utf-8",
  .UTF16 = "utf-16",
  .UTF32 = "utf-32",
};

typedef struct {
  Position start;
  Position end;
} Range;

typedef struct {
  DocumentUri uri;
  char* languageId;
  int version;
  char* text;
} TextDocumentItem;

typedef struct {
  DocumentUri uri;
} TextDocumentIdentifier;

typedef struct {
  DocumentUri uri;
  int version;
} VersionedTextDocumentIdentifier;

typedef struct {
  DocumentUri uri;
  int* version;
} OptionalVersionedTextDocumentIdentifier;

typedef struct {
  TextDocumentIdentifier text_document;
  Position position;
} TextDocumentPositionParams;

typedef struct {
  char* language;
  char* scheme;
  char* pattern;
} DocumentFilter;

typedef struct {
  DocumentFilter document_selector[];
} DocumentSelector;

typedef struct {
  Range range;
  char* new_text;
} TextEdit;

typedef struct {
  char* label;
  bool* needs_confirmation;
  char* description;
} ChangeAnnotation;

typedef char* ChangeAnnotationIdentifier;

typedef struct {
  Range range;
  char* new_text;
  ChangeAnnotationIdentifier annotation_id;
} AnnotatedTextEdit;

typedef struct {
  OptionalVersionedTextDocumentIdentifier text_document;
  union {
    TextEdit txt_edit[];
    AnnotatedTextEdit antd_txt_edit;
  } edits;
} TextDocumentEdit;

typedef struct {
  DocumentUri uri;
  Range range;
} Location;

typedef struct {
  Range* origin_selection_range;
  DocumentUri target_uri;
  Range target_range;
  Range target_selection_range;
} LocationLink;

typedef struct {
  Uri href;
} CodeDescription;

typedef enum {
  ERROR = 1,
  WARN,
  INFO,
  HINT,
} DiagnosticSeverity;

typedef enum {
  UNNECESSARY = 1,
  DEPRECATED,
} DiagnosticTag;

typedef struct {
  Location location;
  char* message;
} DiagnosticRelatedInformation;

typedef struct {
  Range range;
  DiagnosticSeverity* severity;
  union {
    int   code_num;
    char* code_str;
  } *code;
  CodeDescription* code_description;
  char* source;
  char* message;
  DiagnosticTag* tags;
  DiagnosticRelatedInformation related_information;
  JsonValue* data;
} Diagnostic;

typedef struct {
  char* title;
  char* command;
  JsonValue* arguments;
} Command;

typedef enum {
  PLAINTEXT,
  MARKDOWN,
} MarkupKind;

typedef struct {
  MarkupKind kind;
  char* value;
} MarkupContent;

typedef struct {
  const char* parser;
  char* version;
  char** allowed_tags;
} MarkDownCapabilities;

typedef struct {
  bool* overwrite;
  bool* ignore_if_exists;
} CreateFileOptions;

typedef struct {
  const char* kind;
  DocumentUri uri;
  CreateFileOptions* options;
  ChangeAnnotationIdentifier* annotation_id;
} CreateFile;

typedef struct {
  bool* overwrite;
  bool* ignore_if_file_exists;
} RenameFileOptions;

typedef struct {
  const char* kind;
  DocumentUri old_uri;
  DocumentUri new_uri;
  RenameFileOptions* options;
  ChangeAnnotationIdentifier* annotation_id;
} RenameFile;


