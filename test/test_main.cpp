#include <gtest.h>

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  char c;
  int i = RUN_ALL_TESTS();
  std::cin >> c;
  return i;
}
