#include "testutils/FuseRenameTest.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "fspp/fuse/FuseErrnoException.h"

using ::testing::_;
using ::testing::StrEq;
using ::testing::Throw;
using ::testing::WithParamInterface;
using ::testing::Values;

using namespace fspp::fuse;

class FuseRenameErrorTest: public FuseRenameTest, public WithParamInterface<int> {
};
INSTANTIATE_TEST_CASE_P(FuseRenameErrorTest, FuseRenameErrorTest, Values(EACCES, EBUSY, EDQUOT, EFAULT, EINVAL, EISDIR, ELOOP, EMLINK, ENAMETOOLONG, ENOENT, ENOMEM, ENOSPC, ENOTDIR, ENOTEMPTY, EEXIST, EPERM, EROFS, EXDEV, EBADF, ENOTDIR));

TEST_P(FuseRenameErrorTest, ReturnedErrorIsCorrect) {
  ReturnIsFileOnLstat(FILENAME1);
  ReturnIsFileOnLstat(FILENAME2);
  EXPECT_CALL(fsimpl, rename(StrEq(FILENAME1), StrEq(FILENAME2)))
    .Times(1).WillOnce(Throw(FuseErrnoException(GetParam())));

  int retval = RenameAllowError(FILENAME1, FILENAME2);
  EXPECT_EQ(GetParam(), errno);
  EXPECT_EQ(-1, retval);
}
