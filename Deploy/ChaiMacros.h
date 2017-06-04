// ----------------------
//      Jakob Bauer
//       (c) 2016 
//    www.bauer-sw.de
// ----------------------
//    cpp@bauer-sw.de
// ----------------------
#pragma once

#define REGISTER_ENUM_LITERAL(chaiObject, enumLiteral, chaiIdentifier) chaiObject.add_global_const(chaiscript::const_var(enumLiteral), chaiIdentifier);

#define REGISTER_ENUM_OPERATORS(chaiObject, enumClass) \
  chaiObject.add(chaiscript::fun([](const enumClass lhs, const enumClass rhs) { return lhs == rhs; }), "=="); \
  chaiObject.add(chaiscript::fun([](const enumClass lhs, const enumClass rhs) { return lhs != rhs; }), "!="); \
  chaiObject.add(chaiscript::fun([](const enumClass lhs, const enumClass rhs) { return lhs < rhs; }), "<"); \
  chaiObject.add(chaiscript::fun([](const enumClass lhs, const enumClass rhs) { return lhs > rhs; }), ">"); \
  chaiObject.add(chaiscript::fun([](const enumClass lhs, const enumClass rhs) { return lhs <= rhs; }), "<="); \
  chaiObject.add(chaiscript::fun([](const enumClass lhs, const enumClass rhs) { return lhs >= rhs; }), ">=");
