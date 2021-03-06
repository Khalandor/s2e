//===-- Context.cpp -------------------------------------------------------===//
//
//                     The KLEE Symbolic Virtual Machine
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "klee/Context.h"

#include "klee/Expr.h"

#include "llvm/Type.h"
#include "llvm/DerivedTypes.h"

#include <cassert>

using namespace klee;

static bool Initialized = false;
static Context TheContext;

void Context::initialize(bool IsLittleEndian, Expr::Width PointerWidth) {
  assert(!Initialized && "Duplicate context initialization!");
  TheContext = Context(IsLittleEndian, PointerWidth);
  Initialized = true;
}

const Context &Context::get() {
  assert(Initialized && "Context has not been initialized!");
  return TheContext;
}


ref<Expr> Expr::createCoerceToPointerType(ref<Expr> e) {
  return ZExtExpr::create(e, Context::get().getPointerWidth());
}

ref<ConstantExpr> Expr::createPointer(uint64_t v) {
  return ConstantExpr::create(v, Context::get().getPointerWidth());
}
