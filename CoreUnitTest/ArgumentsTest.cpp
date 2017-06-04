#include "stdafx.h"
#include "CppUnitTest.h"

#include "Core/Arguments.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CoreUnitTest
{

  TEST_CLASS(ArgumentsTest)
  {
  public:

    TEST_METHOD(HasSwitchTest)
    {
      char* cli[] = { { "-test" },{ "asd" },{ "-next" } };
      Core::Arguments args(3, cli, "-");

      Assert::IsTrue(args.hasSwitch("test"));
      Assert::IsTrue(args.hasSwitch("next"));

      Assert::IsFalse(args.hasSwitch("asd"));
    }

    TEST_METHOD(GetTest)
    {
      char* cli[] = { { "-test" },{ "1" },{ "2.5" } };
      Core::Arguments args(3, cli, "-");

      int i = 0;
      float f = 0.0f;

      Assert::IsTrue(args.get("test", i, f));
      
      Assert::AreEqual(1, i, 0, LINE_INFO());
      Assert::AreEqual(2.5f, f, 0, LINE_INFO());
    }

  };

}