/**
 ******************************************************************************
 * Xenia : Xbox 360 Emulator Research Project                                 *
 ******************************************************************************
 * Copyright 2014 Ben Vanik. All rights reserved.                             *
 * Released under the BSD license - see LICENSE in the root for more details. *
 ******************************************************************************
 */

#include <alloy/backend/x64/lowering/tracers.h>

#include <alloy/backend/x64/x64_emitter.h>
#include <alloy/runtime/runtime.h>
#include <alloy/runtime/thread_state.h>

using namespace alloy;
using namespace alloy::backend::x64;
using namespace alloy::backend::x64::lowering;
using namespace alloy::runtime;

namespace alloy {
namespace backend {
namespace x64 {
namespace lowering {


#define IPRINT
#define IFLUSH()
#define DPRINT
#define DFLUSH()

#define IPRINT if (thread_state->thread_id() == 1) printf
#define IFLUSH() fflush(stdout)
#define DPRINT if (thread_state->thread_id() == 1) printf
#define DFLUSH() fflush(stdout)


void TraceString(void* raw_context, const char* str) {
  auto thread_state = *((ThreadState**)raw_context);
  IPRINT("XE[t] :%d: %s\n", thread_state->GetThreadID(), str);
  IFLUSH();
}

void TraceContextLoadI8(void* raw_context, uint64_t offset, uint8_t value) {
  auto thread_state = *((ThreadState**)raw_context);
  DPRINT("%d (%X) = ctx i8 +%d\n", (int8_t)value, value, offset);
}
void TraceContextLoadI16(void* raw_context, uint64_t offset, uint16_t value) {
  auto thread_state = *((ThreadState**)raw_context);
  DPRINT("%d (%X) = ctx i16 +%d\n", (int16_t)value, value, offset);
}
void TraceContextLoadI32(void* raw_context, uint64_t offset, uint32_t value) {
  auto thread_state = *((ThreadState**)raw_context);
  DPRINT("%d (%X) = ctx i32 +%d\n", (int32_t)value, value, offset);
}
void TraceContextLoadI64(void* raw_context, uint64_t offset, uint64_t value) {
  auto thread_state = *((ThreadState**)raw_context);
  DPRINT("%lld (%llX) = ctx i64 +%d\n", (int64_t)value, value, offset);
}
void TraceContextLoadF32(void* raw_context, uint64_t offset, float value) {
  auto thread_state = *((ThreadState**)raw_context);
  union {
    float f;
    uint32_t u;
  } x;
  x.f = value;
  DPRINT("%e (%X) = ctx f32 +%d\n", x.f, x.u, offset);
}
void TraceContextLoadF64(void* raw_context, uint64_t offset, double value) {
  auto thread_state = *((ThreadState**)raw_context);
  union {
    double f;
    uint64_t u;
  } x;
  x.f = value;
  DPRINT("%lle (%llX) = ctx f64 +%d\n", x.f, x.u, offset);
}
void TraceContextLoadV128(void* raw_context, uint64_t offset, __m128 value) {
  auto thread_state = *((ThreadState**)raw_context);
  //DPRINT("%d (%.X) = ctx i8 +%d\n", (int8_t)value, value, offset);
}

void TraceContextStoreI8(void* raw_context, uint64_t offset, uint8_t value) {
  auto thread_state = *((ThreadState**)raw_context);
  DPRINT("ctx i8 +%d = %d (%X)\n", offset, (int8_t)value, value);
}
void TraceContextStoreI16(void* raw_context, uint64_t offset, uint16_t value) {
  auto thread_state = *((ThreadState**)raw_context);
  DPRINT("ctx i16 +%d = %d (%X)\n", offset, (int16_t)value, value);
}
void TraceContextStoreI32(void* raw_context, uint64_t offset, uint32_t value) {
  auto thread_state = *((ThreadState**)raw_context);
  DPRINT("ctx i32 +%d = %d (%X)\n", offset, (int32_t)value, value);
}
void TraceContextStoreI64(void* raw_context, uint64_t offset, uint64_t value) {
  auto thread_state = *((ThreadState**)raw_context);
  DPRINT("ctx i64 +%d = %lld (%llX)\n", offset, (int64_t)value, value);
}
void TraceContextStoreF32(void* raw_context, uint64_t offset, float value) {
  auto thread_state = *((ThreadState**)raw_context);
  union {
    float f;
    uint32_t u;
  } x;
  x.f = value;
  DPRINT("ctx f32 +%d = %e (%.X)\n", offset, x.f, x.u);
}
void TraceContextStoreF64(void* raw_context, uint64_t offset, double value) {
  auto thread_state = *((ThreadState**)raw_context);
  union {
    double f;
    uint64_t u;
  } x;
  x.f = value;
  DPRINT("ctx f64 +%d = %lle (%.llX)\n", offset, x.f, x.u);
}
void TraceContextStoreV128(void* raw_context, uint64_t offset, __m128 value) {
  auto thread_state = *((ThreadState**)raw_context);
  /*DPRINT("ctx v128 +%d = [%e, %e, %e, %e] [%.8X, %.8X, %.8X, %.8X]\n", ics.rf[i->src1_reg].u64,
         VECF4(ics.rf[i->src2_reg].v128,0), VECF4(ics.rf[i->src2_reg].v128,1), VECF4(ics.rf[i->src2_reg].v128,2), VECF4(ics.rf[i->src2_reg].v128,3),
         VECI4(ics.rf[i->src2_reg].v128,0), VECI4(ics.rf[i->src2_reg].v128,1), VECI4(ics.rf[i->src2_reg].v128,2), VECF4(ics.rf[i->src2_reg].v128,3));*/
}

void TraceMemoryLoadI8(void* raw_context, uint64_t address, uint8_t value) {
  auto thread_state = *((ThreadState**)raw_context);
  DPRINT("%d (%X) = load.i8 %.8X\n", (int8_t)value, value, address);
}
void TraceMemoryLoadI16(void* raw_context, uint64_t address, uint16_t value) {
  auto thread_state = *((ThreadState**)raw_context);
  DPRINT("%d (%X) = load.i16 %.8X\n", (int16_t)value, value, address);
}
void TraceMemoryLoadI32(void* raw_context, uint64_t address, uint32_t value) {
  auto thread_state = *((ThreadState**)raw_context);
  DPRINT("%d (%X) = load.i32 %.8X\n", (int32_t)value, value, address);
}
void TraceMemoryLoadI64(void* raw_context, uint64_t address, uint64_t value) {
  auto thread_state = *((ThreadState**)raw_context);
  DPRINT("%lld (%llX) = load.i64 %.8X\n", (int64_t)value, value, address);
}
void TraceMemoryLoadF32(void* raw_context, uint64_t address, float value) {
  auto thread_state = *((ThreadState**)raw_context);
  union {
    float f;
    uint32_t u;
  } x;
  x.f = value;
  DPRINT("%e (%X) = load.f32 %.8X\n", x.f, x.u, address);
}
void TraceMemoryLoadF64(void* raw_context, uint64_t address, double value) {
  auto thread_state = *((ThreadState**)raw_context);
  union {
    double f;
    uint64_t u;
  } x;
  x.f = value;
  DPRINT("%lle (%llX) = load.f64 %.8X\n", x.f, x.u, address);
}
void TraceMemoryLoadV128(void* raw_context, uint64_t address, __m128 value) {
  auto thread_state = *((ThreadState**)raw_context);
  //DPRINT("%d (%.X) = load.v128 +%d\n", (int8_t)value, value, offset);
}

void TraceMemoryStoreI8(void* raw_context, uint64_t address, uint8_t value) {
  auto thread_state = *((ThreadState**)raw_context);
  DPRINT("store.i8 %.8X = %d (%X)\n", address, (int8_t)value, value);
}
void TraceMemoryStoreI16(void* raw_context, uint64_t address, uint16_t value) {
  auto thread_state = *((ThreadState**)raw_context);
  DPRINT("store.i16 %.8X = %d (%X)\n", address, (int16_t)value, value);
}
void TraceMemoryStoreI32(void* raw_context, uint64_t address, uint32_t value) {
  auto thread_state = *((ThreadState**)raw_context);
  DPRINT("store.i32 %.8X = %d (%X)\n", address, (int32_t)value, value);
}
void TraceMemoryStoreI64(void* raw_context, uint64_t address, uint64_t value) {
  auto thread_state = *((ThreadState**)raw_context);
  DPRINT("store.i64 %.8X = %lld (%llX)\n", address, (int64_t)value, value);
}
void TraceMemoryStoreF32(void* raw_context, uint64_t address, float value) {
  auto thread_state = *((ThreadState**)raw_context);
  union {
    float f;
    uint32_t u;
  } x;
  x.f = value;
  DPRINT("store.f32 %.8X = %e (%X)\n", address, x.f, x.u);
}
void TraceMemoryStoreF64(void* raw_context, uint64_t address, double value) {
  auto thread_state = *((ThreadState**)raw_context);
  union {
    double f;
    uint64_t u;
  } x;
  x.f = value;
  DPRINT("store.f64 %.8X = %lle (%llX)\n", address, x.f, x.u);
}
void TraceMemoryStoreV128(void* raw_context, uint64_t address, __m128 value) {
  auto thread_state = *((ThreadState**)raw_context);
  /*DPRINT("ctx v128 +%d = [%e, %e, %e, %e] [%.8X, %.8X, %.8X, %.8X]\n", ics.rf[i->src1_reg].u64,
         VECF4(ics.rf[i->src2_reg].v128,0), VECF4(ics.rf[i->src2_reg].v128,1), VECF4(ics.rf[i->src2_reg].v128,2), VECF4(ics.rf[i->src2_reg].v128,3),
         VECI4(ics.rf[i->src2_reg].v128,0), VECI4(ics.rf[i->src2_reg].v128,1), VECI4(ics.rf[i->src2_reg].v128,2), VECF4(ics.rf[i->src2_reg].v128,3));*/
}


}  // namespace lowering
}  // namespace x64
}  // namespace backend
}  // namespace alloy