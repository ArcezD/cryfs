#pragma once
#ifndef MESSMER_BLOCKSTORE_IMPLEMENTATIONS_INMEMORY_INMEMORYBLOCKSTORE_H_
#define MESSMER_BLOCKSTORE_IMPLEMENTATIONS_INMEMORY_INMEMORYBLOCKSTORE_H_

#include "../../interface/helpers/BlockStoreWithRandomKeys.h"
#include <cpp-utils/macros.h>
#include "InMemoryBlock.h"

#include <mutex>
#include <unordered_map>
#include "InMemoryBlock.h"

namespace blockstore {
namespace inmemory {

class InMemoryBlockStore final: public BlockStoreWithRandomKeys {
public:
  InMemoryBlockStore();

  boost::optional<cpputils::unique_ref<Block>> tryCreate(const Key &key, cpputils::Data data) override;
  boost::optional<cpputils::unique_ref<Block>> load(const Key &key) override;
  cpputils::unique_ref<Block> overwrite(const blockstore::Key &key, cpputils::Data data) override;
  void remove(const Key &key) override;
  void removeIfExists(const Key &key) override;
  uint64_t numBlocks() const override;
  uint64_t estimateNumFreeBytes() const override;
  uint64_t blockSizeFromPhysicalBlockSize(uint64_t blockSize) const override;
  void forEachBlock(std::function<void (const Key &)> callback) const override;
  bool exists(const Key &key) const override;

private:
  std::unordered_map<Key, InMemoryBlock> _blocks;

  DISALLOW_COPY_AND_ASSIGN(InMemoryBlockStore);
};

}
}

#endif
