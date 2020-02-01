// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: ts.proto

#ifndef PROTOBUF_ts_2eproto__INCLUDED
#define PROTOBUF_ts_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 3000000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 3000000 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)

namespace tinysocial {

// Internal implementation detail -- do not call these.
void protobuf_AddDesc_ts_2eproto();
void protobuf_AssignDesc_ts_2eproto();
void protobuf_ShutdownFile_ts_2eproto();

class NewPost;
class Post;
class Status;
class User;

// ===================================================================

class User : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:tinysocial.User) */ {
 public:
  User();
  virtual ~User();

  User(const User& from);

  inline User& operator=(const User& from) {
    CopyFrom(from);
    return *this;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const User& default_instance();

  void Swap(User* other);

  // implements Message ----------------------------------------------

  inline User* New() const { return New(NULL); }

  User* New(::google::protobuf::Arena* arena) const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const User& from);
  void MergeFrom(const User& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const {
    return InternalSerializeWithCachedSizesToArray(false, output);
  }
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  void InternalSwap(User* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return _internal_metadata_.arena();
  }
  inline void* MaybeArenaPtr() const {
    return _internal_metadata_.raw_arena_ptr();
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // optional string name = 1;
  void clear_name();
  static const int kNameFieldNumber = 1;
  const ::std::string& name() const;
  void set_name(const ::std::string& value);
  void set_name(const char* value);
  void set_name(const char* value, size_t size);
  ::std::string* mutable_name();
  ::std::string* release_name();
  void set_allocated_name(::std::string* name);

  // @@protoc_insertion_point(class_scope:tinysocial.User)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  bool _is_default_instance_;
  ::google::protobuf::internal::ArenaStringPtr name_;
  mutable int _cached_size_;
  friend void  protobuf_AddDesc_ts_2eproto();
  friend void protobuf_AssignDesc_ts_2eproto();
  friend void protobuf_ShutdownFile_ts_2eproto();

  void InitAsDefaultInstance();
  static User* default_instance_;
};
// -------------------------------------------------------------------

class Status : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:tinysocial.Status) */ {
 public:
  Status();
  virtual ~Status();

  Status(const Status& from);

  inline Status& operator=(const Status& from) {
    CopyFrom(from);
    return *this;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const Status& default_instance();

  void Swap(Status* other);

  // implements Message ----------------------------------------------

  inline Status* New() const { return New(NULL); }

  Status* New(::google::protobuf::Arena* arena) const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Status& from);
  void MergeFrom(const Status& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const {
    return InternalSerializeWithCachedSizesToArray(false, output);
  }
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  void InternalSwap(Status* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return _internal_metadata_.arena();
  }
  inline void* MaybeArenaPtr() const {
    return _internal_metadata_.raw_arena_ptr();
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // optional int32 stat = 1;
  void clear_stat();
  static const int kStatFieldNumber = 1;
  ::google::protobuf::int32 stat() const;
  void set_stat(::google::protobuf::int32 value);

  // @@protoc_insertion_point(class_scope:tinysocial.Status)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  bool _is_default_instance_;
  ::google::protobuf::int32 stat_;
  mutable int _cached_size_;
  friend void  protobuf_AddDesc_ts_2eproto();
  friend void protobuf_AssignDesc_ts_2eproto();
  friend void protobuf_ShutdownFile_ts_2eproto();

  void InitAsDefaultInstance();
  static Status* default_instance_;
};
// -------------------------------------------------------------------

class Post : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:tinysocial.Post) */ {
 public:
  Post();
  virtual ~Post();

  Post(const Post& from);

  inline Post& operator=(const Post& from) {
    CopyFrom(from);
    return *this;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const Post& default_instance();

  void Swap(Post* other);

  // implements Message ----------------------------------------------

  inline Post* New() const { return New(NULL); }

  Post* New(::google::protobuf::Arena* arena) const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Post& from);
  void MergeFrom(const Post& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const {
    return InternalSerializeWithCachedSizesToArray(false, output);
  }
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  void InternalSwap(Post* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return _internal_metadata_.arena();
  }
  inline void* MaybeArenaPtr() const {
    return _internal_metadata_.raw_arena_ptr();
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // optional string name = 1;
  void clear_name();
  static const int kNameFieldNumber = 1;
  const ::std::string& name() const;
  void set_name(const ::std::string& value);
  void set_name(const char* value);
  void set_name(const char* value, size_t size);
  ::std::string* mutable_name();
  ::std::string* release_name();
  void set_allocated_name(::std::string* name);

  // optional int32 time = 2;
  void clear_time();
  static const int kTimeFieldNumber = 2;
  ::google::protobuf::int32 time() const;
  void set_time(::google::protobuf::int32 value);

  // optional string postText = 3;
  void clear_posttext();
  static const int kPostTextFieldNumber = 3;
  const ::std::string& posttext() const;
  void set_posttext(const ::std::string& value);
  void set_posttext(const char* value);
  void set_posttext(const char* value, size_t size);
  ::std::string* mutable_posttext();
  ::std::string* release_posttext();
  void set_allocated_posttext(::std::string* posttext);

  // @@protoc_insertion_point(class_scope:tinysocial.Post)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  bool _is_default_instance_;
  ::google::protobuf::internal::ArenaStringPtr name_;
  ::google::protobuf::internal::ArenaStringPtr posttext_;
  ::google::protobuf::int32 time_;
  mutable int _cached_size_;
  friend void  protobuf_AddDesc_ts_2eproto();
  friend void protobuf_AssignDesc_ts_2eproto();
  friend void protobuf_ShutdownFile_ts_2eproto();

  void InitAsDefaultInstance();
  static Post* default_instance_;
};
// -------------------------------------------------------------------

class NewPost : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:tinysocial.NewPost) */ {
 public:
  NewPost();
  virtual ~NewPost();

  NewPost(const NewPost& from);

  inline NewPost& operator=(const NewPost& from) {
    CopyFrom(from);
    return *this;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const NewPost& default_instance();

  void Swap(NewPost* other);

  // implements Message ----------------------------------------------

  inline NewPost* New() const { return New(NULL); }

  NewPost* New(::google::protobuf::Arena* arena) const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const NewPost& from);
  void MergeFrom(const NewPost& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const {
    return InternalSerializeWithCachedSizesToArray(false, output);
  }
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  void InternalSwap(NewPost* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return _internal_metadata_.arena();
  }
  inline void* MaybeArenaPtr() const {
    return _internal_metadata_.raw_arena_ptr();
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // optional string postFrom = 1;
  void clear_postfrom();
  static const int kPostFromFieldNumber = 1;
  const ::std::string& postfrom() const;
  void set_postfrom(const ::std::string& value);
  void set_postfrom(const char* value);
  void set_postfrom(const char* value, size_t size);
  ::std::string* mutable_postfrom();
  ::std::string* release_postfrom();
  void set_allocated_postfrom(::std::string* postfrom);

  // optional string postTo = 2;
  void clear_postto();
  static const int kPostToFieldNumber = 2;
  const ::std::string& postto() const;
  void set_postto(const ::std::string& value);
  void set_postto(const char* value);
  void set_postto(const char* value, size_t size);
  ::std::string* mutable_postto();
  ::std::string* release_postto();
  void set_allocated_postto(::std::string* postto);

  // optional string postText = 3;
  void clear_posttext();
  static const int kPostTextFieldNumber = 3;
  const ::std::string& posttext() const;
  void set_posttext(const ::std::string& value);
  void set_posttext(const char* value);
  void set_posttext(const char* value, size_t size);
  ::std::string* mutable_posttext();
  ::std::string* release_posttext();
  void set_allocated_posttext(::std::string* posttext);

  // @@protoc_insertion_point(class_scope:tinysocial.NewPost)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  bool _is_default_instance_;
  ::google::protobuf::internal::ArenaStringPtr postfrom_;
  ::google::protobuf::internal::ArenaStringPtr postto_;
  ::google::protobuf::internal::ArenaStringPtr posttext_;
  mutable int _cached_size_;
  friend void  protobuf_AddDesc_ts_2eproto();
  friend void protobuf_AssignDesc_ts_2eproto();
  friend void protobuf_ShutdownFile_ts_2eproto();

  void InitAsDefaultInstance();
  static NewPost* default_instance_;
};
// ===================================================================


// ===================================================================

#if !PROTOBUF_INLINE_NOT_IN_HEADERS
// User

// optional string name = 1;
inline void User::clear_name() {
  name_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& User::name() const {
  // @@protoc_insertion_point(field_get:tinysocial.User.name)
  return name_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void User::set_name(const ::std::string& value) {
  
  name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:tinysocial.User.name)
}
inline void User::set_name(const char* value) {
  
  name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:tinysocial.User.name)
}
inline void User::set_name(const char* value, size_t size) {
  
  name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:tinysocial.User.name)
}
inline ::std::string* User::mutable_name() {
  
  // @@protoc_insertion_point(field_mutable:tinysocial.User.name)
  return name_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* User::release_name() {
  // @@protoc_insertion_point(field_release:tinysocial.User.name)
  
  return name_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void User::set_allocated_name(::std::string* name) {
  if (name != NULL) {
    
  } else {
    
  }
  name_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), name);
  // @@protoc_insertion_point(field_set_allocated:tinysocial.User.name)
}

// -------------------------------------------------------------------

// Status

// optional int32 stat = 1;
inline void Status::clear_stat() {
  stat_ = 0;
}
inline ::google::protobuf::int32 Status::stat() const {
  // @@protoc_insertion_point(field_get:tinysocial.Status.stat)
  return stat_;
}
inline void Status::set_stat(::google::protobuf::int32 value) {
  
  stat_ = value;
  // @@protoc_insertion_point(field_set:tinysocial.Status.stat)
}

// -------------------------------------------------------------------

// Post

// optional string name = 1;
inline void Post::clear_name() {
  name_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& Post::name() const {
  // @@protoc_insertion_point(field_get:tinysocial.Post.name)
  return name_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void Post::set_name(const ::std::string& value) {
  
  name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:tinysocial.Post.name)
}
inline void Post::set_name(const char* value) {
  
  name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:tinysocial.Post.name)
}
inline void Post::set_name(const char* value, size_t size) {
  
  name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:tinysocial.Post.name)
}
inline ::std::string* Post::mutable_name() {
  
  // @@protoc_insertion_point(field_mutable:tinysocial.Post.name)
  return name_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* Post::release_name() {
  // @@protoc_insertion_point(field_release:tinysocial.Post.name)
  
  return name_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void Post::set_allocated_name(::std::string* name) {
  if (name != NULL) {
    
  } else {
    
  }
  name_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), name);
  // @@protoc_insertion_point(field_set_allocated:tinysocial.Post.name)
}

// optional int32 time = 2;
inline void Post::clear_time() {
  time_ = 0;
}
inline ::google::protobuf::int32 Post::time() const {
  // @@protoc_insertion_point(field_get:tinysocial.Post.time)
  return time_;
}
inline void Post::set_time(::google::protobuf::int32 value) {
  
  time_ = value;
  // @@protoc_insertion_point(field_set:tinysocial.Post.time)
}

// optional string postText = 3;
inline void Post::clear_posttext() {
  posttext_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& Post::posttext() const {
  // @@protoc_insertion_point(field_get:tinysocial.Post.postText)
  return posttext_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void Post::set_posttext(const ::std::string& value) {
  
  posttext_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:tinysocial.Post.postText)
}
inline void Post::set_posttext(const char* value) {
  
  posttext_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:tinysocial.Post.postText)
}
inline void Post::set_posttext(const char* value, size_t size) {
  
  posttext_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:tinysocial.Post.postText)
}
inline ::std::string* Post::mutable_posttext() {
  
  // @@protoc_insertion_point(field_mutable:tinysocial.Post.postText)
  return posttext_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* Post::release_posttext() {
  // @@protoc_insertion_point(field_release:tinysocial.Post.postText)
  
  return posttext_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void Post::set_allocated_posttext(::std::string* posttext) {
  if (posttext != NULL) {
    
  } else {
    
  }
  posttext_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), posttext);
  // @@protoc_insertion_point(field_set_allocated:tinysocial.Post.postText)
}

// -------------------------------------------------------------------

// NewPost

// optional string postFrom = 1;
inline void NewPost::clear_postfrom() {
  postfrom_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& NewPost::postfrom() const {
  // @@protoc_insertion_point(field_get:tinysocial.NewPost.postFrom)
  return postfrom_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void NewPost::set_postfrom(const ::std::string& value) {
  
  postfrom_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:tinysocial.NewPost.postFrom)
}
inline void NewPost::set_postfrom(const char* value) {
  
  postfrom_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:tinysocial.NewPost.postFrom)
}
inline void NewPost::set_postfrom(const char* value, size_t size) {
  
  postfrom_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:tinysocial.NewPost.postFrom)
}
inline ::std::string* NewPost::mutable_postfrom() {
  
  // @@protoc_insertion_point(field_mutable:tinysocial.NewPost.postFrom)
  return postfrom_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* NewPost::release_postfrom() {
  // @@protoc_insertion_point(field_release:tinysocial.NewPost.postFrom)
  
  return postfrom_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void NewPost::set_allocated_postfrom(::std::string* postfrom) {
  if (postfrom != NULL) {
    
  } else {
    
  }
  postfrom_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), postfrom);
  // @@protoc_insertion_point(field_set_allocated:tinysocial.NewPost.postFrom)
}

// optional string postTo = 2;
inline void NewPost::clear_postto() {
  postto_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& NewPost::postto() const {
  // @@protoc_insertion_point(field_get:tinysocial.NewPost.postTo)
  return postto_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void NewPost::set_postto(const ::std::string& value) {
  
  postto_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:tinysocial.NewPost.postTo)
}
inline void NewPost::set_postto(const char* value) {
  
  postto_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:tinysocial.NewPost.postTo)
}
inline void NewPost::set_postto(const char* value, size_t size) {
  
  postto_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:tinysocial.NewPost.postTo)
}
inline ::std::string* NewPost::mutable_postto() {
  
  // @@protoc_insertion_point(field_mutable:tinysocial.NewPost.postTo)
  return postto_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* NewPost::release_postto() {
  // @@protoc_insertion_point(field_release:tinysocial.NewPost.postTo)
  
  return postto_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void NewPost::set_allocated_postto(::std::string* postto) {
  if (postto != NULL) {
    
  } else {
    
  }
  postto_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), postto);
  // @@protoc_insertion_point(field_set_allocated:tinysocial.NewPost.postTo)
}

// optional string postText = 3;
inline void NewPost::clear_posttext() {
  posttext_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& NewPost::posttext() const {
  // @@protoc_insertion_point(field_get:tinysocial.NewPost.postText)
  return posttext_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void NewPost::set_posttext(const ::std::string& value) {
  
  posttext_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:tinysocial.NewPost.postText)
}
inline void NewPost::set_posttext(const char* value) {
  
  posttext_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:tinysocial.NewPost.postText)
}
inline void NewPost::set_posttext(const char* value, size_t size) {
  
  posttext_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:tinysocial.NewPost.postText)
}
inline ::std::string* NewPost::mutable_posttext() {
  
  // @@protoc_insertion_point(field_mutable:tinysocial.NewPost.postText)
  return posttext_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* NewPost::release_posttext() {
  // @@protoc_insertion_point(field_release:tinysocial.NewPost.postText)
  
  return posttext_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void NewPost::set_allocated_posttext(::std::string* posttext) {
  if (posttext != NULL) {
    
  } else {
    
  }
  posttext_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), posttext);
  // @@protoc_insertion_point(field_set_allocated:tinysocial.NewPost.postText)
}

#endif  // !PROTOBUF_INLINE_NOT_IN_HEADERS
// -------------------------------------------------------------------

// -------------------------------------------------------------------

// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)

}  // namespace tinysocial

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_ts_2eproto__INCLUDED
