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

#ifndef WABT_BINARY_READER_NOP_H_
#define WABT_BINARY_READER_NOP_H_

#include "src/binary-reader.h"

namespace wabt {

class BinaryReaderNop : public BinaryReaderDelegate {
 public:
  bool OnError(const Error&) override { return false; }

  /* Module */
  Result BeginModule(uint32_t version) override { return Result::Ok; }
  Result EndModule() override { return Result::Ok; }

  Result BeginSection(Index section_index,
                      BinarySection section_type,
                      Offset size) override {
    return Result::Ok;
  }

  /* Custom section */
  Result BeginCustomSection(Offset size, string_view section_name) override {
    return Result::Ok;
  }
  Result EndCustomSection() override { return Result::Ok; }

  /* Type section */
  Result BeginTypeSection(Offset size) override { return Result::Ok; }
  Result OnTypeCount(Index count) override { return Result::Ok; }
  Result OnType(Index index,
                Index param_count,
                Type* param_types,
                Index result_count,
                Type* result_types) override {
    return Result::Ok;
  }
  Result EndTypeSection() override { return Result::Ok; }

  /* Import section */
  Result BeginImportSection(Offset size) override { return Result::Ok; }
  Result OnImportCount(Index count) override { return Result::Ok; }
  Result OnImport(Index index,
                  string_view module_name,
                  string_view field_name) override {
    return Result::Ok;
  }
  Result OnImportFunc(Index import_index,
                      string_view module_name,
                      string_view field_name,
                      Index func_index,
                      Index sig_index) override {
    return Result::Ok;
  }
  Result OnImportTable(Index import_index,
                       string_view module_name,
                       string_view field_name,
                       Index table_index,
                       Type elem_type,
                       const Limits* elem_limits) override {
    return Result::Ok;
  }
  Result OnImportMemory(Index import_index,
                        string_view module_name,
                        string_view field_name,
                        Index memory_index,
                        const Limits* page_limits) override {
    return Result::Ok;
  }
  Result OnImportGlobal(Index import_index,
                        string_view module_name,
                        string_view field_name,
                        Index global_index,
                        Type type,
                        bool mutable_) override {
    return Result::Ok;
  }
  Result OnImportEvent(Index import_index,
                       string_view module_name,
                       string_view field_name,
                       Index event_index,
                       Index sig_index) override {
    return Result::Ok;
  }
  Result EndImportSection() override { return Result::Ok; }

  /* Function section */
  Result BeginFunctionSection(Offset size) override { return Result::Ok; }
  Result OnFunctionCount(Index count) override { return Result::Ok; }
  Result OnFunction(Index index, Index sig_index) override {
    return Result::Ok;
  }
  Result EndFunctionSection() override { return Result::Ok; }

  /* Table section */
  Result BeginTableSection(Offset size) override { return Result::Ok; }
  Result OnTableCount(Index count) override { return Result::Ok; }
  Result OnTable(Index index,
                 Type elem_type,
                 const Limits* elem_limits) override {
    return Result::Ok;
  }
  Result EndTableSection() override { return Result::Ok; }

  /* Memory section */
  Result BeginMemorySection(Offset size) override { return Result::Ok; }
  Result OnMemoryCount(Index count) override { return Result::Ok; }
  Result OnMemory(Index index, const Limits* limits) override {
    return Result::Ok;
  }
  Result EndMemorySection() override { return Result::Ok; }

  /* Global section */
  Result BeginGlobalSection(Offset size) override { return Result::Ok; }
  Result OnGlobalCount(Index count) override { return Result::Ok; }
  Result BeginGlobal(Index index, Type type, bool mutable_) override {
    return Result::Ok;
  }
  Result BeginGlobalInitExpr(Index index) override { return Result::Ok; }
  Result EndGlobalInitExpr(Index index) override { return Result::Ok; }
  Result EndGlobal(Index index) override { return Result::Ok; }
  Result EndGlobalSection() override { return Result::Ok; }

  /* Exports section */
  Result BeginExportSection(Offset size) override { return Result::Ok; }
  Result OnExportCount(Index count) override { return Result::Ok; }
  Result OnExport(Index index,
                  ExternalKind kind,
                  Index item_index,
                  string_view name) override {
    return Result::Ok;
  }
  Result EndExportSection() override { return Result::Ok; }

  /* Start section */
  Result BeginStartSection(Offset size) override { return Result::Ok; }
  Result OnStartFunction(Index func_index) override { return Result::Ok; }
  Result EndStartSection() override { return Result::Ok; }

  /* Code section */
  Result BeginCodeSection(Offset size) override { return Result::Ok; }
  Result OnFunctionBodyCount(Index count) override { return Result::Ok; }
  Result BeginFunctionBody(Index index, Offset size) override {
    return Result::Ok;
  }
  Result OnLocalDeclCount(Index count) override { return Result::Ok; }
  Result OnLocalDecl(Index decl_index, Index count, Type type) override {
    return Result::Ok;
  }

  /* Function expressions; called between BeginFunctionBody and
   EndFunctionBody */
  Result OnOpcode(Opcode Opcode) override { return Result::Ok; }
  Result OnOpcodeBare() override { return Result::Ok; }
  Result OnOpcodeIndex(Index value) override { return Result::Ok; }
  Result OnOpcodeIndexIndex(Index value, Index value2) override {
    return Result::Ok;
  }
  Result OnOpcodeUint32(uint32_t value) override { return Result::Ok; }
  Result OnOpcodeUint32Uint32(uint32_t value, uint32_t value2) override {
    return Result::Ok;
  }
  Result OnOpcodeUint64(uint64_t value) override { return Result::Ok; }
  Result OnOpcodeF32(uint32_t value) override { return Result::Ok; }
  Result OnOpcodeF64(uint64_t value) override { return Result::Ok; }
  Result OnOpcodeV128(v128 value) override { return Result::Ok; }
  Result OnOpcodeBlockSig(Type sig_type) override { return Result::Ok; }
  Result OnAtomicLoadExpr(Opcode opcode,
                          uint32_t alignment_log2,
                          Address offset) override {
    return Result::Ok;
  }
  Result OnAtomicStoreExpr(Opcode opcode,
                           uint32_t alignment_log2,
                           Address offset) override {
    return Result::Ok;
  }
  Result OnAtomicRmwExpr(Opcode opcode,
                         uint32_t alignment_log2,
                         Address offset) override {
    return Result::Ok;
  }
  Result OnAtomicRmwCmpxchgExpr(Opcode opcode,
                                uint32_t alignment_log2,
                                Address offset) override {
    return Result::Ok;
  }
  Result OnAtomicWaitExpr(Opcode, uint32_t, Address) override {
    return Result::Ok;
  }
  Result OnAtomicNotifyExpr(Opcode, uint32_t, Address) override {
    return Result::Ok;
  }
  Result OnBinaryExpr(Opcode opcode) override { return Result::Ok; }
  Result OnBlockExpr(Type sig_type) override { return Result::Ok; }
  Result OnBrExpr(Index depth) override { return Result::Ok; }
  Result OnBrIfExpr(Index depth) override { return Result::Ok; }
  Result OnBrOnExnExpr(Index depth, Index event_index) override {
    return Result::Ok;
  }
  Result OnBrTableExpr(Index num_targets,
                       Index* target_depths,
                       Index default_target_depth) override {
    return Result::Ok;
  }
  Result OnCallExpr(Index func_index) override { return Result::Ok; }
  Result OnCallIndirectExpr(Index sig_index, Index table_index) override { return Result::Ok; }
  Result OnCatchExpr() override { return Result::Ok; }
  Result OnCompareExpr(Opcode opcode) override { return Result::Ok; }
  Result OnConvertExpr(Opcode opcode) override { return Result::Ok; }
  Result OnDropExpr() override { return Result::Ok; }
  Result OnElseExpr() override { return Result::Ok; }
  Result OnEndExpr() override { return Result::Ok; }
  Result OnEndFunc() override { return Result::Ok; }
  Result OnF32ConstExpr(uint32_t value_bits) override { return Result::Ok; }
  Result OnF64ConstExpr(uint64_t value_bits) override { return Result::Ok; }
  Result OnV128ConstExpr(v128 value_bits) override { return Result::Ok; }
  Result OnGlobalGetExpr(Index global_index) override { return Result::Ok; }
  Result OnGlobalSetExpr(Index global_index) override { return Result::Ok; }
  Result OnI32ConstExpr(uint32_t value) override { return Result::Ok; }
  Result OnI64ConstExpr(uint64_t value) override { return Result::Ok; }
  Result OnIfExpr(Type sig_type) override { return Result::Ok; }
  Result OnLoadExpr(Opcode opcode,
                    uint32_t alignment_log2,
                    Address offset) override {
    return Result::Ok;
  }
  Result OnLocalGetExpr(Index local_index) override { return Result::Ok; }
  Result OnLocalSetExpr(Index local_index) override { return Result::Ok; }
  Result OnLocalTeeExpr(Index local_index) override { return Result::Ok; }
  Result OnLoopExpr(Type sig_type) override { return Result::Ok; }
  Result OnMemoryCopyExpr() override { return Result::Ok; }
  Result OnDataDropExpr(Index segment_index) override { return Result::Ok; }
  Result OnMemoryFillExpr() override { return Result::Ok; }
  Result OnMemoryGrowExpr() override { return Result::Ok; }
  Result OnMemoryInitExpr(Index segment_index) override { return Result::Ok; }
  Result OnMemorySizeExpr() override { return Result::Ok; }
  Result OnTableCopyExpr() override { return Result::Ok; }
  Result OnElemDropExpr(Index segment_index) override { return Result::Ok; }
  Result OnTableInitExpr(Index segment_index) override { return Result::Ok; }
  Result OnTableGetExpr(Index table_index) override { return Result::Ok; }
  Result OnTableSetExpr(Index table_index) override { return Result::Ok; }
  Result OnTableGrowExpr(Index table_index) override { return Result::Ok; }
  Result OnTableSizeExpr(Index table_index) override { return Result::Ok; }
  Result OnRefNullExpr() override { return Result::Ok; }
  Result OnRefIsNullExpr() override { return Result::Ok; }
  Result OnNopExpr() override { return Result::Ok; }
  Result OnRethrowExpr() override { return Result::Ok; }
  Result OnReturnCallExpr(Index sig_index) override { return Result::Ok; }
  Result OnReturnCallIndirectExpr(Index sig_index, Index table_index) override { return Result::Ok; }
  Result OnReturnExpr() override { return Result::Ok; }
  Result OnSelectExpr() override { return Result::Ok; }
  Result OnStoreExpr(Opcode opcode,
                     uint32_t alignment_log2,
                     Address offset) override {
    return Result::Ok;
  }
  Result OnThrowExpr(Index depth) override { return Result::Ok; }
  Result OnTryExpr(Type sig_type) override { return Result::Ok; }
  Result OnUnaryExpr(Opcode opcode) override { return Result::Ok; }
  Result OnTernaryExpr(Opcode opcode) override { return Result::Ok; }
  Result OnUnreachableExpr() override { return Result::Ok; }
  Result EndFunctionBody(Index index) override { return Result::Ok; }
  Result EndCodeSection() override { return Result::Ok; }
  Result OnSimdLaneOpExpr(Opcode opcode, uint64_t value) override {
    return Result::Ok;
  }
  Result OnSimdShuffleOpExpr(Opcode opcode, v128 value) override {
    return Result::Ok;
  }

  /* Elem section */
  Result BeginElemSection(Offset size) override { return Result::Ok; }
  Result OnElemSegmentCount(Index count) override { return Result::Ok; }
  Result BeginElemSegment(Index index,
                          Index table_index,
                          bool passive,
                          Type elem_type) override {
    return Result::Ok;
  }
  Result BeginElemSegmentInitExpr(Index index) override { return Result::Ok; }
  Result EndElemSegmentInitExpr(Index index) override { return Result::Ok; }
  Result OnElemSegmentElemExprCount(Index index, Index count) override {
    return Result::Ok;
  }
  Result OnElemSegmentElemExpr_RefNull(Index segment_index) override {
    return Result::Ok;
  }
  Result OnElemSegmentElemExpr_RefFunc(Index segment_index,
                                       Index func_index) override {
    return Result::Ok;
  }
  Result EndElemSegment(Index index) override { return Result::Ok; }
  Result EndElemSection() override { return Result::Ok; }

  /* Data section */
  Result BeginDataSection(Offset size) override { return Result::Ok; }
  Result OnDataSegmentCount(Index count) override { return Result::Ok; }
  Result BeginDataSegment(Index index, Index memory_index, bool passive) override {
    return Result::Ok;
  }
  Result BeginDataSegmentInitExpr(Index index) override { return Result::Ok; }
  Result EndDataSegmentInitExpr(Index index) override { return Result::Ok; }
  Result OnDataSegmentData(Index index,
                           const void* data,
                           Address size) override {
    return Result::Ok;
  }
  Result EndDataSegment(Index index) override { return Result::Ok; }
  Result EndDataSection() override { return Result::Ok; }

  /* DataCount section */
  Result BeginDataCountSection(Offset size) override { return Result::Ok; }
  Result OnDataCount(Index count) override { return Result::Ok; }
  Result EndDataCountSection() override { return Result::Ok; }

  /* Names section */
  Result BeginNamesSection(Offset size) override { return Result::Ok; }
  Result OnModuleNameSubsection(Index index,
                                uint32_t name_type,
                                Offset subsection_size) override {
    return Result::Ok;
  }
  Result OnModuleName(string_view name) override { return Result::Ok; }
  Result OnFunctionNameSubsection(Index index,
                                  uint32_t name_type,
                                  Offset subsection_size) override {
    return Result::Ok;
  }
  Result OnFunctionNamesCount(Index num_functions) override {
    return Result::Ok;
  }
  Result OnFunctionName(Index function_index,
                        string_view function_name) override {
    return Result::Ok;
  }
  Result OnLocalNameSubsection(Index index,
                               uint32_t name_type,
                               Offset subsection_size) override {
    return Result::Ok;
  }
  Result OnLocalNameFunctionCount(Index num_functions) override {
    return Result::Ok;
  }
  Result OnLocalNameLocalCount(Index function_index,
                               Index num_locals) override {
    return Result::Ok;
  }
  Result OnLocalName(Index function_index,
                     Index local_index,
                     string_view local_name) override {
    return Result::Ok;
  }
  Result EndNamesSection() override { return Result::Ok; }

  /* Reloc section */
  Result BeginRelocSection(Offset size) override { return Result::Ok; }
  Result OnRelocCount(Index count, Index section_code) override {
    return Result::Ok;
  }
  Result OnReloc(RelocType type,
                 Offset offset,
                 Index index,
                 uint32_t addend) override {
    return Result::Ok;
  }
  Result EndRelocSection() override { return Result::Ok; }

  /* Event section */
  Result BeginEventSection(Offset size) override { return Result::Ok; }
  Result OnEventCount(Index count) override { return Result::Ok; }
  Result OnEventType(Index index, Index sig_index) override {
    return Result::Ok;
  }
  Result EndEventSection() override { return Result::Ok; }

  /* Dylink section */
  Result BeginDylinkSection(Offset size) override { return Result::Ok; }
  Result OnDylinkInfo(uint32_t mem_size,
                      uint32_t mem_align,
                      uint32_t table_size,
                      uint32_t table_align) override {
    return Result::Ok;
  }
  Result OnDylinkNeededCount(Index count) override { return Result::Ok; }
  Result OnDylinkNeeded(string_view so_name) override { return Result::Ok; }
  Result EndDylinkSection() override { return Result::Ok; }

  /* Linking section */
  Result BeginLinkingSection(Offset size) override { return Result::Ok; }
  Result OnSymbolCount(Index count) override { return Result::Ok; }
  Result OnSymbol(Index sybmol_index,
                  SymbolType type,
                  uint32_t flags) override {
    return Result::Ok;
  }
  Result OnDataSymbol(Index index,
                      uint32_t flags,
                      string_view name,
                      Index segment,
                      uint32_t offset,
                      uint32_t size) override {
    return Result::Ok;
  }
  Result OnFunctionSymbol(Index index,
                          uint32_t flags,
                          string_view name,
                          Index func_index) override {
    return Result::Ok;
  }
  Result OnGlobalSymbol(Index index,
                        uint32_t flags,
                        string_view name,
                        Index global_index) override {
    return Result::Ok;
  }
  Result OnSectionSymbol(Index index,
                         uint32_t flags,
                         Index section_index) override {
    return Result::Ok;
  }
  Result OnEventSymbol(Index index,
                       uint32_t flags,
                       string_view name,
                       Index event_index) override {
    return Result::Ok;
  }
  Result OnSegmentInfoCount(Index count) override { return Result::Ok; }
  Result OnSegmentInfo(Index index,
                       string_view name,
                       uint32_t alignment,
                       uint32_t flags) override {
    return Result::Ok;
  }
  Result OnInitFunctionCount(Index count) override { return Result::Ok; }
  Result OnInitFunction(uint32_t priority, Index function_index) override {
    return Result::Ok;
  }
  Result OnComdatCount(Index count) override { return Result::Ok; }
  Result OnComdatBegin(string_view name, uint32_t flags, Index count) override {
    return Result::Ok;
  }
  Result OnComdatEntry(ComdatType kind, Index index) override {
    return Result::Ok;
  }
  Result EndLinkingSection() override { return Result::Ok; }

  /* InitExpr - used by elem, data and global sections; these functions are
   * only called between calls to Begin*InitExpr and End*InitExpr */
  Result OnInitExprF32ConstExpr(Index index, uint32_t value) override {
    return Result::Ok;
  }
  Result OnInitExprF64ConstExpr(Index index, uint64_t value) override {
    return Result::Ok;
  }
  Result OnInitExprV128ConstExpr(Index index, v128 value) override {
    return Result::Ok;
  }
  Result OnInitExprGlobalGetExpr(Index index, Index global_index) override {
    return Result::Ok;
  }
  Result OnInitExprI32ConstExpr(Index index, uint32_t value) override {
    return Result::Ok;
  }
  Result OnInitExprI64ConstExpr(Index index, uint64_t value) override {
    return Result::Ok;
  }
};

}  // namespace wabt

#endif /* WABT_BINARY_READER_H_ */
