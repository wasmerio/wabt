/*
 * Copyright 2016 WebAssembly Community Group participants
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef WABT_BINARY_READER_H_
#define WABT_BINARY_READER_H_

#include <stddef.h>
#include <stdint.h>

#include "src/binary.h"
#include "src/common.h"
#include "src/error.h"
#include "src/feature.h"
#include "src/opcode.h"
#include "src/string-view.h"

namespace wabt {

class Stream;

struct ReadBinaryOptions {
  ReadBinaryOptions() = default;
  ReadBinaryOptions(const Features& features,
                    Stream* log_stream,
                    bool read_debug_names,
                    bool stop_on_first_error,
                    bool fail_on_custom_section_error)
      : features(features),
        log_stream(log_stream),
        read_debug_names(read_debug_names),
        stop_on_first_error(stop_on_first_error),
        fail_on_custom_section_error(fail_on_custom_section_error) {}

  Features features;
  Stream* log_stream = nullptr;
  bool read_debug_names = false;
  bool stop_on_first_error = true;
  bool fail_on_custom_section_error = true;
};

class BinaryReaderDelegate {
 public:
  struct State {
    State(const uint8_t* data, Offset size)
        : data(data), size(size), offset(0) {}

    const uint8_t* data;
    Offset size;
    Offset offset;
  };

  virtual ~BinaryReaderDelegate() {}

  virtual bool OnError(const Error&) = 0;
  virtual void OnSetState(const State* s) { state = s; }

  /* Module */
  virtual Result BeginModule(uint32_t version) = 0;
  virtual Result EndModule() = 0;

  virtual Result BeginSection(Index section_index,
                              BinarySection section_type,
                              Offset size) = 0;

  /* Custom section */
  virtual Result BeginCustomSection(Offset size, string_view section_name) = 0;
  virtual Result EndCustomSection() = 0;

  /* Type section */
  virtual Result BeginTypeSection(Offset size) = 0;
  virtual Result OnTypeCount(Index count) = 0;
  virtual Result OnType(Index index,
                        Index param_count,
                        Type* param_types,
                        Index result_count,
                        Type* result_types) = 0;
  virtual Result EndTypeSection() = 0;

  /* Import section */
  virtual Result BeginImportSection(Offset size) = 0;
  virtual Result OnImportCount(Index count) = 0;
  virtual Result OnImport(Index index,
                          string_view module_name,
                          string_view field_name) = 0;
  virtual Result OnImportFunc(Index import_index,
                              string_view module_name,
                              string_view field_name,
                              Index func_index,
                              Index sig_index) = 0;
  virtual Result OnImportTable(Index import_index,
                               string_view module_name,
                               string_view field_name,
                               Index table_index,
                               Type elem_type,
                               const Limits* elem_limits) = 0;
  virtual Result OnImportMemory(Index import_index,
                                string_view module_name,
                                string_view field_name,
                                Index memory_index,
                                const Limits* page_limits) = 0;
  virtual Result OnImportGlobal(Index import_index,
                                string_view module_name,
                                string_view field_name,
                                Index global_index,
                                Type type,
                                bool mutable_) = 0;
  virtual Result OnImportEvent(Index import_index,
                               string_view module_name,
                               string_view field_name,
                               Index event_index,
                               Index sig_index) = 0;
  virtual Result EndImportSection() = 0;

  /* Function section */
  virtual Result BeginFunctionSection(Offset size) = 0;
  virtual Result OnFunctionCount(Index count) = 0;
  virtual Result OnFunction(Index index, Index sig_index) = 0;
  virtual Result EndFunctionSection() = 0;

  /* Table section */
  virtual Result BeginTableSection(Offset size) = 0;
  virtual Result OnTableCount(Index count) = 0;
  virtual Result OnTable(Index index,
                         Type elem_type,
                         const Limits* elem_limits) = 0;
  virtual Result EndTableSection() = 0;

  /* Memory section */
  virtual Result BeginMemorySection(Offset size) = 0;
  virtual Result OnMemoryCount(Index count) = 0;
  virtual Result OnMemory(Index index, const Limits* limits) = 0;
  virtual Result EndMemorySection() = 0;

  /* Global section */
  virtual Result BeginGlobalSection(Offset size) = 0;
  virtual Result OnGlobalCount(Index count) = 0;
  virtual Result BeginGlobal(Index index, Type type, bool mutable_) = 0;
  virtual Result BeginGlobalInitExpr(Index index) = 0;
  virtual Result EndGlobalInitExpr(Index index) = 0;
  virtual Result EndGlobal(Index index) = 0;
  virtual Result EndGlobalSection() = 0;

  /* Exports section */
  virtual Result BeginExportSection(Offset size) = 0;
  virtual Result OnExportCount(Index count) = 0;
  virtual Result OnExport(Index index,
                          ExternalKind kind,
                          Index item_index,
                          string_view name) = 0;
  virtual Result EndExportSection() = 0;

  /* Start section */
  virtual Result BeginStartSection(Offset size) = 0;
  virtual Result OnStartFunction(Index func_index) = 0;
  virtual Result EndStartSection() = 0;

  /* Code section */
  virtual Result BeginCodeSection(Offset size) = 0;
  virtual Result OnFunctionBodyCount(Index count) = 0;
  virtual Result BeginFunctionBody(Index index, Offset size) = 0;
  virtual Result OnLocalDeclCount(Index count) = 0;
  virtual Result OnLocalDecl(Index decl_index, Index count, Type type) = 0;

  /* Function expressions; called between BeginFunctionBody and
   EndFunctionBody */
  virtual Result OnOpcode(Opcode Opcode) = 0;
  virtual Result OnOpcodeBare() = 0;
  virtual Result OnOpcodeUint32(uint32_t value) = 0;
  virtual Result OnOpcodeIndex(Index value) = 0;
  virtual Result OnOpcodeIndexIndex(Index value, Index value2) = 0;
  virtual Result OnOpcodeUint32Uint32(uint32_t value, uint32_t value2) = 0;
  virtual Result OnOpcodeUint64(uint64_t value) = 0;
  virtual Result OnOpcodeF32(uint32_t value) = 0;
  virtual Result OnOpcodeF64(uint64_t value) = 0;
  virtual Result OnOpcodeV128(v128 value) = 0;
  virtual Result OnOpcodeBlockSig(Type sig_type) = 0;
  virtual Result OnAtomicLoadExpr(Opcode opcode,
                                  uint32_t alignment_log2,
                                  Address offset) = 0;
  virtual Result OnAtomicStoreExpr(Opcode opcode,
                                   uint32_t alignment_log2,
                                   Address offset) = 0;
  virtual Result OnAtomicRmwExpr(Opcode opcode,
                                 uint32_t alignment_log2,
                                 Address offset) = 0;
  virtual Result OnAtomicRmwCmpxchgExpr(Opcode opcode,
                                        uint32_t alignment_log2,
                                        Address offset) = 0;
  virtual Result OnAtomicWaitExpr(Opcode opcode,
                                  uint32_t alignment_log2,
                                  Address offset) = 0;
  virtual Result OnAtomicNotifyExpr(Opcode opcode,
                                    uint32_t alignment_log2,
                                    Address offset) = 0;
  virtual Result OnBinaryExpr(Opcode opcode) = 0;
  virtual Result OnBlockExpr(Type sig_type) = 0;
  virtual Result OnBrExpr(Index depth) = 0;
  virtual Result OnBrIfExpr(Index depth) = 0;
  virtual Result OnBrOnExnExpr(Index depth, Index event_index) = 0;
  virtual Result OnBrTableExpr(Index num_targets,
                               Index* target_depths,
                               Index default_target_depth) = 0;
  virtual Result OnCallExpr(Index func_index) = 0;
  virtual Result OnCallIndirectExpr(Index sig_index, Index table_index) = 0;
  virtual Result OnCatchExpr() = 0;
  virtual Result OnCompareExpr(Opcode opcode) = 0;
  virtual Result OnConvertExpr(Opcode opcode) = 0;
  virtual Result OnDropExpr() = 0;
  virtual Result OnElseExpr() = 0;
  virtual Result OnEndExpr() = 0;
  virtual Result OnEndFunc() = 0;
  virtual Result OnF32ConstExpr(uint32_t value_bits) = 0;
  virtual Result OnF64ConstExpr(uint64_t value_bits) = 0;
  virtual Result OnV128ConstExpr(v128 value_bits) = 0;
  virtual Result OnGlobalGetExpr(Index global_index) = 0;
  virtual Result OnGlobalSetExpr(Index global_index) = 0;
  virtual Result OnI32ConstExpr(uint32_t value) = 0;
  virtual Result OnI64ConstExpr(uint64_t value) = 0;
  virtual Result OnIfExpr(Type sig_type) = 0;
  virtual Result OnLoadExpr(Opcode opcode,
                            uint32_t alignment_log2,
                            Address offset) = 0;
  virtual Result OnLocalGetExpr(Index local_index) = 0;
  virtual Result OnLocalSetExpr(Index local_index) = 0;
  virtual Result OnLocalTeeExpr(Index local_index) = 0;
  virtual Result OnLoopExpr(Type sig_type) = 0;
  virtual Result OnMemoryCopyExpr() = 0;
  virtual Result OnDataDropExpr(Index segment_index) = 0;
  virtual Result OnMemoryFillExpr() = 0;
  virtual Result OnMemoryGrowExpr() = 0;
  virtual Result OnMemoryInitExpr(Index segment_index) = 0;
  virtual Result OnMemorySizeExpr() = 0;
  virtual Result OnTableCopyExpr() = 0;
  virtual Result OnElemDropExpr(Index segment_index) = 0;
  virtual Result OnTableInitExpr(Index segment_index) = 0;
  virtual Result OnTableGetExpr(Index table_index) = 0;
  virtual Result OnTableSetExpr(Index table_index) = 0;
  virtual Result OnTableGrowExpr(Index table_index) = 0;
  virtual Result OnTableSizeExpr(Index table_index) = 0;
  virtual Result OnRefNullExpr() = 0;
  virtual Result OnRefIsNullExpr() = 0;
  virtual Result OnNopExpr() = 0;
  virtual Result OnRethrowExpr() = 0;
  virtual Result OnReturnExpr() = 0;
  virtual Result OnReturnCallExpr(Index func_index) = 0;
  virtual Result OnReturnCallIndirectExpr(Index sig_index,
                                          Index table_index) = 0;
  virtual Result OnSelectExpr() = 0;
  virtual Result OnStoreExpr(Opcode opcode,
                             uint32_t alignment_log2,
                             Address offset) = 0;
  virtual Result OnThrowExpr(Index event_index) = 0;
  virtual Result OnTryExpr(Type sig_type) = 0;

  virtual Result OnUnaryExpr(Opcode opcode) = 0;
  virtual Result OnTernaryExpr(Opcode opcode) = 0;
  virtual Result OnUnreachableExpr() = 0;
  virtual Result EndFunctionBody(Index index) = 0;
  virtual Result EndCodeSection() = 0;

  /* Simd instructions with Lane Imm operand*/
  virtual Result OnSimdLaneOpExpr(Opcode opcode, uint64_t value) = 0;
  virtual Result OnSimdShuffleOpExpr(Opcode opcode, v128 value) = 0;

  /* Elem section */
  virtual Result BeginElemSection(Offset size) = 0;
  virtual Result OnElemSegmentCount(Index count) = 0;
  virtual Result BeginElemSegment(Index index,
                                  Index table_index,
                                  bool passive,
                                  Type elem_type) = 0;
  virtual Result BeginElemSegmentInitExpr(Index index) = 0;
  virtual Result EndElemSegmentInitExpr(Index index) = 0;
  virtual Result OnElemSegmentElemExprCount(Index index, Index count) = 0;
  virtual Result OnElemSegmentElemExpr_RefNull(Index segment_index) = 0;
  virtual Result OnElemSegmentElemExpr_RefFunc(Index segment_index,
                                               Index func_index) = 0;
  virtual Result EndElemSegment(Index index) = 0;
  virtual Result EndElemSection() = 0;

  /* Data section */
  virtual Result BeginDataSection(Offset size) = 0;
  virtual Result OnDataSegmentCount(Index count) = 0;
  virtual Result BeginDataSegment(Index index,
                                  Index memory_index,
                                  bool passive) = 0;
  virtual Result BeginDataSegmentInitExpr(Index index) = 0;
  virtual Result EndDataSegmentInitExpr(Index index) = 0;
  virtual Result OnDataSegmentData(Index index,
                                   const void* data,
                                   Address size) = 0;
  virtual Result EndDataSegment(Index index) = 0;
  virtual Result EndDataSection() = 0;

  /* DataCount section */
  virtual Result BeginDataCountSection(Offset size) = 0;
  virtual Result OnDataCount(Index count) = 0;
  virtual Result EndDataCountSection() = 0;

  /* Names section */
  virtual Result BeginNamesSection(Offset size) = 0;
  virtual Result OnModuleNameSubsection(Index index,
                                        uint32_t name_type,
                                        Offset subsection_size) = 0;
  virtual Result OnModuleName(string_view name) = 0;
  virtual Result OnFunctionNameSubsection(Index index,
                                          uint32_t name_type,
                                          Offset subsection_size) = 0;
  virtual Result OnFunctionNamesCount(Index num_functions) = 0;
  virtual Result OnFunctionName(Index function_index,
                                string_view function_name) = 0;
  virtual Result OnLocalNameSubsection(Index index,
                                       uint32_t name_type,
                                       Offset subsection_size) = 0;
  virtual Result OnLocalNameFunctionCount(Index num_functions) = 0;
  virtual Result OnLocalNameLocalCount(Index function_index,
                                       Index num_locals) = 0;
  virtual Result OnLocalName(Index function_index,
                             Index local_index,
                             string_view local_name) = 0;
  virtual Result EndNamesSection() = 0;

  /* Reloc section */
  virtual Result BeginRelocSection(Offset size) = 0;
  virtual Result OnRelocCount(Index count,
                              Index section_index) = 0;
  virtual Result OnReloc(RelocType type,
                         Offset offset,
                         Index index,
                         uint32_t addend) = 0;
  virtual Result EndRelocSection() = 0;

  /* Dylink section */
  virtual Result BeginDylinkSection(Offset size) = 0;
  virtual Result OnDylinkInfo(uint32_t mem_size,
                              uint32_t mem_align_log2,
                              uint32_t table_size,
                              uint32_t table_align_log2) = 0;
  virtual Result OnDylinkNeededCount(Index count) = 0;
  virtual Result OnDylinkNeeded(string_view so_name) = 0;
  virtual Result EndDylinkSection() = 0;

  /* Linking section */
  virtual Result BeginLinkingSection(Offset size) = 0;
  virtual Result OnSymbolCount(Index count) = 0;
  virtual Result OnSymbol(Index index, SymbolType type, uint32_t flags) = 0;
  virtual Result OnDataSymbol(Index index,
                              uint32_t flags,
                              string_view name,
                              Index segment,
                              uint32_t offset,
                              uint32_t size) = 0;
  virtual Result OnFunctionSymbol(Index index,
                                  uint32_t flags,
                                  string_view name,
                                  Index function_index) = 0;
  virtual Result OnGlobalSymbol(Index index,
                                uint32_t flags,
                                string_view name,
                                Index global_index) = 0;
  virtual Result OnSectionSymbol(Index index,
                                 uint32_t flags,
                                 Index section_index) = 0;
  virtual Result OnEventSymbol(Index index,
                               uint32_t flags,
                               string_view name,
                               Index event_index) = 0;
  virtual Result OnSegmentInfoCount(Index count) = 0;
  virtual Result OnSegmentInfo(Index index,
                               string_view name,
                               uint32_t alignment_log2,
                               uint32_t flags) = 0;
  virtual Result OnInitFunctionCount(Index count) = 0;
  virtual Result OnInitFunction(uint32_t priority, Index function_index) = 0;
  virtual Result OnComdatCount(Index count) = 0;
  virtual Result OnComdatBegin(string_view name,
                               uint32_t flags,
                               Index count) = 0;
  virtual Result OnComdatEntry(ComdatType kind, Index index) = 0;
  virtual Result EndLinkingSection() = 0;

  /* Event section */
  virtual Result BeginEventSection(Offset size) = 0;
  virtual Result OnEventCount(Index count) = 0;
  virtual Result OnEventType(Index index, Index sig_index) = 0;
  virtual Result EndEventSection() = 0;

  /* InitExpr - used by elem, data and global sections; these functions are
   * only called between calls to Begin*InitExpr and End*InitExpr */
  virtual Result OnInitExprF32ConstExpr(Index index, uint32_t value) = 0;
  virtual Result OnInitExprF64ConstExpr(Index index, uint64_t value) = 0;
  virtual Result OnInitExprV128ConstExpr(Index index, v128 value) = 0;
  virtual Result OnInitExprGlobalGetExpr(Index index, Index global_index) = 0;
  virtual Result OnInitExprI32ConstExpr(Index index, uint32_t value) = 0;
  virtual Result OnInitExprI64ConstExpr(Index index, uint64_t value) = 0;

  const State* state = nullptr;
};

Result ReadBinary(const void* data,
                  size_t size,
                  BinaryReaderDelegate* reader,
                  const ReadBinaryOptions& options);

size_t ReadU32Leb128(const uint8_t* ptr,
                     const uint8_t* end,
                     uint32_t* out_value);

size_t ReadI32Leb128(const uint8_t* ptr,
                     const uint8_t* end,
                     uint32_t* out_value);

}  // namespace wabt

#endif /* WABT_BINARY_READER_H_ */
