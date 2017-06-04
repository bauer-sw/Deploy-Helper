#include "stdafx.h"
#include "CppUnitTest.h"

#include "Core/Class.h"
#include "Core/StreamReader.h"
#include "Core/StreamWriter.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CoreUnitTest
{
  class Simple {
  public:
    void setC(char c) { m_c = c; }
    char getC() const { return m_c; }

    void setStr(const std::string& str) { m_str = str; }
    const std::string& getStr() const { return m_str; }

    bool m_b = false;
    int m_i = -1;

  private:
    char m_c = 0;
    std::string m_str;
  };

  Core::RTTI::Class<Simple> SimpleClass = Core::RTTI::Class<Simple>::create("SimpleClass")
    .registerProperty<bool>("bool", &Simple::m_b)
    .registerProperty<int>("int", &Simple::m_i)
    .registerProperty<char>("char", &Simple::setC, &Simple::getC)
    .registerReferencedProperty<std::string>("string", &Simple::setStr, &Simple::getStr)
  ;

  class DerivedFromSimple : public Simple {
  public:
  };

  Core::RTTI::Class<DerivedFromSimple,1> DerivedFromSimpleClass = Core::RTTI::Class<DerivedFromSimple>::create<Simple>("DerivedFromSimple")
  ;

  class Other {
  public:
    void setOther(int i) { m_other = i; }
    int getOther() const { return m_other; }

  private:
    int m_other;
  };

  Core::RTTI::Class<Other> OtherClass = Core::RTTI::Class<Other>::create("Other")
    .registerProperty<int>("other", &Other::setOther, &Other::getOther)
  ;

  class DerivedFromSimpleAndOther : public Simple, public Other {
  public:
    void setDerived(int i) { m_derived = i; }
    int getDerived() const { return m_derived; }

  private:
    int m_derived;
  };

  Core::RTTI::Class<DerivedFromSimpleAndOther,2> DerivedFromSimpleAndOtherClass = Core::RTTI::Class<DerivedFromSimpleAndOther>::create<Simple, Other>("DerivedFromSimpleAndOther")
    .registerProperty<int>("derived", &DerivedFromSimpleAndOther::setDerived, &DerivedFromSimpleAndOther::getDerived)
  ;

  TEST_CLASS(RTTITest)
  {
  public:

    TEST_METHOD(hasProperty)
    {
      Assert::IsTrue(SimpleClass.hasProperty("bool"), 0, LINE_INFO());
      Assert::IsTrue(SimpleClass.hasProperty("int"), 0, LINE_INFO());
      Assert::IsTrue(SimpleClass.hasProperty("char"), 0, LINE_INFO());
      Assert::IsTrue(SimpleClass.hasProperty("string"), 0, LINE_INFO());

      Assert::IsFalse(SimpleClass.hasProperty(""), 0, LINE_INFO());
      Assert::IsFalse(SimpleClass.hasProperty("hello"), 0, LINE_INFO());
    }

    TEST_METHOD(getProperty)
    {    
      std::shared_ptr<Core::RTTI::Property> boolProperty = SimpleClass.getProperty("bool");
      Assert::IsTrue(boolProperty.operator bool(), 0, LINE_INFO());

      std::shared_ptr<Core::RTTI::Property> intProperty = SimpleClass.getProperty("int");
      Assert::IsTrue(intProperty.operator bool(), 0, LINE_INFO());

      Assert::IsTrue(SimpleClass.getProperty("char").operator bool(), 0, LINE_INFO());
      Assert::IsTrue(SimpleClass.getProperty("string").operator bool(), 0, LINE_INFO());      

      if (!boolProperty || !intProperty) {
        return;
      }

      Simple obj;
      
      std::stringstream ss;
            
      Core::IO::StreamWriter sw(&ss);
      //sw.setTextMode(true);
      SimpleClass.writeTo(&obj, sw);

      std::string tmp = ss.str();

      obj.m_b = true;
      obj.m_i = 123;
       
      Core::IO::StreamReader sr(&ss);
      //sr.setTextMode(true);
      SimpleClass.readFrom(&obj, sr);

      Assert::IsFalse(obj.m_b, 0, LINE_INFO());
      Assert::IsTrue(-1 == obj.m_i, 0, LINE_INFO());
    }



  };
}