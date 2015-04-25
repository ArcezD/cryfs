#pragma once
#ifndef MESSMER_CPPUTILS_DATA_DATABLOCKFIXTURE_H_
#define MESSMER_CPPUTILS_DATA_DATABLOCKFIXTURE_H_

#include <cstdio>

namespace cpputils {

//TODO Rewrite to using cpputils::Data (but take care that the cpputils::Data tests actually still test something, they use DataBlockFixture)
//TODO Add tests

class DataBlockFixture {
public:
  DataBlockFixture(size_t size, long long int IV = 1);
  virtual ~DataBlockFixture();

  int read(void *buf, size_t count, off_t offset);

  // Return true, iff the given data is equal to the data of the file at the given offset.
  bool fileContentEqual(const char *content, size_t count, off_t offset);

  const char *data() const;

  size_t size() const;

protected:
  char *_fileData;
  size_t _size;

private:
  void fillFileWithRandomData(long long int IV);
};

class DataBlockFixtureWriteable: public DataBlockFixture {
public:
  DataBlockFixtureWriteable(size_t size, long long int IV = 1);
  virtual ~DataBlockFixtureWriteable();

  void write(const void *buf, size_t count, off_t offset);

  bool sizeUnchanged();
  bool regionUnchanged(off_t offset, size_t count);

private:
  void extendFileSizeIfNecessary(size_t size);
  void extendFileSize(size_t size);

  char *_originalFileData;
  size_t _originalSize;
};

}

#endif