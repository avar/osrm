// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: fileformat.proto

#ifndef PROTOBUF_fileformat_2eproto__INCLUDED
#define PROTOBUF_fileformat_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 2003000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 2003000 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/generated_message_reflection.h>
// @@protoc_insertion_point(includes)

namespace OSMPBF {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_fileformat_2eproto();
void protobuf_AssignDesc_fileformat_2eproto();
void protobuf_ShutdownFile_fileformat_2eproto();

class Blob;
class BlobHeader;

// ===================================================================

class Blob : public ::google::protobuf::Message {
 public:
  Blob();
  virtual ~Blob();
  
  Blob(const Blob& from);
  
  inline Blob& operator=(const Blob& from) {
    CopyFrom(from);
    return *this;
  }
  
  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }
  
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }
  
  static const ::google::protobuf::Descriptor* descriptor();
  static const Blob& default_instance();
  
  void Swap(Blob* other);
  
  // implements Message ----------------------------------------------
  
  Blob* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Blob& from);
  void MergeFrom(const Blob& from);
  void Clear();
  bool IsInitialized() const;
  
  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:
  
  ::google::protobuf::Metadata GetMetadata() const;
  
  // nested types ----------------------------------------------------
  
  // accessors -------------------------------------------------------
  
  // optional bytes raw = 1;
  inline bool has_raw() const;
  inline void clear_raw();
  static const int kRawFieldNumber = 1;
  inline const ::std::string& raw() const;
  inline void set_raw(const ::std::string& value);
  inline void set_raw(const char* value);
  inline void set_raw(const void* value, size_t size);
  inline ::std::string* mutable_raw();
  
  // optional int32 raw_size = 2;
  inline bool has_raw_size() const;
  inline void clear_raw_size();
  static const int kRawSizeFieldNumber = 2;
  inline ::google::protobuf::int32 raw_size() const;
  inline void set_raw_size(::google::protobuf::int32 value);
  
  // optional bytes zlib_data = 3;
  inline bool has_zlib_data() const;
  inline void clear_zlib_data();
  static const int kZlibDataFieldNumber = 3;
  inline const ::std::string& zlib_data() const;
  inline void set_zlib_data(const ::std::string& value);
  inline void set_zlib_data(const char* value);
  inline void set_zlib_data(const void* value, size_t size);
  inline ::std::string* mutable_zlib_data();
  
  // optional bytes lzma_data = 4;
  inline bool has_lzma_data() const;
  inline void clear_lzma_data();
  static const int kLzmaDataFieldNumber = 4;
  inline const ::std::string& lzma_data() const;
  inline void set_lzma_data(const ::std::string& value);
  inline void set_lzma_data(const char* value);
  inline void set_lzma_data(const void* value, size_t size);
  inline ::std::string* mutable_lzma_data();
  
  // optional bytes OBSOLETE_bzip2_data = 5 [deprecated = true];
  inline bool has_obsolete_bzip2_data() const PROTOBUF_DEPRECATED;
  inline void clear_obsolete_bzip2_data() PROTOBUF_DEPRECATED;
  static const int kOBSOLETEBzip2DataFieldNumber = 5;
  inline const ::std::string& obsolete_bzip2_data() const PROTOBUF_DEPRECATED;
  inline void set_obsolete_bzip2_data(const ::std::string& value) PROTOBUF_DEPRECATED;
  inline void set_obsolete_bzip2_data(const char* value) PROTOBUF_DEPRECATED;
  inline void set_obsolete_bzip2_data(const void* value, size_t size) PROTOBUF_DEPRECATED;
  inline ::std::string* mutable_obsolete_bzip2_data() PROTOBUF_DEPRECATED;
  
  // @@protoc_insertion_point(class_scope:OSMPBF.Blob)
 private:
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  mutable int _cached_size_;
  
  ::std::string* raw_;
  static const ::std::string _default_raw_;
  ::google::protobuf::int32 raw_size_;
  ::std::string* zlib_data_;
  static const ::std::string _default_zlib_data_;
  ::std::string* lzma_data_;
  static const ::std::string _default_lzma_data_;
  ::std::string* obsolete_bzip2_data_;
  static const ::std::string _default_obsolete_bzip2_data_;
  friend void  protobuf_AddDesc_fileformat_2eproto();
  friend void protobuf_AssignDesc_fileformat_2eproto();
  friend void protobuf_ShutdownFile_fileformat_2eproto();
  
  ::google::protobuf::uint32 _has_bits_[(5 + 31) / 32];
  
  // WHY DOES & HAVE LOWER PRECEDENCE THAN != !?
  inline bool _has_bit(int index) const {
    return (_has_bits_[index / 32] & (1u << (index % 32))) != 0;
  }
  inline void _set_bit(int index) {
    _has_bits_[index / 32] |= (1u << (index % 32));
  }
  inline void _clear_bit(int index) {
    _has_bits_[index / 32] &= ~(1u << (index % 32));
  }
  
  void InitAsDefaultInstance();
  static Blob* default_instance_;
};
// -------------------------------------------------------------------

class BlobHeader : public ::google::protobuf::Message {
 public:
  BlobHeader();
  virtual ~BlobHeader();
  
  BlobHeader(const BlobHeader& from);
  
  inline BlobHeader& operator=(const BlobHeader& from) {
    CopyFrom(from);
    return *this;
  }
  
  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }
  
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }
  
  static const ::google::protobuf::Descriptor* descriptor();
  static const BlobHeader& default_instance();
  
  void Swap(BlobHeader* other);
  
  // implements Message ----------------------------------------------
  
  BlobHeader* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const BlobHeader& from);
  void MergeFrom(const BlobHeader& from);
  void Clear();
  bool IsInitialized() const;
  
  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:
  
  ::google::protobuf::Metadata GetMetadata() const;
  
  // nested types ----------------------------------------------------
  
  // accessors -------------------------------------------------------
  
  // required string type = 1;
  inline bool has_type() const;
  inline void clear_type();
  static const int kTypeFieldNumber = 1;
  inline const ::std::string& type() const;
  inline void set_type(const ::std::string& value);
  inline void set_type(const char* value);
  inline void set_type(const char* value, size_t size);
  inline ::std::string* mutable_type();
  
  // optional bytes indexdata = 2;
  inline bool has_indexdata() const;
  inline void clear_indexdata();
  static const int kIndexdataFieldNumber = 2;
  inline const ::std::string& indexdata() const;
  inline void set_indexdata(const ::std::string& value);
  inline void set_indexdata(const char* value);
  inline void set_indexdata(const void* value, size_t size);
  inline ::std::string* mutable_indexdata();
  
  // required int32 datasize = 3;
  inline bool has_datasize() const;
  inline void clear_datasize();
  static const int kDatasizeFieldNumber = 3;
  inline ::google::protobuf::int32 datasize() const;
  inline void set_datasize(::google::protobuf::int32 value);
  
  // @@protoc_insertion_point(class_scope:OSMPBF.BlobHeader)
 private:
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  mutable int _cached_size_;
  
  ::std::string* type_;
  static const ::std::string _default_type_;
  ::std::string* indexdata_;
  static const ::std::string _default_indexdata_;
  ::google::protobuf::int32 datasize_;
  friend void  protobuf_AddDesc_fileformat_2eproto();
  friend void protobuf_AssignDesc_fileformat_2eproto();
  friend void protobuf_ShutdownFile_fileformat_2eproto();
  
  ::google::protobuf::uint32 _has_bits_[(3 + 31) / 32];
  
  // WHY DOES & HAVE LOWER PRECEDENCE THAN != !?
  inline bool _has_bit(int index) const {
    return (_has_bits_[index / 32] & (1u << (index % 32))) != 0;
  }
  inline void _set_bit(int index) {
    _has_bits_[index / 32] |= (1u << (index % 32));
  }
  inline void _clear_bit(int index) {
    _has_bits_[index / 32] &= ~(1u << (index % 32));
  }
  
  void InitAsDefaultInstance();
  static BlobHeader* default_instance_;
};
// ===================================================================


// ===================================================================

// Blob

// optional bytes raw = 1;
inline bool Blob::has_raw() const {
  return _has_bit(0);
}
inline void Blob::clear_raw() {
  if (raw_ != &_default_raw_) {
    raw_->clear();
  }
  _clear_bit(0);
}
inline const ::std::string& Blob::raw() const {
  return *raw_;
}
inline void Blob::set_raw(const ::std::string& value) {
  _set_bit(0);
  if (raw_ == &_default_raw_) {
    raw_ = new ::std::string;
  }
  raw_->assign(value);
}
inline void Blob::set_raw(const char* value) {
  _set_bit(0);
  if (raw_ == &_default_raw_) {
    raw_ = new ::std::string;
  }
  raw_->assign(value);
}
inline void Blob::set_raw(const void* value, size_t size) {
  _set_bit(0);
  if (raw_ == &_default_raw_) {
    raw_ = new ::std::string;
  }
  raw_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* Blob::mutable_raw() {
  _set_bit(0);
  if (raw_ == &_default_raw_) {
    raw_ = new ::std::string;
  }
  return raw_;
}

// optional int32 raw_size = 2;
inline bool Blob::has_raw_size() const {
  return _has_bit(1);
}
inline void Blob::clear_raw_size() {
  raw_size_ = 0;
  _clear_bit(1);
}
inline ::google::protobuf::int32 Blob::raw_size() const {
  return raw_size_;
}
inline void Blob::set_raw_size(::google::protobuf::int32 value) {
  _set_bit(1);
  raw_size_ = value;
}

// optional bytes zlib_data = 3;
inline bool Blob::has_zlib_data() const {
  return _has_bit(2);
}
inline void Blob::clear_zlib_data() {
  if (zlib_data_ != &_default_zlib_data_) {
    zlib_data_->clear();
  }
  _clear_bit(2);
}
inline const ::std::string& Blob::zlib_data() const {
  return *zlib_data_;
}
inline void Blob::set_zlib_data(const ::std::string& value) {
  _set_bit(2);
  if (zlib_data_ == &_default_zlib_data_) {
    zlib_data_ = new ::std::string;
  }
  zlib_data_->assign(value);
}
inline void Blob::set_zlib_data(const char* value) {
  _set_bit(2);
  if (zlib_data_ == &_default_zlib_data_) {
    zlib_data_ = new ::std::string;
  }
  zlib_data_->assign(value);
}
inline void Blob::set_zlib_data(const void* value, size_t size) {
  _set_bit(2);
  if (zlib_data_ == &_default_zlib_data_) {
    zlib_data_ = new ::std::string;
  }
  zlib_data_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* Blob::mutable_zlib_data() {
  _set_bit(2);
  if (zlib_data_ == &_default_zlib_data_) {
    zlib_data_ = new ::std::string;
  }
  return zlib_data_;
}

// optional bytes lzma_data = 4;
inline bool Blob::has_lzma_data() const {
  return _has_bit(3);
}
inline void Blob::clear_lzma_data() {
  if (lzma_data_ != &_default_lzma_data_) {
    lzma_data_->clear();
  }
  _clear_bit(3);
}
inline const ::std::string& Blob::lzma_data() const {
  return *lzma_data_;
}
inline void Blob::set_lzma_data(const ::std::string& value) {
  _set_bit(3);
  if (lzma_data_ == &_default_lzma_data_) {
    lzma_data_ = new ::std::string;
  }
  lzma_data_->assign(value);
}
inline void Blob::set_lzma_data(const char* value) {
  _set_bit(3);
  if (lzma_data_ == &_default_lzma_data_) {
    lzma_data_ = new ::std::string;
  }
  lzma_data_->assign(value);
}
inline void Blob::set_lzma_data(const void* value, size_t size) {
  _set_bit(3);
  if (lzma_data_ == &_default_lzma_data_) {
    lzma_data_ = new ::std::string;
  }
  lzma_data_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* Blob::mutable_lzma_data() {
  _set_bit(3);
  if (lzma_data_ == &_default_lzma_data_) {
    lzma_data_ = new ::std::string;
  }
  return lzma_data_;
}

// optional bytes OBSOLETE_bzip2_data = 5 [deprecated = true];
inline bool Blob::has_obsolete_bzip2_data() const {
  return _has_bit(4);
}
inline void Blob::clear_obsolete_bzip2_data() {
  if (obsolete_bzip2_data_ != &_default_obsolete_bzip2_data_) {
    obsolete_bzip2_data_->clear();
  }
  _clear_bit(4);
}
inline const ::std::string& Blob::obsolete_bzip2_data() const {
  return *obsolete_bzip2_data_;
}
inline void Blob::set_obsolete_bzip2_data(const ::std::string& value) {
  _set_bit(4);
  if (obsolete_bzip2_data_ == &_default_obsolete_bzip2_data_) {
    obsolete_bzip2_data_ = new ::std::string;
  }
  obsolete_bzip2_data_->assign(value);
}
inline void Blob::set_obsolete_bzip2_data(const char* value) {
  _set_bit(4);
  if (obsolete_bzip2_data_ == &_default_obsolete_bzip2_data_) {
    obsolete_bzip2_data_ = new ::std::string;
  }
  obsolete_bzip2_data_->assign(value);
}
inline void Blob::set_obsolete_bzip2_data(const void* value, size_t size) {
  _set_bit(4);
  if (obsolete_bzip2_data_ == &_default_obsolete_bzip2_data_) {
    obsolete_bzip2_data_ = new ::std::string;
  }
  obsolete_bzip2_data_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* Blob::mutable_obsolete_bzip2_data() {
  _set_bit(4);
  if (obsolete_bzip2_data_ == &_default_obsolete_bzip2_data_) {
    obsolete_bzip2_data_ = new ::std::string;
  }
  return obsolete_bzip2_data_;
}

// -------------------------------------------------------------------

// BlobHeader

// required string type = 1;
inline bool BlobHeader::has_type() const {
  return _has_bit(0);
}
inline void BlobHeader::clear_type() {
  if (type_ != &_default_type_) {
    type_->clear();
  }
  _clear_bit(0);
}
inline const ::std::string& BlobHeader::type() const {
  return *type_;
}
inline void BlobHeader::set_type(const ::std::string& value) {
  _set_bit(0);
  if (type_ == &_default_type_) {
    type_ = new ::std::string;
  }
  type_->assign(value);
}
inline void BlobHeader::set_type(const char* value) {
  _set_bit(0);
  if (type_ == &_default_type_) {
    type_ = new ::std::string;
  }
  type_->assign(value);
}
inline void BlobHeader::set_type(const char* value, size_t size) {
  _set_bit(0);
  if (type_ == &_default_type_) {
    type_ = new ::std::string;
  }
  type_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* BlobHeader::mutable_type() {
  _set_bit(0);
  if (type_ == &_default_type_) {
    type_ = new ::std::string;
  }
  return type_;
}

// optional bytes indexdata = 2;
inline bool BlobHeader::has_indexdata() const {
  return _has_bit(1);
}
inline void BlobHeader::clear_indexdata() {
  if (indexdata_ != &_default_indexdata_) {
    indexdata_->clear();
  }
  _clear_bit(1);
}
inline const ::std::string& BlobHeader::indexdata() const {
  return *indexdata_;
}
inline void BlobHeader::set_indexdata(const ::std::string& value) {
  _set_bit(1);
  if (indexdata_ == &_default_indexdata_) {
    indexdata_ = new ::std::string;
  }
  indexdata_->assign(value);
}
inline void BlobHeader::set_indexdata(const char* value) {
  _set_bit(1);
  if (indexdata_ == &_default_indexdata_) {
    indexdata_ = new ::std::string;
  }
  indexdata_->assign(value);
}
inline void BlobHeader::set_indexdata(const void* value, size_t size) {
  _set_bit(1);
  if (indexdata_ == &_default_indexdata_) {
    indexdata_ = new ::std::string;
  }
  indexdata_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* BlobHeader::mutable_indexdata() {
  _set_bit(1);
  if (indexdata_ == &_default_indexdata_) {
    indexdata_ = new ::std::string;
  }
  return indexdata_;
}

// required int32 datasize = 3;
inline bool BlobHeader::has_datasize() const {
  return _has_bit(2);
}
inline void BlobHeader::clear_datasize() {
  datasize_ = 0;
  _clear_bit(2);
}
inline ::google::protobuf::int32 BlobHeader::datasize() const {
  return datasize_;
}
inline void BlobHeader::set_datasize(::google::protobuf::int32 value) {
  _set_bit(2);
  datasize_ = value;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace OSMPBF

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_fileformat_2eproto__INCLUDED
