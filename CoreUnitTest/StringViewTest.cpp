#include "stdafx.h"
#include "CppUnitTest.h"

#include "Core/StringView.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CoreUnitTest
{		
  TEST_CLASS(StringViewTest)
  {
  public:
    
    TEST_METHOD(StartsWithTest)
    {
      Core::StringView view("Hello World!");

      Assert::IsTrue(view.startsWith(view));
      Assert::IsTrue(view.startsWith("Hello"), 0, LINE_INFO());

      Assert::IsFalse(view.startsWith(""), 0, LINE_INFO());
      Assert::IsFalse(view.startsWith("hello"), 0, LINE_INFO());
    }

    /*
    TEST_METHOD(EndsWithTest)
    {
      Core::StringView view("Hello World!");

      Assert::IsTrue(view.endsWith(view));
      Assert::IsTrue(view.endsWith("World!"), 0, LINE_INFO());

      Assert::IsFalse(view.endsWith(""), 0, LINE_INFO());
      Assert::IsFalse(view.endsWith("world!"), 0, LINE_INFO());
    }
    */

    TEST_METHOD(IsEqual)
    {
      Assert::IsTrue(Core::StringView() == Core::StringView(), 0, LINE_INFO());

      Core::StringView view1("Hello World!");
      Core::StringView view2("Hello World!");

      Assert::IsTrue(view1 == view2, 0, LINE_INFO());
      Assert::IsTrue(view1 == "Hello World!", 0, LINE_INFO());

      Assert::IsFalse(view1 == "", 0, LINE_INFO());
      Assert::IsFalse(view1 == "Blub", 0, LINE_INFO());
    }

    TEST_METHOD(SplitBy)
    {
      Core::StringView::Vector result = Core::StringView::splitBy("Hello my name is Jakob!", ' ');

      Assert::IsFalse(result.empty());
      Assert::AreEqual(std::size_t(5), result.size(), 0, LINE_INFO());

      Assert::IsTrue(result[0] == "Hello");
      Assert::IsTrue(result[1] == "my");
      Assert::IsTrue(result[2] == "name");
      Assert::IsTrue(result[3] == "is");
      Assert::IsTrue(result[4] == "Jakob!");
    }

  };
}